#!/bin/sh

set -xe
CFLAGS = "-Wall -Wextra `pkg-config --cflags raylib`"
LIBS = "`pkg-config --libs raylib` -lglfw -lm -ldl -lpthread"

clang $CFLAGS -o music_visualizer main.c $LIBS
