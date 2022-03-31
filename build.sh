#!/bin/bash

if [ -d build  ]
then
	rm -rf build
fi
mkdir build
cd lex
bison -d yar_protoc.y
if [ $? -ne 0 ]
then
	echo "fail bison"
	exit 1
fi
mv yar_protoc.tab.c ../src/yar_protoc.tab.cc
mv yar_protoc.tab.h ../include
lex yar_protoc.lex
if [ $? -ne 0 ]
then
	echo "fail lex"
	exit 1
fi
mv lex.yy.c ../src/lex.yy.cc
cd ..
cd build
if [ $# -eq 1  ]
then
	cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$1 ..
else
	cmake -DCMAKE_BUILD_TYPE=Debug ..
fi
make
make install
cd ..
rm include/yar_protoc.tab.h
rm src/yar_protoc.tab.cc src/lex.yy.cc
echo "success"
