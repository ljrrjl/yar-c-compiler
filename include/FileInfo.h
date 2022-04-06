#pragma once

class FileInfo
{
public:
	enum class Type : int
	{
		MESSAGEHEADER,
		MESSAGESOURCE,
		RPCHEADER,
		RPCSOURCE,
		YARSOURCE,
		CLIENTSOURCE,
		CLIENTHEADER,
		IN,
		OUT,
		NANO
	};
	FileInfo(): _type(FileInfo::Type::NANO), _mode(FileInfo::Type::NANO){}
	FileInfo(FileInfo::Type type, FileInfo::Type mode) : _type(type), _mode(mode){}
	FileInfo::Type get_type() const { return _type; }
	FileInfo::Type get_mode() const { return _mode; }
	bool is_available() const { return (_type != FileInfo::Type::NANO && _mode != FileInfo::Type::NANO); }
private:
	FileInfo::Type _type;
	FileInfo::Type _mode;
};
