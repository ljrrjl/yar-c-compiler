#pragma once
#include "PropertyGenerator.h"
#include "SymbolGenerator.h"
#include "ClientGenerator.h"

class GeneratorFactory
{
public:
	std::shared_ptr<Generator> create_generator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol);
	std::shared_ptr<Generator> create_generator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty);
	std::shared_ptr<Generator> create_generator(const FileID& file_id, const std::vector<std::shared_ptr<Symbol> >& symbols);
	static std::shared_ptr<GeneratorFactory> Instance();
private:
	GeneratorFactory() = default;
	static std::shared_ptr<GeneratorFactory> _instance;
};
