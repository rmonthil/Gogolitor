cmake_minimum_required(VERSION 2.8.12)
project(gogolitor)

add_subdirectory(pybind11)

file(GLOB SRCS
	"modules/*.cpp"
	)

file(GLOB HEADERS
	"modules/*.h"
	)

pybind11_add_module(gogolitor python_bindings.cpp ${SRCS} ${HEADERS})
