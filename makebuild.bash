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

RUN_FILE=run
echo Generating $RUN_FILE
echo "YOURS_CLASSES=target/scala-2.11/classes/" > $RUN_FILE
echo "TYPESAFE=/home/igor/.ivy2/cache/com.typesafe/config/bundles/config-1.3.0.jar" >> $RUN_FILE
echo "AKKA=/home/igor/.ivy2/cache/com.typesafe.akka/akka-actor_2.11/jars/akka-actor_2.11-2.4.7.jar" >> $RUN_FILE
echo "scala -cp \$YOURS_CLASSES:\$AKKA:\$TYPESAFE Yours \$@" >> $RUN_FILE
