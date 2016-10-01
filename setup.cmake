#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#OSX CLANG
add_compile_options(-Weverything -Wno-deprecated-declarations -Wno-padded -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-newline-eof -Wno-weak-vtables -Wno-weak-template-vtables -Wno-missing-prototypes -Wno-reserved-id-macro)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
IF(${CMAKE_CXX_COMPILER} MATCHES ".*clang\\+\\+")
#LINUX CLANG
add_compile_options(-Weverything -Wthread-safety -Wno-padded -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-newline-eof -Wno-weak-vtables -Wno-weak-template-vtables -Wno-missing-prototypes -Wno-reserved-id-macro -fcolor-diagnostics -Wno-undefined-var-template)
#LINUX GCC
ELSE(${CMAKE_CXX_COMPILER} MATCHES ".*clang\\+\\+")
add_compile_options(-Wno-attributes -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-parameter -Wlogical-op -Wnoexcept -Wstrict-null-sentinel -Wtrampolines -Wvector-operation-performance -Wno-terminate)

ENDIF(${CMAKE_CXX_COMPILER} MATCHES ".*clang\\+\\+")
#LINUX CLANG OR GCC
#add_compile_options(-fstack-protector-strong -Wdate-time)
add_compile_options(-Wdate-time)
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -z relro -z now -pie")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#WINDOWS VISUAL STUDIO
add_compile_options(/W4 /sdl /WX /MP)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#LINUX OR OSX
add_compile_options(-std=c++1z -Wall -Wextra -pedantic-errors -fexceptions -Wno-unused-value -Wno-invalid-offsetof -Wnonnull -Wformat=2 -Wformat-security  -Wformat-nonliteral -Winit-self -Werror -Wswitch-default -Wstrict-overflow=1 -Wcast-align  -Wcast-qual -Wdisabled-optimization -Winit-self -march=native -fno-omit-frame-pointer -Wno-unknown-pragmas)
add_compile_options(--param ssp-buffer-size=4 )
add_compile_options(-fvisibility=hidden)
add_compile_options(-fvisibility-inlines-hidden)
#SET( CMAKE__LINKER_FLAGS "${CMAKE__LINKER_FLAGS} -fPIC")
#SET( STATIC_LIBRARY_FLAGS "${STATIC_LIBRARY_FLAGS} -fPIC")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
FIND_PACKAGE(Boost)
include_directories(${Boost_INCLUDE_DIRS})
