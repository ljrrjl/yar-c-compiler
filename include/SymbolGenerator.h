#pragma once
#include "Generator.h"
#include "Symbol.h"
#include <iostream>

class SymbolGenerator : public Generator
{
public:
	SymbolGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol) : Generator(file_id), _symbol(symbol) {}
	virtual void generate() override
	{
		std::cout << "symbol generate" << std::endl;
	}
private:
	std::shared_ptr<Symbol> _symbol;
};
