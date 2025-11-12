#!/bin/bash

# Robot WiFi Management App - Build Script for Qt Android
# This script builds the Qt 6.8.3 Android application

set -e

# Configuration
APP_NAME="RobotWiFiManager"
PACKAGE_NAME="com.robot.wifimanager"
ANDROID_TARGET_SDK="33"
ANDROID_MIN_SDK="23"

echo "========================================"
echo "Building Qt Android App: $APP_NAME"
echo "========================================"

# Check if Qt is installed
if ! command -v qmake &> /dev/null; then
    echo "Error: Qt is not installed or not in PATH"
    echo "Please install Qt 6.8.3 with Android support"
    exit 1
fi

# Check if Android SDK/NDK is configured
if [ -z "$ANDROID_SDK_ROOT" ]; then
    echo "Warning: ANDROID_SDK_ROOT not set"
    echo "Please configure Android SDK path"
fi

if [ -z "$ANDROID_NDK_ROOT" ]; then
    echo "Warning: ANDROID_NDK_ROOT not set"  
    echo "Please configure Android NDK path"
fi

# Create build directory
BUILD_DIR="build/android"
mkdir -p $BUILD_DIR
cd $BUILD_DIR

echo "Configuring project with CMake..."
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_PLATFORM=android-$ANDROID_MIN_SDK \
      -DCMAKE_BUILD_TYPE=Release \
      -DQT_ANDROID_PACKAGE_SOURCE_DIR=../../android \
      ../..

echo "Building project..."
cmake --build . --parallel $(nproc)

echo "Creating APK..."
# Qt's androiddeployqt tool will be used here
# This requires proper Qt Android setup

echo "========================================"
echo "Build completed!"
echo "========================================"
echo ""
echo "To install on device:"
echo "adb install $BUILD_DIR/android-build/build/outputs/apk/debug/android-build-debug.apk"
echo ""
echo "To run the robot server on Ubuntu 22.04:"
echo "sudo apt install python3-bluetooth network-manager"  
echo "pip3 install pybluez"
echo "python3 robot_server.py"