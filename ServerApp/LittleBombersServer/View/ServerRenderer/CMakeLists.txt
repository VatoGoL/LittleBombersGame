add_library(ServerRenderer
    STATIC
    ServerRenderer.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(ServerRenderer PRIVATE Qt6::Core)
target_include_directories(ServerRenderer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ServerRenderer PRIVATE ${PTHREAD_LIBRARY})
