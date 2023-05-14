add_library(ClientManager
    STATIC
    ClientManager.cpp
)
find_package(Qt6 6.4 REQUIRED COMPONENTS Core)

target_link_libraries(ClientManager PRIVATE Qt6::Core)
target_include_directories(ClientManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
