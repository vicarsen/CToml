cmake_minimum_required(VERSION 3.11)

project(
  CToml
	VERSION 0.0.1
  DESCRIPTION "A basic toml parser written in C."
	LANGUAGES C
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	
	set(CMAKE_C_EXTENSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()

endif()

include(FetchContent)

add_subdirectory(libs)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CTOML_BUILD_TESTING) AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

