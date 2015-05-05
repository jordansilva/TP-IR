# Adds a library called parser from the source files
file(GLOB parser_SRC
    "*.h"
    "*.cpp"
)


ADD_LIBRARY( parser ${parser_SRC})
target_link_libraries(parser)