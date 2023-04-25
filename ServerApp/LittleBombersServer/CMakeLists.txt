cmake_minimum_required(VERSION 3.14)

project(LittleBombersServer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_library(PTHREAD_LIBRARY pthread)

add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(Controller)
#add_compile_options(-lpthread)

add_executable(LittleBombersServer
  main.cpp
)

add_library(ServerApp
    STATIC
    ServerApp.cpp
)
target_link_libraries(ServerApp PRIVATE Qt6::Core)
target_include_directories(ServerApp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ServerApp PRIVATE ${PTHREAD_LIBRARY})

target_link_libraries(LittleBombersServer Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(LittleBombersServer ${PTHREAD_LIBRARY})
target_link_libraries(LittleBombersServer ServerApp)

target_link_libraries(ServerApp PUBLIC ServerRenderer)
target_link_libraries(ServerApp PUBLIC ServerManager)

target_link_libraries(ServerManager PUBLIC NetWorker)



install(TARGETS LittleBombersServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
