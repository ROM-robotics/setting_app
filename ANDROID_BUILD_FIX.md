# Android Build Workflow Error - Explanation and Fix

## Error Description

The Android APK Release workflow (`.github/workflows/android_release.yml`) was failing during the CMake configuration step with the following error:

```
CMake Error at CMakeLists.txt:4 (find_package):
  By not providing "FindQt6.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "Qt6", but
  CMake did not find one.

  Could not find a package configuration file provided by "Qt6" (requested
  version 6.8) with any of the following names:

    Qt6Config.cmake
    qt6-config.cmake
```

### Workflow Run Details
- **Failed Run ID**: 19306773698
- **Failed Step**: "8. Configure CMake for Android"
- **Exit Code**: 1

## Root Cause

When building Qt applications for Android, you need **two Qt installations**:

1. **Desktop Qt (Host Tools)**: Provides the build tools like `moc`, `rcc`, `uic`, `qmake`, and `androiddeployqt` that run on the build machine
2. **Android Qt (Target Libraries)**: Provides the Qt libraries compiled for the Android platform

The original workflow only installed Qt for Android target (`android_arm64_v8a`), which contains the libraries but not the build tools needed for cross-compilation.

### Why This Matters

The CMake configuration step uses:
- `-DCMAKE_PREFIX_PATH=/home/runner/work/setting_app/Qt/6.8.3/android_arm64_v8a` - Points to Android Qt libs
- `-DQT_HOST_PATH=/home/runner/work/setting_app/Qt/6.8.3/android_arm64_v8a/../gcc_64` - Points to desktop Qt tools

Without the desktop Qt installation (gcc_64), the `QT_HOST_PATH` points to a non-existent directory, and CMake cannot find the necessary host tools.

## Solution

The fix was to split the Qt installation into two separate steps:

### Before (Incorrect)
```yaml
- name: 3. Install Qt 6.8.3 for Android
  uses: jurplel/install-qt-action@v3
  with:
    version: '6.8.3'
    host: 'linux'
    target: 'android'
    arch: 'android_arm64_v8a'
    modules: 'qtnetworkauth'
```

### After (Correct)
```yaml
- name: 3a. Install Qt 6.8.3 for Desktop (Host Tools)
  uses: jurplel/install-qt-action@v3
  with:
    version: '6.8.3'
    host: 'linux'
    target: 'desktop'
    arch: 'gcc_64'
    modules: 'qtnetworkauth'

- name: 3b. Install Qt 6.8.3 for Android
  uses: jurplel/install-qt-action@v3
  with:
    version: '6.8.3'
    host: 'linux'
    target: 'android'
    arch: 'android_arm64_v8a'
    modules: 'qtnetworkauth'
```

## Technical Details

### What the install-qt-action Does

The `jurplel/install-qt-action@v3` installs Qt in the directory structure:
```
/home/runner/work/setting_app/Qt/6.8.3/
├── gcc_64/              (Desktop Qt - Step 3a)
│   ├── bin/            (moc, rcc, uic, androiddeployqt, etc.)
│   ├── lib/
│   └── ...
└── android_arm64_v8a/   (Android Qt - Step 3b)
    ├── lib/            (libQt6Core.so, libQt6Widgets.so, etc.)
    └── ...
```

### Environment Variables Set

After both installation steps:
- `Qt6_DIR`: Points to Android Qt (`/home/runner/work/setting_app/Qt/6.8.3/android_arm64_v8a`)
- `QT_HOST_PATH`: Points to Desktop Qt (`/home/runner/work/setting_app/Qt/6.8.3/android_arm64_v8a/../gcc_64`)

## Verification

To verify this fix works:
1. Create a new tag matching the pattern `android-alpha*.*.*`, `android-beta*.*.*`, or `android-r*.*.*`
2. Or manually trigger the workflow from the GitHub Actions UI
3. Check that step "8. Configure CMake for Android" completes successfully
4. Verify the build completes and produces an APK file

## Additional Notes

### YAML Linting Issues

The workflow file has some minor YAML linting warnings (trailing spaces, lines over 80 characters). These are cosmetic and do not affect functionality, but they could be fixed in a future cleanup:
- Trailing spaces on lines: 87, 108, 124, 127, 130, 139, 143, 159, 162, 168, 170, 177
- Lines over 80 characters: 12, 71, 100, 102, 105, 126, 129, 141, 153, 161, 223, 249, 251, 262, 264, 265

### References

- [Qt for Android Documentation](https://doc.qt.io/qt-6/android.html)
- [jurplel/install-qt-action](https://github.com/jurplel/install-qt-action)
- [CMake Android Cross-Compiling](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-android)

## Date

Fixed: 2025-11-13
