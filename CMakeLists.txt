cmake_minimum_required (VERSION 3.14)

project ("convexl")

add_subdirectory(deps/geometry-central)
add_subdirectory(deps/polyscope)
add_subdirectory(src)

target_link_libraries(convexl polyscope)
target_link_libraries(convexl geometry-central)