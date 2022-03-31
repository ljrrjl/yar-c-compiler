#pragma once
#include "Identifier.h"
#include <memory>

class IdentifierManager
{
public:
	static std::shared_ptr<IdentifierManager> Instance();
	FileID generate_fileid();
	TokenID generate_tokenid(TokenID::Type type);
	SymbolID generate_symbolid(const SymbolID::Type type, const std::string& symbol);
private:
	IdentifierManager() :_fileid_base(0) {}
	int _fileid_base;
	static std::shared_ptr<IdentifierManager> _instance;
};