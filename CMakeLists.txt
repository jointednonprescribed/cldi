
cmake_minimum_required(VERSION 3.10)
project(cldi VERSION 25.0.0.0 LANGUAGES C CXX)

option(BUILD_STATIC "Build into static libraries instead of dynamic libraries (default: OFF)." OFF)
option(BUILD_CXX "Build using the C++ library (default: ON)." ON)
option(ONEFILE "Build into a single shared or static library file (default: OFF)." OFF)
set(STD "17" CACHE STRING "The version of the C or C++ Standard to compile with (default: 17)")

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
	else()
		file (GLOB_RECURSE SRC "stdlib/head-layer/lib/c/*.c" "stdlib/core-layer/lib/c/*.c")
		if(BUILD_STATIC)
			add_library(libcldi STATIC ${SRC})
		else()
			add_library(libcldi SHARED ${SRC})
		endif()
	endif()

	set_target_properties(
		libcldi
		VERSION ${PROJECT_VERSION}
		LIBRARY_OUTPUT_DIRECTORY bin
		ARCHIVE_OUTPUT_DIRECTORY bin
		LIBRARY_OUTPUT_NAME      cldi.${LIBSTAMP}
		ARCHIVE_OUTPUT_NAME      cldi.${LIBSTAMP}
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
	endif()

	#target_link_libraries(cldi_core cldi_head)

	set_target_properties(cldi_head PROPERTIES VERSION ${PROJECT_VERSION} LIBRARY_OUTPUT_DIRECTORY bin ARCHIVE_OUTPUT_DIRECTORY bin LIBRARY_OUTPUT_NAME cldi-head-${LIBSTAMP}  ARCHIVE_OUTPUT_NAME cldi-head-${LIBSTAMP})

	#set_target_properties(cldi_core PROPERTIES VERSION ${PROJECT_VERSION} LIBRARY_OUTPUT_DIRECTORY bin ARCHIVE_OUTPUT_DIRECTORY bin LIBRARY_OUTPUT_NAME "cldi-core.${LIBSTAMP}"  ARCHIVE_OUTPUT_NAME "cldi-core.${LIBSTAMP}")
endif()
