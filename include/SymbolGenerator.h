#pragma once
#include "Generator.h"
#include "Sentence.h"
#include "Symbol.h"

#include <iostream>
#include <memory>

class SymbolGenerator : public Generator
{
public:
	SymbolGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol) : Generator(file_id), _symbol(symbol) {}
	virtual std::shared_ptr<Sentence> generate() override = 0;
protected:
	std::shared_ptr<Symbol> _symbol;
};

class MessageGenerator : public SymbolGenerator
{
public:
	MessageGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
};

class RpcGenerator: public SymbolGenerator
{
public:
	RpcGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override
	{
		return nullptr;
	}
};
