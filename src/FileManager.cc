#include "FileManager.h"

std::shared_ptr<FileManager> FileManager::_filemanager = nullptr;

std::shared_ptr<FileManager> FileManager::Instance()
{
	if (FileManager::_filemanager == nullptr)
		FileManager::_filemanager.reset(new FileManager);
	return FileManager::_filemanager;
}