project(yar-c-protoc)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
include_directories(
	./include
)

add_executable(yar-c-protoc
	src/FileManager.cc
	src/IdentifierMagager.cc
	src/SymbolTable.cc
	src/TokenQueue.cc
	src/yar_protoc.tab.cc
	src/lex.yy.cc
	src/Sentence.cc
	src/GeneratorFactory.cc
	src/File.cc
	src/SymbolGenerator.cc
	src/PropertyGenerator.cc
	src/ClientGenerator.cc
	src/Context.cc
)

install(TARGETS yar-c-protoc DESTINATION bin)
