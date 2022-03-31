#pragma once
#include "Token.h"
#include <queue>
#include <memory>

class TokenQueue
{
public:
	void push(std::shared_ptr<Token> token);
	std::shared_ptr<Token> pop_back();
	static std::shared_ptr<TokenQueue> Instance();
	TokenQueue& operator<<(std::shared_ptr<Token> token);
	std::shared_ptr<Token> pop_until_last_id();
private:
	static std::shared_ptr<TokenQueue> _instance;
	TokenQueue() = default;
	std::deque<std::shared_ptr<Token> > _token_stream;
};
