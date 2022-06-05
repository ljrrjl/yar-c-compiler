#include "Context.h"
#include <cstring>

Context::Context():_row(1), _col(0), _last_token_begin(0){}

int Context::get_row() const
{
	return _row;
}
void Context::add_row(int num)
{
	_row += num;
	_col = 0;
}
int Context::get_col() const
{
	return _col;
}

int Context::get_last_token_begin() const
{
	return _last_token_begin;
}

void Context::add_col(int num)
{
	_col += num;
}
const std::string Context::get_row_text() const
{
	return _row_text.str();
}
void Context::reset_row_text()
{
	std::stringstream empty;
	_row_text.swap(empty);
}
Context* Context::Instance()
{
	static Context context;
	return &context;
}

Context& Context::operator<<(const char* str)
{
	if (str == nullptr)
		return *this;
	_last_token_begin = _col;
	int str_index = 0;
	while (str[str_index] != '\0')
	{
		if (str[str_index] == '\n')
		{
			add_row(1);
			reset_row_text();
		}
		else if (str[str_index] == '\t')
		{
			add_col(4);
			_row_text << "    ";
		}
		else
		{
			add_col(1);
			_row_text << str[str_index];
		}
		str_index++;
	}
	return *this;
}
