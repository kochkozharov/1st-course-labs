#!/usr/bin/env bash
DIR=${1:-'.'}
HELP='unque_suffix.sh finds and counts all of the distinct file suffixes in a folder recursively. Default folder is a current folder.'
case "$1" in
    -h) echo $HELP;;
    --help) echo $HELP;;
    *) find $DIR -name '*?.*' -type f -exec basename "{}" \; | rev | cut -d'.' -f1 | rev | sort | uniq -c | sort -rn ;;
esac
