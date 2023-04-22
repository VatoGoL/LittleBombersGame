cmake_minimum_required(VERSION 3.16)

project(LittleBombers VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

add_subdirectory(View/ServerList)
add_subdirectory(Model/DataBaseManager)
add_subdirectory(Model/TableModel)

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
              View/GameScreen/GameScreen.qml
    SOURCES Model/Client/Client.cpp
            Model/Client/Client.hpp
            Model/Engine/Object.hpp
            Model/GameLevels/ObjectLevel.cpp
            Model/GameLevels/ObjectLevel.hpp
            Model/GameLevels/LevelOne/LevelOne.cpp
            Model/GameLevels/LevelOne/LevelOne.hpp
            Model/GameObject/Being/ObjectBeing.cpp
            Model/GameObject/Being/ObjectBeing.hpp
            Model/GameObject/Being/Enemy/Enemy.cpp
            Model/GameObject/Being/Enemy/Enemy.hpp
            Model/GameObject/Being/Player/Player.cpp
            Model/GameObject/Being/Player/Player.hpp
            Model/GameObject/Props/ObjectProp.cpp
            Model/GameObject/Props/ObjectProp.hpp
            Model/GameObject/Props/Wall/Wall.cpp
            Model/GameObject/Props/Wall/Wall.hpp
            Model/Server/Server.cpp
            Model/Server/Server.hpp
            Model/TableModel/TableModel.cpp
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

install(TARGETS appLittleBombers
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
