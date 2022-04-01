#pragma once
#include "Identifier.h"
#include <memory>

class IdentifierManager
{
public:
    static std::shared_ptr<IdentifierManager> Instance();
    FileID generate_fileid(const std::string& filename);
    TokenID generate_tokenid(TokenID::Type type);
    SymbolID generate_symbolid(const SymbolID::Type type, const std::string& symbol);
    BufferID generate_bufferid();
private:
    IdentifierManager() {}
    static std::shared_ptr<IdentifierManager> _instance;
    static int _buffer_base;
};