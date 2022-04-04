#include "SymbolGenerator.h"
#include "SymbolTable.h"
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

std::shared_ptr<Sentence> RpcHeaderGenerator::generate()
{
	auto res_sentence = EXP("");
	for(auto kvproperty : _symbol->get_properties())
	{
		switch(kvproperty->_key.get_id().get_type())
		{
		case TokenID::Type::RPC:
			*res_sentence << EXP("void %s_%s_handler(struct %s_message* input, struct %s_message* output);", {_symbol->get_symbol_value(), kvproperty->_name, kvproperty->_key.get_addtion()[0], kvproperty->_key.get_addtion()[1]});
			*res_sentence << EXP("void yar_%s_%s_handler(yar_request* input, yar_response* output, void* cookie);", {_symbol->get_symbol_value(), kvproperty->_name});
		break;
		default:
			throw "unsupport rpc type";
		break;
		}
	}
	return res_sentence;
}

std::shared_ptr<Sentence> RpcSourceGenerator::generate()
{
	auto res_sentence = EXP("");
	std::shared_ptr<Sentence> func_sentence = nullptr;
	for(auto kvproperty : _symbol->get_properties())
	{
		switch(kvproperty->_key.get_id().get_type())
		{
		case TokenID::Type::RPC:
			func_sentence = FUNC("void %s_%s_handler(struct %s_message* input, struct %s_message* output)", {_symbol->get_symbol_value(), kvproperty->_name, kvproperty->_key.get_addtion()[0], kvproperty->_key.get_addtion()[1]});
			*func_sentence << EXP("//Enter the code here...\n");
			*res_sentence << func_sentence;
		break;
		default:
			throw "unsupport rpc type";
		break;
		}
	}
	return res_sentence;
}

std::shared_ptr<Sentence> YarSourceGenerator::generate()
{
	auto res_sentence = EXP("");
	for(auto kvproperty : _symbol->get_properties())
	{
		auto input_symbol_ptr = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty->_key.get_addtion()[0]));
		auto output_symbol_ptr = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty->_key.get_addtion()[1]));
		if(input_symbol_ptr == nullptr || output_symbol_ptr == nullptr)
		{
			throw "some message is no defined.";
		}
		auto func_sentence = FUNC("void yar_%s_%s_handler(yar_request* input, yar_response* output, void* cookie)", {_symbol->get_symbol_value(), kvproperty->_name});
		*func_sentence << EXP("yar_packager* packager = NULL;");
		*func_sentence << EXP("struct %s_message* input_msg = %s_message_create();", {input_symbol_ptr->get_symbol_value(), input_symbol_ptr->get_symbol_value()});
		*func_sentence << EXP("const yar_data* parameters = yar_request_get_parameters(input);");
		*func_sentence << EXP("yar_unpack_iterator* it_array = yar_unpack_iterator_init(parameters);");
		auto dowhile_sentence = DOWHILE("yar_unpack_iterator_next(it_array)");

		*dowhile_sentence << EXP("const yar_data* map_data = yar_unpack_iterator_current(it_array);");
		*dowhile_sentence << EXP("yar_unpack_iterator* it_map = yar_unpack_iterator_init(map_data);");
		auto dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(it_map)");

		*dowhile_sentence_2 << EXP("struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);");
		*dowhile_sentence_2 << EXP("uint32_t strlength = kv_data->key.via.str.size;");
		*dowhile_sentence_2 << EXP("char* buffer = (char*)malloc(strlength + 1);");
		*dowhile_sentence_2 << EXP("memset(buffer, 0, strlength + 1);");
		*dowhile_sentence_2 << EXP("memcpy(buffer, kv_data->key.via.str.ptr, strlength);");
		*dowhile_sentence_2 << EXP("yar_unpack_iterator_next(it_map);");

		for(auto kvproperty_input : input_symbol_ptr->get_properties())
		{
			auto if_sentence = IF("strcmp(buffer, \"%s\") == 0", {kvproperty_input->_name});
			std::shared_ptr<Sentence> dowhile_sentence_3 = nullptr;
			std::shared_ptr<Sentence> if_sentence_2 = nullptr;
			std::shared_ptr<Sentence> else_sentence = nullptr;
			std::shared_ptr<Symbol> user_symbol = nullptr;
			switch(kvproperty_input->_key.get_id().get_type())
			{
			case TokenID::Type::INT64:
				*if_sentence << EXP("%s_message_set_%s(input_msg, kv_data->val.via.i64);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
			break;
			case TokenID::Type::FLOAT64:
				*if_sentence << EXP("%s_message_set_%s(input_msg, kv_data->val.via.f64);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
			break;
			case TokenID::Type::STRING:
				*if_sentence << EXP("uint32_t val_strlength = kv_data->val.via.str.size;");
				*if_sentence << EXP("char* str = (char*)malloc(val_strlength + 1);");
				*if_sentence << EXP("memset(str, 0, val_strlength + 1);");
				*if_sentence << EXP("memcpy(str, kv_data->val.via.str.ptr, val_strlength);");
				*if_sentence << EXP("%s_message_set_%s(input_msg, str);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
				*if_sentence << EXP("free(str);");
			break;
			case TokenID::Type::BOOLEAN:
				*if_sentence << EXP("%s_message_set_%s(input_msg, kv_data->val.via.boolean);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
			break;
			case TokenID::Type::ARRAY:
				*if_sentence << EXP("const yar_data* %s_data = yar_unpack_iterator_current(it_map);", {kvproperty_input->_name});
				*if_sentence << EXP("yar_unpack_iterator* %s_it_array = yar_unpack_iterator_init(%s_data);", {kvproperty_input->_name, kvproperty_input->_name});
				switch(TokenID::from_str_to_id(kvproperty_input->_key.get_addtion()[0]).get_type())
				{
				case TokenID::Type::INT64:
					*if_sentence << EXP("int index = 0;");
					dowhile_sentence_3 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("%s value = 0;", {INT64_t});
					*dowhile_sentence_3 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("yar_unpack_data_value(array_value, &value);");
					*dowhile_sentence_3 << EXP("%s_message_set_%s(input_msg, value, index);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("index++;");
					*if_sentence << dowhile_sentence_3;
					*if_sentence << EXP("yar_unpack_iterator_free(%s_it_array);", {kvproperty_input->_name});
				break;
				case TokenID::Type::FLOAT64:
					*if_sentence << EXP("int index = 0;");
					dowhile_sentence_3 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("%s value = 0;", {FLOAT64_t});
					*dowhile_sentence_3 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("yar_unpack_data_value(array_value, &value);");
					*dowhile_sentence_3 << EXP("%s_message_set_%s(input_msg, value, index);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("index++;");
					*if_sentence << dowhile_sentence_3;
					*if_sentence << EXP("yar_unpack_iterator_free(%s_it_array);", {kvproperty_input->_name});
				break;
				case TokenID::Type::STRING:
					*if_sentence << EXP("int index = 0;");
					dowhile_sentence_3 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("%s value = NULL;", {STRING_t});
					*dowhile_sentence_3 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("msgpack_object* obj = (msgpack_object*)array_value;");
					*dowhile_sentence_3 << EXP("int length = obj->via.str.size;");
					*dowhile_sentence_3 << EXP("value = (char*)malloc(length + 1);");
					*dowhile_sentence_3 << EXP("memset(value, 0, length + 1);");
					*dowhile_sentence_3 << EXP("memcpy(value, obj->via.str.ptr, length);");
					*dowhile_sentence_3 << EXP("%s_message_set_%s(input_msg, value, index);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("free(value);");
					*dowhile_sentence_3 << EXP("index++;");
					*if_sentence << dowhile_sentence_3;

					*if_sentence << EXP("yar_unpack_iterator_free(%s_it_array);", {kvproperty_input->_name});
				break;
				case TokenID::Type::BOOLEAN:
					*if_sentence << EXP("int index = 0;");
					dowhile_sentence_3 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {kvproperty_input->_name});	
					*dowhile_sentence_3 << EXP("%s value = 0;", {BOOLEAN_t});
					*dowhile_sentence_3 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("struct msgpack_object* obj = (struct msgpack_object*)array_value;");
					*dowhile_sentence_3 << EXP("value = obj->via.boolean;");
					*dowhile_sentence_3 << EXP("%s_message_set_%s(input_msg, value, index);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("index++;");
					*if_sentence << dowhile_sentence_3;

					*if_sentence << EXP("yar_unpack_iterator_free(%s_it_array);", {kvproperty_input->_name});
				break;
				case TokenID::Type::ARRAY:
					throw "unsupport array<array>";
				break;
				case TokenID::Type::USER:
					user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty_input->_key.get_addtion()[0]));	
					if(user_symbol == nullptr)
					{
						throw "some message no define";
					}
					*if_sentence << EXP("int index = 0;");
					dowhile_sentence_3 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {kvproperty_input->_name});
					*dowhile_sentence_3 << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
					*dowhile_sentence_3 << EXP("uint dummy = 0;");
					*dowhile_sentence_3 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {kvproperty_input->_name});
					if_sentence_2 = IF("yar_unpack_data_type(array_value, &dummy) == YAR_DATA_NULL");
					*if_sentence_2 << EXP("//pass");
					*dowhile_sentence_3 << if_sentence_2;
					else_sentence = std::make_shared<ElseSentence>();
					*else_sentence << EXP("%s_msg = %s_message_create();", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
					*else_sentence << unpack_map_generate(user_symbol);
					*else_sentence << EXP("%s_message_set_%s(input_msg, %s_msg, index);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name, user_symbol->get_symbol_value()});
					*dowhile_sentence_3 << else_sentence;

					*dowhile_sentence_3 << EXP("index++;");
					*if_sentence << EXP("yar_unpack_iterator_free(%s_it_array);", {kvproperty_input->_name});
				break;
				default:
					throw "unsupport type";
				break;
				}
			break;
			case TokenID::Type::USER:
				user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty_input->_key.get_addtion()[0]));
				if(user_symbol == nullptr)
				{
					throw "some message undefine";
				}
				*if_sentence << EXP("struct %s_message* %s_msg = %s_message_create();", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
				*if_sentence << EXP("const yar_data* %s_yar_data = yar_unpack_iterator_current(it_map);", {user_symbol->get_symbol_value()});
				*if_sentence << unpack_map_generate(user_symbol);
				*if_sentence << EXP("%s_message_set_%s(input_msg, %s_msg);", {input_symbol_ptr->get_symbol_value(), kvproperty_input->_name, user_symbol->get_symbol_value()});
			break;
			}
			*dowhile_sentence_2 << if_sentence;
		}
		*dowhile_sentence_2 << EXP("free(buffer);");
		*dowhile_sentence << dowhile_sentence_2;
		*dowhile_sentence << EXP("yar_unpack_iterator_free(it_map);");
		*func_sentence << dowhile_sentence;
		
		*func_sentence << EXP("yar_unpack_iterator_free(it_array);\n");
		
		//call user's callback
		*func_sentence << EXP("struct %s_message* output_msg = %s_message_create();", {output_symbol_ptr->get_symbol_value(), output_symbol_ptr->get_symbol_value()});
		*func_sentence << EXP("%s_%s_handler(input_msg, output_msg);", {_symbol->get_symbol_value(), kvproperty->_name});
		*func_sentence << EXP("packager = yar_pack_start_map(%s);", {std::to_string(output_symbol_ptr->get_properties().size())});

		std::shared_ptr<Sentence> for_sentence = nullptr;
		std::shared_ptr<Sentence> if_sentence = nullptr;
		std::shared_ptr<Sentence> else_sentence = nullptr;
		std::shared_ptr<Symbol> user_symbol = nullptr;
		for(auto kvproperty_output : output_symbol_ptr->get_properties())
		{
			*func_sentence << EXP("yar_pack_push_string(packager, \"%s\", %s);", {kvproperty_output->_name, std::to_string(kvproperty_output->_name.length())});
			switch(kvproperty_output->_key.get_id().get_type())
			{
			case TokenID::Type::INT64:
				*func_sentence << EXP("%s response_number = 0;", {INT64_t});
				*func_sentence << EXP("%s_message_get_%s(&response_number, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
				*func_sentence << EXP("yar_pack_push_long(packager, response_number);");
			break;
			case TokenID::Type::FLOAT64:
				*func_sentence << EXP("%s response_number = 0;", {FLOAT64_t});
				*func_sentence << EXP("%s_message_get_%s(&response_number, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
				*func_sentence << EXP("yar_pack_push_double(packager, response_number);");
			break;
			case TokenID::Type::STRING:
				*func_sentence << EXP("%s response_number = NULL;", {STRING_t});
				*func_sentence << EXP("%s_message_get_%s(&response_number, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
				*func_sentence << EXP("yar_pack_push_string(packager, response_number, strlen(response_number));");
			break;
			case TokenID::Type::BOOLEAN:
				*func_sentence << EXP("%s response_number = 0;", {BOOLEAN_t});
				*func_sentence << EXP("%s_message_get_%s(&response_number, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
				*func_sentence << EXP("yar_pack_push_bool(packager, response_number);");
			break;
			case TokenID::Type::ARRAY:
				*func_sentence << EXP("yar_pack_push_array(packager, %s);", {kvproperty_output->_key.get_addtion()[1]});
				switch(TokenID::from_str_to_id(kvproperty_output->_key.get_addtion()[0]).get_type())
				{
				case TokenID::Type::INT64:
					*func_sentence << EXP("%s value;", {INT64_t});
					for_sentence = FOR("int i = 0; i < %s; i++", {kvproperty_output->_key.get_addtion()[1]});
					*for_sentence << EXP("%s_message_get_%s(&value, i, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
					*for_sentence << EXP("yar_pack_push_long(packager, value);");
					*func_sentence << for_sentence;
				break;
				case TokenID::Type::FLOAT64:
					*func_sentence << EXP("%s value;", {FLOAT64_t});
					for_sentence = FOR("int i = 0; i < %s; i++", {kvproperty_output->_key.get_addtion()[1]});
					*for_sentence << EXP("%s_message_get_%s(&value, i, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
					*for_sentence << EXP("yar_pack_push_double(packager, value);");
					*func_sentence << for_sentence;
				break;
				case TokenID::Type::STRING:
					*func_sentence << EXP("%s value;", {STRING_t});
					for_sentence = FOR("int i = 0; i < %s; i++", {kvproperty_output->_key.get_addtion()[1]});
					*for_sentence << EXP("%s_message_get_%s(&value, i, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
					if_sentence = IF("value == NULL");
					*if_sentence << EXP("yar_pack_push_string(packager, \"\", 0);");
					*for_sentence << if_sentence;
					else_sentence = std::make_shared<ElseSentence>();
					*else_sentence << EXP("yar_pack_push_string(packager, value, strlen(value));");
					*for_sentence << else_sentence;
					*func_sentence << for_sentence;
				break;
				case TokenID::Type::BOOLEAN:
					*func_sentence << EXP("%s value;", {BOOLEAN_t});
					for_sentence = FOR("int i = 0; i < %s; i++", {kvproperty_output->_key.get_addtion()[1]});
					*for_sentence << EXP("%s_message_get_%s(&value, i, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name});
					*for_sentence << EXP("yar_pack_push_bool(packager, value);");
					*func_sentence << for_sentence;
				break;
				case TokenID::Type::ARRAY:
					throw "unsupport array<array>";
				break;
				case TokenID::Type::USER:
					user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty_output->_key.get_addtion()[0]));
					if(user_symbol == nullptr)
					{
						throw "some message undefine";
					}
					*func_sentence << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
					for_sentence = FOR("int i = 0; i < %s; i++", {kvproperty_output->_key.get_addtion()[1]});
					*for_sentence << EXP("%s_message_get_%s(&%s_msg, output_msg, i);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name, user_symbol->get_symbol_value()});
					if_sentence = IF("%s_msg == NULL", {user_symbol->get_symbol_value()});
					*if_sentence << EXP("yar_pack_push_null(packager);");
					*for_sentence << if_sentence;
					else_sentence = std::make_shared<ElseSentence>();
					*else_sentence << pack_map_generate(user_symbol);
					*for_sentence << else_sentence;
					*func_sentence << for_sentence;
				break;
				default:
					throw "unsupport type";
				break;
				}
			break;
			case TokenID::Type::USER:
				user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty_output->_key.get_addtion()[0]));
				if(user_symbol == nullptr)
				{
					throw "some message undefine";
				}
				*func_sentence << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
				*func_sentence << EXP("%s_message_get_%s(&%s_msg, output_msg);", {output_symbol_ptr->get_symbol_value(), kvproperty_output->_name, user_symbol->get_symbol_value()});
				*func_sentence << pack_map_generate(user_symbol);
			break;
			default:
				throw "unsupport type";
			break;
			}
		}
		*func_sentence << EXP("yar_response_set_retval(output, packager);");
		*func_sentence << EXP("yar_pack_free(packager);");
		*func_sentence << EXP("%s_message_free(output_msg);", {output_symbol_ptr->get_symbol_value()});
		*func_sentence << EXP("%s_message_free(input_msg);", {input_symbol_ptr->get_symbol_value()});

		*res_sentence << func_sentence;
	}
	return res_sentence;
}
