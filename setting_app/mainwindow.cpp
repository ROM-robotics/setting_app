#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <QEvent>
#include <QDateTime>
#include <QDialog>
#include <QListWidget>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_keyboardVisible(false)
    , m_currentInput(nullptr)
{
    ui->setupUi(this);
    
    // Initialize network manager
    m_networkManager = new NetworkManager(this);
    
    // Setup UI
    setupUI();
    setupStyle();
    setupVirtualKeyboard();
    
    // Connect network manager signals
    connect(m_networkManager, &NetworkManager::connectionStatusChanged,
            this, &MainWindow::onConnectionStatusChanged);
    connect(m_networkManager, &NetworkManager::wifiStatusReceived,
            this, &MainWindow::onWifiStatusReceived);
    connect(m_networkManager, &NetworkManager::wifiNetworkChanged,
            this, &MainWindow::onWifiNetworkChanged);
    connect(m_networkManager, &NetworkManager::errorOccurred,
            this, &MainWindow::onNetworkError);
    
    // Setup connection indicator timer
    m_connectionTimer = new QTimer(this);
    connect(m_connectionTimer, &QTimer::timeout, this, &MainWindow::updateConnectionIndicator);
    m_connectionTimer->start(1000);
    
    // Initialize display
    updateModeDisplay();
    updateWifiDisplay();
    
    // Set window properties - Landscape orientation
    setWindowTitle("Robot WiFi Manager");
    
    // Landscape size: wider than tall
    resize(1200, 700);
    setMinimumSize(1024, 600);
    
    // Auto-connect on startup
    QTimer::singleShot(1000, [this]() {
        m_networkManager->connectToRobot();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Event filter for virtual keyboard support (if needed in future)
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Header Frame
    m_headerFrame = new QFrame();
    m_headerFrame->setObjectName("headerFrame");
    QHBoxLayout *headerLayout = new QHBoxLayout(m_headerFrame);
    
    m_titleLabel = new QLabel("Robot WiFi Manager");
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    
    m_connectionIndicator = new QLabel("●");
    m_connectionIndicator->setObjectName("connectionIndicator");
    m_connectionIndicator->setAlignment(Qt::AlignCenter);
    
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addWidget(m_connectionIndicator);
    
    // Mode Selection Frame
    m_modeFrame = new QFrame();
    m_modeFrame->setObjectName("modeFrame");
    QVBoxLayout *modeLayout = new QVBoxLayout(m_modeFrame);
    
    m_modeToggle = new QPushButton("Switch to Bluetooth Mode");
    m_modeToggle->setObjectName("modeToggle");
    connect(m_modeToggle, &QPushButton::clicked, this, &MainWindow::onModeToggleClicked);
    
    m_modeLabel = new QLabel("Current Mode: Ethernet");
    m_modeLabel->setObjectName("modeLabel");
    m_modeLabel->setAlignment(Qt::AlignCenter);
    
    modeLayout->addWidget(m_modeToggle);
    modeLayout->addWidget(m_modeLabel);
    
    // Connection Status Frame
    m_statusFrame = new QFrame();
    m_statusFrame->setObjectName("statusFrame");
    QHBoxLayout *statusLayout = new QHBoxLayout(m_statusFrame);
    
    m_statusLabel = new QLabel("Status: Connecting...");
    m_statusLabel->setObjectName("statusLabel");
    
    m_refreshButton = new QPushButton("Refresh WiFi");
    m_refreshButton->setObjectName("refreshButton");
    connect(m_refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshWifiClicked);
    
    statusLayout->addWidget(m_statusLabel, 2);
    statusLayout->addWidget(m_refreshButton, 1);
    
    // WiFi Information Frame
    m_wifiFrame = new QFrame();
    m_wifiFrame->setObjectName("wifiFrame");
    QVBoxLayout *wifiLayout = new QVBoxLayout(m_wifiFrame);
    
    QLabel *wifiTitle = new QLabel("Current WiFi Network");
    wifiTitle->setObjectName("sectionTitle");
    
    m_wifiSSIDLabel = new QLabel("SSID: Not Connected");
    m_wifiSSIDLabel->setObjectName("wifiSSID");
    
    m_wifiStatusLabel = new QLabel("Status: Unknown");
    m_wifiStatusLabel->setObjectName("wifiStatus");
    
    m_wifiIPLabel = new QLabel("IP Address: N/A");
    m_wifiIPLabel->setObjectName("wifiIP");
    
    wifiLayout->addWidget(wifiTitle);
    wifiLayout->addWidget(m_wifiSSIDLabel);
    wifiLayout->addWidget(m_wifiStatusLabel);
    wifiLayout->addWidget(m_wifiIPLabel);
    
    // WiFi Change Frame - REMOVED (will use dialog instead)
    
    // Log Text Edit
    m_logTextEdit = new QTextEdit();
    m_logTextEdit->setObjectName("logTextEdit");
    m_logTextEdit->setMaximumHeight(150);
    m_logTextEdit->setPlaceholderText("Status messages will appear here...");
    
    // Create main horizontal layout for landscape
    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    // Left column - Controls
    QVBoxLayout *leftColumn = new QVBoxLayout();
    leftColumn->addWidget(m_modeFrame);
    leftColumn->addWidget(m_statusFrame);
    leftColumn->addStretch();
    
    // Right column - Info & Log
    QVBoxLayout *rightColumn = new QVBoxLayout();
    rightColumn->addWidget(m_wifiFrame);
    rightColumn->addWidget(m_logTextEdit);
    rightColumn->addStretch();
    
    contentLayout->addLayout(leftColumn, 1);
    contentLayout->addLayout(rightColumn, 1);
    
    // Add all to main layout
    m_mainLayout->addWidget(m_headerFrame);
    m_mainLayout->addLayout(contentLayout);
}

void MainWindow::setupStyle()
{
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, 
                stop:0 #FF6B35, stop:0.5 #F7931E, stop:1 #FFD23F);
        }
        
        #headerFrame {
            background: rgba(255, 255, 255, 0.9);
            border-radius: 15px;
            padding: 15px;
            margin: 10px;
        }
        
        #titleLabel {
            font-size: 28px;
            font-weight: bold;
            color: #2C3E50;
            margin: 0px;
        }
        
        #connectionIndicator {
            font-size: 24px;
            color: #E74C3C;
            min-width: 30px;
        }
        
        #modeFrame, #statusFrame, #wifiFrame {
            background: rgba(255, 255, 255, 0.85);
            border-radius: 12px;
            padding: 15px;
            margin: 5px;
        }
        
        #sectionTitle {
            font-size: 20px;
            font-weight: bold;
            color: #2C3E50;
            margin-bottom: 10px;
        }
        
        #modeToggle, #refreshButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                stop:0 #3498DB, stop:1 #2980B9);
            color: white;
            border: none;
            border-radius: 8px;
            padding: 12px 20px;
            font-size: 16px;
            font-weight: bold;
            min-height: 40px;
        }
        
        #modeToggle:pressed, #refreshButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                stop:0 #2980B9, stop:1 #1F4E79);
        }
        
        #modeLabel, #statusLabel, #wifiSSID, #wifiStatus, #wifiIP {
            font-size: 16px;
            color: #2C3E50;
            margin: 5px 0px;
        }
        
        #logTextEdit {
            background: rgba(255, 255, 255, 0.9);
            border: 2px solid #BDC3C7;
            border-radius: 8px;
            padding: 10px;
            font-family: monospace;
            font-size: 12px;
        }
        
        #keyboardFrame {
            background: rgba(44, 62, 80, 0.95);
            border-top: 3px solid #3498DB;
            padding: 10px;
        }
        
        .keyboardKey {
            background: #34495E;
            color: white;
            border: 1px solid #2C3E50;
            border-radius: 6px;
            padding: 10px;
            margin: 2px;
            font-size: 14px;
            font-weight: bold;
            min-height: 35px;
        }
        
        .keyboardKey:pressed {
            background: #3498DB;
        }
    )");
}

void MainWindow::setupVirtualKeyboard()
{
    m_keyboardFrame = new QFrame();
    m_keyboardFrame->setObjectName("keyboardFrame");
    m_keyboardFrame->setVisible(false);
    
    m_keyboardScrollArea = new QScrollArea();
    m_keyboardScrollArea->setWidgetResizable(true);
    m_keyboardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_keyboardScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    QWidget *keyboardWidget = new QWidget();
    m_keyboardLayout = new QGridLayout(keyboardWidget);
    m_keyboardLayout->setSpacing(5);
    
    // Create keyboard layout (QWERTY)
    QStringList row1 = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    QStringList row2 = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
    QStringList row3 = {"A", "S", "D", "F", "G", "H", "J", "K", "L"};
    QStringList row4 = {"Z", "X", "C", "V", "B", "N", "M"};
    
    // Row 1 - Numbers
    for (int i = 0; i < row1.size(); ++i) {
        createKeyboardButton(row1[i], m_keyboardLayout, 0, i);
    }
    
    // Row 2 - QWERTYUIOP
    for (int i = 0; i < row2.size(); ++i) {
        createKeyboardButton(row2[i], m_keyboardLayout, 1, i);
    }
    
    // Row 3 - ASDFGHJKL
    for (int i = 0; i < row3.size(); ++i) {
        createKeyboardButton(row3[i], m_keyboardLayout, 2, i);
    }
    
    // Row 4 - ZXCVBNM
    for (int i = 0; i < row4.size(); ++i) {
        createKeyboardButton(row4[i], m_keyboardLayout, 3, i + 1);
    }
    
    // Special keys
    createKeyboardButton("Space", m_keyboardLayout, 4, 2, 4);
    createKeyboardButton("Back", m_keyboardLayout, 4, 0, 2);
    createKeyboardButton("Done", m_keyboardLayout, 4, 6, 2);
    createKeyboardButton(".", m_keyboardLayout, 3, 8);
    createKeyboardButton("-", m_keyboardLayout, 3, 9);
    
    m_keyboardScrollArea->setWidget(keyboardWidget);
    
    QVBoxLayout *keyboardMainLayout = new QVBoxLayout(m_keyboardFrame);
    keyboardMainLayout->addWidget(m_keyboardScrollArea);
    
    m_mainLayout->addWidget(m_keyboardFrame);
}

void MainWindow::createKeyboardButton(const QString &text, QGridLayout *layout, int row, int col, int colspan)
{
    QPushButton *button = new QPushButton(text);
    button->setProperty("class", "keyboardKey");
    button->setStyleSheet(
        ".keyboardKey { "
        "background: #34495E; "
        "color: white; "
        "border: 1px solid #2C3E50; "
        "border-radius: 6px; "
        "padding: 10px; "
        "margin: 2px; "
        "font-size: 14px; "
        "font-weight: bold; "
        "min-height: 35px; "
        "} "
        ".keyboardKey:pressed { "
        "background: #3498DB; "
        "}"
    );
    
    connect(button, &QPushButton::clicked, [this, text]() {
        onKeyboardKeyPressed(text);
    });
    
    layout->addWidget(button, row, col, 1, colspan);
}

void MainWindow::onModeToggleClicked()
{
    NetworkManager::ConnectionMode currentMode = m_networkManager->getConnectionMode();
    NetworkManager::ConnectionMode newMode = (currentMode == NetworkManager::EthernetMode) 
        ? NetworkManager::BluetoothMode : NetworkManager::EthernetMode;
    
    m_networkManager->setConnectionMode(newMode);
    updateModeDisplay();
    
    showStatusMessage(QString("Switched to %1 mode").arg(
        newMode == NetworkManager::EthernetMode ? "Ethernet" : "Bluetooth"));
}

void MainWindow::onRefreshWifiClicked()
{
    if (m_networkManager->isConnected()) {
        // First scan for networks
        m_networkManager->scanWifiNetworks();
        showStatusMessage("Scanning WiFi networks...");
    } else {
        showStatusMessage("Not connected to robot", true);
    }
}

void MainWindow::onConnectionStatusChanged(bool connected)
{
    m_statusLabel->setText(QString("Status: %1").arg(connected ? "Connected" : "Disconnected"));
    
    if (connected) {
        showStatusMessage("Connected to robot successfully");
        // Automatically request WiFi status when connected
        QTimer::singleShot(500, [this]() {
            m_networkManager->requestWifiStatus();
        });
    } else {
        showStatusMessage("Disconnected from robot");
        updateWifiDisplay(); // Clear WiFi info
    }
}

void MainWindow::onWifiStatusReceived(const QString &ssid, const QString &status, const QString &ipAddress)
{
    m_wifiSSIDLabel->setText(QString("SSID: %1").arg(ssid.isEmpty() ? "Not Connected" : ssid));
    m_wifiStatusLabel->setText(QString("Status: %1").arg(status));
    m_wifiIPLabel->setText(QString("IP Address: %1").arg(ipAddress.isEmpty() ? "N/A" : ipAddress));
    
    showStatusMessage(QString("WiFi Status - SSID: %1, Status: %2, IP: %3").arg(ssid, status, ipAddress));
}

void MainWindow::onWifiNetworksScanned(const QStringList &networks)
{
    if (networks.isEmpty()) {
        showStatusMessage("No WiFi networks found", true);
        return;
    }
    
    // Show dialog with WiFi list
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Available WiFi Networks");
    dialog->setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    
    QLabel *label = new QLabel("Select a WiFi network:");
    layout->addWidget(label);
    
    QListWidget *listWidget = new QListWidget();
    listWidget->addItems(networks);
    layout->addWidget(listWidget);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *connectBtn = new QPushButton("Connect");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    buttonLayout->addWidget(connectBtn);
    buttonLayout->addWidget(cancelBtn);
    layout->addLayout(buttonLayout);
    
    connect(cancelBtn, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(connectBtn, &QPushButton::clicked, [=]() {
        if (listWidget->currentItem()) {
            QString selectedSSID = listWidget->currentItem()->text();
            dialog->accept();
            
            // Ask for password
            bool ok;
            QString password = QInputDialog::getText(this, "WiFi Password",
                                                    QString("Enter password for '%1':").arg(selectedSSID),
                                                    QLineEdit::Password, "", &ok);
            if (ok) {
                m_networkManager->changeWifiNetwork(selectedSSID, password);
                showStatusMessage(QString("Connecting to %1...").arg(selectedSSID));
            }
        }
    });
    
    dialog->exec();
    delete dialog;
}

void MainWindow::onWifiNetworkChanged(bool success, const QString &message)
{
    if (success) {
        showStatusMessage(QString("WiFi changed successfully: %1").arg(message));
        // Refresh WiFi status after change
        QTimer::singleShot(2000, [this]() {
            m_networkManager->requestWifiStatus();
        });
    } else {
        showStatusMessage(QString("WiFi change failed: %1").arg(message), true);
    }
}

void MainWindow::onNetworkError(const QString &error)
{
    showStatusMessage(QString("Error: %1").arg(error), true);
}

void MainWindow::showVirtualKeyboard()
{
    if (m_currentInput) {
        m_keyboardVisible = true;
        m_keyboardFrame->setVisible(true);
        
        // Scroll to show keyboard
        QTimer::singleShot(100, [this]() {
            m_keyboardScrollArea->ensureVisible(0, m_keyboardScrollArea->widget()->height());
        });
    }
}

void MainWindow::hideVirtualKeyboard()
{
    m_keyboardVisible = false;
    m_keyboardFrame->setVisible(false);
    m_currentInput = nullptr;
}

void MainWindow::onKeyboardKeyPressed(const QString &key)
{
    if (!m_currentInput) return;
    
    if (key == "Done") {
        hideVirtualKeyboard();
        m_currentInput->clearFocus();
    } else if (key == "Back") {
        QString text = m_currentInput->text();
        if (!text.isEmpty()) {
            text.chop(1);
            m_currentInput->setText(text);
        }
    } else if (key == "Space") {
        m_currentInput->setText(m_currentInput->text() + " ");
    } else {
        m_currentInput->setText(m_currentInput->text() + key);
    }
}

void MainWindow::updateConnectionIndicator()
{
    static bool blink = false;
    blink = !blink;
    
    if (m_networkManager->isConnected()) {
        m_connectionIndicator->setText("●");
        m_connectionIndicator->setStyleSheet("color: #27AE60; font-size: 24px;");
    } else {
        m_connectionIndicator->setText(blink ? "●" : "○");
        m_connectionIndicator->setStyleSheet("color: #E74C3C; font-size: 24px;");
    }
}

void MainWindow::updateModeDisplay()
{
    NetworkManager::ConnectionMode mode = m_networkManager->getConnectionMode();
    QString modeText = (mode == NetworkManager::EthernetMode) ? "Ethernet" : "Bluetooth";
    QString buttonText = (mode == NetworkManager::EthernetMode) ? 
        "Switch to Bluetooth Mode" : "Switch to Ethernet Mode";
    
    m_modeLabel->setText(QString("Current Mode: %1").arg(modeText));
    m_modeToggle->setText(buttonText);
}

void MainWindow::updateWifiDisplay()
{
    if (!m_networkManager->isConnected()) {
        m_wifiSSIDLabel->setText("SSID: Not Connected");
        m_wifiStatusLabel->setText("Status: Unknown");
        m_wifiIPLabel->setText("IP Address: N/A");
    }
}

void MainWindow::showStatusMessage(const QString &message, bool isError)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString coloredMessage = QString("<span style='color: %1;'>[%2] %3</span>")
        .arg(isError ? "#E74C3C" : "#27AE60")
        .arg(timestamp)
        .arg(message);
    
    m_logTextEdit->append(coloredMessage);
    
    // Auto-scroll to bottom
    QTextCursor cursor = m_logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    m_logTextEdit->setTextCursor(cursor);
}
