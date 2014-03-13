project(garmin-ant-tools)
cmake_minimum_required(VERSION 2.8)

#ant include directory
#include directory from all recurse sub-directories
file(GLOB_RECURSE headers "../../ANT-Library/src/ANT_LIB/*.h" "../../ANT-Library/src/ANT_LIB/*.hpp")

set (ant_INCLUDE_DIRS "")
foreach (_headerFile ${headers})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND ant_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES ant_INCLUDE_DIRS)

include_directories(${ant_INCLUDE_DIRS})

#lib files
file(GLOB  source_file  "[^g]*.c" "antfs_garmin.cpp")
add_library (garmin-ant ${source_file})

#execute files, names garmin_*.c
link_directories (${PROJECT_BINARY_DIR})
file(GLOB  exe_source_files  "garmin*.c")
foreach(_filename ${exe_source_files})
    get_filename_component(_prefix ${_filename} NAME_WE)
    add_executable(${_prefix} ${_filename})
    target_link_libraries (${_prefix} garmin-ant usb m)
endforeach()

