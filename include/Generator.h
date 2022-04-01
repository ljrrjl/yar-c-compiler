#pragma once
#include "IdentifierManager.h"
class Generator
{
public:
	Generator(const FileID& file_id): _file_id(file_id){}
	virtual void generate(){}
protected:
	FileID _file_id;
};