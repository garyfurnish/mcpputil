include_directories(../mcpputil/include/)
find_path(BANDIT_INCLUDE_PATH bandit/bandit.h PATHS ../../bandit)
include_directories(${BANDIT_INCLUDE_PATH})
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_compile_options(-fPIE)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_executable(mcpputil_test
  main.cpp
  flat_set_extrensic_allocator.cpp
  memory_range_group.cpp
  vector_extrensic_allocator.cpp
  )
target_link_libraries(mcpputil_test mcpputil pthread)
