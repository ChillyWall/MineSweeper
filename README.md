# Minesweeper

A minesweeper game written in C++, which provides two UIs: a console based UI,
and a Qt-GUI based UI.

## Requirements

- Qt base 6 for the GUI module.

## Build

To build the project, you can use the provided `CMakeLists.txt` file. Here is,
an example of how to build the project:

```bash
$ cmake -B build .
$ cmake --build build
# install to /usr/local for default
$ sudo cmake --install build
# run the console based one
$ Minesweeper
# run the GUI based one
$ Minesweeper-qt
```

## How to play

### TUI version

First type three integers, separated by spaces, which are the height, weight,
and the count of mines.

Then follow the guidance to type two integers as coordinates, and then select
the operation you want to take on this cell. 0 to sweep, and 1 to flag.

To flag twice on the same cell will unflag it. To sweep a swept cell will reveal
the cells around if there are already enough flags around this cell.

Flag all mines and sweep all non-mine cells to win the game. Sweep a mine cell
to lose the game.

### GUI version

Just the same with other minesweeper game.
