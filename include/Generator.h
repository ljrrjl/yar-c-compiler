#pragma once
#include "IdentifierManager.h"
#include "Sentence.h"
#include <memory>
class Generator
{
public:
	Generator(const FileID& file_id): _file_id(file_id){}
	virtual std::shared_ptr<Sentence> generate(){ return std::make_shared<Sentence>(); }
protected:
	FileID _file_id;
};
