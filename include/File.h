#pragma once
#include <memory>
#include <string>
#include <fstream>
#include "FileInfo.h"
#include "Sentence.h"

class File
{
public:
	File() = default;
	File(const std::string& filename, const FileInfo& info): _filename(filename), _info(info){}
	virtual bool open();
	virtual void close();
	virtual bool is_open() const;
	virtual FileInfo get_info() const;
	virtual void write(const std::shared_ptr<Sentence>& sentence);
private:
	std::fstream _filestream;
	std::string _filename;
	FileInfo _info;
};
