#pragma once
#include "PropertyGenerator.h"
#include "SymbolGenerator.h"

class GeneratorFactory
{
public:
	std::shared_ptr<Generator> create_generator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol);
	std::shared_ptr<Generator> create_generator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty);
	static std::shared_ptr<GeneratorFactory> Instance();
private:
	GeneratorFactory() = default;
	static std::shared_ptr<GeneratorFactory> _instance;
};
