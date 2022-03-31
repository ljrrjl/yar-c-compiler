#pragma once
#include <string>
#include <fstream>

class File
{
public:
	File(){}
	File(const std::string& filename) : _filename(filename){}
	virtual bool open() {}
	virtual void close() {}
	virtual bool is_open() {}
private:
	std::fstream _filestream;
	std::string _filename;
};