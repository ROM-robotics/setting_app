#!/bin/bash

# Qt Android Development Environment Setup
# Run this script to check if your environment is ready for building

echo "=========================================="
echo "Qt Android Development Environment Check"
echo "=========================================="
echo ""

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

check_command() {
    if command -v $1 &> /dev/null; then
        echo -e "${GREEN}✓${NC} $1 found: $(command -v $1)"
        return 0
    else
        echo -e "${RED}✗${NC} $1 not found"
        return 1
    fi
}

check_env_var() {
    if [ -n "${!1}" ]; then
        echo -e "${GREEN}✓${NC} $1 is set: ${!1}"
        return 0
    else
        echo -e "${RED}✗${NC} $1 is not set"
        return 1
    fi
}

check_path() {
    if [ -d "$1" ]; then
        echo -e "${GREEN}✓${NC} Path exists: $1"
        return 0
    else
        echo -e "${RED}✗${NC} Path not found: $1"
        return 1
    fi
}

# Check Qt installation
echo "Checking Qt installation..."
check_command qmake
check_command cmake

# Check Java
echo ""
echo "Checking Java..."
check_command java
check_command javac
check_env_var JAVA_HOME

# Check Android SDK
echo ""
echo "Checking Android SDK..."
check_env_var ANDROID_SDK_ROOT || check_env_var ANDROID_HOME
if [ -n "$ANDROID_SDK_ROOT" ]; then
    check_path "$ANDROID_SDK_ROOT/platform-tools"
    check_path "$ANDROID_SDK_ROOT/build-tools"
fi

# Check Android NDK
echo ""
echo "Checking Android NDK..."
check_env_var ANDROID_NDK_ROOT || check_env_var ANDROID_NDK
if [ -n "$ANDROID_NDK_ROOT" ]; then
    check_path "$ANDROID_NDK_ROOT/build"
fi

# Check ADB
echo ""
echo "Checking Android Debug Bridge..."
check_command adb

# Check connected devices
echo ""
echo "Checking connected Android devices..."
if command -v adb &> /dev/null; then
    DEVICES=$(adb devices | grep -v "List" | grep "device$" | wc -l)
    if [ $DEVICES -gt 0 ]; then
        echo -e "${GREEN}✓${NC} Found $DEVICES connected device(s)"
        adb devices
    else
        echo -e "${YELLOW}⚠${NC} No Android devices connected"
    fi
fi

# Check Python (for robot server)
echo ""
echo "Checking Python (for robot server)..."
check_command python3
if command -v python3 &> /dev/null; then
    PYTHON_VERSION=$(python3 --version)
    echo "  Python version: $PYTHON_VERSION"
fi

# Check project files
echo ""
echo "Checking project files..."
check_path "$(pwd)/CMakeLists.txt"
check_path "$(pwd)/mainwindow.cpp"
check_path "$(pwd)/networkmanager.cpp"
check_path "$(pwd)/android/AndroidManifest.xml"

echo ""
echo "=========================================="
echo "Environment Check Complete"
echo "=========================================="
echo ""
echo -e "${YELLOW}Next Steps:${NC}"
echo "1. If Qt is missing: Install Qt 6.8.3 from https://www.qt.io/download"
echo "2. If Android SDK/NDK is missing: Install via Android Studio or sdkmanager"
echo "3. If environment variables are not set, add them to ~/.bashrc:"
echo "   export ANDROID_SDK_ROOT=/path/to/android/sdk"
echo "   export ANDROID_NDK_ROOT=/path/to/android/ndk"  
echo "   export JAVA_HOME=/path/to/jdk"
echo "4. Connect an Android device via USB and enable USB debugging"
echo "5. Build the project using Qt Creator or ./build_android.sh"
echo ""
echo "For robot server setup, see README.md or README_MM.md"
echo ""