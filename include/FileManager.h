#pragma once
#include <map>
#include <memory>
#include "IdentifierManager.h"
#include "File.h"
#include "FileInfo.h"

class FileManager
{
public:
	static FileManager* Instance();
	FileID register_file(const std::string& filename, const FileInfo& fileinfo);
	bool have_file(const FileID& file_id);
	std::shared_ptr<File> get_file(const FileID& file_id);
private:
	FileManager() {}
	std::map<FileID, std::shared_ptr<File> > _files;
};
