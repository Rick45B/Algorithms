# Algorithms
## Description
An expanding collection of algorithms and ADT's completely written in C and requiring no dependencies.
## Project structure
Inside the **src** folder of the project, there are a variety of sub-folders, each containing the source code implementation of each class of algorithms (all their headers can be found inside the **includes** subfolder).<br>
For each class of algorithms, three folders can be found: **build**, **src** and **Tests**.
* The **Tests** folder contains the source code implementation of the tests used for checking the implementation of methods (and for sanity checks).
* the **src** folder contains the source code implementation of the methods of that class of algorithms.
* the **build** folder contains the makefile needed to compile (as for now all the makefiles are for gcc ONLY!) the source code into .o files.<br><br>

Inside the **includes** sub-folder of the project, all the header files are located. "Rick45B-AlgorithmsADT.h" contains the specification of much of the metods and objects used, as well as a small standardized API for every single method, while "Rick45B-Utils.h" contains the specification of all the methods of the Utils module, which are used to implement some features needed by "Rick45B-AlgorithmsADT.h" and its associated source files.

## Available algorithms/ADT's
The library currently supports the following ADT's: lists, stack, queues, basic BST.

## Installation and usage
Compile all the source files using the various makefiles contained inside the **build** folders of every class of algorithms. After that, use the library according to the API contained in the header files under the **includes** folder.

## Features
* Error retrieval using the 'RICK45B_GetError()' function.
* Standardized API.
* Test-rich implementation using asserts inside the **Tests** folders.
* Heavily debugged against memory-leaks, no leaks seems to be present as for now.
* stddef.h aside, the library doesn't necessarily need any standard C libraries.
* Client can decide which allocation/deallocation functions the library will be using.

## TODO
There are a lot of things to do, as this is a very immature project:
* Adding algorithms of the various ADT's implemented.
* Completing the BST ADT's
* Adding graphs and their algorithms.

## LICENSE
The project is licensed under the MIT license.
