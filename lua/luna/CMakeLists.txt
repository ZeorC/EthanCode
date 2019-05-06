

include(${CMAKE_SOURCE_DIR}/CMakeLists_Common.txt)

set(target test_luna)

aux_source_directory(. srcList)
set(srcList ${srcList} ${lunaSrc}/luna.cpp)

add_definitions("-g -std=c++0x -DLUNA_KEEP_MEMBER_PREFIX")
include_directories( .  ${luaSrc} ${lunaSrc})
link_directories(${luaSrc})
add_executable(${target} ${srcList})
target_link_libraries(${target} lua dl )
