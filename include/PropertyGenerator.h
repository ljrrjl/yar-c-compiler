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

class MessagePropertyHeaderGenerator : public PropertyGenerator
{
public:
	MessagePropertyHeaderGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate() override;
private:
	std::shared_ptr<Sentence> generate_array();
};

class MessagePropertySourceGenerator : public PropertyGenerator
{
public:
	MessagePropertySourceGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate() override; 
private:
	std::shared_ptr<Sentence> generate_array();
};

class RpcHeaderPropertyGenerator : public PropertyGenerator
{
public:
	RpcHeaderPropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate() override;
};

class RpcSourcePropertyGenerator: public PropertyGenerator
{
public:
	RpcSourcePropertyGenerator(const FileID& file_id, const std::shared_ptr<KVProperty>& kvproperty):PropertyGenerator(file_id, kvproperty){} 
	virtual std::shared_ptr<Sentence> generate() override
	{
		return nullptr;
	}
};
