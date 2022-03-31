#pragma once
#include "File.h"
#include <memory>
class FileDecorator : public File
{
public:
	FileDecorator(std::shared_ptr<File> file): _file(file){}
	virtual ~FileDecorator(){}
	virtual bool open() override{ _file->open(); }
	virtual void close() override { _file->close(); }
	virtual bool is_open() override { _file->is_open(); }
protected:
	std::shared_ptr<File> _file;
};

class HeaderFileDecorator : public FileDecorator
{
public:
	HeaderFileDecorator(std::shared_ptr<File> file):FileDecorator(file){}
	virtual bool open() override { 
		_file->open();
		//Ð´Èë#pragma once
	}
	virtual void close() override { _file->close(); }
	virtual bool is_open() override { _file->is_open(); }
	virtual ~HeaderFileDecorator(){}
};