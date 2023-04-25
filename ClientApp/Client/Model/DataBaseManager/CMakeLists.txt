add_library(DataBaseManager
    STATIC
    DataBaseManager.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(DataBaseManager PRIVATE Qt6::Sql)
target_include_directories(DataBaseManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
