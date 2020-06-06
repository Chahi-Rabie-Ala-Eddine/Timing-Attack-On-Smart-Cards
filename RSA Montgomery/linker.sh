#!/bin/bash

declare -a array_files=( 
"bin" 
"obj" 
"obj/header" 
"obj/cpp" 
)

mkdir ${array_files[@]} 2> /dev/null 

unset array[@]
