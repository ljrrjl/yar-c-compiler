#pragma once
#include "Sentence.h"

#include <initializer_list>
#include <sstream>
#include <string>
#include <memory>
namespace
{
	template<typename T>
	std::shared_ptr<Sentence> exp(const std::string& str, std::initializer_list<std::string> args = {})
	{
		auto cur_args = args.begin();
		bool flag = false;
		std::stringstream os;
		for (const char& ch : str)
		{
			if (ch == '%')
				flag = true;
			else if (ch == 's' && flag)
			{
				os << *cur_args++;
				flag = false;
			}
			else
			{
				flag = false;
				os << ch;
			}
		}
		return std::make_shared<T>(os.str());
	}
}

#define EXP(...) exp<Sentence>(__VA_ARGS__);
#define IF(...) exp<IfSentence>(__VA_ARGS__);
#define STRUCT(...) exp<StructSentence>(__VA_ARGS__);

