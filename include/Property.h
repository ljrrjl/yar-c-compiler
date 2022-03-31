#pragma once
#include <memory>
#include <queue>
#include "IdentifierManager.h"

class PredefType
{
public:
	PredefType(const TokenID& id, std::deque<std::string> additon) :_id(id), _addtion(std::move(additon)) {}
	PredefType(const TokenID& id) : _id(id) {}
	friend std::ostream& operator<<(std::ostream& os, const PredefType& type)
	{
		os << "[Predef] " << type._id << " ";
		for (const std::string& s : type._addtion)
		{
			os << s << " ";
		}
		return os;
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
