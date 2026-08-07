set(LIBRARY_NAME "bitcoinBlockContainer")
set(LIBRARY_INCLUDES "${CMAKE_BINARY_DIR}/lib/bitcoinBinToText/")
add_library(${LIBRARY_NAME} ${LIBRARY_NAME}.cpp ${LIBRARY_NAME}.h)
target_include_directories("bitcoinBlockContainer" PUBLIC ${LIBRARY_INCLUDES} .)

