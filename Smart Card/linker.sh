#!/bin/bash

declare -a array_files=( 
"bin" 
"obj" 
)

mkdir ${array_files[@]} 2> /dev/null 

unset array[@]
