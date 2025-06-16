# Compared to original CMakeLists.txt, we integrate all Include files in add_executable to be sure that
# SonaQube analyzes these files.
add_executable(PiouPiou
        Source/Main.cpp
        Source/Bullet.cpp Include/Bullet.hpp
        Source/Character.cpp Include/Character.hpp
        Source/Enemy.cpp Include/Enemy.hpp
        Source/Player.cpp Include/Player.hpp
        Source/Gun.cpp Include/Gun.hpp
        Source/Weapon.cpp Include/Weapon.hpp

)

target_include_directories(PiouPiou
        PRIVATE
        Include
)

target_link_libraries(PiouPiou PUBLIC sfml-graphics)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
