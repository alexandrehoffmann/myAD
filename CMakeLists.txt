cmake_minimum_required(VERSION 3.1)

project(myAD VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "Lightweigh HP finite-element library")

set(CMAKE_VERBOSE_MAKEFILE 0)

########################################################################
####                             Build                              ####
########################################################################

set(HEADERS
	include/Forward/Var.hpp
	include/Forward/Var.tpp
	#
	include/Reverse/Var.hpp
	include/Reverse/VarGraph.hpp
	include/Reverse/Var.tpp
	include/Reverse/VarGraph.tpp
	#
	include/ReverseOnForward/Var.hpp
	include/ReverseOnForward/Var.tpp
)

# Declare the library target.
add_library(${PROJECT_NAME} SHARED ${HEADERS})

# Configure compiler options.
target_compile_options(${PROJECT_NAME} PRIVATE -Wundef -Wvarargs -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self -flax-vector-conversions -pedantic -pedantic-errors)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Link dependencies. (NONE)

# Configure the directories to search for header files.
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Set the version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Set the shared object version property to the project's major version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

########################################################################
####                          Installation                          ####
########################################################################

# For access to standard installation directory variables (CMAKE_INSTALL_xDIR).
include(GNUInstallDirs)

# Set library shared object file to install.
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set library API header file to install.
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

########################################################################
####                    pkg-config Installation                     ####
########################################################################

# Create the pkg-config file from the template.
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

# Set pkg-config file to install.
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
