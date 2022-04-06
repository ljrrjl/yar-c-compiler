#pragma once

#include "Generator.h"
#include "Sentence.h"
#include "Symbol.h"
#include <vector>

class ClientGenerator : public Generator
{
public:
	ClientGenerator(const FileID& file_id, const std::vector<std::shared_ptr<Symbol> >& symbols): Generator(file_id), _symbols(symbols){}
	virtual std::shared_ptr<Sentence> generate() override = 0;
protected:
	std::vector<std::shared_ptr<Symbol> > _symbols;
};

class ClientHeaderGenerator : public ClientGenerator
{
public:
	ClientHeaderGenerator(const FileID& file_id, const std::vector<std::shared_ptr<Symbol> >& symbols): ClientGenerator(file_id, symbols){}
	virtual std::shared_ptr<Sentence> generate() override; 
};

class ClientSourceGenerator : public ClientGenerator
{
public:
	ClientSourceGenerator(const FileID& file_id, const std::vector<std::shared_ptr<Symbol> >& symbols): ClientGenerator(file_id, symbols){}
	virtual std::shared_ptr<Sentence> generate() override; 
};
