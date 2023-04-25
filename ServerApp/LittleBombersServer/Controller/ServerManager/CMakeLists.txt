add_library(ServerManager
    STATIC
    ServerManager.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(ServerManager PRIVATE Qt6::Core)
target_include_directories(ServerManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ServerManager PRIVATE ${PTHREAD_LIBRARY})
