cmake_minimum_required (VERSION 3.8)

project(SpirvTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wno-implicit-fallthrough -Wshadow")
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CPP_VERSION} -g")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CPP_VERSION} -O3")
elseif (MSVC)
    add_compile_options("/std:c++17")
endif()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

#add_subdirectory(ext/SPIRV-Cross)

set(
	SPIRV_DIR
	"C:/Users/Liam Tyler/Documents/SPIRV-Cross"
)

set(
	INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ext
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	${SPIRV_DIR}
)

set(
	LIBS
	spirv-cross-c
    spirv-cross-core
	spirv-cross-cpp
	spirv-cross-glsl
	spirv-cross-hlsl
    spirv-cross-msl
	spirv-cross-reflect
    spirv-cross-util
)

set(
	LIB_DIR
	${SPIRV_DIR}/build/
)

link_directories(${LIB_DIR})
include_directories(${INCLUDE_DIRS})

set(
    SRCS
	src/main.cpp
)

set(
    HEADERS
)

add_executable(spirvTest ${SRCS} ${HEADERS})

set_target_properties(
    spirvTest
    PROPERTIES
    DEBUG_POSTFIX _debug
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT spirvTest)

target_link_libraries(spirvTest ${LIBS})
