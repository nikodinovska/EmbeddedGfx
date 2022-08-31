cmake_minimum_required (VERSION 3.18)

set(TARGET canvas-console)

add_executable(${TARGET})
target_compile_options(${TARGET} PUBLIC -Wall -Wextra -pedantic)
target_sources(${TARGET}
  PRIVATE
    canvas.cpp
)
target_link_libraries(${TARGET} PRIVATE embedded-gfx)
