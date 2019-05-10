

include(${CMAKE_SOURCE_DIR}/CMakeLists_Common.txt)

set(target test_hive)

aux_source_directory(. srcList)
set(srcList ${srcList} ${lunaSrc}/luna.cpp)

add_definitions("-g -std=c++0x -DLUNA_KEEP_MEMBER_PREFIX")
include_directories( .  ${luaSrc} ${lunaSrc} ${hiveLib})
link_directories(${luaSrc} ${hiveLib})
add_executable(${target} ${srcList})
target_link_libraries(${target} lua dl hive )

install(TARGETS ${target} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
