
#get a list of all svg files
file(GLOB SVG_FILES *.svg)

set(PNG_FILES)

#cycle through all svg
foreach(SVG ${SVG_FILES})

#get filename without exstension
get_filename_component (PNG ${SVG} NAME_WE)

#build output png
set(PNG ${CMAKE_CURRENT_BINARY_DIR}/${PNG}.png)

#message(STATUS ${PNG})

#create a custom command for converting x.png
add_custom_command(OUTPUT ${PNG} COMMAND rsvg-convert -o ${PNG} ${SVG})

#adds the png to a list
list (APPEND PNG_FILES ${PNG})

endforeach(SVG)

#creates the target
add_custom_target(render ALL DEPENDS ${PNG_FILES})

install(FILES ${PNG_FILES} DESTINATION /usr/share/pixmaps/robolliurex/)
