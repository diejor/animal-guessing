add_executable(app app_main.cpp)

# include directories here
target_link_libraries(app PRIVATE
    # for example
    # input::input
    )

install(TARGETS app DESTINATION bin)
