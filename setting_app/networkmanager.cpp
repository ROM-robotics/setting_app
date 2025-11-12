#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QBluetoothServiceInfo>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_currentMode(EthernetMode)
    , m_connected(false)
    , m_currentWifiSSID("")
    , m_robotIpAddress("192.168.1.100") // Default static IP
    , m_robotPort(8080)
{
    // Initialize network manager for Ethernet
    m_networkManager = new QNetworkAccessManager(this);
    
    // Initialize Bluetooth components
    m_bluetoothSocket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    
    // Setup connections
    connect(m_bluetoothSocket, &QBluetoothSocket::connected, this, &NetworkManager::onBluetoothConnected);
    connect(m_bluetoothSocket, &QBluetoothSocket::disconnected, this, &NetworkManager::onBluetoothDisconnected);
    connect(m_bluetoothSocket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::errorOccurred),
            this, &NetworkManager::onBluetoothError);
    connect(m_bluetoothSocket, &QBluetoothSocket::readyRead, this, &NetworkManager::onBluetoothDataReady);
    
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &NetworkManager::onDeviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &NetworkManager::onDiscoveryFinished);
    
    // Connection status timer
    m_connectionTimer = new QTimer(this);
    connect(m_connectionTimer, &QTimer::timeout, this, &NetworkManager::checkConnectionStatus);
    m_connectionTimer->start(5000); // Check every 5 seconds
}

NetworkManager::~NetworkManager()
{
    disconnectFromRobot();
}

void NetworkManager::setConnectionMode(ConnectionMode mode)
{
    if (m_currentMode != mode) {
        disconnectFromRobot();
        m_currentMode = mode;
        qDebug() << "Connection mode changed to:" << (mode == EthernetMode ? "Ethernet" : "Bluetooth");
    }
}

void NetworkManager::connectToRobot()
{
    if (m_currentMode == EthernetMode) {
        setupEthernet();
    } else {
        setupBluetooth();
    }
}

void NetworkManager::disconnectFromRobot()
{
    if (m_currentMode == EthernetMode) {
        // Ethernet disconnection is handled automatically
    } else {
        if (m_bluetoothSocket->state() != QBluetoothSocket::SocketState::UnconnectedState) {
            m_bluetoothSocket->disconnectFromService();
        }
    }
    
    m_connected = false;
    emit connectionStatusChanged(m_connected);
}

void NetworkManager::setupEthernet()
{
    // Test connection with a simple ping request
    requestWifiStatus();
}

void NetworkManager::setupBluetooth()
{
    if (m_robotBluetoothAddress.isNull()) {
        // Start device discovery
        qDebug() << "Starting Bluetooth device discovery...";
        m_discoveryAgent->start();
    } else {
        // Connect to known device
        m_bluetoothSocket->connectToService(m_robotBluetoothAddress, QBluetoothUuid(QBluetoothUuid::ServiceClassUuid::SerialPort));
    }
}

void NetworkManager::requestWifiStatus()
{
    if (m_currentMode == EthernetMode) {
        sendEthernetRequest("/api/wifi/status");
    } else {
        QJsonObject command;
        command["action"] = "get_wifi_status";
        sendBluetoothCommand(command);
    }
}

void NetworkManager::scanWifiNetworks()
{
    if (m_currentMode == EthernetMode) {
        sendEthernetRequest("/api/wifi/scan");
    } else {
        QJsonObject command;
        command["action"] = "scan_wifi";
        sendBluetoothCommand(command);
    }
}

void NetworkManager::changeWifiNetwork(const QString &ssid, const QString &password)
{
    QJsonObject data;
    data["ssid"] = ssid;
    data["password"] = password;
    
    if (m_currentMode == EthernetMode) {
        sendEthernetRequest("/api/wifi/connect", data);
    } else {
        QJsonObject command;
        command["action"] = "change_wifi";
        command["data"] = data;
        sendBluetoothCommand(command);
    }
}

void NetworkManager::sendEthernetRequest(const QString &endpoint, const QJsonObject &data)
{
    QUrl url(QString("http://%1:%2%3").arg(m_robotIpAddress).arg(m_robotPort).arg(endpoint));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply;
    if (data.isEmpty()) {
        reply = m_networkManager->get(request);
    } else {
        QJsonDocument doc(data);
        reply = m_networkManager->post(request, doc.toJson());
    }
    
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::onEthernetReplyFinished);
}

void NetworkManager::sendBluetoothCommand(const QJsonObject &command)
{
    if (m_bluetoothSocket->state() == QBluetoothSocket::SocketState::ConnectedState) {
        QJsonDocument doc(command);
        QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";
        m_bluetoothSocket->write(data);
    } else {
        emit errorOccurred("Bluetooth not connected");
    }
}

void NetworkManager::onEthernetReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull()) {
            processReceivedData(doc.object());
        }
        
        if (!m_connected) {
            m_connected = true;
            emit connectionStatusChanged(m_connected);
        }
    } else {
        if (m_connected) {
            m_connected = false;
            emit connectionStatusChanged(m_connected);
        }
        emit errorOccurred("Ethernet error: " + reply->errorString());
    }
    
    reply->deleteLater();
}

void NetworkManager::onBluetoothConnected()
{
    qDebug() << "Bluetooth connected";
    m_connected = true;
    emit connectionStatusChanged(m_connected);
}

void NetworkManager::onBluetoothDisconnected()
{
    qDebug() << "Bluetooth disconnected";
    m_connected = false;
    emit connectionStatusChanged(m_connected);
}

void NetworkManager::onBluetoothError(QBluetoothSocket::SocketError error)
{
    QString errorString;
    switch (error) {
    case QBluetoothSocket::SocketError::UnknownSocketError:
        errorString = "Unknown error";
        break;
    case QBluetoothSocket::SocketError::HostNotFoundError:
        errorString = "Host not found";
        break;
    case QBluetoothSocket::SocketError::ServiceNotFoundError:
        errorString = "Service not found";
        break;
    case QBluetoothSocket::SocketError::NetworkError:
        errorString = "Network error";
        break;
    case QBluetoothSocket::SocketError::UnsupportedProtocolError:
        errorString = "Unsupported protocol";
        break;
    case QBluetoothSocket::SocketError::OperationError:
        errorString = "Operation error";
        break;
    case QBluetoothSocket::SocketError::RemoteHostClosedError:
        errorString = "Remote host closed connection";
        break;
    default:
        return; // No error or unknown
    }
    
    emit errorOccurred("Bluetooth error: " + errorString);
    
    if (m_connected) {
        m_connected = false;
        emit connectionStatusChanged(m_connected);
    }
}

void NetworkManager::onBluetoothDataReady()
{
    QByteArray data = m_bluetoothSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isNull()) {
        processReceivedData(doc.object());
    }
}

void NetworkManager::onDeviceDiscovered(const QBluetoothDeviceInfo &device)
{
    // Look for robot device (you may need to adjust the name/address matching logic)
    if (device.name().contains("robot", Qt::CaseInsensitive) || 
        device.name().contains("ubuntu", Qt::CaseInsensitive)) {
        qDebug() << "Found robot device:" << device.name() << device.address();
        m_robotBluetoothAddress = device.address();
        m_discoveryAgent->stop();
        m_bluetoothSocket->connectToService(m_robotBluetoothAddress, QBluetoothUuid(QBluetoothUuid::ServiceClassUuid::SerialPort));
    }
}

void NetworkManager::onDiscoveryFinished()
{
    if (m_robotBluetoothAddress.isNull()) {
        emit errorOccurred("Robot Bluetooth device not found");
    }
}

void NetworkManager::checkConnectionStatus()
{
    if (m_currentMode == EthernetMode && m_connected) {
        // Periodically check wifi status to keep connection alive
        requestWifiStatus();
    }
}

void NetworkManager::processReceivedData(const QJsonObject &data)
{
    QString action = data["action"].toString();
    
    if (action == "wifi_status") {
        QString ssid = data["ssid"].toString();
        QString status = data["status"].toString();
        QString ipAddress = data["ip_address"].toString();
        m_currentWifiSSID = ssid;
        emit wifiStatusReceived(ssid, status, ipAddress);
    } else if (action == "wifi_scan") {
        QJsonArray networksArray = data["networks"].toArray();
        QStringList networks;
        for (const QJsonValue &value : networksArray) {
            networks.append(value.toString());
        }
        emit wifiNetworksScanned(networks);
    } else if (action == "wifi_changed") {
        bool success = data["success"].toBool();
        QString message = data["message"].toString();
        emit wifiNetworkChanged(success, message);
    }
}