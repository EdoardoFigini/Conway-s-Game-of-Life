# Conway's Game of Life
[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) implemented in C.

## Usage:
###Compiling:
```bash
$ gcc Resources/err.c gameoflife.c -o gameoflife
```

###Execution:
Recieves x dimension, y dimension, input seed text file, number of generations and mode as arguments
```console
$ ./gameoflife 23 23 seed.txt 10 0
```

- **x dimension**: int
- **y dimension**: int
- **input seed file**: string (filename or path to file)
- **n of generations**: int (if 0 simulation never stops)
- **mode**: int (0 automatic, 1 step)
