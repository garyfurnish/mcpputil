include_directories(include)
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_compile_options(-fPIC)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
list (APPEND SRC_FILES src/memory_range.cpp)
add_library(mcpputil ${SRC_FILES})
INSTALL(DIRECTORY "include/mcpputil" DESTINATION "include")
INSTALL(TARGETS mcpputil
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
