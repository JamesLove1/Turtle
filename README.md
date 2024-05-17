# Turtle
A parser that checks if an imputed TTL file conforms to the given grammar. As well as an Interpreter to handle the logic of these files and output them to a desired format. This was then followed by an extension which gives the user a way to visually create their own TTL files.  

Project Gramma in <a href="https://raw.githubusercontent.com/JamesLove1/Turtle/main/grammar.txt" target="_blank"> BNF</a>  form

## Getting Started

These instructions will provide you with a copy of the project and get them running on your local machine for development and testing purposes.


### Prerequisites

- GCC
- Clang
- Valgrind 

### Installing

Follow these steps to get the development environment running:

1. Clone this repository using `git clone https://github.com/JamesLove1/Turtle.git`.
2. Navigate to the project directory using `cd Turtle`.

### Compiling
Run `make all` to compile the project.

### Using the Parser

replace FILE with a .ttl file found with the TTLs Dir
Run `make ./parse_s TTLs/FILE.ttl` to parse a TTL file.

### Using the Interpreter

Replace FILE with a .ttl file found with the TTLs Dir <br>
Run `./interp_s TTLs/FILE.ttl` <br>
If no output is specified the code will output to the terminal.

For .txt output replace OUTPUT_FILE.txt with the name of the file you wish to output. <br>
Run `./interp_s TTLs/FILE.ttl OUTPUT_FILE.txt` <br>

For .ps output replace OUTPUT_FILE.ps with the name of the file you wish to output. <br>
Run `./interp_s TTLs/FILE.ttl OUTPUT_FILE.ps`

### Using the Extension

1. Compile code e.g. `Make extension_s` 

2. Run executable with place holder TTL file and .ttl out file e.g. <br>
` ./extension_s ./TTLs/turn.ttl ./out_Extension.ttl`

3. Use the instructions within the program to operate the terminal

4. Check the outputted TTL file (The file can be passed to the `./interp_s file`).

## Acknowledgments

This is an assignment given by the instructor at the University of Bristol: [Neil](https://github.com/csnwc) from the Programming in C course.
