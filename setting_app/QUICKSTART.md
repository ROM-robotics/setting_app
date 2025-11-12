# Quick Start Guide - Robot WiFi Manager

## Overview
This Android app controls a robot computer's WiFi settings via Ethernet or Bluetooth connection.

## Design
- **Color Scheme**: Orange gradient (matching the UI mockup)
  - Primary: #FF6B35 (Orange)
  - Secondary: #F7931E (Mid Orange) 
  - Accent: #FFD23F (Yellow)
- **Layout**: Clean, modern interface with clear sections
- **Components**: 
  - Connection indicator (animated dot)
  - Mode toggle button
  - WiFi status display
  - Network change form with virtual keyboard
  - Status log area

## Quick Setup Steps

### 1. Robot Computer (Ubuntu 22.04)

```bash
# Install dependencies
sudo apt install python3 python3-pip network-manager bluetooth bluez
pip3 install pybluez

# Configure static IP (for Ethernet mode)
sudo nmcli con modify "Ethernet Connection" ipv4.addresses 192.168.1.100/24
sudo nmcli con modify "Ethernet Connection" ipv4.method manual
sudo nmcli con up "Ethernet Connection"

# Enable Bluetooth
sudo systemctl start bluetooth
sudo hciconfig hci0 up
sudo hciconfig hci0 piscan

# Run server
cd /path/to/setting_app
sudo python3 robot_server.py
```

### 2. Build Android App

**Using Qt Creator (Recommended):**
1. Install Qt 6.8.3 with Android support
2. Open `CMakeLists.txt` in Qt Creator
3. Select Android Kit (arm64-v8a)
4. Build → Deploy

**Manual Build:**
```bash
# Set environment variables
export ANDROID_SDK_ROOT=/path/to/android/sdk
export ANDROID_NDK_ROOT=/path/to/android/ndk

# Build
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
./build_android.sh
```

### 3. Install & Run

```bash
# Install APK on device
adb install build/android/android-build-debug.apk

# Or use Qt Creator's "Run" button
```

## Features in App

### Main Screen Components

1. **Header**
   - Title: "Robot WiFi Manager"
   - Connection indicator (●): Red (disconnected) / Green (connected)

2. **Mode Selection**
   - Toggle button to switch between Ethernet and Bluetooth
   - Current mode label

3. **Connection Controls**
   - Status display
   - Connect/Disconnect button
   - Refresh WiFi button

4. **WiFi Information**
   - Current SSID display
   - Connection status

5. **WiFi Change**
   - SSID input field (triggers virtual keyboard)
   - Password input field
   - Change WiFi button

6. **Status Log**
   - Timestamped messages
   - Color-coded (green=success, red=error)

7. **Virtual Keyboard**
   - QWERTY layout with numbers
   - Special keys: Space, Back, Done
   - Auto-appears when text field is focused

## Usage Flow

```
1. Launch app
   ↓
2. App auto-connects (Ethernet by default)
   ↓
3. View current WiFi status
   ↓
4. (Optional) Switch to Bluetooth mode
   ↓
5. Enter new SSID and password
   ↓
6. Tap "Change WiFi Network"
   ↓
7. Monitor status messages
```

## Connection Modes

### Ethernet Mode
- **Pros**: Fast, stable, reliable
- **Cons**: Requires network cable/same network
- **Default IP**: 192.168.1.100:8080
- **Protocol**: HTTP REST API

### Bluetooth Mode
- **Pros**: Wireless, no network required
- **Cons**: Shorter range, potentially slower
- **Range**: ~10-30 meters
- **Protocol**: RFCOMM (Serial Port Profile)

## API Endpoints

### HTTP (Ethernet)
- `GET /api/wifi/status` - Get WiFi status
- `POST /api/wifi/connect` - Change WiFi network

### Bluetooth (Commands)
- `{"action":"get_wifi_status"}` - Get status
- `{"action":"change_wifi","data":{"ssid":"...","password":"..."}}` - Change network

## File Structure

```
setting_app/
├── main.cpp                 # Entry point
├── mainwindow.h/cpp        # Main UI (2000+ lines)
├── networkmanager.h/cpp    # Communication layer
├── CMakeLists.txt          # Build config
├── android/
│   ├── AndroidManifest.xml # Permissions
│   └── res/                # Android resources
├── robot_server.py         # Python server for robot
├── build_android.sh        # Build script
└── README*.md              # Documentation
```

## Key Classes & Methods

### MainWindow
- `setupUI()` - Creates all UI components
- `setupStyle()` - Applies gradient design
- `setupVirtualKeyboard()` - Creates on-screen keyboard
- `onModeToggleClicked()` - Switch Ethernet/Bluetooth
- `onChangeWifiClicked()` - Send WiFi change request

### NetworkManager
- `setConnectionMode()` - Switch mode
- `connectToRobot()` - Establish connection
- `requestWifiStatus()` - Query current WiFi
- `changeWifiNetwork()` - Change WiFi settings

## Testing Checklist

- [ ] App launches and displays UI correctly
- [ ] Gradient background renders properly
- [ ] Connection indicator animates (blinking red when disconnected)
- [ ] Ethernet mode connects to robot
- [ ] Bluetooth mode discovers and connects to robot
- [ ] WiFi status refreshes correctly
- [ ] Virtual keyboard appears on text field focus
- [ ] WiFi network change works
- [ ] Status messages display properly
- [ ] Mode switching works without crashes

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Cannot connect (Ethernet) | Check robot IP, ensure same network |
| Cannot connect (Bluetooth) | Enable Bluetooth, check permissions |
| Virtual keyboard not showing | Tap directly on input field |
| WiFi not changing | Check NetworkManager on robot |
| Build fails | Verify Qt 6.8.3 with Android support installed |

## Performance Notes

- Connection check interval: 5 seconds
- Bluetooth discovery timeout: 10 seconds (default)
- HTTP request timeout: 30 seconds (default)
- UI refresh rate: 60 FPS (Qt default)

## Security Considerations

⚠️ **Important for Production:**
- Add authentication (API keys, tokens)
- Use HTTPS instead of HTTP
- Encrypt Bluetooth communication
- Validate all user inputs
- Implement rate limiting
- Add proper error handling

## Next Steps

1. Test on physical Android device
2. Test robot server on Ubuntu 22.04
3. Verify both Ethernet and Bluetooth modes
4. Test WiFi changing functionality
5. Fine-tune UI for different screen sizes
6. Add error recovery mechanisms

## Support

- **Documentation**: See README.md (English) or README_MM.md (Myanmar)
- **Qt Documentation**: https://doc.qt.io/qt-6/
- **Issues**: Check status log in app for detailed error messages

---

**Created with Qt 6.8.3 for Android**