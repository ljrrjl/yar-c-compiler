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
    #include "ProtocException.h"

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

message : MESSAGE ID LC kv_sentence RC SEMI {
	try{
	throw ProtocException("Excess ';'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	
	| MESSAGE ID LC kv_sentence RC {
	auto file_id = FileManager::Instance()->register_file(std::string("message.h"), FileInfo(FileInfo::Type::MESSAGEHEADER, FileInfo::Type::OUT));
	auto symbol_generator_ptr = GeneratorFactory::Instance()->create_generator(file_id, SymbolTable::Instance()->last_insert());
	auto message_sentence_ptr = symbol_generator_ptr->generate();
        FileManager::Instance()->get_file(file_id)->write(message_sentence_ptr);
	auto src_file_id = FileManager::Instance()->register_file(std::string("message.c"), FileInfo(FileInfo::Type::MESSAGESOURCE, FileInfo::Type::OUT));
	auto symbol_source_generator_ptr = GeneratorFactory::Instance()->create_generator(src_file_id, SymbolTable::Instance()->last_insert());
	auto message_source_sentence_ptr = symbol_source_generator_ptr->generate();
	FileManager::Instance()->get_file(src_file_id)->write(message_source_sentence_ptr);
}
	| MESSAGE ID LC RC {
	try{
	throw ProtocException("Message body is empty.");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| MESSAGE ID LC kv_sentence {
	try{
	throw ProtocException("Except a '}'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| MESSAGE ID {
	try{
	throw ProtocException("Except a '{'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| MESSAGE LC {
	try{
	throw ProtocException("Except a Identifiers");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| error {
	throw ProtocException("syntax error");
}
	;

service : SERVICE ID LC rpc_methods RC SEMI {
	try{
	throw ProtocException("Excess ';'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

	| SERVICE ID LC rpc_methods RC  {
	auto file_id = FileManager::Instance()->register_file(std::string("handler.h"), FileInfo(FileInfo::Type::RPCHEADER, FileInfo::Type::OUT));
	auto symbol_generator_ptr = GeneratorFactory::Instance()->create_generator(file_id, SymbolTable::Instance()->last_insert());
	auto service_sentence_ptr = symbol_generator_ptr->generate();
	FileManager::Instance()->get_file(file_id)->write(service_sentence_ptr);

	auto src_file_id = FileManager::Instance()->register_file(std::string("handler.c"), FileInfo(FileInfo::Type::RPCSOURCE, FileInfo::Type::OUT));
	auto symbol_source_generator_ptr = GeneratorFactory::Instance()->create_generator(src_file_id, SymbolTable::Instance()->last_insert());
	service_sentence_ptr = symbol_source_generator_ptr->generate();
	FileManager::Instance()->get_file(src_file_id)->write(service_sentence_ptr);

	auto yar_src_file_id = FileManager::Instance()->register_file(std::string("yar_handler.c"), FileInfo(FileInfo::Type::YARSOURCE, FileInfo::Type::OUT));
	symbol_source_generator_ptr = GeneratorFactory::Instance()->create_generator(yar_src_file_id, SymbolTable::Instance()->last_insert());
	auto yar_service_sentence_ptr = symbol_source_generator_ptr->generate();
	FileManager::Instance()->get_file(yar_src_file_id)->write(yar_service_sentence_ptr);

	auto yar_client_src_file_id = FileManager::Instance()->register_file(std::string("yar_client.c"), FileInfo(FileInfo::Type::CLIENTSOURCE, FileInfo::Type::OUT));
	auto yar_client_generator_ptr = GeneratorFactory::Instance()->create_generator(yar_client_src_file_id, SymbolTable::Instance()->find_all_service());
	auto yar_client_sentence_ptr = yar_client_generator_ptr->generate();
	FileManager::Instance()->get_file(yar_client_src_file_id)->write(yar_client_sentence_ptr);

	auto yar_client_header_file_id = FileManager::Instance()->register_file(std::string("client.h"), FileInfo(FileInfo::Type::CLIENTHEADER, FileInfo::Type::OUT));
	yar_client_generator_ptr = GeneratorFactory::Instance()->create_generator(yar_client_header_file_id, SymbolTable::Instance()->find_all_service());
	yar_client_sentence_ptr = yar_client_generator_ptr->generate();
	FileManager::Instance()->get_file(yar_client_header_file_id)->write(yar_client_sentence_ptr);

	auto yar_server_src_file_id = FileManager::Instance()->register_file(std::string("yar_server.c"), FileInfo(FileInfo::Type::SERVERSOURCE, FileInfo::Type::OUT));
	auto yar_server_generator_ptr = GeneratorFactory::Instance()->create_generator(yar_server_src_file_id, SymbolTable::Instance()->find_all_service());	
	auto yar_server_src_sentence = yar_server_generator_ptr->generate();
	FileManager::Instance()->get_file(yar_server_src_file_id)->write(yar_server_src_sentence);
}
	| SERVICE ID LC rpc_methods {
	try{
	throw ProtocException("Except a '}'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| SERVICE ID LC RC {
	try{
	throw ProtocException("Service body is empty.");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| SERVICE ID {
	try{
	throw ProtocException("Except a '{'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| SERVICE LC {
	try{
	throw ProtocException("Except a Identifiers");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	;

rpc_methods : rpc_method
	   | rpc_methods rpc_method 
	;

rpc_method : RPC ID LP ID RP RETURNS LP ID RP SEMI {
	auto output_token = TokenQueue::Instance()->pop_until_last_id();
	auto input_token = TokenQueue::Instance()->pop_until_last_id();
	auto rpc_token = TokenQueue::Instance()->pop_until_last_id();

	auto input_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, input_token->text()));
	auto output_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, output_token->text()));

	if(input_symbol == nullptr)
	{
		try{
		throw ProtocException(input_token->text() + " is undefined");
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
			exit(1);
		}
	}
	if(output_symbol == nullptr)
	{
		try{
		throw ProtocException(output_token->text() + " is undefined");
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
			exit(1);
		}
	}
	PredefType type(TokenID(TokenID::Type::RPC), {input_token->text(), output_token->text()});
	*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, rpc_token->text());
}
	| RPC ID LP ID RP RETURNS LP ID RP {
	try{
	throw ProtocException("Except a ';'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| RPC ID LP ID RP RETURNS LP RP {
	try{
        throw ProtocException("Missing output type");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP ID RP RETURNS LP ID {
	try{
	throw ProtocException("Except a ')'");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
	| RPC ID LP ID RP RETURNS LP {
	try{
        throw ProtocException("Except a Identifiers");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP ID RP RETURNS {
	try{
        throw ProtocException("Except a '('");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP ID RP {
	try{
        throw ProtocException("Except a 'RETURN'");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP RP {
	try{
        throw ProtocException("Missing input type");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP ID {
	try{
	throw ProtocException("Except a ')'");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID LP {
	try{
        throw ProtocException("Except a Identifiers");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC ID {
	try{
        throw ProtocException("Except a '('");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}
	| RPC {
	try{
        throw ProtocException("Except a Identifiers");
        }catch(const ProtocException& e){
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}

kv_sentence : id_id_semi
	| type_id_semi
	| kv_sentence id_id_semi
	| kv_sentence type_id_semi
	;

id_id_semi : ID ID SEMI {
	auto name_token = TokenQueue::Instance()->pop_until_last_id();
	auto type_token = TokenQueue::Instance()->pop_until_last_id();

	auto type_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, type_token->text()));
	try{
	if(type_symbol == nullptr)
		throw ProtocException(type_token->text() + "is undefined");
	}catch(const ProtocException& e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	PredefType type(TokenID(TokenID::Type::USER), {type_token->text()});
	*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
}
	| ID ID {
		try{
		throw ProtocException("Expect a ';'");
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
			exit(1);
		}
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
		PredefType type(TokenID(g_type), {array_type_token->text(), array_size_token->text()});
		*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
	}
	else
	{
		PredefType type(TokenID(g_type),{});
		*SymbolTable::Instance()->last_insert() << std::make_shared<KVProperty>(type, name_token->text());
	}
}
	| type ID {
		try{
		throw ProtocException("Expect a ';'");
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
			exit(1);
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
