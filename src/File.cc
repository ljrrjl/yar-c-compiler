#include "File.h"

bool File::open()
{
	if(_filestream.is_open())
		return true;
	if (!_info.is_available())
	{
		return false;
	}
	if (_info.get_mode() == FileInfo::Type::OUT)
	{
		_filestream.open(_filename, std::ios::out);
	}
	else if(_info.get_mode() == FileInfo::Type::IN)
	{
		_filestream.open(_filename, std::ios::in);
	}
	else
	{
		return false;
	}
	if (!_filestream.is_open())
		return false;
	return true;
}

bool File::is_open() const
{
	return _filestream.is_open();
}

void File::close()
{
	_filestream.close();
}

void File::write(const std::shared_ptr<Sentence>& sentence)
{
	if (this->open() && _info.get_mode() == FileInfo::Type::OUT && sentence != nullptr)
	{
		_filestream << sentence->out();
	}
}
