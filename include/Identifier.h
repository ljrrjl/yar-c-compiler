#pragma once
#include <iostream>
#include <string>
class FileID
{
public:
	FileID(const std::string& filename) : _filename(filename) {}
	bool operator<(const FileID& other) const
	{
		return _filename < other._filename;
	}
	friend std::ostream& operator<<(std::ostream& os, const FileID& fileid)
	{
		os << "[file id] " << fileid._filename;
		return os;
	}
private:
	std::string _filename;
};

class TokenID
{
public:
	enum class Type : int
	{
		MESSAGE, SERVICE, RPC, RETURNS, NUMBER, ID, LC, RC, LB, RB, LP, RP, SEMI, INT64, FLOAT64, STRING, ARRAY, BOOLEAN, LESS, BIGER, DOUHAO, SPACE, USER, NONE
	};
	TokenID() :_type(TokenID::Type::NONE) {}
	TokenID(TokenID::Type type) : _type(type){}
	TokenID::Type get_type() { return _type; }
	bool operator<(const TokenID& other) const
	{
		return _type < other._type;
	}
	friend std::ostream& operator<<(std::ostream& os, const TokenID& tokenid)
	{
		os << "[token id] " << static_cast<int>(tokenid._type);
		return os;
	}
private:
	TokenID::Type _type;
};

class SymbolID
{
public:
	enum class Type : int 
	{
		MESSAGE,
		RPC
	};
	SymbolID(const SymbolID::Type type, const std::string& symbolid): _type(type), _symbol(symbolid){}
	bool operator<(const SymbolID& other) const
	{
		if (static_cast<int>(_type) < static_cast<int>(other._type) || (_symbol < other._symbol))
		{
			return true;
		}
		return false;
	}
	friend std::ostream& operator<<(std::ostream& os, const SymbolID& symbolid)
	{
		os << "[symbol id] " << static_cast<int>(symbolid._type) << "-" << symbolid._symbol;
		return os;
	}
	const std::string& get_symbol() { return _symbol; }
	const SymbolID::Type& get_type() { return _type; }
private:
	std::string _symbol;
	SymbolID::Type _type;
};

class BufferID
{
public:
	explicit BufferID(int num): _num(num){}
	bool operator<(const BufferID& other) const
	{
		return _num < other._num;
	}
	friend std::ostream& operator<<(std::ostream& os, const BufferID& buffer_id)
	{
		os << "[buffer id] " << buffer_id._num;
		return os;
	}

private:
	int _num;
};
