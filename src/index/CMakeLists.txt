# Adds a library called common from the source files
file(GLOB index_SRC
    "*.h"
    "*.cpp"
)


ADD_LIBRARY( index ${index_SRC})
target_link_libraries(index parser util htmlcxx reader)