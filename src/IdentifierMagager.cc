/**
 * @file src/IdentifierMagager.cc
 * @brief Identifier Factory
 * @details Generate various identifiers
 * @author jiarui.liu
 * @email jiarui-liu@qq.com
 * @version v0.1
 * @date 2022-04-06
 */

#include "IdentifierManager.h"

std::shared_ptr<IdentifierManager> IdentifierManager::_instance = nullptr;

int IdentifierManager::_buffer_base = 0;

std::shared_ptr<IdentifierManager> IdentifierManager::Instance()
{
	if (IdentifierManager::_instance == nullptr)
		IdentifierManager::_instance.reset(new IdentifierManager);
	return _instance;
}

FileID IdentifierManager::generate_fileid(const std::string& filename)
{
	return FileID(filename);
}

TokenID IdentifierManager::generate_tokenid(TokenID::Type type)
{
	return TokenID(type);
}

SymbolID IdentifierManager::generate_symbolid(const SymbolID::Type type, const std::string& symbol)
{
	return SymbolID(type, symbol);
}

BufferID IdentifierManager::generate_bufferid()
{
	BufferID buffer_id(_buffer_base++);
	return buffer_id;
}
