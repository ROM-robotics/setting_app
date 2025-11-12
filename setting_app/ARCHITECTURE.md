# System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                         ANDROID DEVICE                               │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │                    Qt Application (C++)                        │  │
│  │                                                                 │  │
│  │  ┌──────────────────────────────────────────────────────────┐ │  │
│  │  │                     MainWindow                            │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  Header (Title + Connection Indicator)          │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  Mode Selection (Ethernet ⇄ Bluetooth)          │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  Status Panel (Connected/Disconnected)           │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  WiFi Info Display (SSID, Status)               │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  WiFi Change Form (SSID, Password inputs)        │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  Virtual Keyboard (QWERTY)                       │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  │  ┌──────────────────────────────────────────────────┐   │ │  │
│  │  │  │  Status Log (Timestamped messages)               │   │ │  │
│  │  │  └──────────────────────────────────────────────────┘   │ │  │
│  │  └──────────────────────────────────────────────────────────┘ │  │
│  │                                                                 │  │
│  │  ┌──────────────────────────────────────────────────────────┐ │  │
│  │  │                   NetworkManager                          │ │  │
│  │  │                                                            │ │  │
│  │  │  ┌─────────────────┐      ┌─────────────────────────┐   │ │  │
│  │  │  │ Ethernet Mode   │      │  Bluetooth Mode         │   │ │  │
│  │  │  │                 │      │                         │   │ │  │
│  │  │  │ • QNetworkAM    │      │ • QBluetoothSocket     │   │ │  │
│  │  │  │ • HTTP REST     │      │ • RFCOMM Protocol      │   │ │  │
│  │  │  │ • Static IP     │      │ • Device Discovery     │   │ │  │
│  │  │  └─────────────────┘      └─────────────────────────┘   │ │  │
│  │  └──────────────────────────────────────────────────────────┘ │  │
│  └───────────────────────────────────────────────────────────────┘  │
│                                                                       │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │                  Android System Services                       │  │
│  │  • Network Stack  • Bluetooth Stack  • Permissions            │  │
│  └───────────────────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────────────────────┘
                                │                  │
                      ┌─────────┴────────┐        │
                      │                  │        │
              Ethernet Cable       WiFi Network   Bluetooth
                      │                  │        │
                      └─────────┬────────┘        │
                                │                  │
┌───────────────────────────────┴──────────────────┴───────────────────┐
│                      ROBOT COMPUTER (Ubuntu 22.04)                    │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │                   Python Server (robot_server.py)              │  │
│  │                                                                 │  │
│  │  ┌──────────────────────────────────────────────────────────┐ │  │
│  │  │                  HTTP Server (Port 8080)                  │ │  │
│  │  │  • GET /api/wifi/status                                   │ │  │
│  │  │  • POST /api/wifi/connect                                 │ │  │
│  │  └──────────────────────────────────────────────────────────┘ │  │
│  │                                                                 │  │
│  │  ┌──────────────────────────────────────────────────────────┐ │  │
│  │  │                Bluetooth Server (RFCOMM)                  │ │  │
│  │  │  • Service: RobotWiFiService                              │ │  │
│  │  │  • Commands: get_wifi_status, change_wifi                 │ │  │
│  │  └──────────────────────────────────────────────────────────┘ │  │
│  │                                                                 │  │
│  │  ┌──────────────────────────────────────────────────────────┐ │  │
│  │  │                    WiFi Manager                            │ │  │
│  │  │  • Uses NetworkManager (nmcli)                             │ │  │
│  │  │  • Get current WiFi status                                 │ │  │
│  │  │  • Change WiFi network                                     │ │  │
│  │  └──────────────────────────────────────────────────────────┘ │  │
│  └───────────────────────────────────────────────────────────────┘  │
│                                                                       │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │                      System Services                           │  │
│  │  • NetworkManager  • Bluetooth Daemon  • Network Hardware     │  │
│  └───────────────────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────────────────────┘
                                │
                                │ WiFi Control
                                ▼
                    ┌───────────────────────┐
                    │   WiFi Access Point   │
                    │    (Target Network)    │
                    └───────────────────────┘
```

## Data Flow Diagrams

### 1. Connection Establishment (Ethernet Mode)

```
┌─────────┐                                        ┌──────────────┐
│ Android │                                        │ Robot Server │
│   App   │                                        │  (Python)    │
└────┬────┘                                        └──────┬───────┘
     │                                                     │
     │ 1. User taps "Connect"                            │
     ├────────────────────────────────────────────────►  │
     │                                                     │
     │ 2. HTTP GET /api/wifi/status                      │
     ├────────────────────────────────────────────────►  │
     │                                                     │
     │                                                     │ 3. Execute:
     │                                                     │    nmcli -t -f 
     │                                                     │    ACTIVE,SSID
     │                                                     │    dev wifi
     │                                                     │
     │ 4. JSON Response:                                  │
     │    {                                                │
     │      "action": "wifi_status",                      │
     │      "ssid": "MyNetwork",                          │
     │      "status": "connected"                         │
     │    }                                                │
     │ ◄────────────────────────────────────────────────┤
     │                                                     │
     │ 5. Update UI:                                      │
     │    - Connection indicator → Green                  │
     │    - Display SSID                                  │
     │                                                     │
```

### 2. Connection Establishment (Bluetooth Mode)

```
┌─────────┐                                        ┌──────────────┐
│ Android │                                        │ Robot Server │
│   App   │                                        │  (Python)    │
└────┬────┘                                        └──────┬───────┘
     │                                                     │
     │ 1. User taps "Switch to Bluetooth Mode"           │
     │                                                     │
     │ 2. Start device discovery                          │
     ├─────────────────────►                              │
     │                                                     │
     │ 3. Bluetooth scan...                               │
     │                                                     │
     │ 4. Found device: "robot" or "ubuntu"              │
     │ ◄────────────────────────────────────────────────┤
     │                                                     │
     │ 5. Connect to RFCOMM service                       │
     ├────────────────────────────────────────────────►  │
     │                                                     │
     │                                                     │ 6. Accept
     │                                                     │    connection
     │ 7. Connected                                       │
     │ ◄────────────────────────────────────────────────┤
     │                                                     │
```

### 3. WiFi Network Change

```
┌─────────┐                                        ┌──────────────┐
│ Android │                                        │ Robot Server │
│   App   │                                        │  (Python)    │
└────┬────┘                                        └──────┬───────┘
     │                                                     │
     │ 1. User enters SSID: "NewWiFi"                    │
     │ 2. User enters Password: "pass123"                │
     │ 3. User taps "Change WiFi Network"                │
     │                                                     │
     │ 4. POST /api/wifi/connect                         │
     │    Body: {                                         │
     │      "ssid": "NewWiFi",                            │
     │      "password": "pass123"                         │
     │    }                                                │
     ├────────────────────────────────────────────────►  │
     │                                                     │
     │                                                     │ 5. Execute:
     │                                                     │    nmcli dev
     │                                                     │    wifi connect
     │                                                     │    "NewWiFi"
     │                                                     │    password
     │                                                     │    "pass123"
     │                                                     │
     │                                                     │ 6. Wait for
     │                                                     │    connection
     │                                                     │
     │ 7. JSON Response:                                  │
     │    {                                                │
     │      "action": "wifi_changed",                     │
     │      "success": true,                              │
     │      "message": "Successfully connected"           │
     │    }                                                │
     │ ◄────────────────────────────────────────────────┤
     │                                                     │
     │ 8. Show success message                            │
     │ 9. Auto-refresh WiFi status                        │
     ├────────────────────────────────────────────────►  │
     │                                                     │
```

## Class Diagram

```
┌─────────────────────────────────┐
│          QMainWindow            │
└────────────┬────────────────────┘
             │
             │ inherits
             │
┌────────────▼────────────────────┐
│         MainWindow              │
├─────────────────────────────────┤
│ - ui: Ui::MainWindow*           │
│ - m_networkManager: NetworkMgr* │
│ - m_modeToggle: QPushButton*    │
│ - m_wifiSSIDLabel: QLabel*      │
│ - m_newSSIDEdit: QLineEdit*     │
│ - m_keyboardFrame: QFrame*      │
│ - ...                            │
├─────────────────────────────────┤
│ + MainWindow(parent)            │
│ + ~MainWindow()                 │
│ - setupUI()                     │
│ - setupStyle()                  │
│ - setupVirtualKeyboard()        │
│ - onModeToggleClicked()         │
│ - onConnectClicked()            │
│ - onChangeWifiClicked()         │
│ - showVirtualKeyboard()         │
│ - ...                            │
└────────────┬────────────────────┘
             │
             │ uses
             │
┌────────────▼────────────────────┐
│      NetworkManager             │
├─────────────────────────────────┤
│ - m_currentMode: Mode           │
│ - m_connected: bool             │
│ - m_networkManager: QNAM*       │
│ - m_bluetoothSocket: QBTSock*   │
│ - m_robotIpAddress: QString     │
│ - m_connectionTimer: QTimer*    │
│ - ...                            │
├─────────────────────────────────┤
│ + setConnectionMode(mode)       │
│ + connectToRobot()              │
│ + requestWifiStatus()           │
│ + changeWifiNetwork(ssid,pass)  │
│ + isConnected(): bool           │
│ - sendEthernetRequest()         │
│ - sendBluetoothCommand()        │
│ - processReceivedData()         │
│ - ...                            │
├─────────────────────────────────┤
│ signals:                         │
│ + connectionStatusChanged(bool) │
│ + wifiStatusReceived(...)       │
│ + wifiNetworkChanged(...)       │
│ + errorOccurred(QString)        │
└─────────────────────────────────┘
```

## Component Interaction

```
┌──────────────────────────────────────────────────────────────┐
│                        User Actions                           │
└───────┬──────────────────────────────────────────────────┬───┘
        │                                                   │
   ┌────▼────┐                                        ┌────▼────┐
   │ Button  │                                        │  Text   │
   │ Clicks  │                                        │  Input  │
   └────┬────┘                                        └────┬────┘
        │                                                   │
        │ emit clicked()                       focus()      │
        │                                                   │
   ┌────▼─────────────────────────────────────────────────▼───┐
   │                     MainWindow                           │
   │  • Handle button clicks                                  │
   │  • Manage UI state                                       │
   │  • Display results                                       │
   │  • Show/hide keyboard                                    │
   └────┬─────────────────────────────────────────────────────┘
        │
        │ calls methods
        │
   ┌────▼─────────────────────────────────────────────────────┐
   │                   NetworkManager                          │
   │  • Manage connection                                      │
   │  • Send/receive data                                      │
   │  • Handle errors                                          │
   └────┬─────────────────────────────────────────────────────┘
        │
        │ emits signals
        │
   ┌────▼─────────────────────────────────────────────────────┐
   │                      Qt Network                           │
   │  • QNetworkAccessManager (HTTP)                           │
   │  • QBluetoothSocket (Bluetooth)                           │
   └────┬─────────────────────────────────────────────────────┘
        │
        │ network I/O
        │
   ┌────▼─────────────────────────────────────────────────────┐
   │                   Robot Server                            │
   │  • Process requests                                       │
   │  • Execute nmcli                                          │
   │  • Return results                                         │
   └───────────────────────────────────────────────────────────┘
```

## File Dependencies

```
main.cpp
  └─► mainwindow.h
       ├─► mainwindow.ui (Qt Designer)
       ├─► networkmanager.h
       │    ├─► QNetworkAccessManager
       │    ├─► QBluetoothSocket
       │    └─► QJsonDocument
       ├─► QLabel, QPushButton, QLineEdit
       ├─► QVBoxLayout, QHBoxLayout
       └─► QTimer, QPropertyAnimation

CMakeLists.txt
  ├─► Qt6::Core
  ├─► Qt6::Widgets
  ├─► Qt6::Network
  └─► Qt6::Bluetooth

AndroidManifest.xml
  ├─► Permissions
  ├─► Activity configuration
  └─► Qt metadata

robot_server.py
  ├─► http.server (HTTP API)
  ├─► bluetooth (Bluetooth)
  └─► subprocess (nmcli)
```

---

This architecture provides:
- **Separation of concerns**: UI (MainWindow) vs Logic (NetworkManager)
- **Flexibility**: Easy to switch between Ethernet and Bluetooth
- **Extensibility**: Easy to add new features
- **Maintainability**: Clear structure and responsibilities