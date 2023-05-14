add_library(ClientWrapper
    STATIC
    WrapperForClientManager.cpp
)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

target_link_libraries(ClientWrapper PRIVATE Qt6::Quick)
target_include_directories(ClientWrapper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
