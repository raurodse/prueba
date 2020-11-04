
#resource build
set(RSRC banner.robolliurex.png;robolliurex-48.png;robolliurex-32.png)

add_custom_command(OUTPUT banner.robolliurex.png COMMAND rsvg-convert -o ${CMAKE_CURRENT_BINARY_DIR}/banner.robolliurex.png ${CMAKE_SOURCE_DIR}/rsrc/banner.robolliurex.svg)
add_custom_command(OUTPUT robolliurex-48.png COMMAND rsvg-convert -o ${CMAKE_CURRENT_BINARY_DIR}/robolliurex-48.png -w 48 -h 48 ${CMAKE_SOURCE_DIR}/rsrc/icon.robolliurex.svg)
add_custom_command(OUTPUT robolliurex-32.png COMMAND rsvg-convert -o ${CMAKE_CURRENT_BINARY_DIR}/robolliurex-32.png -w 32 -h 32 ${CMAKE_SOURCE_DIR}/rsrc/icon.robolliurex.svg)

add_custom_target(resources ALL DEPENDS ${RSRC})


#resource install 
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/banner.robolliurex.png DESTINATION /usr/share/banners/lliurex-neu/ RENAME robolliurex.png)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/robolliurex-48.png DESTINATION /usr/share/icons/hicolor/48x48/apps/ RENAME robolliurex.png)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/robolliurex-32.png DESTINATION /usr/share/icons/hicolor/32x32/apps/ RENAME robolliurex.png)

#unprocessed files
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/icon.robolliurex.svg DESTINATION share/icons/hicolor/scalable/apps/ RENAME robolliurex.svg)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/robolliurex.desktop DESTINATION share/applications/)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/10-robolliurex.rules DESTINATION /lib/udev/rules.d/)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/FIRM0309.lgo DESTINATION /lib/firmware/rcx/)
install(FILES ${CMAKE_SOURCE_DIR}/rsrc/FIRM0328.lgo DESTINATION /lib/firmware/rcx/)
