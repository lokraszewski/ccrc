#!/bin/sh

main(){
    local SEARCH_PATH=$(pwd)

    # A POSIX variable
    OPTIND=1         # Reset in case getopts has been used previously in the shell.

    while getopts "h?p:" opt; do
        case "$opt" in
        h|\?)
            show_help
            exit 0
            ;;
        p)  SEARCH_PATH=$OPTARG
            ;;
        esac
    done

    shift $((OPTIND-1))

    echo "Looking for tests in ${SEARCH_PATH}"
    find "${SEARCH_PATH}" -executable -type f -iname "*_test" -exec {} \;
    echo "All tests done!"
}

set -e

main "$@"