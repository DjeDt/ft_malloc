#!/bin/bash

OS=$(uname -s)
if [ "${OS}" == "Linux" ] ; then
    export LD_PRELOAD=/home/dje/Dev/ft_malloc/libft_malloc_x86_64_Linux.so
    $@
else
#	env DYLD_LIBRARY_PATH="." DYLD_INSERT_LIBRARIES="libft_malloc.so" DYLD_FORCE_FLAT_NAMESPACE=1 $@
#	exit
    export DYLD_LIBRARY_PATH="/Users/ddinaut/Desktop/Dev/ft_malloc"
    export DYLD_INSERT_LIBRARIES="libft_malloc.so"
    export DYLD_FORCE_FLAT_NAMESPACE=1
    $@
fi
