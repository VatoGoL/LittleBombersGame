add_library(JsonMessages
    STATIC
    JsonMessages.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(JsonMessages PRIVATE Qt6::Core)
target_include_directories(JsonMessages INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
