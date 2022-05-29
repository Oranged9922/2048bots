# 2048

### Author of the product: 

Lukáš Salak

------

### Semestral work for class 

NPRG041

------

### Revision 

* 19.11.2021 - Lukáš Salak, created the document
* 19.11.2021 - Lukáš Salak, version 0.1.0.
* 21.11.2021 - Lukáš Salak, added deadline dates
* 21.11.2021 - Lukáš Salak, version 0.1.1.
* 27.04.2022 - Lukáš Salak, added todo, changed deadline date
* 27.04.2022 - Lukáš Salak, version 0.2.0.


------

### Product goal:

Create a console application that will allow user to play well-known game 2048 ( https://play2048.co/), but allowing user to upscale the game from `4*4`  to `n*n` with ability to let the game itself try to reach maximum score. 

------

### Functional description:

​	Console argument interface:

* `--help`(provides list of all parameters)

* `-d x, y` (-d as dimensions of 2D grid (rows, cols))

* `-pmode (autoplay1,...,autoplayN, player)` (sets mode of the game - whether an heuristic algorithm should play or if player wants to play)

* `-allowHints (0 / 1)`(sets hint for next move (calculated with default heuristic algorithm))

* **TODO** - other arguments tbd (if necessary)

    

    **TODO** : 

    -   cli parser (external lib)
    -   polymorphism (rewrite bots class)
    -   implement three more bots
    -   evaluation of bots
    -   add test framework

------

### User interface

The game will be displayed in console as a grid of rows and columns with aligned values of individual cells. 

*Controls*: Keyboard keys `W,S,A,D` and/or `arrow keys` respectively.

------

### Functional requirements

* use of console and handling display of current game and / or other values (like current score, selected heuristics etc.)
* handling user input
* a way of implementing  and adding different algorithms for solving the game
* ability to handle large grids for bigger `x,y` parameters
* check for overflow of big numbers and computing with bigger numbers
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
