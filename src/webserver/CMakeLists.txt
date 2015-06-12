# Adds a library called util from the source files

file(GLOB webserver_SRC
    "*.h"
    "*.hpp"
    "*.cpp"
)

ADD_LIBRARY(webserver ${webserver_SRC})
target_link_libraries(webserver)