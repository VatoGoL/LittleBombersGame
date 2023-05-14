cmake_minimum_required(VERSION 3.16)

project(LittleBombers VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "/home/QT/6.4.3/gcc_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Quick)

add_subdirectory(View)
add_subdirectory(Model)
add_subdirectory(Controller)

qt_standard_project_setup()

qt_add_executable(appLittleBombers
    main.cpp
)

qt_add_qml_module(appLittleBombers
    URI LittleBombers
    VERSION 1.0
    QML_FILES Main.qml
              View/ServerList/ServerList.qml
              View/ServerList/DialogWindow/DialogServerList.qml
              View/StartScreen/StartScreen.qml
              View/FormInput/FormInput.qml
              View/GameScreen/GameScreenHarvard.qml
              #View/GameScreen/GameScreenLB.qml

    SOURCES Model/TableModel/TableModel.cpp
            Model/TableModel/TableModel.hpp

            game_resources.qrc
)



set_target_properties(appLittleBombers PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appLittleBombers
    PRIVATE Qt6::Quick
)

target_link_libraries(appLittleBombers PRIVATE ServerListt)
target_link_libraries(appLittleBombers PRIVATE DataBaseManager)
target_link_libraries(appLittleBombers PRIVATE TableModel)
target_link_libraries(appLittleBombers PRIVATE ClientManager)
target_link_libraries(appLittleBombers PRIVATE ClientWrapper)
target_link_libraries(appLittleBombers PRIVATE GameHarvard)

target_link_libraries(ClientManager PUBLIC NetWorker)
target_link_libraries(ClientManager PUBLIC JsonMessages)

target_link_libraries(ServerListt PUBLIC NetWorker)
#target_link_libraries(ServerListt PUBLIC ClientWrapper)


target_link_libraries(ClientWrapper PUBLIC ClientManager)

install(TARGETS appLittleBombers
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
