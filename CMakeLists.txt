
cmake_minimum_required(VERSION 3.10)
project(cldi VERSION 25.0.0.0 LANGUAGES C CXX)

option(BUILD_STATIC "Build into static libraries instead of dynamic libraries (default: OFF)." OFF)
option(BUILD_CXX "Build using the C++ library (default: ON)." ON)
option(ONEFILE "Build into a single shared or static library file (default: OFF)." OFF)
set(STD "" CACHE STRING "The version of the C or C++ Standard to compile with (default: 17)")
if (STD STREQUAL "")
	set(CMAKE_CXX_STD 17)
else()
	string(REGEX REPLACE "[^0-9]" "" CMAKE_CXX_STD "${STD}")
endif()

if(BUILD_CXX)
	set(LIBSTAMP "linux-gnu-x86_64-g++${STD}")
else()
	set(LIBSTAMP "linux-gnu-x86_64-gcc${STD}")
endif()

include_directories(stdlib/head-layer/include)
link_directories(bin)

if(ONEFILE)
	if(BUILD_CXX)
		file (GLOB_RECURSE SRC "stdlib/head-layer/lib/c/*.c" "stdlib/head-layer/lib/c++/*.cxx" "stdlib/core-layer/lib/c/*.c" "stdlib/core-layer/lib/c++/*.cxx")
		if(BUILD_STATIC)
			add_library(libcldi STATIC ${SRC})
		else()
			add_library(libcldi SHARED ${SRC})
		endif()
		set_target_properties(libcldi PROPERTIES LINKER_LANGUAGE C)
	else()
		file (GLOB_RECURSE SRC "stdlib/head-layer/lib/c/*.c" "stdlib/core-layer/lib/c/*.c")
		if(BUILD_STATIC)
			add_library(libcldi STATIC ${SRC})
		else()
			add_library(libcldi SHARED ${SRC})
		endif()
		set_target_properties(libcldi PROPERTIES LINKER_LANGUAGE CXX)
	endif()

	if (UNIX)
		find_library(UNIXLIB_MATH m PATHS /usr/lib NO_DEFAULT_PATH)
		target_link_libraries(libcldi ${UNIXLIB_MATH})
	endif()

	set_target_properties(
		libcldi
		VERSION ${PROJECT_VERSION}
		LIBRARY_OUTPUT_DIRECTORY "bin"
		ARCHIVE_OUTPUT_DIRECTORY "bin"
		LIBRARY_OUTPUT_NAME      "cldi.${LIBSTAMP}"
		ARCHIVE_OUTPUT_NAME      "cldi.${LIBSTAMP}"
	)
else()
	if(BUILD_CXX)
		file (GLOB_RECURSE SRC_HEAD "stdlib/head-layer/lib/c/*.c" "stdlib/head-layer/lib/c++/*.cxx")
		#file (GLOB_RECURSE SRC_CORE "stdlib/core-layer/lib/c/*.c" "stdlib/core-layer/lib/c++/*.cxx")
		if(BUILD_STATIC)
			add_library(cldi_head STATIC ${SRC_HEAD})
			#add_library(cldi_core STATIC ${SRC_CORE})
		else()
			add_library(cldi_head SHARED ${SRC_HEAD})
			#add_library(cldi_core SHARED ${SRC_CORE})
		endif()
		set_target_properties(cldi_head PROPERTIES LINKER_LANGUAGE CXX)
		#set_target_properties(cldi_core PROPERTIES LINKER_LANGUAGE CXX)
	else()
		file (GLOB_RECURSE SRC_HEAD "stdlib/head-layer/lib/c/*.c")
		#file (GLOB_RECURSE SRC_CORE "stdlib/core-layer/lib/c/*.c")
		if(BUILD_STATIC)
			add_library(cldi_head STATIC ${SRC_HEAD})
			#add_library(cldi_core STATIC ${SRC_CORE})
		else()
			add_library(cldi_head SHARED ${SRC_HEAD})
			#add_library(cldi_core SHARED ${SRC_CORE})
		endif()
		set_target_properties(cldi_head PROPERTIES LINKER_LANGUAGE C)
		#set_target_properties(cldi_core PROPERTIES LINKER_LANGUAGE C)
	endif()

	#target_link_libraries(cldi_core cldi_head)

	if (UNIX)
		find_library(UNIXLIB_MATH m PATHS /usr/lib NO_DEFAULT_PATH)
		target_link_libraries(cldi_head ${UNIXLIB_MATH})
		#target_link_libraries(cldi_core ${UNIXLIB_MATH})
	endif()

	set_target_properties(cldi_head PROPERTIES 
		VERSION ${PROJECT_VERSION}
		LIBRARY_OUTPUT_DIRECTORY "bin"
		ARCHIVE_OUTPUT_DIRECTORY "bin"
		LIBRARY_OUTPUT_NAME      "cldi-head-${LIBSTAMP}"
		ARCHIVE_OUTPUT_NAME      "cldi-head-${LIBSTAMP}"
	)

	#set_target_properties(cldi_core PROPERTIES
	#VERSION ${PROJECT_VERSION}
	#LIBRARY_OUTPUT_DIRECTORY "bin"
	#ARCHIVE_OUTPUT_DIRECTORY "bin"
	#LIBRARY_OUTPUT_NAME      "cldi-core.${LIBSTAMP}"
	#ARCHIVE_OUTPUT_NAME      "cldi-core.${LIBSTAMP}"
	#)
endif()
