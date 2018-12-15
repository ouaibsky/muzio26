#!/bin/bash

DIR="${PWD}/tmp/muzio26"
mkdir -p "${DIR}"
cp -f include/*.h  "${DIR}/"
cp -f src/muzio26.cpp  "${DIR}/"muzio26.ino

echo "Generate ArduinoIDE project in '${DIR}' done"

