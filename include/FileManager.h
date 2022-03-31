#pragma once
#include <memory>
#include <map>
#include "Identifier.h"

class FileManager
{
public:
	static std::shared_ptr<FileManager> Instance();
private:
	FileManager() {}
	static std::shared_ptr<FileManager> _filemanager;
	std::map<FileID, std::shared_ptr<FILE> > _files;
};
