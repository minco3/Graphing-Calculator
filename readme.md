# Graphing Calculator
Dynamic graphing calculator using SFML, RPN and shunting yard

## Description

Uses RPN and shunting yard to parse expressions and graph them

### Features

#### What you can graph

- binary operators (+-/*)
- exponents (^)
- parentheses
- unary negation (-)
- sin/cos/tan
- arcsin/arccos/arctan
- log
- sqrt

#### Shortcuts

- `ENTER` Open text box or submit expression
- `Ctrl 0` Reset camera
- `Ctrl +, Ctrl -` Zoom in/out
- `Arrow keys` Move the camera
- `Scroll wheel` Dynamic zoom in/out to where your cursor is

#### Expression List Features

- `Mouse1` on an expression to randomize its color
- `Mouse2` on an expression to remove it from the list and the graph
- You can resize the expression list by dragging the line between the graph and the expression list

## What I Learned

#### Linked Lists
- Stack and Queue classes
- Iterators

#### Window Manager
- SFML
- Draw calls using objects
- Views
- Zoom/pan using mouse events
- Synchronized updating of components
- Resizing

#### Parsing
- Parsing operations from a string
- RPN and shunting yard

## Screenshots

![view of a graph with a few functions](/images/graphing_calculator.png)
![detailed view of a graph with a few functions](/images/graphing_calculator_detail.png)

## Known issues

- Resising Expression list after resizing window doesnt use the correct location
- Random crashing when parsing expressions

## Getting Started

### Dependencies
- CMake
- SFML

### Setup

#### simple setup with CMake and GCC

```
mkdir build
cd build
cmake .. -G "Unix Makefiles"
cmake --build . --target main
main
```