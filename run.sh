#!/bin/bash

OS=$(uname -s)
if [ "${OS}" == "Linux" ] ; then
    export LD_PRELOAD=/home/dje/Dev/ft_malloc/libft_malloc_x86_64_Linux.so
    $@
else
    export DYLD_LIBRARY_PATH="."
    export DYLD_INSERT_LIBRARIES="libft_malloc.so"
    export DYLD_FORCE_FLAT_NAMESPACE=1
    $@
fi
