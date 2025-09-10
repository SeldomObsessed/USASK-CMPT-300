#!/bin/bash
#  Name: Fossenier, Logan
#  NSID: hzv143
#  Student Number: 11343891

# Verify there is exactly one argument
if [ "$#" -ne 1 ] ; then
  echo "Invalid usage: must provide exactly one argument" >&2; exit 1
fi

# Verify the argument is a number
# https://stackoverflow.com/questions/806906
re='^[0-9]+$'
if ! [[ $1 =~ $re ]] ; then
  echo "Invalid usage: must provide an integer as the argument" >&2; exit 1
fi

# Check the architecture, and run the appropriate executable
case "$(uname -m)" in
  x86_64)
    ./sample-linux "$1"
    ;;
  armv7l)
    ./sample-linux-arm "$1"
    ;;
  ppc)
    ./sample-linux-ppc "$1"
    ;;
  *)
    echo "Hmm, this isn't an expected machine architecture" >&2; exit 1
    ;;
esac

