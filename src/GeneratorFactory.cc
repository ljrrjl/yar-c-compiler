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
		if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::RPCHEADER)
			return std::make_shared<RpcHeaderGenerator>(file_id, symbol);
		else if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::YARSOURCE)
		{
			return std::make_shared<YarSourceGenerator>(file_id, symbol);
		}
		return std::make_shared<RpcSourceGenerator>(file_id, symbol);
	break;
	}
	return nullptr;
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty)
{
	if(kvproperty->_key.get_id().get_type() == TokenID::Type::RPC)
	{
		if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::RPCSOURCE)
			return std::make_shared<RpcSourcePropertyGenerator>(file_id, kvproperty);
		else
			return std::make_shared<RpcHeaderPropertyGenerator>(file_id, kvproperty);
	}
	else
	{
		if(FileManager::Instance()->get_file(file_id)->get_info().get_type() == FileInfo::Type::MESSAGEHEADER)
			return std::make_shared<MessagePropertyHeaderGenerator>(file_id, kvproperty);
		else
			return std::make_shared<MessagePropertySourceGenerator>(file_id, kvproperty);
	}
}

std::shared_ptr<Generator> GeneratorFactory::create_generator(const FileID& file_id, const std::vector<std::shared_ptr<Symbol> >& symbols)
{
	switch(FileManager::Instance()->get_file(file_id)->get_info().get_type())
	{
	case FileInfo::Type::CLIENTSOURCE:
		return std::make_shared<ClientSourceGenerator>(file_id, symbols);
	break;
	case FileInfo::Type::CLIENTHEADER:
		return std::make_shared<ClientHeaderGenerator>(file_id, symbols);
	break;
	case FileInfo::Type::SERVERSOURCE:
		return std::make_shared<ServerSourceGenerator>(file_id, symbols);
	break;
	}
	return nullptr;
}


