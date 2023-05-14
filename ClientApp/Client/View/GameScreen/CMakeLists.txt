find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
add_library(GameHarvard
    STATIC
    GameScreenHarvard.cpp
)

find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(GameHarvard PRIVATE Qt6::Quick)
target_include_directories(GameHarvard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GameHarvard PRIVATE ${PTHREAD_LIBRARY})
