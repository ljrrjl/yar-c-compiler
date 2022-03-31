#include "TokenQueue.h"

std::shared_ptr<TokenQueue> TokenQueue::_instance = nullptr;

std::shared_ptr<TokenQueue> TokenQueue::Instance()
{
	if(_instance == nullptr)
		_instance.reset(new TokenQueue);
	return _instance;
}

void TokenQueue::push(std::shared_ptr<Token> token)
{
	_token_stream.push_back(token);
}

std::shared_ptr<Token> TokenQueue::pop_back()
{
	if (_token_stream.empty())
		return nullptr;
	std::shared_ptr<Token> value = _token_stream.back();
	_token_stream.pop_back();
	return value;
}

TokenQueue& TokenQueue::operator<<(std::shared_ptr<Token> token)
{
	Instance()->push(token);
	return *Instance();
}

std::shared_ptr<Token> TokenQueue::pop_until_last_id()
{
	while (auto token = pop_back())
	{
		if (token->is_type() == TokenID::Type::ID)
		{
			return token;
		}
	}
	return nullptr;
}
