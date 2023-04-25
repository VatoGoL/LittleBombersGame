add_library(TableModel
    STATIC
    TableModel.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Quick)
target_link_libraries(TableModel PRIVATE Qt6::Quick)
target_link_libraries(TableModel PRIVATE Qt6::Core)
target_include_directories(TableModel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
