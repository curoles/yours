#!/bin/bash

BASE=$(realpath $(dirname "${BASH_SOURCE[0]}"))
CWD=`pwd`

echo "Initialize build directory $CWD"
echo "Source base: $BASE"

BUILD_SBT=build.sbt
echo Generating $BUILD_SBT
echo "baseDirectory := file(\"$BASE/code\")" > $BUILD_SBT
echo >> $BUILD_SBT
echo "target := file(\"$CWD/target\")" >> $BUILD_SBT
echo >> $BUILD_SBT
cat $BASE/code/build.sbt >> $BUILD_SBT

MAKE_FILE=Makefile
echo Generating $MAKE_FILE
echo "BASE := $BASE" > $MAKE_FILE
echo "include $BASE/code/Makefile" >> $MAKE_FILE
