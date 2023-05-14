add_library(Controller_DB_Manager
    STATIC
    Controller_DB_Manager.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(Controller_DB_Manager PUBLIC Qt6::Sql)
target_include_directories(Controller_DB_Manager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
