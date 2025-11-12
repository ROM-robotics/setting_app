# Robot WiFi Management Android App

Qt 6.8.3 Android application for managing WiFi connections on a robot computer (Ubuntu 22.04) via Ethernet or Bluetooth.

## Features

- **Dual Connection Modes**: Switch between Ethernet and Bluetooth communication
- **WiFi Status Monitoring**: Real-time WiFi network status from robot computer
- **WiFi Network Management**: Change WiFi networks remotely with SSID and password
- **Virtual Keyboard**: On-screen keyboard for text input
- **Modern UI**: Orange/gradient design matching the requirements
- **Auto-reconnection**: Automatic connection monitoring and status updates

## Project Structure

```
setting_app/
├── main.cpp                    # Application entry point
├── mainwindow.h/cpp           # Main UI window with all controls
├── mainwindow.ui              # Qt Designer UI file
├── networkmanager.h/cpp       # Network communication (Ethernet/Bluetooth)
├── CMakeLists.txt             # CMake build configuration
├── build_android.sh           # Android build script
├── robot_server.py            # Server script for robot computer
└── android/                   # Android-specific files
    ├── AndroidManifest.xml    # Android app manifest
    └── res/                   # Android resources
        ├── drawable/
        │   └── splash.xml     # Splash screen
        └── values/
            └── arrays.xml     # Qt library arrays
```

## Requirements

### Android Device
- Android 6.0 (API 23) or higher
- Bluetooth support
- WiFi connectivity

### Robot Computer (Ubuntu 22.04)
- Network Manager (nmcli)
- Python 3.8+
- Bluetooth support
- Static IP configuration for Ethernet mode

### Development Environment
- Qt 6.8.3 with Android support
- Android SDK (API 33)
- Android NDK (r21+)
- CMake 3.19+

## Installation

### 1. Setup Development Environment

#### Install Qt 6.8.3
```bash
# Download Qt installer from https://www.qt.io/download
# Install Qt 6.8.3 with Android components:
# - Qt 6.8.3 for Android
# - Qt Connectivity (Bluetooth)
# - Qt Network
# - CMake
```

#### Configure Android SDK/NDK
```bash
export ANDROID_SDK_ROOT=/path/to/android/sdk
export ANDROID_NDK_ROOT=/path/to/android/ndk
export JAVA_HOME=/path/to/jdk
```

### 2. Build the Application

#### Using Qt Creator (Recommended)
1. Open `CMakeLists.txt` in Qt Creator
2. Select Android kit (arm64-v8a)
3. Configure project
4. Build and deploy to device

#### Using Command Line
```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build_android.sh
```

### 3. Setup Robot Computer

#### Install Dependencies
```bash
sudo apt update
sudo apt install python3 python3-pip network-manager bluetooth bluez
pip3 install pybluez
```

#### Configure Static IP (Ethernet Mode)
```bash
# Edit network connection
sudo nmcli con modify "Ethernet Connection" ipv4.addresses 192.168.1.100/24
sudo nmcli con modify "Ethernet Connection" ipv4.method manual
sudo nmcli con up "Ethernet Connection"
```

#### Enable Bluetooth
```bash
sudo systemctl enable bluetooth
sudo systemctl start bluetooth
sudo hciconfig hci0 up
sudo hciconfig hci0 piscan
```

#### Run Server
```bash
# Make server executable
chmod +x robot_server.py

# Run server (requires root for Bluetooth)
sudo python3 robot_server.py
```

The server will start:
- HTTP API on port 8080
- Bluetooth RFCOMM service "RobotWiFiService"

## Usage

### Android App

1. **Launch App**: Open "Robot WiFi Manager" on Android device

2. **Connect to Robot**:
   - Default mode: Ethernet (Static IP: 192.168.1.100)
   - Tap "Connect" to establish connection
   - Connection indicator (●) shows status (green=connected, red=disconnected)

3. **Switch Connection Mode**:
   - Tap "Switch to Bluetooth Mode" button
   - App will disconnect and switch modes
   - Bluetooth mode auto-discovers robot device

4. **View WiFi Status**:
   - Tap "Refresh WiFi" to get current WiFi network
   - SSID and connection status displayed

5. **Change WiFi Network**:
   - Enter new SSID in text field (virtual keyboard appears)
   - Enter password (optional for open networks)
   - Tap "Change WiFi Network"
   - Status messages show progress

6. **Virtual Keyboard**:
   - Automatically appears when text field is focused
   - QWERTY layout with numbers and special characters
   - "Back" button: Delete character
   - "Space" button: Add space
   - "Done" button: Hide keyboard

### Configuration

#### Change Robot IP Address
Edit `networkmanager.cpp`:
```cpp
NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_robotIpAddress("192.168.1.100") // Change this IP
    , m_robotPort(8080)
```

#### Change Bluetooth Device Name
Edit `networkmanager.cpp` in `onDeviceDiscovered()`:
```cpp
if (device.name().contains("robot", Qt::CaseInsensitive) || 
    device.name().contains("your_device_name", Qt::CaseInsensitive)) {
```

#### Customize UI Colors
Edit `mainwindow.cpp` in `setupStyle()` to change gradient colors:
```cpp
background: qlineargradient(x1:0, y1:0, x2:1, y2:1, 
    stop:0 #FF6B35,  // Orange
    stop:0.5 #F7931E, // Mid orange
    stop:1 #FFD23F);  // Yellow
```

## API Reference

### HTTP API (Ethernet Mode)

#### Get WiFi Status
```
GET http://192.168.1.100:8080/api/wifi/status

Response:
{
  "action": "wifi_status",
  "ssid": "MyNetwork",
  "status": "connected",
  "success": true
}
```

#### Change WiFi Network
```
POST http://192.168.1.100:8080/api/wifi/connect
Content-Type: application/json

{
  "ssid": "NewNetwork",
  "password": "password123"
}

Response:
{
  "action": "wifi_changed",
  "success": true,
  "message": "Successfully connected to NewNetwork"
}
```

### Bluetooth Protocol

Commands are JSON objects terminated with newline (`\n`):

#### Get WiFi Status
```json
{"action": "get_wifi_status"}
```

#### Change WiFi Network
```json
{
  "action": "change_wifi",
  "data": {
    "ssid": "NewNetwork",
    "password": "password123"
  }
}
```

## Troubleshooting

### App cannot connect via Ethernet
1. Check robot computer IP address: `ip addr show`
2. Verify server is running: `sudo netstat -tlnp | grep 8080`
3. Test connection: `curl http://192.168.1.100:8080/api/wifi/status`
4. Check firewall: `sudo ufw status`

### App cannot connect via Bluetooth
1. Verify Bluetooth is enabled on both devices
2. Check Bluetooth service: `sudo systemctl status bluetooth`
3. Check device visibility: `sudo hciconfig hci0 piscan`
4. Grant Android permissions: Settings → Apps → Robot WiFi Manager → Permissions

### WiFi change not working
1. Check Network Manager service: `systemctl status NetworkManager`
2. Verify WiFi adapter: `nmcli device status`
3. Test manually: `nmcli dev wifi connect "SSID" password "pass"`
4. Check permissions: Server must run with sudo

### Virtual keyboard not appearing
1. Tap directly on input field
2. Check if keyboard is hidden at bottom
3. Scroll down to reveal keyboard

## Development Notes

### Key Classes

- **MainWindow**: Main UI with all controls and event handling
- **NetworkManager**: Handles Ethernet and Bluetooth communication
- **WiFiManager** (Python): Server-side WiFi management

### Signal/Slot Connections

```cpp
// Network status updates
connectionStatusChanged(bool) → onConnectionStatusChanged()
wifiStatusReceived(QString, QString) → onWifiStatusReceived()
wifiNetworkChanged(bool, QString) → onWifiNetworkChanged()
errorOccurred(QString) → onNetworkError()
```

### Android Permissions

Required permissions in AndroidManifest.xml:
- INTERNET: Network access
- ACCESS_NETWORK_STATE: Network status
- BLUETOOTH: Bluetooth communication
- BLUETOOTH_SCAN: Bluetooth device discovery (Android 12+)
- BLUETOOTH_CONNECT: Bluetooth connections (Android 12+)
- ACCESS_FINE_LOCATION: Required for Bluetooth scanning

## License

This project is created for robot control purposes.

## Support

For issues or questions:
1. Check logs in app's text area
2. Check robot server logs: `sudo python3 robot_server.py`
3. Enable Qt logging: `QT_LOGGING_RULES="qt.bluetooth*=true"`

## Future Enhancements

- [ ] WiFi network scanning
- [ ] Signal strength display
- [ ] Connection history
- [ ] Multiple robot profiles
- [ ] Encrypted communication
- [ ] File transfer capability