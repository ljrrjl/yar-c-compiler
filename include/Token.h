#pragma once
#include <string>
#include "IdentifierManager.h"

class Token
{
public:
	Token(const TokenID& tokenid, const std::string& text):_id(tokenid), _str(text){}
	TokenID::Type is_type() { return _id.get_type(); }
	const std::string& text() { return _str; }
	friend std::ostream& operator<<(std::ostream& os, const Token& token)
	{
		os << "[token] " << token._id << "-" << token._str;
		return os;
	}
private:
	TokenID _id;
	std::string _str;
};
