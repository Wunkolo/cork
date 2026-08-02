cmake_minimum_required( VERSION 3.18 )
project( cork )

### Standard
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

### Verbosity
set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


### Cork
option( CORK_BUILD_TESTING "" ${cork_IS_TOP_LEVEL} )
option( CORK_BUILD_TOOLS "" ${cork_IS_TOP_LEVEL} )

set(
	CORK_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/cork/cork.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/cork/code_block.hpp
)
set(
	CORK_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/source/cork/code_block.cpp
)

add_library( cork )
target_sources( cork INTERFACE "$<BUILD_INTERFACE:${CORK_HEADER_FILES}>" )
target_sources( cork PRIVATE "$<BUILD_INTERFACE:${CORK_SOURCE_FILES}>" )
target_include_directories( cork PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features( cork INTERFACE cxx_std_20 )

### Tools
if( CORK_BUILD_TOOLS )

# PugiXML
find_package( PugiXML 1.15)
if( NOT TARGET pugixml::pugixml )
	message( WARNING "pugixml not found. Using embedded submodule")
	add_subdirectory( externals/pugixml EXCLUDE_FROM_ALL )
endif()

# fmt
find_package( fmt 11.1.4)
if( NOT TARGET fmt::fmt )
	message( WARNING "fmt not found. Using embedded submodule")
	add_subdirectory( externals/fmt EXCLUDE_FROM_ALL )
endif()


add_executable( generate
	tools/generate.cpp
)
target_include_directories( generate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests )
target_link_libraries( generate PRIVATE pugixml::pugixml fmt::fmt )

endif()


### Tests
if( CORK_BUILD_TESTING )
enable_testing()

find_package( Catch2 3 )
if( NOT TARGET Catch2::Catch2WithMain )
	message( WARNING "Catch2 v3 not found. Using embedded submodule")
	add_subdirectory( externals/Catch2 EXCLUDE_FROM_ALL )
endif()

include(Catch)

add_executable( cork-tests
	tests/a64.cpp
	tests/code_block.cpp
)
target_include_directories( cork-tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests )
target_link_libraries( cork-tests PRIVATE Catch2::Catch2WithMain cork )

catch_discover_tests(cork-tests)

### Optimizations
if( MSVC )
	target_compile_options( cork-tests PRIVATE
		/MP # Parallel builds 
		/permissive- # Stricter C++ conformance

		# Warnings
		/W3

		# Consider these warnings as errors
		/we4018 # 'expression': signed/unsigned mismatch
		/we4062 # Enumerator 'identifier' in a switch of enum 'enumeration' is not handled
		/we4101 # 'identifier': unreferenced local variable
		/we4265 # 'class': class has virtual functions, but destructor is not virtual
		/we4305 # 'context': truncation from 'type1' to 'type2'
		/we4388 # 'expression': signed/unsigned mismatch
		/we4389 # 'operator': signed/unsigned mismatch

		/we4456 # Declaration of 'identifier' hides previous local declaration
		/we4457 # Declaration of 'identifier' hides function parameter
		/we4458 # Declaration of 'identifier' hides class member
		/we4459 # Declaration of 'identifier' hides global declaration

		/we4505 # 'function': unreferenced local function has been removed
		/we4547 # 'operator': operator before comma has no effect; expected operator with side-effect
		/we4549 # 'operator1': operator before comma has no effect; did you intend 'operator2'?
		/we4555 # Expression has no effect; expected expression with side-effect
		/we4715 # 'function': not all control paths return a value
		/we4834 # Discarding return value of function with 'nodiscard' attribute
		/we5038 # data member 'member1' will be initialized after data member 'member2'
		/we5245 # 'function': unreferenced function with internal linkage has been removed

	)
elseif( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
	target_compile_options( cork-tests PRIVATE
		-Wall
		-Wpedantic
		-Werror
		-Warray-bounds
		-Wextra
		-Wimplicit-fallthrough
		-Wmissing-declarations
		-Wmissing-declarations
		-Wmissing-field-initializers
		-Wno-attributes
		-Wno-invalid-offsetof
		-Wno-unused-parameter
		-Wreorder
		-Wshadow
		-Wsign-compare
		-Wswitch
		-Wuninitialized
		-Wunused-function
		-Wunused-result
		-Wunused-variable
	)
endif()

endif()