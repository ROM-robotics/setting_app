cmake_minimum_required(VERSION 3.19)
project(setting_app LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Widgets Network Bluetooth)

qt_standard_project_setup()

qt_add_executable(setting_app
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    networkmanager.cpp
    networkmanager.h
)

target_link_libraries(setting_app
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Bluetooth
)

include(GNUInstallDirs)

install(TARGETS setting_app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET setting_app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
