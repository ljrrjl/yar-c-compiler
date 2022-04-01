#include "GeneratorFactory.h"

std::shared_ptr<GeneratorFactory> GeneratorFactory::_instance = nullptr;

std::shared_ptr<GeneratorFactory> GeneratorFactory::Instance()
{
	if (_instance == nullptr)
		_instance.reset(new GeneratorFactory);
	return _instance;
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol)
{
	return std::make_shared<SymbolGenerator>(file_id, symbol);
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty)
{
	return std::make_shared<PropertyGenerator>(file_id, kvproperty);
}