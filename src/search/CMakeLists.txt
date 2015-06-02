# Adds a library called search from the source files
file(GLOB search_SRC
    "*.h"
    "*.cpp"
)


ADD_LIBRARY( search ${search_SRC})
target_link_libraries(search index util parser)