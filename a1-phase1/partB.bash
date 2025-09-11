#!/bin/bash
# filename.bash
# Logan Fossenier & William Morris
# hzv143 & wjm625
# 11343891 & 11278140
# CMPT332 Fall 2025


if [[ $# -ne 1 }}; then
  echo "Usage: $0 {partA1|partA2|partA3|partA4}"
  exit 1
fi

# File name for partA1 through partA4
version=$1

case $version in
  partA1)
    #check if running in WINDOWS
      case $os in
        CYGWIN*|MINGW*|MSYS*)
         ;;
        # if on WINDOWS compatible with BASH, do nothing, else: throw a fit 
        *)
          echo "Error: $version can only be run on WINDOWS (detected by $os)"
          exit 1
          ;;
      esac
      ;;
  partA2|partA3|partA4)
    #if valid do nothing, otherwise throw a fit
    ;;
  *)
    echo "Invalid version: $version"
    exit 1
    ;;
esac

while read -r a b c; do
  ./"$version" "$a" "$b" "$c"
done
