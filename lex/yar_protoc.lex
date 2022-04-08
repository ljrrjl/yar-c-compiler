%{
    #include <iostream>
    #include "yar_protoc.tab.h"
    #include "TokenQueue.h"
    #include "SymbolTable.h"
    #include "Context.h"
    #include "ProtocException.h"
    int state = 0;
%}

MESSAGE message
SERVICE service
RPC rpc
RETURNS returns
NUMBER [0-9]+
ID [a-zA-Z_][a-zA-Z0-9_]*
LC \{
RC \}
LB \[
RB \]
LP \(
RP \)
SEMI ;
INT64 int64
FLOAT64 float64
STRING string
ARRAY array
BOOLEAN bool
LESS \<
BIGER \>
DOUHAO \,
COMMENTS #.*
SPACE [ \t]+
NEWLINE \n
OTHER .
%%

{INT64} {
	state = INT64;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::INT64, std::string(yytext));
	*Context::Instance() << yytext;
	return INT64;
}
{FLOAT64} {
	state = FLOAT64; 
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::FLOAT64, std::string(yytext));
	*Context::Instance() << yytext;
	return FLOAT64;
}
{STRING} {
	state = STRING;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::STRING, std::string(yytext));
	*Context::Instance() << yytext;
	return STRING;
}
{ARRAY} {
	state = ARRAY; 
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::ARRAY, std::string(yytext));
	*Context::Instance() << yytext;
	return ARRAY;
}
{BOOLEAN} {
	state = BOOLEAN;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::BOOLEAN, std::string(yytext));
	*Context::Instance() << yytext;
	return BOOLEAN;
}
{MESSAGE} {
	state = MESSAGE;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::MESSAGE, std::string(yytext));
	*Context::Instance() << yytext;
	return MESSAGE;
}
{SERVICE} {
	state = SERVICE;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::SERVICE, std::string(yytext));
	*Context::Instance() << yytext;
	return SERVICE;
}
{RPC} {
	state = RPC;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RPC, std::string(yytext));
	*Context::Instance() << yytext;
	return RPC;
}
{RETURNS} {
	state = RETURNS;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RETURNS, std::string(yytext));
	*Context::Instance() << yytext;
	return RETURNS;
}
{NUMBER} {
	state = NUMBER;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::NUMBER, std::string(yytext));
	*Context::Instance() << yytext;
	return NUMBER;
}

{ID} {
	*Context::Instance() << yytext;
	switch(state)
	{
	case MESSAGE:
		try{
		if(!SymbolTable::Instance()->insert(SymbolID(SymbolID::Type::MESSAGE, std::string(yytext))))
		{
			throw ProtocException("message redefine.");
		}
		}catch(const ProtocException& e)
		{
			std::cerr << e.what() << std::endl;
			exit(1);
		}
		break;
	case SERVICE:
		try{
		if(!SymbolTable::Instance()->insert(SymbolID(SymbolID::Type::RPC, std::string(yytext))))
		{
			throw ProtocException("service redefine.");
		}
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
			exit(1);
		}
		break;
	}
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::ID, std::string(yytext));
	state = ID;
	return ID;
}
{LC} {
	state = LC;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LC, std::string(yytext));
	*Context::Instance() << yytext;
	return LC;
}
{RC} {
	state = RC;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RC, std::string(yytext));
	*Context::Instance() << yytext;
	return RC;
}
{LB} {
	state = LB;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LB, std::string(yytext));
	*Context::Instance() << yytext;
	return LB;
}
{RB} {
	state = RB;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RB, std::string(yytext));
	*Context::Instance() << yytext;
	return RB;
}
{LP} {
	state = LP;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LP, std::string(yytext));
	*Context::Instance() << yytext;
	return LP;
}
{RP} {
	state = RP;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RP, std::string(yytext));
	*Context::Instance() << yytext;
	return RP;
}
{LESS} {
	state = LESS;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LESS, std::string(yytext));
	*Context::Instance() << yytext;
	return LESS;
}
{BIGER} {
	state = BIGER;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::BIGER, std::string(yytext));
	*Context::Instance() << yytext;
	return BIGER;
}
{SEMI} {
	state = SEMI;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::SEMI, std::string(yytext));
	*Context::Instance() << yytext;
	return SEMI;
}
{DOUHAO} {
	state = DOUHAO;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::DOUHAO, std::string(yytext));
	*Context::Instance() << yytext;
	return DOUHAO;
}
{SPACE} {  *Context::Instance() << yytext; }
{COMMENTS} { *Context::Instance() << yytext; }
{NEWLINE} { *Context::Instance() << yytext; }
{OTHER} {
	*Context::Instance() << yytext;
	try{
	throw ProtocException("unknow Token");  
	}catch(const ProtocException& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

%%
