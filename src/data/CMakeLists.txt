add_library(data 
    animal_node.cpp
    animal_tree.cpp
)

target_link_libraries(data PRIVATE utils)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
