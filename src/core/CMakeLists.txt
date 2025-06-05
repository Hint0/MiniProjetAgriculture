add_library(lib_core
  myMain.cpp
  myMain.h
 "Room.h" "Room.cpp" "DungeonGenerator.h" "DungeonGenerator.cpp")
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
