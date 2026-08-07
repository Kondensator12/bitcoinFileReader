find_package(Doxygen)
configure_file(${CMAKE_SOURCE_DIR}/docs/Doxyfile ${CMAKE_BINARY_DIR} COPYONLY)
if(DOXYGEN_FOUND)
    add_custom_target(
        docs
        ${DOXYGEN_EXECUTABLE}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}) 
endif()

