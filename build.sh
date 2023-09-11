#!/bin/bash

docker run \
    -v `pwd`:/app \
    -ti \
    raylib \
    /bin/bash -c "cd ${1} && make clean && make"
