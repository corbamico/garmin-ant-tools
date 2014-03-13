project(garmin-ant-tools)
cmake_minimum_required(VERSION 2.8)

#lib files
file(GLOB  source_file  "[^g]*.c")
add_library (garmin-ant ${source_file})

#execute files, names garmin_*.c
link_directories (${PROJECT_BINARY_DIR})
file(GLOB  exe_source_files  "garmin*.c")
foreach(_filename ${exe_source_files})
    get_filename_component(_prefix ${_filename} NAME_WE)
    add_executable(${_prefix} ${_filename})
    target_link_libraries (${_prefix} garmin-ant usb m)
endforeach()

