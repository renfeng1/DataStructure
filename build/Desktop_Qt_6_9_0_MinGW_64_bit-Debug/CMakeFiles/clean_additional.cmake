# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\youjv_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\youjv_autogen.dir\\ParseCache.txt"
  "youjv_autogen"
  )
endif()
