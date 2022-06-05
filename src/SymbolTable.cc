/**
 * @file src/SymbolTable.cc
 * @brief Collection of generated symbols
 * @details There are two types of symbols, Message and RPC
 * @author jiarui.liu
 * @email jiarui-liu@qq.com
 * @version v0.1
 * @date 2022-04-06
 */

#include "SymbolTable.h"

SymbolTable* SymbolTable::Instance()
{
	static SymbolTable symbole_table;
	return &symbole_table;
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

std::vector<std::shared_ptr<Symbol> > SymbolTable::find_all_service()
{
	std::vector<std::shared_ptr<Symbol> > res;
	for(auto& [symbol_id, symbol] : _symbols)
	{
		if(symbol_id.get_type() == SymbolID::Type::RPC)
			res.emplace_back(symbol);
	}
	return res;
}
