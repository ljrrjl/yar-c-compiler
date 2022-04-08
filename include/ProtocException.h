#pragma once
#include <exception>
#include "Context.h"
#include <iostream>

class ProtocException : public std::exception
{
public:
	ProtocException(const std::string& msg) : _msg(msg)
	{

	}
	virtual const char* what() const throw() override
	{
		std::cerr << "line: " << Context::Instance()->get_row() << '\n';
		std::cerr << Context::Instance()->get_row_text() << '\n';
		do_align();
		std::cerr << "^";
		for (int i = Context::Instance()->get_last_token_begin(); i < Context::Instance()->get_col() - 1; i++)
			std::cerr << "~";
		std::cerr << std::endl;
		return _msg.c_str();
	}
private:
	void do_align() const
	{
		for (int i = 0; i < Context::Instance()->get_last_token_begin(); i++)
			std::cerr << " ";
	}
	std::string _msg;
};
