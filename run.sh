#!/bin/bash

# Compile the C++ program
g++ s.cpp -lglut -lGL -lGLU

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the program
    ./a.out
else
    echo "Compilation failed."
fi
