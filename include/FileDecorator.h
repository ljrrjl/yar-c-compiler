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

class MessageHeaderFileDecorator : public FileDecorator
{
public:
	MessageHeaderFileDecorator(std::shared_ptr<File> file):FileDecorator(file){}
	virtual bool open() override { 
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#pragma once\n"));
			_file->write(std::make_shared<Sentence>("#include <stdint.h>\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open();_file->write(sentence); }
	virtual ~MessageHeaderFileDecorator() { }
};

class MessageSourceFileDecorator : public FileDecorator
{
public:
	MessageSourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#include <stdlib.h>\n"));
			_file->write(std::make_shared<Sentence>("#include <string.h>\n"));
			_file->write(std::make_shared<Sentence>("#include \"message.h\"\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~MessageSourceFileDecorator() {}
};

class ServiceHeaderFileDecorator : public FileDecorator
{
public:
	ServiceHeaderFileDecorator(std::shared_ptr<File> file):FileDecorator(file){}
	virtual bool open() override { 
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#pragma once\n"));
			_file->write(std::make_shared<Sentence>("#include \"message.h\"\n"));
			_file->write(std::make_shared<Sentence>("#include \"yar.h\"\n"));
			_file->write(std::make_shared<Sentence>("#include \"msgpack.h\"\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open();_file->write(sentence); }
	virtual ~ServiceHeaderFileDecorator() { }
};

class ServiceSourceFileDecorator : public FileDecorator
{
public:
	ServiceSourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#include \"handler.h\""));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~ServiceSourceFileDecorator() {}
};

class YarSourceFileDecorator : public FileDecorator
{
public:
	YarSourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#include \"handler.h\""));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~YarSourceFileDecorator() {}
};

class ClientSourceFileDecorator : public FileDecorator
{
public:
	ClientSourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#include \"client.h\"\n"));
			_file->write(std::make_shared<Sentence>("#include \"yar.h\"\n"));
			_file->write(std::make_shared<Sentence>("#include \"msgpack.h\"\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~ClientSourceFileDecorator() {}
};

class ClientHeaderFileDecorator : public FileDecorator
{
public:
	ClientHeaderFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#pragma once\n"));
			_file->write(std::make_shared<Sentence>("#include \"message.h\"\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~ClientHeaderFileDecorator() {}
};

class ServerSourceFileDecorator : public FileDecorator
{
public:
	ServerSourceFileDecorator(std::shared_ptr<File> file) :FileDecorator(file) {} 

	virtual bool open() override {
		if (_file->is_open())
			return true;
		else if(_file->open())
		{
			_file->write(std::make_shared<Sentence>("#include \"handler.h\"\n"));
			_file->write(std::make_shared<Sentence>("#include <getopt.h>\n"));
			return true;
		}
		return false;
	}
	virtual FileInfo get_info() const override { return _file->get_info();  }
	virtual void close() override { _file->close(); }
	virtual bool is_open() const override { return _file->is_open(); }
	virtual void write(const std::shared_ptr<Sentence>& sentence) override { open(); _file->write(sentence); }
	virtual ~ServerSourceFileDecorator() {}
};
