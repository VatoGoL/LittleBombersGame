add_library(NetWorker
    STATIC
    NetWorker.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(NetWorker PRIVATE Qt6::Core)
target_include_directories(NetWorker INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NetWorker PRIVATE ${PTHREAD_LIBRARY})
