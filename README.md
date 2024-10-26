# Game of Life

A C++ implementation of Conway's Game of Life.


## About the Project

The **Game of Life** is a zero-player cellular automaton game devised by mathematician John Conway. In this C++ implementation, the grid of cells follows Conway's four rules to evolve each generation. Despite the simplicity of these rules, the system can demonstrate complex and varied behaviors.

### Rules of the Game

1. **Underpopulation**: Any live cell with fewer than two live neighbors dies.
2. **Survival**: Any live cell with two or three live neighbors survives to the next generation.
3. **Overpopulation**: Any live cell with more than three live neighbors dies.
4. **Reproduction**: Any dead cell with exactly three live neighbors becomes a live cell.

---

## Getting Started

### Prerequisites

To compile and run this project, you’ll need:
- A **C++11** (or later) compiler
- A **terminal** or **command line** environment for running the program
- Optionally, **CMake** to streamline the build process

### Installation

1. **Clone the Repository**
   - Use Git to clone the repository from your GitHub account.
2. **Build the Project**
   - Build using a C++ compiler or configure with CMake if preferred.
3. **Run the Program**
   - Launch the executable in your terminal or command line environment.

---

## Usage

Upon launching, the Game of Life will simulate cellular automaton based on a grid defined within the code. Cells live, die, or reproduce each generation according to Conway's rules.

### Controls

- **Start/Stop Simulation**: Typically, the simulation begins immediately. If you've added interactive controls, specify here (e.g., pressing a key to start or stop).
- **Advance Generation**: Some versions allow you to step through generations manually.
- **Reset**: This could reset the grid if implemented.

## Examples

Here are some classic patterns seen in Conway's Game of Life:

### 1. Still Lifes (Static Patterns)

Patterns that do not change over generations because they are stable.

**Examples**: 
- **Block**: A 2x2 square that remains static.
- **Beehive**: A hexagonal shape that remains static.

**Image Example**:

![Block and Beehive Still Lifes](https://github.com/user-attachments/assets/45191e86-e281-4ad5-9c9a-ba085fd048bd)


---

### 2. Oscillators (Repeating Patterns)

Patterns that repeat after a fixed number of generations.

**Examples**: 
- **Blinker**: A line of three cells that oscillates between vertical and horizontal.
- **Toad**: A pattern of six cells that oscillates between two shapes.

**Image Example**:

![image](https://github.com/user-attachments/assets/ef7afedc-2f3f-4af0-ac8b-2521d5c9b9a4)


---

### 3. Spaceships (Moving Patterns)

Patterns that travel across the grid over time.

**Examples**:
- **Glider**: A pattern that moves diagonally across the grid.
- **Lightweight Spaceship (LWSS)**: A pattern that moves horizontally across the grid.

**Image Example**:

![Glider and LWSS Spaceships](https://upload.wikimedia.org/wikipedia/commons/3/37/Glider_and_lwss.gif)

---

### 4. Complex Patterns

More elaborate configurations that produce fascinating, long-lasting structures.

**Examples**: 
- **Gosper Glider Gun**: A pattern that produces a continuous stream of gliders.

**Image Example**:

![Gosper Glider Gun](https://upload.wikimedia.org/wikipedia/commons/e/e5/Gospers_glider_gun.gif)

---

### Example of a Simulation

Here’s a step-by-step example showing the evolution of a **Glider**:

1. **Generation 1**: Initial configuration of a glider in the top-left corner of the grid.
2. **Generation 2**: The glider shifts one cell diagonally.
3. **Generation 3**: The glider continues moving diagonally.

**Image Example**:

![Glider Progression](https://upload.wikimedia.org/wikipedia/commons/f/f2/Game_of_life_animated_glider.gif)

---

## Features

- **Grid-based Simulation**: Runs Conway’s rules across a configurable grid.
- **Customizable Initial Patterns**: Easily modify the starting configuration.
- **Multiple Patterns Supported**: Test patterns like still lifes, oscillators, and spaceships.

---

## Contact

**Georgi Lazov** - georgilazov04@gmail.com

---
