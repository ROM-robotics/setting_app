#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBluetoothSocket>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    enum ConnectionMode {
        EthernetMode,
        BluetoothMode
    };

    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void setConnectionMode(ConnectionMode mode);
    ConnectionMode getConnectionMode() const { return m_currentMode; }
    
    void connectToRobot();
    void disconnectFromRobot();
    void requestWifiStatus();
    void scanWifiNetworks();
    void changeWifiNetwork(const QString &ssid, const QString &password);
    
    bool isConnected() const { return m_connected; }
    QString getCurrentWifiSSID() const { return m_currentWifiSSID; }

signals:
    void connectionStatusChanged(bool connected);
    void wifiStatusReceived(const QString &ssid, const QString &status, const QString &ipAddress);
    void wifiNetworksScanned(const QStringList &networks);
    void wifiNetworkChanged(bool success, const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onEthernetReplyFinished();
    void onBluetoothConnected();
    void onBluetoothDisconnected();
    void onBluetoothError(QBluetoothSocket::SocketError error);
    void onBluetoothDataReady();
    void onDeviceDiscovered(const QBluetoothDeviceInfo &device);
    void onDiscoveryFinished();
    void checkConnectionStatus();

private:
    void setupEthernet();
    void setupBluetooth();
    void sendEthernetRequest(const QString &endpoint, const QJsonObject &data = QJsonObject());
    void sendBluetoothCommand(const QJsonObject &command);
    void processReceivedData(const QJsonObject &data);

    ConnectionMode m_currentMode;
    bool m_connected;
    QString m_currentWifiSSID;
    
    // Ethernet components
    QNetworkAccessManager *m_networkManager;
    QString m_robotIpAddress;
    int m_robotPort;
    
    // Bluetooth components
    QBluetoothSocket *m_bluetoothSocket;
    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent;
    QBluetoothAddress m_robotBluetoothAddress;
    
    // Connection monitoring
    QTimer *m_connectionTimer;
};

#endif // NETWORKMANAGER_H