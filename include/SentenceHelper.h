#pragma once
#include "Sentence.h"

#include <initializer_list>
#include <sstream>
#include <string>
#include <memory>
#include <type_traits>

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
		if (std::is_same<T, Sentence>::value)
		{
			os << '\n';
			return std::make_shared<T>(os.str());
		}
		return std::make_shared<T>(os.str());
	}
}

#define EXP(...) exp<Sentence>(__VA_ARGS__);
#define IF(...) exp<IfSentence>(__VA_ARGS__);
#define STRUCT(...) exp<StructSentence>(__VA_ARGS__);
#define FUNC(...) exp<FuncSentence>(__VA_ARGS__);
#define FOR(...) exp<ForSentence>(__VA_ARGS__);
#define DOWHILE(...) exp<DoWhileSentence>(__VA_ARGS__);
#define WHILE(...) exp<WhileSentence>(__VA_ARGS__);
#define SWITCH(...) exp<SwitchSentence>(__VA_ARGS__);
#define CASE(...) exp<CaseSentence>(__VA_ARGS__);

