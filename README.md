# Minesweeper

A minesweeper game written in C++, which provides two UIs: a console based UI,
and a Qt-GUI based UI.

## Requirements

- Qt base 6 for the GUI module.
- A Nerd Font for the console based UI.

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

## Troubleshooting

### (Windows) qt.qpa.plugin: Could not find the Qt platform plugin "windows" in ""

This is caused by the missing of the platform plugin. You can solve this by
manually copying `platforms/qwindows.dll`, `iconengines/qsvgicon.dll` to the
`plugins` directory where the executable file is, or uncomment the lines in
`src/qt_ui/CMakeLists.txt` and fill in the correct path to the Qt installation.

The two .dll files can be found in the plugins directory under Qt installation
directory, which is usually `C:/Qt/6.x.x/mingw_64`

It would look like this:

- MineSweeper
- Minesweeper-qt
- Qt6Core.dll
- Qt6Gui.dll
- Qt6Svg.dll
- Qt6Widgets.dll
- plugins
  - platforms
    - qwindows.dll
  - iconengines
    - qsvgicon.dll

### (Windows) Not displaying anything

Use the mingw-w64 installed with Qt to compile the project, which is usually
in `C:/Qt/Tools/mingwxxxx_64`

### (Windows) Not properly show the characters in console

This is usually caused by the encoding and the missing of the nerd font. Set the
encodings of the console to UTF-8, and set a nerd font as the console's font.
