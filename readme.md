# EmbeddedGfx

The goal of this project is to provide optimized and easy to use graphics library which allows drawing of basic shapes and text rendering, which can be used for display in embedded projects.

## Features

- Header-only library
- Does not use dynamic allocation
- Multiple color modes:
  - Black and white
  - RGB565
  - RGB666
  - RGB888
  - Other color modes can be added manually, refer to the section `Colors` below.
- Two types of canvas:
  - **Buffered canvas**, which includes buffer(matrix) that contains the current state of the canvas.
  This type canvas can be used for small displays, for example small OLED displays.
  - **Unbuffered canvas**, which doesn't include buffer that contains the current state of the canvas.
  This type of canvas can be used for large displays, for example TFT LCDs.
- Includes `Page` mode which is useful for OLEDS based on SSD1306 or similar drivers.

## Requirements

- C++17 compiler
- CMake 3.18 or greater

## Colors

Multiple color modes are already provided for the user, including black and white mode and multiple RGB modes.
Custom color modes can be added by the user by creating custom types that have the function `getValue()` implemented and the alias `Type` for its return type.

## How to use

Refer to the examples.

## Examples

All the examples are stored in the `examples` folder.

To build the examples, ensure that the CMake cache variable `EMBEDDED_GFX_BUILD_EXAMPLES` is set to `ON`.