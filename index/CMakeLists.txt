

add_executable(index 
         index.cpp 
         fibre.cpp
         vector.cpp
         ../main_catch.cpp)
target_link_libraries(index PUBLIC Catch::Catch pthread rt)
add_test(NAME index COMMAND index)