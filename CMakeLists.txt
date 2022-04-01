project(yar-c-protoc)
cmake_minimum_required(VERSION 3.18)
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
)

install(TARGETS yar-c-protoc DESTINATION bin)
