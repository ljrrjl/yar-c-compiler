/**
 * @file src/FileManager.cc
 * @brief File Factory
 * @details Determine the decorator modifier File based on the file type in FileInfo
 * @author jiarui.liu
 * @email jiarui-liu@qq.com
 * @version v0.1
 * @date 2022-04-06
 */

#include "FileManager.h"
#include "FileDecorator.h"


FileManager* FileManager::Instance()
{
	static FileManager file_manager;
	return &file_manager;
}

FileID FileManager::register_file(const std::string& filename, const FileInfo& fileinfo)
{
	auto file_id = IdentifierManager::Instance()->generate_fileid(filename);
	if (have_file(file_id))
		return file_id;
	if (fileinfo.get_type() == FileInfo::Type::MESSAGEHEADER)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto header_file = std::make_shared<MessageHeaderFileDecorator>(file);
		_files.insert(std::make_pair(file_id, header_file));
	}
	else if (fileinfo.get_type() == FileInfo::Type::MESSAGESOURCE)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<MessageSourceFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::RPCHEADER)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto header_file = std::make_shared<ServiceHeaderFileDecorator>(file);
		_files.insert(std::make_pair(file_id, header_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::RPCSOURCE)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<ServiceSourceFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::YARSOURCE)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<YarSourceFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::CLIENTSOURCE)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<ClientSourceFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::CLIENTHEADER)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<ClientHeaderFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else if(fileinfo.get_type() == FileInfo::Type::SERVERSOURCE)
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		auto source_file = std::make_shared<ServerSourceFileDecorator>(file);
		_files.insert(std::make_pair(file_id, source_file));
	}
	else
	{
		auto file = std::make_shared<File>(filename, fileinfo);
		_files.insert(std::make_pair(file_id, file));
	}
	return file_id;
}

bool FileManager::have_file(const FileID& file_id)
{
	return !(_files.find(file_id) == _files.end());
}

std::shared_ptr<File> FileManager::get_file(const FileID& file_id)
{
	auto res = _files.begin();
	if ((res = _files.find(file_id)) == _files.end())
	{
		return nullptr;
	}
	return res->second;
}
