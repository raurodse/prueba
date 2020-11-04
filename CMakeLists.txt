
# ***  robolliurex main cmake ****
cmake_minimum_required (VERSION 2.8)
project (ROBOLLIUREX)


add_subdirectory(svg)
add_subdirectory(rsrc)
add_subdirectory(src)

add_dependencies(robolliurex render resources)

