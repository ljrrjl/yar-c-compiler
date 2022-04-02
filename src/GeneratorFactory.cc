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
	switch(symbol->get_token_id().get_type())
	{
	case TokenID::Type::MESSAGE:
		return std::make_shared<MessageGenerator>(file_id, symbol);
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
		return std::make_shared<MessagePropertyGenerator>(file_id, kvproperty);
}
