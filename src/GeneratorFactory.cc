#include "GeneratorFactory.h"
#include "FileManager.h"

std::shared_ptr<GeneratorFactory> GeneratorFactory::_instance = nullptr;

std::shared_ptr<GeneratorFactory> GeneratorFactory::Instance()
{
	if (_instance == nullptr)
		_instance.reset(new GeneratorFactory);
	return _instance;
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol)
{
	switch(symbol->get_token_id().get_type())
	{
	case TokenID::Type::MESSAGE:
		if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::MESSAGEHEADER)
			return std::make_shared<MessageHeaderGenerator>(file_id, symbol);
		return std::make_shared<MessageSourceGenerator>(file_id, symbol);
	break;
	case TokenID::Type::SERVICE:
		return std::make_shared<RpcGenerator>(file_id, symbol);
	break;
	}
	return nullptr;
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty)
{
	if(kvproperty->_key.get_id().get_type() == TokenID::Type::RPC)
		return std::make_shared<RpcPropertyGenerator>(file_id, kvproperty);
	else
	{
		if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::MESSAGEHEADER)
			return std::make_shared<MessagePropertyHeaderGenerator>(file_id, kvproperty);
		else
			return std::make_shared<MessagePropertySourceGenerator>(file_id, kvproperty);
	}
}
