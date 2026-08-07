set(LIBRARY_NAME "decrypter")
set(LIBRARY_INCLUDES "${CMAKE_BINARY_DIR}/app/")
add_library(${LIBRARY_NAME} ${LIBRARY_NAME}.cpp ${LIBRARY_NAME}.h)
target_include_directories("decrypter" PUBLIC ${LIBRARY_INCLUDES} .)

