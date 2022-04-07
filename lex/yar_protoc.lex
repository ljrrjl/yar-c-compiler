%{
    #include <iostream>
    #include "yar_protoc.tab.h"
    #include "TokenQueue.h"
    #include "SymbolTable.h"
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
	return INT64;
}
{FLOAT64} {
	state = FLOAT64; 
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::FLOAT64, std::string(yytext));
	return FLOAT64;
}
{STRING} {
	state = STRING;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::STRING, std::string(yytext));
	return STRING;
}
{ARRAY} {
	state = ARRAY; 
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::ARRAY, std::string(yytext));
	return ARRAY;
}
{BOOLEAN} {
	state = BOOLEAN;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::BOOLEAN, std::string(yytext));
	return BOOLEAN;
}
{MESSAGE} {
	state = MESSAGE;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::MESSAGE, std::string(yytext));
	return MESSAGE;
}
{SERVICE} {
	state = SERVICE;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::SERVICE, std::string(yytext));
	return SERVICE;
}
{RPC} {
	state = RPC;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RPC, std::string(yytext));
	return RPC;
}
{RETURNS} {
	state = RETURNS;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RETURNS, std::string(yytext));
	return RETURNS;
}
{NUMBER} {
	state = NUMBER;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::NUMBER, std::string(yytext));
	return NUMBER;
}

{ID} {
	switch(state)
	{
	case MESSAGE:
		if(!SymbolTable::Instance()->insert(SymbolID(SymbolID::Type::MESSAGE, std::string(yytext))))
		{
			throw "message redefine.";
		}
		
		break;
	case SERVICE:
		if(!SymbolTable::Instance()->insert(SymbolID(SymbolID::Type::RPC, std::string(yytext))))
		{
			throw "service redefine.";
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
	return LC;
}
{RC} {
	state = RC;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RC, std::string(yytext));
	return RC;
}
{LB} {
	state = LB;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LB, std::string(yytext));
	return LB;
}
{RB} {
	state = RB;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RB, std::string(yytext));
	return RB;
}
{LP} {
	state = LP;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LP, std::string(yytext));
	return LP;
}
{RP} {
	state = RP;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::RP, std::string(yytext));
	return RP;
}
{LESS} {
	state = LESS;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::LESS, std::string(yytext));
	return LESS;
}
{BIGER} {
	state = BIGER;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::BIGER, std::string(yytext));
	return BIGER;
}
{SEMI} {
	state = SEMI;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::SEMI, std::string(yytext));
	return SEMI;
}
{DOUHAO} {
	state = DOUHAO;
	*TokenQueue::Instance() << std::make_shared<Token>(TokenID::Type::DOUHAO, std::string(yytext));
	return DOUHAO;
}
{SPACE} { }
{COMMENTS} { }
{NEWLINE} { }
{OTHER} {   }
%%
