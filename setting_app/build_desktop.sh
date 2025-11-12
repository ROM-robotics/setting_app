#!/bin/bash

# Build script for Linux Desktop
# Qt 6.8.3 Desktop Build

set -e

echo "=========================================="
echo "Building Robot WiFi Manager for Desktop"
echo "=========================================="
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Check if Qt is available
if ! command -v qmake &> /dev/null; then
    echo -e "${RED}Error: Qt not found!${NC}"
    echo "Please install Qt 6.8.3 or set PATH to Qt installation"
    echo "Example: export PATH=~/Qt/6.8.3/gcc_64/bin:\$PATH"
    exit 1
fi

# Check if cmake is available
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: CMake not found!${NC}"
    echo "Please install CMake: sudo apt install cmake"
    exit 1
fi

echo -e "${GREEN}✓${NC} Qt found: $(qmake -version | grep 'Qt version')"
echo -e "${GREEN}✓${NC} CMake found: $(cmake --version | head -1)"
echo ""

# Create build directory
BUILD_DIR="build/Desktop-Debug"
echo "Creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Navigate to build directory
cd "$BUILD_DIR"

# Run CMake
echo ""
echo "Running CMake configuration..."
export CMAKE_PREFIX_PATH=~/Qt/6.8.3/gcc_64
cmake -DCMAKE_BUILD_TYPE=Debug ../..

if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed!${NC}"
    exit 1
fi

# Build
echo ""
echo "Building application..."
cmake --build . --parallel $(nproc)

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}=========================================="
echo "Build completed successfully!"
echo "==========================================${NC}"
echo ""
echo "Executable location:"
echo "  $(pwd)/setting_app"
echo ""
echo "To run the application:"
echo "  cd $(pwd)"
echo "  ./setting_app"
echo ""
echo "Or run from project root:"
echo "  ./build/Desktop-Debug/setting_app"
echo ""
