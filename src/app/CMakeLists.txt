add_executable(app app_main.cpp)

# include directories here
target_link_libraries(app PRIVATE
    utils
    data
)

# Set the output directory for the executable
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS app)
