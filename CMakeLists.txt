cmake_minimum_required (VERSION 3.18)

SET(TARGET "embedded-gfx")

project (
  embedded-gfx
	VERSION 0.1 
  DESCRIPTION "${TARGET}"
	LANGUAGES C CXX ASM)

option(EMBEDDED_GFX_BUILD_EXAMPLES "Build examples" ON)

add_library(${TARGET} INTERFACE)
target_compile_features(${TARGET} INTERFACE cxx_std_17)
target_include_directories(${TARGET} INTERFACE
  include
)
target_sources(${TARGET}
  INTERFACE
    "include/Canvas.hpp"
    "include/Drawable.hpp"
    "include/Vector2D.hpp"
    "include/Shape.hpp"
    "include/Line.hpp"
    "include/Ellipse.hpp"
    "include/Circle.hpp"
)


if(EMBEDDED_GFX_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(EMBEDDED_GFX_BUILD_EXAMPLES)
