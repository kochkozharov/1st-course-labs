#!/usr/bin/env bash
DIR=${1:-'.'}
HELP='unique_suffix.sh [DIR] finds and counts all of the distinct file suffixes in a [DIR] recursively. Default [DIR] is a current directory.'
case "$1" in
    -h) echo $HELP;;
    --help) echo $HELP;;
    *) find $DIR -name '*?.*' -type f -exec basename "{}" \; | rev | cut -d'.' -f1 | rev | sort | uniq -c | sort -rn ;;
esac
