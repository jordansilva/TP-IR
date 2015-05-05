# Adds a library called util from the source files
file(GLOB util_SRC
    "*.h"
    "*.cpp"
)


ADD_LIBRARY( util ${util_SRC})
target_link_libraries(util index)