#pragma once
#include <memory>
#include <sstream>

class Context
{
public:
	int get_row() const;
	int get_col() const;
	int get_last_token_begin() const;
	const std::string get_row_text() const;
	static std::shared_ptr<Context> Instance();
	Context& operator<<(const char* str);
private:
	Context();
	int _row;
	int _col;
	int _last_token_begin;
	std::stringstream _row_text;
	void add_row(int num);
	void add_col(int num);
	void reset_row_text();
	static std::shared_ptr<Context> _instance;
};