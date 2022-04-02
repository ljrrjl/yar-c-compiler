#pragma once
#include "Generator.h"
#include "Property.h"
#include "Sentence.h"

#include <memory>

class PropertyGenerator : public Generator
{
public:
	PropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty): Generator(file_id), _kvproperty(kvproperty){}
	virtual std::shared_ptr<Sentence> generate() override =0;
protected:
	std::shared_ptr<KVProperty> _kvproperty;
};

class MessagePropertyGenerator : public PropertyGenerator
{
public:
	MessagePropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate() override;
private:
	std::shared_ptr<Sentence> generate_array();
};

class RpcPropertyGenerator : public PropertyGenerator
{
public:
	RpcPropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate()
	{
		return nullptr;
	}
};
