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

class MessageHeaderGenerator : public SymbolGenerator
{
public:
	MessageHeaderGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
};

class MessageSourceGenerator : public SymbolGenerator
{
public:
	MessageSourceGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
};

class RpcHeaderGenerator: public SymbolGenerator
{
public:
	RpcHeaderGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
};

class RpcSourceGenerator: public SymbolGenerator
{
public:
	RpcSourceGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
};

class YarSourceGenerator : public SymbolGenerator
{
public:
	YarSourceGenerator(const FileID& file_id, const std::shared_ptr<Symbol>& symbol):SymbolGenerator(file_id, symbol){}
	virtual std::shared_ptr<Sentence> generate() override;
private:
	std::shared_ptr<Sentence> unpack_map_generate(std::shared_ptr<Symbol> symbol, const std::string& yar_data); 
	std::shared_ptr<Sentence> pack_map_generate(std::shared_ptr<Symbol> symbol, const std::string& yar_packager); 
};
