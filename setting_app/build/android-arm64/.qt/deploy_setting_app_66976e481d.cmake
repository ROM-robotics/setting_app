include("/home/mr_robot/Desktop/Git/setting_app/setting_app/build/android-arm64/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/setting_app-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtconnectivity")
_qt_internal_show_skip_runtime_deploy_message("shared Qt libs, cross-compiled, non-bundle app"
    EXTRA_MESSAGE "Executable targets have to be app bundles to use this command on Apple platforms."
)