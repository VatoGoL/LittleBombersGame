find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
add_library(ServerListt
    STATIC
    ServerListt.cpp
)
#add_subdirectory(../../Model/DataBaseManager)

target_link_libraries(ServerListt PRIVATE Qt6::Quick)
#target_link_libraries(ServerListt PRIVATE DataBaseManager)
target_include_directories(ServerListt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
