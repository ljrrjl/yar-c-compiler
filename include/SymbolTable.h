#pragma once
#include <map>
#include <vector>
#include "Symbol.h"

class SymbolTable
{
public:
	static std::shared_ptr<SymbolTable> Instance();
	bool insert(const SymbolID& id);
	std::shared_ptr<Symbol> find(const SymbolID& id);
	void remove(const SymbolID& id);
	std::vector<std::shared_ptr<Symbol> > find_all_service();
	std::shared_ptr<Symbol> last_insert() { return _last_insert; }
private:
	SymbolTable(): _last_insert(nullptr) {}
	static std::shared_ptr<SymbolTable> _symboltable;
	std::map<SymbolID, std::shared_ptr<Symbol> > _symbols;
	std::shared_ptr<Symbol> _last_insert;
};
