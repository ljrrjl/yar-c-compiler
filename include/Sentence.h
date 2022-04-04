#pragma once

#include <memory>
#include <deque>
#include <sstream>

class Sentence
{
public:
	Sentence() = default;
	Sentence(const std::string& str) : _str(str) {}
	virtual ~Sentence() = default;
	virtual std::string out()
	{
		std::stringstream ss;
		do_align(ss);
		ss << _str << '\n';
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence)
	{

		if(sentence != nullptr)
			_str.append(sentence->out());
		return *this;
	}
	int get_align() const{ return _align;  }
	void set_align(int num) { _align = num;  }
protected:
	static int _align;
	std::string _str;
	virtual void do_align(std::ostream& os) final
	{
		for (int i = 0; i < _align * 4; i++)
			os << " ";
	}
};

class StructSentence : public Sentence
{
public:
	StructSentence() = delete;
	StructSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "struct " << _str << "{" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "};\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class WhileSentence : public Sentence
{
public:
	WhileSentence() = delete;
	WhileSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "while( " << _str << " ){" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class IfSentence : public Sentence
{
public:
	IfSentence() = delete;
	IfSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "if( " << _str << " ){" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class ElseIfSentence : public Sentence
{
public:
	ElseIfSentence() = delete;
	ElseIfSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "else if( " << _str << " ){" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class ElseSentence : public Sentence
{
public:
	ElseSentence() = default;
	explicit ElseSentence(const std::deque<std::shared_ptr<Sentence> >& sentences) : _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "else{" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class SwitchSentence : public Sentence
{
public:
	SwitchSentence() = delete;
	SwitchSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) : Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "switch( " << _str << " ){" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class CaseSentence : public Sentence
{
public:
	CaseSentence() = delete;
	CaseSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}, bool have_break = true) : Sentence(str), _sentences(sentences), _have_break(have_break) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "case '" << _str << "':" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		if (_have_break)
			ss << "break;\n";
		else
			ss << '\n';
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
	bool _have_break;
};

class DefaultSentence : public Sentence
{
public:
	DefaultSentence() = delete;
	DefaultSentence(const std::deque<std::shared_ptr<Sentence> >& sentences = {}, bool have_break = true) : _sentences(sentences), _have_break(have_break) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "default:" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		if (_have_break)
			ss << "break;\n";
		else
			ss << '\n';
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
	bool _have_break;
};

class ForSentence : public Sentence
{
public:
	ForSentence() = delete;
	ForSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "for( " << _str << " ){" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class DoWhileSentence : public Sentence
{
public:
	DoWhileSentence() = delete;
	DoWhileSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss << "do{" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}while( " << _str << " );\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};

class FuncSentence : public Sentence
{
public:
	FuncSentence() = delete;
	FuncSentence(const std::string& str, const std::deque<std::shared_ptr<Sentence> >& sentences = {}) :Sentence(str), _sentences(sentences) {}
	virtual std::string out() override
	{
		std::stringstream ss;
		do_align(ss);
		ss <<  _str << "{" << '\n';
		_align++;
		for (auto& sentence : _sentences)
		{
			if(sentence != nullptr)
				ss << std::move(sentence->out());
		}
		_align--;
		do_align(ss);
		ss << "}\n";
		return ss.str();
	}
	virtual Sentence& operator<<(const std::shared_ptr<Sentence>& sentence) override
	{
		_sentences.emplace_back(sentence);
		return *this;
	}
private:
	std::deque<std::shared_ptr<Sentence> > _sentences;
};
