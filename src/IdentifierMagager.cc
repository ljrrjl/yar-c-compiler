#include "IdentifierManager.h"

std::shared_ptr<IdentifierManager> IdentifierManager::_instance = nullptr;

std::shared_ptr<IdentifierManager> IdentifierManager::Instance()
{
	if (IdentifierManager::_instance == nullptr)
		IdentifierManager::_instance.reset(new IdentifierManager);
	return _instance;
}

FileID IdentifierManager::generate_fileid()
{
	return FileID(IdentifierManager::Instance()->_fileid_base++);
}

TokenID IdentifierManager::generate_tokenid(TokenID::Type type)
{
	return TokenID(type);
}

SymbolID IdentifierManager::generate_symbolid(const SymbolID::Type type, const std::string& symbol)
{
	return SymbolID(type, symbol);
}