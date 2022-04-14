#pragma once
#include "IdentifierManager.h"
#include "Sentence.h"
#include <memory>
class Generator
{
public:
	Generator(const FileID& file_id): _file_id(file_id){}
	virtual std::shared_ptr<Sentence> generate() = 0;
protected:
	FileID _file_id;
};
