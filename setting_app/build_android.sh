#!/bin/bash

# Robot WiFi Management App - Build Script for Qt Android
# This script builds the Qt 6.8.3 Android application

set -e

# Configuration
APP_NAME="RobotWiFiManager"
PACKAGE_NAME="com.robot.wifimanager"
ANDROID_TARGET_SDK="34"
ANDROID_MIN_SDK="26"
QT_VERSION="6.8.3"
QT_ANDROID_ARCH="android_arm64_v8a"
QT_ROOT="${HOME}/Qt/${QT_VERSION}"
QT_ANDROID_PATH="${QT_ROOT}/${QT_ANDROID_ARCH}"
QT_HOST_PATH="${QT_ROOT}/gcc_64"

echo "========================================"
echo "Building Qt Android App: $APP_NAME"
echo "========================================"

# Check if Qt Android is installed
if [ ! -d "$QT_ANDROID_PATH" ]; then
    echo "✗ Error: Qt Android ${QT_VERSION} not found at: $QT_ANDROID_PATH"
    echo ""
    echo "Available Qt installations:"
    ls -1 "$QT_ROOT" 2>/dev/null || echo "  No Qt ${QT_VERSION} found"
    echo ""
    echo "Please install Qt ${QT_VERSION} for Android with Qt Maintenance Tool"
    exit 1
fi

echo "✓ Qt Android found: $QT_ANDROID_PATH"

echo "✓ Qt Android found: $QT_ANDROID_PATH"

# Check for Android SDK/NDK
if [ -z "$ANDROID_SDK_ROOT" ]; then
    # Try common locations
    if [ -d "$HOME/Android/Sdk" ]; then
        export ANDROID_SDK_ROOT="$HOME/Android/Sdk"
        echo "✓ Found Android SDK: $ANDROID_SDK_ROOT"
    elif [ -d "$HOME/android-sdk" ]; then
        export ANDROID_SDK_ROOT="$HOME/android-sdk"
        echo "✓ Found Android SDK: $ANDROID_SDK_ROOT"
    else
        echo "✗ Warning: ANDROID_SDK_ROOT not set and not found in default locations"
        echo "  Please install Android SDK or set ANDROID_SDK_ROOT environment variable"
    fi
else
    echo "✓ Android SDK: $ANDROID_SDK_ROOT"
fi

if [ -z "$ANDROID_NDK_ROOT" ]; then
    # Try to find NDK in SDK
    if [ -d "$ANDROID_SDK_ROOT/ndk" ]; then
        # Use the latest NDK version
        NDK_VERSION=$(ls -1 "$ANDROID_SDK_ROOT/ndk" | sort -V | tail -n1)
        if [ -n "$NDK_VERSION" ]; then
            export ANDROID_NDK_ROOT="$ANDROID_SDK_ROOT/ndk/$NDK_VERSION"
            echo "✓ Found Android NDK: $ANDROID_NDK_ROOT"
        fi
    fi
    
    if [ -z "$ANDROID_NDK_ROOT" ]; then
        echo "✗ Warning: ANDROID_NDK_ROOT not set"  
        echo "  Please install Android NDK or set ANDROID_NDK_ROOT environment variable"
    fi
else
    echo "✓ Android NDK: $ANDROID_NDK_ROOT"
fi

# Verify NDK toolchain file exists
if [ -n "$ANDROID_NDK_ROOT" ] && [ ! -f "$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake" ]; then
    echo "✗ Error: NDK toolchain file not found at: $ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake"
    exit 1
fi

# Create build directory
BUILD_DIR="build/android-arm64"
echo ""
echo "Creating build directory: $BUILD_DIR"
mkdir -p $BUILD_DIR

echo "Configuring project with CMake..."
cmake -S . -B $BUILD_DIR \
      -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_PLATFORM=android-${ANDROID_MIN_SDK} \
      -DANDROID_STL=c++_shared \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_FIND_ROOT_PATH=$QT_ANDROID_PATH \
      -DQt6_DIR=$QT_ANDROID_PATH/lib/cmake/Qt6 \
      -DQT_HOST_PATH=$QT_HOST_PATH \
      -DANDROID_NDK=$ANDROID_NDK_ROOT \
      -DANDROID_SDK_ROOT=$ANDROID_SDK_ROOT

if [ $? -ne 0 ]; then
    echo "✗ CMake configuration failed"
    exit 1
fi

echo ""
echo "Building project..."
cmake --build $BUILD_DIR --config Release --parallel $(nproc)

if [ $? -ne 0 ]; then
    echo "✗ Build failed"
    exit 1
fi

echo ""
echo "========================================"
echo "✅ Build completed successfully!"
echo "========================================"
echo ""
echo "📦 APK Location:"
APK_PATH="$BUILD_DIR/android-build/build/outputs/apk/release/android-build-release-unsigned.apk"
if [ -f "$APK_PATH" ]; then
    APK_SIZE=$(du -h "$APK_PATH" | cut -f1)
    echo "  $APK_PATH"
    echo "  Size: $APK_SIZE"
    echo ""
    echo "⚠️  Note: This APK is UNSIGNED (development build)"
    echo ""
    echo "📲 To install on device:"
    echo "  adb install \"$APK_PATH\""
    echo ""
    echo "🔑 To sign the APK for distribution:"
    echo "  1. Create a keystore:"
    echo "     keytool -genkey -v -keystore my-release-key.jks -keyalg RSA -keysize 2048 -validity 10000 -alias my-alias"
    echo ""
    echo "  2. Sign the APK:"
    echo "     jarsigner -verbose -sigalg SHA256withRSA -digestalg SHA-256 -keystore my-release-key.jks \"$APK_PATH\" my-alias"
    echo ""
    echo "  3. Zipalign:"
    echo "     \$ANDROID_SDK_ROOT/build-tools/*/zipalign -v 4 \"$APK_PATH\" app-release.apk"
else
    echo "  ⚠️  APK not found at expected location"
fi
echo ""
echo "🤖 To run the robot server on Ubuntu 22.04:"
echo "  sudo apt install python3-bluetooth network-manager"  
echo "  pip3 install pybluez"
echo "  python3 robot_server.py"