#include "SymbolTable.h"

std::shared_ptr<SymbolTable> SymbolTable::_symboltable = nullptr;

std::shared_ptr<SymbolTable> SymbolTable::Instance()
{
	if (_symboltable == nullptr)
		_symboltable.reset(new SymbolTable);
	return _symboltable;
}

bool SymbolTable::insert(const SymbolID& id)
{
	auto it = _symbols.begin();
	if ((it = _symbols.find(id)) != _symbols.end())
	{
		return false;
	}
	std::shared_ptr<Symbol> new_symbol;
	if (const_cast<SymbolID&>(id).get_type() == SymbolID::Type::MESSAGE)
	{
		new_symbol.reset(new Symbol(const_cast<SymbolID&>(id).get_symbol(), TokenID::Type::MESSAGE));
		_symbols.insert(std::make_pair(id, new_symbol));
	}
	else if (const_cast<SymbolID&>(id).get_type() == SymbolID::Type::RPC)
	{
		new_symbol.reset(new Symbol(const_cast<SymbolID&>(id).get_symbol(), TokenID::Type::SERVICE));
		_symbols.insert(std::make_pair(id, new_symbol));
	}
	_last_insert = new_symbol;
	return true;
}

std::shared_ptr<Symbol> SymbolTable::find(const SymbolID& id)
{
	auto it = _symbols.begin();
	if ((it = _symbols.find(id)) != _symbols.end())
	{
		return it->second;
	}
	return nullptr;
}

void SymbolTable::remove(const SymbolID& id)
{
	auto res = _symbols.find(id);
	if (res != _symbols.end())
	{
		_symbols.erase(res);
	}
}