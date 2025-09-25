#!/bin/bash
# filename.bash
# Logan Fossenier & William Morris
# hzv143 & wjm625
# 11343891 & 11278140
# CMPT332 Fall 2025

# os name for windows check
os=$(uname -s)

# File name for partA1 through partA4
version=$1

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 {partA1|partA2|partA3|partA4}"
  exit 1
fi

case $version in
  partA1)
    # check if running on Windows
    case $os in
      CYGWIN*|MINGW*|MSYS*)
        ;; # okay
      *)
        echo "Error: $version can only be run on WINDOWS (detected $os)"
        exit 1
        ;;
    esac
    ;;
  *)
    ;;
esac

# function to check integer validity                                            
is_valid_int() {                                                                
    [[ "$1" =~ ^[0-9]+$ ]]                                                      
} 

while true; do
    # -t checks is input is coming from terminal eg ./partB.bash partA#
    if [ -t 0 ]; then
        # prompt only shows if running interactively
        echo "Enter 3 non-negative integers (or 'q' to quit):"
    fi
    
    # skips if executed like : ./partB.bash partA# < input.txt

    read -r a b c || break  # exit loop on EOF

    if [[ "$a" == "q" || "$b" == "q" || "$c" == "q" ]]; then
        echo "Exiting."
        break
    fi

    # Validate input
    if ! is_valid_int "$a" || ! is_valid_int "$b" || ! is_valid_int "$c"; then
        echo "Invalid input: all arguments must be non-negative integers"
        continue
    fi

    # Run executable
    ./"$version" "$a" "$b" "$c"
done


