
#main 
add_executable(robolliurex main.cpp robocore.cpp robomenus.cpp robopilot.cpp roboslot.cpp robowidgets.cpp rsrcmanager.cpp)

#require pkg-config support
find_package(PkgConfig REQUIRED)

#required pkg-config libs
pkg_check_modules(LGI REQUIRED lgi-1.0)
pkg_check_modules(LSF REQUIRED lsf-1.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${CAIRO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})

target_link_libraries(robolliurex pthread ${LGI_LIBRARIES} ${LSF_LIBRARIES} ${CAIRO_LIBRARIES} ${GTK3_LIBRARIES})

#add include dirs
include_directories(${CMAKE_SOURCE_DIR}/include)

#add custom lib flags
#add_definitions(-std=c++11 -O3)

install(TARGETS robolliurex RUNTIME DESTINATION bin)

