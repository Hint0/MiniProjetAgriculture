add_library(lib_core
  myMain.cpp
  myMain.h
 "Room.h" "Room.cpp" "DungeonGenerator.h" "DungeonGenerator.cpp" "SMFLOrthogonalLayer.h" 
 "Bullet.hpp" "Bullet.cpp" "Character.hpp" "Character.cpp" "Enemy.hpp" "Enemy.cpp" "Gun.hpp" "Gun.cpp" "Player.hpp" "Player.cpp" "Weapon.hpp" "Weapon.cpp" "RandomHelper.h")
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
