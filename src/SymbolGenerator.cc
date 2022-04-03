#include "SymbolGenerator.h"
#include "SentenceHelper.h"
#include "GeneratorFactory.h"
#include "FileManager.h"

using namespace std::string_literals;

std::shared_ptr<Sentence> MessageHeaderGenerator::generate()
{
	auto res_sentence = EXP("");

	//message define
	auto message_sentence_ptr = STRUCT("%s_message", {_symbol->get_symbol_value()});
	for(auto kvproperty : _symbol->get_properties())
	{
		auto property_generate_ptr = GeneratorFactory::Instance()->create_generator(_file_id, kvproperty);
		*message_sentence_ptr << property_generate_ptr->generate();
	}
	*res_sentence << message_sentence_ptr;

	//message utils
	*res_sentence << EXP("struct %s_message* %s_message_create();", {_symbol->get_symbol_value(), _symbol->get_symbol_value()});
	*res_sentence << EXP("void %s_message_free(struct %s_message* msg);", {_symbol->get_symbol_value(), _symbol->get_symbol_value()});
	for(auto kvproperty : _symbol->get_properties())
	{
		switch(kvproperty->_key.get_id().get_type())
		{
		case TokenID::Type::INT64:
			*res_sentence << EXP("void %s_message_set_%s(struct %s_message* msg, %s value);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), INT64_t});
			*res_sentence << EXP("void %s_message_get_%s(%s* value, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, INT64_t, _symbol->get_symbol_value()});
		break;
		case TokenID::Type::FLOAT64:
			*res_sentence << EXP("void %s_message_set_%s(struct %s_message* msg, %s value);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), FLOAT64_t});
			*res_sentence << EXP("void %s_message_get_%s(%s* value, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, FLOAT64_t, _symbol->get_symbol_value()});
		break;
		case TokenID::Type::STRING:
			*res_sentence << EXP("void %s_message_set_%s(struct %s_message* msg, %s value);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), STRING_t});
			*res_sentence << EXP("void %s_message_get_%s(%s* value, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, STRING_t, _symbol->get_symbol_value()});
		break;
		case TokenID::Type::BOOLEAN:
			*res_sentence << EXP("void %s_message_set_%s(struct %s_message* msg, %s value);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), BOOLEAN_t});
			*res_sentence << EXP("void %s_message_get_%s(%s* value, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, BOOLEAN_t, _symbol->get_symbol_value()});
		break;
		case TokenID::Type::ARRAY:
			switch(TokenID::from_str_to_id(kvproperty->_key.get_addtion().front()).get_type())
			{
			case TokenID::Type::INT64:
				*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, %s value, int index);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), INT64_t});
				*res_sentence << EXP("int %s_message_get_%s(%s* value, int index, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, INT64_t, _symbol->get_symbol_value()});
			break;
			case TokenID::Type::FLOAT64:
				*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, %s value, int index);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), FLOAT64_t});
				*res_sentence << EXP("int %s_message_get_%s(%s* value, int index, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, FLOAT64_t, _symbol->get_symbol_value()});
			break;
			case TokenID::Type::STRING:
				*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, %s value, int index);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), STRING_t});
				*res_sentence << EXP("int %s_message_get_%s(%s* value, int index, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, STRING_t, _symbol->get_symbol_value()});
			break;
			case TokenID::Type::BOOLEAN:
				*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, %s value, int index);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), BOOLEAN_t});
				*res_sentence << EXP("int %s_message_get_%s(%s* value, int index, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, BOOLEAN_t, _symbol->get_symbol_value()});
			break;
			case TokenID::Type::ARRAY:
				throw "array<array> is no support";
			break;
			case TokenID::Type::USER:
				*res_sentence << EXP("int %s_message_get_%s(struct %s_message** value, struct %s_message* msg, int index);", {_symbol->get_symbol_value(), kvproperty->_name, kvproperty->_key.get_addtion().front(), _symbol->get_symbol_value()});
				*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, struct %s_message* value, int index);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), kvproperty->_key.get_addtion().front()});
			break;
			default:
				throw "unsupport type";
			break;
			}
		break;
		default:
			*res_sentence << EXP("int %s_message_get_%s(struct %s_message** value, struct %s_message* msg);", {_symbol->get_symbol_value(), kvproperty->_name, static_cast<std::string>(kvproperty->_key), _symbol->get_symbol_value()});
			*res_sentence << EXP("int %s_message_set_%s(struct %s_message* msg, struct %s_message* value);", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), static_cast<std::string>(kvproperty->_key)});
		break;
		}
	}
	return res_sentence;
}


std::shared_ptr<Sentence> MessageSourceGenerator::generate()
{
	auto res_sentence = EXP("");

	for(auto kvproperty : _symbol->get_properties())
	{
		auto source_property_generator = GeneratorFactory::Instance()->create_generator(_file_id, kvproperty);
		auto sentence = source_property_generator->generate();
		FileManager::Instance()->get_file(_file_id)->write(sentence);
	}
	//struct xxx_message* xxx_message_create();
	auto func_sentence = FUNC("struct %s_message* %s_message_create()", {_symbol->get_symbol_value(), _symbol->get_symbol_value()});
	*func_sentence << EXP("struct %s_message* new_msg = (struct %s_message*)malloc(sizeof(struct %s_message));", {_symbol->get_symbol_value(), _symbol->get_symbol_value(), _symbol->get_symbol_value()});
	for(auto kvproperty : _symbol->get_properties())
	{
		
		switch(kvproperty->_key.get_id().get_type())
		{
		case TokenID::Type::INT64:
			*func_sentence << EXP("new_msg->%s = 0;", {kvproperty->_name});
		break;
		case TokenID::Type::FLOAT64:
			*func_sentence << EXP("new_msg->%s = 0.0;", {kvproperty->_name});
		break;
		case TokenID::Type::STRING:
			*func_sentence << EXP("new_msg->%s = NULL;", {kvproperty->_name});
		break;
		case TokenID::Type::BOOLEAN:
			*func_sentence << EXP("new_msg->%s = 0;", {kvproperty->_name});
		break;
		case TokenID::Type::ARRAY:
			*func_sentence << EXP("new_msg->%s = %s_create(%s);", {kvproperty->_name, static_cast<std::string>(kvproperty->_key), kvproperty->_key.get_addtion()[1]});
		break;
		default:
			*func_sentence << EXP("new_msg->%s = %s_message_create();", {kvproperty->_name, static_cast<std::string>(kvproperty->_key)});
		break;
		}
	}
	*func_sentence << EXP("return new_msg;");
	*res_sentence << func_sentence;

	//free(strcut xxx_message* msg);
	func_sentence = FUNC("void %s_message_free(struct %s_message* msg)", {_symbol->get_symbol_value(), _symbol->get_symbol_value()});
	*func_sentence << EXP("if(msg == NULL) return;");
	for(auto kvproperty : _symbol->get_properties())
        {

                switch(kvproperty->_key.get_id().get_type())
                {
                case TokenID::Type::INT64:
			//pass
                break;
                case TokenID::Type::FLOAT64:
			//pass
                break;
                case TokenID::Type::STRING:
			*func_sentence << EXP("if(msg->%s != NULL) free(msg->%s);", {kvproperty->_name, kvproperty->_name});
                break;
                case TokenID::Type::BOOLEAN:
			//pass
                break;
                case TokenID::Type::ARRAY:
			*func_sentence << EXP("%s_free(msg->%s);", {static_cast<std::string>(kvproperty->_key), kvproperty->_name});
                break;
                default:
			*func_sentence << EXP("%s_message_free(msg->%s);", {static_cast<std::string>(kvproperty->_key), kvproperty->_name});
                break;
                }
        }
	*func_sentence << EXP("free(msg);");
	*res_sentence << func_sentence;

	std::shared_ptr<Sentence> if_sentence = nullptr;
	std::string type_str;
	for(auto kvproperty : _symbol->get_properties())
        {

                switch(kvproperty->_key.get_id().get_type())
                {
                case TokenID::Type::INT64:
			func_sentence = FUNC("void %s_message_get_%s(%s* value, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, INT64_t, _symbol->get_symbol_value()});
			*func_sentence << EXP("*value = msg->%s;", {kvproperty->_name});
			*func_sentence << EXP("return;\n");
			*res_sentence << func_sentence;

			func_sentence = FUNC("void %s_message_set_%s(struct %s_message* msg, %s value)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), INT64_t});
			*func_sentence << EXP("msg->%s = value;", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;
                break;
                case TokenID::Type::FLOAT64:
			func_sentence = FUNC("void %s_message_get_%s(%s* value, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, FLOAT64_t, _symbol->get_symbol_value()});
			*func_sentence << EXP("*value = msg->%s;", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;

			func_sentence = FUNC("void %s_message_set_%s(struct %s_message* msg, %s value)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), FLOAT64_t});
			*func_sentence << EXP("msg->%s = value;", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;
                break;
                case TokenID::Type::STRING:
			func_sentence = FUNC("void %s_message_get_%s(%s* value, struct %s_message* msg)",{_symbol->get_symbol_value(), kvproperty->_name, STRING_t, _symbol->get_symbol_value()});
			*func_sentence << EXP("*value = msg->%s;\n", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;

			func_sentence = FUNC("void %s_message_set_%s(struct %s_message* msg, %s value)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), STRING_t});
			*func_sentence << EXP("int len = strlen(value);");
			if_sentence = IF("msg->%s != NULL", {kvproperty->_name});
			*if_sentence << EXP("free(msg->%s);", {kvproperty->_name});
			*func_sentence << if_sentence;
			*func_sentence << EXP("msg->%s = (%s)malloc(len + 1);", {kvproperty->_name, STRING_t});
			*func_sentence << EXP("strcpy(msg->%s, value);", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;
                break;
                case TokenID::Type::BOOLEAN:
			func_sentence = FUNC("void %s_message_get_%s(%s* value, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, BOOLEAN_t, _symbol->get_symbol_value()});
			*func_sentence << EXP("*value = msg->%s;", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;
			
			func_sentence = FUNC("void %s_message_set_%s(struct %s_message* msg, %s value)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), BOOLEAN_t}); 
			*func_sentence << EXP("msg->%s = value;", {kvproperty->_name});
			*func_sentence << EXP("return;");
			*res_sentence << func_sentence;
                break;
                case TokenID::Type::ARRAY:
			type_str = static_cast<std::string>(kvproperty->_key);
			switch(TokenID::from_str_to_id(kvproperty->_key.get_addtion().front()).get_type())
			{
			case TokenID::Type::INT64:
				func_sentence = FUNC("int %s_message_get_%s(%s* value, int index, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, INT64_t, _symbol->get_symbol_value()});
				*func_sentence << EXP("return %s_get(value, msg->%s, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;

				func_sentence = FUNC("int %s_message_set_%s(struct %s_message* msg, %s value, int index)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), INT64_t});
				*func_sentence << EXP("return %s_set(msg->%s, value, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;
                        break;
                        case TokenID::Type::FLOAT64:
				func_sentence = FUNC("int %s_message_get_%s(%s* value, int index, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, FLOAT64_t, _symbol->get_symbol_value()});
				*func_sentence << EXP("return %s_get(value, msg->%s, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;

				func_sentence = FUNC("int %s_message_set_%s(struct %s_message* msg, %s value, int index)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), FLOAT64_t});
				*func_sentence << EXP("return %s_set(msg->%s, value, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;
                        break;
                        case TokenID::Type::STRING:
				func_sentence = FUNC("int %s_message_get_%s(%s* value, int index, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, STRING_t, _symbol->get_symbol_value()});
				*func_sentence << EXP("return %s_get(value, msg->%s, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;

				func_sentence = FUNC("int %s_message_set_%s(struct %s_message* msg, %s value, int index)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), STRING_t});
				*func_sentence << EXP("return %s_set(msg->%s, value, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;
                        break;
                        case TokenID::Type::BOOLEAN:
				func_sentence = FUNC("int %s_message_get_%s(%s* value, int index, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, BOOLEAN_t, _symbol->get_symbol_value()});
				*func_sentence << EXP("return %s_get(value, msg->%s, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;

				func_sentence = FUNC("int %s_message_set_%s(struct %s_message* msg, %s value, int index)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), BOOLEAN_t});
				*func_sentence << EXP("return %s_set(msg->%s, value, index);", {type_str, kvproperty->_name});
				*res_sentence << func_sentence;
                        break;
                        case TokenID::Type::ARRAY:
                                throw "array<array> is no support";
                        break;
                        case TokenID::Type::USER:
				func_sentence = FUNC("int %s_message_get_%s(struct %s_message** value, struct %s_message* msg)", {_symbol->get_symbol_value(), kvproperty->_name, kvproperty->_key.get_addtion().front(), _symbol->get_symbol_value()});
				*func_sentence << EXP("*value = msg->%s;", {kvproperty->_name});
				*func_sentence << EXP("return 0;");
				*res_sentence << func_sentence;

				func_sentence = FUNC("int %s_message_set_%s(struct %s_message* msg, struct %s_message* value)", {_symbol->get_symbol_value(), kvproperty->_name, _symbol->get_symbol_value(), kvproperty->_key.get_addtion().front()});
				if_sentence = IF("msg->%s != NULL", {kvproperty->_name});
				*if_sentence << EXP("%s_message_free(msg->%s);", {kvproperty->_key.get_addtion().front(), kvproperty->_name});
				*func_sentence << if_sentence;
				*func_sentence << EXP("msg->%s = value;", {kvproperty->_name});
				*func_sentence << EXP("return 0;");
				*res_sentence << func_sentence;
                        break;
                        default:
                                throw "unsupport type";
                        break;
			}
                break;
                default:
                        *res_sentence << EXP("%s_message_free(msg->%s);", {static_cast<std::string>(kvproperty->_key), kvproperty->_name});
                break;
                }
        }
	return res_sentence;
}
