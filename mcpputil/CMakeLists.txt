include_directories(include)
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_compile_options(-fPIC)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
list (APPEND SRC_FILES src/memory_range.cpp)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
list (APPEND SRC_FILES ${SRC_FILES}
  include/mcpputil/mcpputil/algorithm.hpp
  include/mcpputil/mcpputil/aligned_allocator.hpp
  include/mcpputil/mcpputil/alignment.HPP
  include/mcpputil/mcpputil/backed_ordered_map.hpp
  include/mcpputil/mcpputil/backed_ordered_map_impl.hpp
  include/mcpputil/mcpputil/bandit.hpp
  include/mcpputil/mcpputil/clang_concurrency.hpp
  include/mcpputil/mcpputil/concurrency.hpp
  include/mcpputil/mcpputil/concurrency_apple.hpp
  include/mcpputil/mcpputil/condition_variable.hpp
  include/mcpputil/mcpputil/condition_variable_impl.hpp
  include/mcpputil/mcpputil/container.hpp
  include/mcpputil/mcpputil/container_functions.hpp
  include/mcpputil/mcpputil/declarations.hpp
  include/mcpputil/mcpputil/equipartition.hpp
  include/mcpputil/mcpputil/function_iterator.hpp
  include/mcpputil/mcpputil/intrinsics.hpp
  include/mcpputil/mcpputil/iterator.hpp
  include/mcpputil/mcpputil/literals.hpp
  include/mcpputil/mcpputil/make_unique.hpp
  include/mcpputil/mcpputil/memory_range.hpp
  include/mcpputil/mcpputil/memory_range_impl.hpp
  include/mcpputil/mcpputil/posix_slab.hpp
  include/mcpputil/mcpputil/posix_slab_impl.hpp
  include/mcpputil/mcpputil/security.hpp
  include/mcpputil/mcpputil/std.hpp
  include/mcpputil/mcpputil/thread_local_pointer.hpp
  include/mcpputil/mcpputil/timed_algorithm.hpp
  include/mcpputil/mcpputil/unsafe_cast.hpp
  include/mcpputil/mcpputil/view_traits.hpp
  include/mcpputil/mcpputil/warning_wrapper_pop.hpp
  include/mcpputil/mcpputil/warning_wrapper_push.hpp
  include/mcpputil/mcpputil/win32_slab.hpp
  include/mcpputil/mcpputil/win32_slab_impl.hpp
  src/win32_slab.cpp)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_library(mcpputil ${SRC_FILES})
INSTALL(DIRECTORY "include/mcpputil" DESTINATION "include")
INSTALL(TARGETS mcpputil
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
