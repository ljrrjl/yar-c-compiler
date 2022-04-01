#pragma once
#include "Generator.h"
#include "Property.h"

class PropertyGenerator : public Generator
{
public:
	PropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty): Generator(file_id), _kvproperty(kvproperty){}
	virtual void generate() override
	{

	}
private:
	std::shared_ptr<KVProperty> _kvproperty;
};