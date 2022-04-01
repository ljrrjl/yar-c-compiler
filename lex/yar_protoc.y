%{
    #include "yar_protoc.tab.h"
    #include <stdio.h>

    #include <sstream>
    #include <string>
    #include "TokenQueue.h"
    #include "SymbolTable.h"
    #include "GeneratorFactory.h"
    #include "IdentifierManager.h"
    #include "FileManager.h"
    #include "Sentence.h"

    extern int yylex(void);
    extern void yyerror(const char* s);
    extern int yyparse(void);
    extern int g_line_number;
    TokenID::Type g_type;
%}

%token MESSAGE SERVICE RPC RETURNS  NUMBER  ID LC RC LB RB LP RP  SEMI INT64 FLOAT64 STRING ARRAY BOOLEAN LESS BIGER DOUHAO SPACE
%%

sentence : message
	 | service
	 | sentence service
	 | sentence message
	;

message : MESSAGE ID LC kv_sentence RC {
	auto file_id = FileManager::Instance()->register_file(std::string("message.h"), FileInfo(FileInfo::Type::HEADER, FileInfo::Type::OUT));
	auto symbol_generator_ptr = GeneratorFactory::Instance()->create_generator(file_id, SymbolTable::Instance()->last_insert());
	symbol_generator_ptr->generate();
}
	| error {  }
	;

service : SERVICE ID LC rpc_methods RC  {
}
	;

rpc_methods : rpc_method
	   | rpc_methods rpc_method 
	;

rpc_method : RPC ID LP ID RP RETURNS LP ID RP SEMI {
	auto output_token = TokenQueue::Instance()->pop_until_last_id();
	auto input_token = TokenQueue::Instance()->pop_until_last_id();
	auto rpc_token = TokenQueue::Instance()->pop_until_last_id();

	PredefType type(TokenID(TokenID::Type::SERVICE), {input_token->text(), output_token->text()});
	*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, rpc_token->text());
} 

kv_sentence : id_id_semi
	| type_id_semi
	| kv_sentence id_id_semi
	| kv_sentence type_id_semi
	;

id_id_semi : ID ID SEMI {
	auto name_token = TokenQueue::Instance()->pop_until_last_id();
	auto type_token = TokenQueue::Instance()->pop_until_last_id();
		
	PredefType type(TokenID(TokenID::Type::USER), {type_token->text()});
	*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
}
	   ;

type_id_semi : type ID SEMI {
	auto name_token = TokenQueue::Instance()->pop_until_last_id();
	if(g_type == TokenID::Type::ARRAY)
	{
		std::shared_ptr<Token> array_size_token = nullptr;
		std::shared_ptr<Token> array_type_token = nullptr;
		array_size_token = TokenQueue::Instance()->pop_back();
		array_size_token = TokenQueue::Instance()->pop_back();
		array_type_token = TokenQueue::Instance()->pop_back();
		array_type_token = TokenQueue::Instance()->pop_back();
		array_type_token = TokenQueue::Instance()->pop_back();
		if(array_type_token && array_size_token)
		{
			PredefType type(TokenID(g_type), {array_type_token->text(), array_size_token->text()});
			*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
		}
		else
		{
			throw "type_id_semi error";
		}
	}
	else
	{
		PredefType type(TokenID(g_type),{});
		*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
	}
}
	     ;

type : INT64				     { g_type = TokenID::Type::INT64;   }
	| FLOAT64			     { g_type = TokenID::Type::FLOAT64; }
	| STRING			     { g_type = TokenID::Type::STRING;  }
	| BOOLEAN			     { g_type = TokenID::Type::BOOLEAN; }
	| ARRAY LESS type BIGER LB NUMBER RB { g_type = TokenID::Type::ARRAY; }
	| ARRAY LESS ID BIGER LB NUMBER RB   { g_type = TokenID::Type::ARRAY; }
	;
%%

extern FILE *yyin;

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("[error] usage: <source>\n");
		exit(1);
	}
	FILE* f;
	char filename[200];	
	f = fopen(argv[1],"r");
	if(!f)
	{
		printf("open file error\n");
		exit(1);
	}
	yyin = f;
	yyparse();
	return 0;
}

void yyerror (char const *s) {
  	fprintf (stderr, "[error] %s\n", s);
}

#ifdef __cplusplus
extern "C"{
#endif
int yywrap()
{
    return 1;
}
#ifdef __cplusplus
}
#endif
