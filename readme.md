# 2048

### Author of the product: 

Lukáš Salak

------

### Semestral work for class 

NPRG041

------

### Product goal:

Create a console application that will allow user to play well-known game 2048 ( https://play2048.co/), but allowing user to upscale the game from `4*4`  to `n*n` with ability to let the game itself try to reach maximum score. 

------

### Functional description:

​	Console argument interface:

-   With no arguments, the game starts with default values (4x4, goal to reach 2048, human input)

* `--help`(provides list of all parameters)

* `--sizeX`, `--sizeY` (dimensions of 2D grid (rows, cols)), default 4x4

* `-max` (set max tile for win condition), default 2048

* `--comparison-repeat` starts bots comparison, takes integer for how many runs to repeat every bot play (for changing parameters and/or adding new bots to test, change `run_comparison(int repeat)` function)

      

### User interface

The game will be displayed in console as a grid of rows and columns with aligned values of individual cells. 

*Controls*: Keyboard keys `W,S,A,D` and/or `arrow keys` respectively.

------

### Revision 

* 19.11.2021 - Lukáš Salak, created the document
* 19.11.2021 - Lukáš Salak, version 0.1.0.
* 21.11.2021 - Lukáš Salak, added deadline dates
* 21.11.2021 - Lukáš Salak, version 0.1.1.
* 27.04.2022 - Lukáš Salak, added todo, changed deadline date
* 27.04.2022 - Lukáš Salak, version 0.2.0.
* 30.04.2022 - Lukáš Salak, version 1.0.0


------

### Functional requirements

* use of console and handling display of current game and / or other values (like current score, selected heuristics etc.)
* handling user input
* a way of implementing bots - inline header `bots.h` where bots are implemented, all bots must inherit from `bot` class and implement `int getMove(game& g)` function that returns `0,1,2,3` (right, up, left, down accordingly)
* ability to handle large grids for bigger `x,y` parameters
* score counter

------

### Data inputs

* User input and setting parameters (if desired different from default)

------

### Notes to resolve

* OS dependency (handling console? win/linux differences)

------

### Deadline

* April 30th 2022 -> Deadline for the first submission attempt
* May **28th** 2022 -> Deadline for the last submission attempt including all fixes.
