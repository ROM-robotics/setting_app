# Qt Creator Setup Guide for Android Development

## Prerequisites Installation

### 1. Install Qt 6.8.3

1. Download Qt Online Installer from https://www.qt.io/download-qt-installer
2. Run the installer
3. Select components:
   - ✅ Qt 6.8.3
   - ✅ Qt 6.8.3 for Android (arm64-v8a, armv7, x86_64)
   - ✅ Qt Network
   - ✅ Qt Bluetooth
   - ✅ CMake
   - ✅ Ninja
   - ✅ Qt Creator

### 2. Install Android Studio (for SDK/NDK)

**Option A: Full Android Studio**
1. Download from https://developer.android.com/studio
2. Install Android Studio
3. Open SDK Manager (Tools → SDK Manager)
4. Install:
   - Android SDK Platform 33 (API 33)
   - Android SDK Build-Tools 33.0.0+
   - Android NDK (Side by side) - version 21.3+
   - Android SDK Command-line Tools
   - Android SDK Platform-Tools

**Option B: Command Line Tools Only**
```bash
# Download from https://developer.android.com/studio#command-tools
cd ~/Android
unzip commandlinetools-linux-*.zip
cd cmdline-tools/bin

# Install required packages
./sdkmanager --sdk_root=$HOME/Android/Sdk "platform-tools" "platforms;android-33" "build-tools;33.0.0" "ndk;21.3.6528147"
```

### 3. Install Java JDK

```bash
# Ubuntu/Debian
sudo apt install openjdk-11-jdk

# Verify installation
java -version
javac -version
```

### 4. Set Environment Variables

Add to `~/.bashrc` or `~/.zshrc`:

```bash
# Android SDK
export ANDROID_SDK_ROOT=$HOME/Android/Sdk
export ANDROID_HOME=$ANDROID_SDK_ROOT

# Android NDK
export ANDROID_NDK_ROOT=$ANDROID_SDK_ROOT/ndk/21.3.6528147
export ANDROID_NDK=$ANDROID_NDK_ROOT

# Java
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64

# Add to PATH
export PATH=$PATH:$ANDROID_SDK_ROOT/platform-tools
export PATH=$PATH:$ANDROID_SDK_ROOT/cmdline-tools/latest/bin
```

Then reload:
```bash
source ~/.bashrc
```

## Qt Creator Configuration

### 1. Open Qt Creator

```bash
# Launch Qt Creator
qtcreator
```

### 2. Configure Android Settings

1. Go to **Edit → Preferences** (or **Qt Creator → Preferences** on macOS)
2. Navigate to **Devices → Android**
3. Set paths:
   - **JDK location**: `/usr/lib/jvm/java-11-openjdk-amd64` (or your Java path)
   - **Android SDK location**: `$HOME/Android/Sdk`
   - **Android NDK location**: `$HOME/Android/Sdk/ndk/21.3.6528147`
4. Click **Apply**
5. Wait for automatic detection and setup
6. Verify all items show green checkmarks

### 3. Configure Android Kits

1. Go to **Kits** section in Preferences
2. You should see auto-detected Android kits:
   - Android Qt 6.8.3 (arm64-v8a)
   - Android Qt 6.8.3 (armv7)
   - Android Qt 6.8.3 (x86_64)
3. Select the kit you want to use (typically arm64-v8a for modern devices)
4. Verify kit configuration:
   - Qt version: Qt 6.8.3
   - Compiler: Android Clang
   - Device type: Android
5. Click **OK**

## Open and Configure Project

### 1. Open Project in Qt Creator

1. **File → Open File or Project**
2. Navigate to: `/home/mr_robot/Desktop/Git/setting_app/setting_app/`
3. Select `CMakeLists.txt`
4. Click **Open**

### 2. Configure Project

1. **Configure Project** dialog appears
2. Select kit(s):
   - ✅ Android Qt 6.8.3 Clang arm64-v8a (recommended)
   - ⬜ Desktop Qt 6.8.3 (for testing UI on desktop)
3. Click **Configure Project**

### 3. Build Settings

1. Select **Projects** mode (left sidebar)
2. Under **Build & Run → Android Qt 6.8.3 arm64-v8a → Build**:
   - Build directory: `build/android-arm64-v8a`
   - Build type: **Release** (for final APK) or **Debug** (for development)

### 4. Run Settings

1. Under **Build & Run → Android Qt 6.8.3 arm64-v8a → Run**:
   - Deployment method: **Copy APK to device**
   - Deploy action: **Install the app on the device**

## Connect Android Device

### 1. Enable Developer Options on Android

1. Go to **Settings → About Phone**
2. Tap **Build Number** 7 times
3. Developer options enabled

### 2. Enable USB Debugging

1. Go to **Settings → Developer Options**
2. Enable **USB Debugging**
3. Connect device via USB cable
4. Accept USB debugging prompt on device

### 3. Verify Connection

```bash
# Check connected devices
adb devices

# Should show something like:
# List of devices attached
# ABC123XYZ    device
```

In Qt Creator:
1. Click on device dropdown (top toolbar)
2. Your device should appear in the list

## Build and Deploy

### 1. Build the Project

**Option A: Qt Creator**
1. Select **Build → Build Project "setting_app"**
2. Or press **Ctrl+B** (Cmd+B on macOS)
3. Wait for build to complete (check Build Output panel)

**Option B: Command Line**
```bash
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
mkdir -p build/android-arm64-v8a
cd build/android-arm64-v8a

# Configure
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_PLATFORM=android-23 \
      -DCMAKE_PREFIX_PATH=~/Qt/6.8.3/android_arm64_v8a \
      -DCMAKE_BUILD_TYPE=Release \
      ../..

# Build
cmake --build . --parallel $(nproc)
```

### 2. Deploy and Run

1. Ensure device is connected
2. Click **Run** button (green play icon) or press **Ctrl+R**
3. Qt Creator will:
   - Build the APK
   - Sign the APK
   - Install on device
   - Launch the app

### 3. Monitor Logs

1. **Application Output** panel shows app stdout/stderr
2. Or use command line:
```bash
adb logcat | grep -i "robot\|wifi\|setting"
```

## Troubleshooting Qt Creator

### Build Fails with "No Android NDK found"

**Solution:**
1. Go to Preferences → Devices → Android
2. Click **Android NDK list** dropdown
3. Select or add NDK path manually
4. Restart Qt Creator

### "Android SDK Platform-tools not found"

**Solution:**
```bash
cd $ANDROID_SDK_ROOT
./cmdline-tools/latest/bin/sdkmanager "platform-tools"
```

### "Could not find gradle"

Qt Creator includes gradle, but if needed:
**Solution:**
```bash
cd $ANDROID_SDK_ROOT
./cmdline-tools/latest/bin/sdkmanager "gradle"
```

### Device Not Detected

**Solution:**
1. Check USB cable (use data cable, not charge-only)
2. Re-enable USB debugging on device
3. Try different USB port
4. On Linux, check udev rules:
```bash
# Add user to plugdev group
sudo usermod -aG plugdev $USER

# Restart udev
sudo systemctl restart udev

# Replug device
```

### "INSTALL_FAILED_UPDATE_INCOMPATIBLE"

**Solution:**
```bash
# Uninstall existing app
adb uninstall com.robot.settingapp

# Or on device: Settings → Apps → Robot WiFi Manager → Uninstall
```

### APK Won't Install on Device

**Solution:**
1. Check minimum Android version (app requires API 23+)
2. Check device architecture matches build (use arm64-v8a for modern devices)
3. Enable **Install unknown apps** in device settings

## Testing the Application

### 1. Desktop Testing (UI Only)

Build with Desktop kit first to test UI:
1. Select **Desktop Qt 6.8.3** kit
2. Build and run
3. Test UI layout, buttons, keyboard
4. Note: Network features won't work on desktop without robot server on same machine

### 2. Android Testing

1. **Launch app** on device
2. **Check UI rendering** - orange gradient background visible?
3. **Test mode toggle** - switch between Ethernet/Bluetooth
4. **Test virtual keyboard** - tap text fields, keyboard appears?
5. **Test connection** - requires robot server running

### 3. Integration Testing with Robot

Requires robot server running on Ubuntu 22.04:

**On Robot Computer:**
```bash
# Ensure on same network (for Ethernet mode)
# Or Bluetooth enabled (for Bluetooth mode)
cd /home/mr_robot/Desktop/Git/setting_app/setting_app
sudo python3 robot_server.py
```

**On Android App:**
1. Open app
2. (Ethernet mode) Verify robot IP matches (default: 192.168.1.100)
3. Tap **Connect**
4. Should show "Connected" with green dot
5. Tap **Refresh WiFi** - should display robot's current WiFi
6. Try changing WiFi network

## Debug APK Location

After successful build:
```
build/android-arm64-v8a/android-build/build/outputs/apk/debug/
└── android-build-debug.apk

build/android-arm64-v8a/android-build/build/outputs/apk/release/
└── android-build-release.apk
```

## Manual APK Installation

```bash
# Install debug APK
adb install -r build/android-arm64-v8a/android-build/build/outputs/apk/debug/android-build-debug.apk

# Install release APK
adb install -r build/android-arm64-v8a/android-build/build/outputs/apk/release/android-build-release.apk
```

## Performance Tips

1. **Use Release build** for final testing (faster, smaller APK)
2. **Enable multidex** if APK size exceeds 64K methods
3. **Use arm64-v8a** for modern devices (better performance than armv7)
4. **Test on actual device** rather than emulator for Bluetooth/Network features

## Additional Resources

- Qt Documentation: https://doc.qt.io/qt-6/android.html
- Qt Android Examples: https://doc.qt.io/qt-6/examples-android.html
- Android Developer Guide: https://developer.android.com/guide
- Project Documentation: See README.md, README_MM.md, QUICKSTART.md

---

**Ready to Build!** 🚀

After completing this setup, you should be able to build and deploy the Robot WiFi Manager app to your Android device using Qt Creator.