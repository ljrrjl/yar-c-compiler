#pragma once
#include <memory>
#include <queue>
#include "IdentifierManager.h"

#define INT64_t   "int64_t"s
#define BOOLEAN_t "char"s
#define FLOAT64_t "double"s
#define STRING_t  "char*"s

class PredefType
{
public:
	PredefType(const TokenID& id, std::deque<std::string> additon) :_id(id), _addtion(std::move(additon)) {}
	PredefType(const TokenID& id) : _id(id) {}
	TokenID get_id() const { return _id;  }
	const std::deque<std::string>& get_addtion() const { return _addtion; }
	friend std::ostream& operator<<(std::ostream& os, const PredefType& type)
	{
		os << "[Predef] " << type._id << " ";
		for (const std::string& s : type._addtion)
		{
			os << s << " ";
		}
		return os;
	}

	explicit operator std::string()
	{
		return serialize();
	}

	std::string serialize()
	{
		switch(_id.get_type())
		{
		case TokenID::Type::INT64:
			return "int64_t";
		break;
		case TokenID::Type::BOOLEAN:
			return "char";
		break;
		case TokenID::Type::FLOAT64:
			return "double";
		break;
		case TokenID::Type::STRING:
			return "char*";
		break;
		case TokenID::Type::ARRAY:
			if(_addtion.size() == 1)
				return "array_" + _addtion.front();
		break;
		case TokenID::Type::USER:
			if(_addtion.size() == 1)
				return _addtion.front();
		break;
		}
		throw "serial fault";
	}
private:
	TokenID _id;
	std::deque<std::string> _addtion;
};

class KVProperty
{
public:
	PredefType _key;
	std::string _name;
	KVProperty(const PredefType& key, const std::string& name): _key(key), _name(name){}
	virtual bool operator<(const KVProperty& other)
	{
		return _name < other._name;
	}
	friend std::ostream& operator<<(std::ostream& os, const KVProperty& kv)
	{
		os << "[KVProperty] " << kv._key << "--" << kv._name;
		return os;
	}
};
