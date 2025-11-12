include("/home/mr_robot/Desktop/Git/setting_app/setting_app/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/setting_app-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtconnectivity")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/mr_robot/Desktop/Git/setting_app/setting_app/build/Desktop-Debug/setting_app
    GENERATE_QT_CONF
)
