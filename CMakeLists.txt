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
    "include/EmbeddedGfx/Canvas.hpp"
    "include/EmbeddedGfx/Vector2D.hpp"
    "include/EmbeddedGfx/Drawable.hpp"
    "include/EmbeddedGfx/Shape.hpp"
    "include/EmbeddedGfx/Line.hpp"
    "include/EmbeddedGfx/Polygon.hpp"
    "include/EmbeddedGfx/Ellipse.hpp"
    "include/EmbeddedGfx/Circle.hpp"
    "include/EmbeddedGfx/Triangle.hpp"
)


if(EMBEDDED_GFX_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(EMBEDDED_GFX_BUILD_EXAMPLES)
