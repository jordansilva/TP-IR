# CmakeLists.txt in src dir

# Adds a library called reader from the source files

ADD_LIBRARY( reader CollectionReader.h CollectionReader.cpp Document.h Document.cpp envDefault.h)

target_link_libraries(reader)