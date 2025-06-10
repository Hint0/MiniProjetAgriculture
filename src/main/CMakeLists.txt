add_executable(main
  main.cpp
)

target_link_libraries(main PUBLIC lib_core pugixml sfml-graphics tmxlite)

add_custom_target(copy-res ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/res)
file(GLOB RESOURCES_TILEMAP CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/res/tilemap/*.*)
file(GLOB RESOURCES_MAPS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/res/maps/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res
                   DEPENDS ${CMAKE_SOURCE_DIR}/res
                   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                           ${CMAKE_SOURCE_DIR}/res
                           ${CMAKE_CURRENT_BINARY_DIR}/res
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES_TILEMAP}
                           ${CMAKE_CURRENT_BINARY_DIR}/res/tilemap
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES_MAPS}
                           ${CMAKE_CURRENT_BINARY_DIR}/res/maps)

add_dependencies(main copy-res)
