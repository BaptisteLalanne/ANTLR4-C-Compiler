# PLD-Compilateur
[![CI PLD Compilateur](https://github.com/BaptisteLalanne/PLD-Compilateur/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/BaptisteLalanne/PLD-Compilateur/actions/workflows/ci.yml)
## Description

A C-like compiler, programmed in C++ with ANTLR4. The compiler only generates x86 ASM code.

## Getting started

First, download the entire repository :
```sh
$ git clone https://github.com/BaptisteLalanne/PLD-Compilateur.git c_comp
```

### Build

We use a Makefile to build the binary. ANTLR4 lib is included in repository. \
Build was tested with Ubuntu 20 and forks (PopOS, Debian 11).

The Makefile is in `compiler` directory, so we open a shell inside :
```sh
$ cd c_comp/compiler
```

Commands for Makefile are:
- `make`: build binary,
- `make clean`: delete binary and built object files,
- `make re`: delete binary, built object files, then rebuild the project,
- `make gui`: generate parse tree code.

Once built, an executable `ifcc` can be found in current directory.

### Run

To get x86 asm code for your c-like program, go to `compiler` directory and run :
```sh
$ ./ifcc your_input_file.c 
```

If you want to add our optimization methods, you can add the `-o` parameter :
```sh
$ ./ifcc -o your_input_file.c 
```

To launch your c-like program, you can use `runner.sh` script, in `compiler` directory :
```sh
$ ./runner.sh your_input_file.c
```

### Tests

A python script launch all the C-like test files.

In `tests` directory, simply type :
```sh
$ python3 ifcc-test.py testfiles
```

The script run our binary with c-like file as input, do the same with a legit c compiler (i.e.: gcc), and then compare results.

For each test, there is four possibles cases :
- TEST OK,
- TEST FAIL (your compiler accepts an invalid program),
- TEST FAIL (your compiler rejects a valid program),
- TEST FAIL (your compiler produces incorrect assembly).

### Memory leaks

A python script launch `valgrind` for all the C-like test files.

In `tests` directory, simply type :
```sh
$ python3 ifcc-valgrind.py testfiles
```

The script run valgrind with our binary on very c-like file as input. As ANTLR4 parser involves memory leaks when a syntax error is encountered, a test file which doesn't compile is not analyzed with valgrind (we "skip" it).

For each test, there is three possibles cases :
- TEST OK,
- TEST INVALID
- TEST SKIPPED

## Authors

Tom PERRILLAT-COLLOMB \
Laetitia DODO \
Baptiste LALANNE \
Bastien BARBE \
David TOMA \
Loann LARGERON \
Arthur DURAND \
Amine LBATH


