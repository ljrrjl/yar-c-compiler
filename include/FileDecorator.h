#pragma once
#include "File.h"
#include <memory>
class FileDecorator : public File
{
public:
	FileDecorator(const std::shared_ptr<File>& file) : _file(file){}
	virtual ~FileDecorator(){}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual bool open() override{ return _file->open(); }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { return _file->write(sentence); }
protected:
	std::shared_ptr<File> _file;
};

class HeaderFileDecorator : public FileDecorator
{
public:
	HeaderFileDecorator(std::shared_ptr<File> file):FileDecorator(file){}
	virtual bool open() override { 
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#pragma once"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open();_file->write(sentence); }
	virtual ~HeaderFileDecorator() { }
};

class SourceFileDecorator : public FileDecorator
{
public:
	SourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {}
	virtual bool open() override {
		return _file->open();
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { return _file->write(sentence); }
	virtual ~SourceFileDecorator() {}
};
