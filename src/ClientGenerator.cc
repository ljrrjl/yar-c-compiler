#include "ClientGenerator.h"
#include "SymbolGenerator.h"
#include "SymbolTable.h"
#include "SentenceHelper.h"

using namespace std::string_literals;

std::shared_ptr<Sentence> ClientSourceGenerator::generate()
{
	auto res_sentence = EXP("");
	auto func_sentence = FUNC("void* yar_protoc_call(char* hostname, char* group, char* func, void* input)");
	*func_sentence << EXP("yar_client *client = NULL;");
	*func_sentence << EXP("yar_packager* packager = NULL;");
	for(auto symbol : _symbols)
	{
		auto if_sentence = IF("strcmp(group, \"%s\") == 0", {symbol->get_symbol_value()});
		for(auto kvproperty : symbol->get_properties())
		{
			auto if_sentence_2 = IF("strcmp(func, \"%s\") == 0", {kvproperty->_name});
			auto input_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty->_key.get_addtion()[0]));
			auto output_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, kvproperty->_key.get_addtion()[1]));
			if(input_symbol == nullptr || output_symbol == nullptr)
			{
				throw "some message undefine";
			}
			*if_sentence_2 << EXP("struct %s_message* input_msg = (struct %s_message*)input;", {input_symbol->get_symbol_value(), input_symbol->get_symbol_value()});
			*if_sentence_2 << EXP("packager = yar_pack_start_map(%s);", {std::to_string(input_symbol->get_properties().size())});
			std::shared_ptr<Sentence> if_sentence_3 = nullptr;
			std::shared_ptr<Sentence> else_sentence_3 = nullptr;
			std::shared_ptr<Symbol> user_symbol = nullptr;
			for(auto input_kvproperty : input_symbol->get_properties())
			{
				std::shared_ptr<Sentence> for_sentence = nullptr;
                                *if_sentence_2 << EXP("yar_pack_push_string(packager, \"%s\", %s);", {input_kvproperty->_name, std::to_string(input_kvproperty->_name.length())});
                                switch(input_kvproperty->_key.get_id().get_type())
                                {
				case TokenID::Type::INT64:
                                	*if_sentence_2 << EXP("%s %s = 0;", {INT64_t, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("%s_message_get_%s(&%s, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("yar_pack_push_long(packager, %s);", {input_kvproperty->_name});
                                break;
                                case TokenID::Type::FLOAT64:
                                	*if_sentence_2 << EXP("%s %s = 0;", {FLOAT64_t, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("%s_message_get_%s(&%s, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("yar_pack_push_double(packager, %s);", {input_kvproperty->_name});
                                break;
                                case TokenID::Type::STRING:
                                	*if_sentence_2 << EXP("char* %s = NULL;", {input_kvproperty->_name});
                                	*if_sentence_2 << EXP("%s_message_get_%s(&%s, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("yar_pack_push_string(packager, %s, strlen(%s));", {input_kvproperty->_name, input_kvproperty->_name});
                                break;
                                case TokenID::Type::BOOLEAN:
                                	*if_sentence_2 << EXP("%s %s = 0;", {BOOLEAN_t, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("%s_message_get_%s(&%s, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name, input_kvproperty->_name});
                                	*if_sentence_2 << EXP("yar_pack_push_bool(packager, %s);", {input_kvproperty->_name});
                                break;
				case TokenID::Type::ARRAY:
					*if_sentence_2 << EXP("yar_pack_push_array(packager, %s);", {input_kvproperty->_key.get_addtion()[1]});
                                        switch(TokenID::from_str_to_id(input_kvproperty->_key.get_addtion()[0]).get_type())
                                        {
                                        case TokenID::Type::INT64:
						*if_sentence_2 << EXP("%s value;", {INT64_t});
						for_sentence = FOR("int i = 0; i < %s; i++", {input_kvproperty->_key.get_addtion()[1]});
						*for_sentence << EXP("%s_message_get_%s(&value, i, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name});
						*for_sentence << EXP("yar_pack_push_long(packager, value);");
						*if_sentence_2 << for_sentence;
                                        break;
                                        case TokenID::Type::FLOAT64:
						*if_sentence_2 << EXP("%s value;", {FLOAT64_t});
						for_sentence = FOR("int i = 0; i < %s; i++", {input_kvproperty->_key.get_addtion()[1]});
						*for_sentence << EXP("%s_message_get_%s(&value, i, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name});
						*for_sentence << EXP("yar_pack_push_double(packager, value);");
						*if_sentence_2 << for_sentence;
                                        break;
                                        case TokenID::Type::STRING:
						*if_sentence_2 << EXP("%s value;", {STRING_t});
						for_sentence = FOR("int i = 0; i < %s; i++", {input_kvproperty->_key.get_addtion()[1]});
						*for_sentence << EXP("%s_message_get_%s(&value, i, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name});
						if_sentence_3 = IF("value == NULL");
                                                *if_sentence_3 << EXP("yar_pack_push_string(packager, \"\", 0);");
						*for_sentence << if_sentence_3;
						else_sentence_3 = std::make_shared<ElseSentence>();
                                                *else_sentence_3 << EXP("yar_pack_push_string(packager, value, strlen(value));");
						*for_sentence << else_sentence_3;
                                		*if_sentence_2 << for_sentence;
                                        break;
					case TokenID::Type::BOOLEAN:
						*if_sentence_2 << EXP("%s value = 0;", {BOOLEAN_t});
						for_sentence = FOR("int i = 0; i < %s; i++", {input_kvproperty->_key.get_addtion()[1]});
						*for_sentence << EXP("%s_message_get_%s(&value, i, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name});
						*for_sentence << EXP("yar_pack_push_bool(packager, value);");
						*if_sentence_2 << for_sentence;
                                        break;
                                        case TokenID::Type::ARRAY:
						throw "unsupport array<array>";
                                        break;
					case TokenID::Type::USER:
                                                user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, input_kvproperty->_key.get_addtion()[0]));
                                                if(user_symbol == nullptr)
                                                {
							throw "some message undefine";
                                                }
                                                *if_sentence_2 << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
                                                for_sentence = FOR("int i = 0; i < %s; i++", {input_kvproperty->_key.get_addtion()[1]})
						*for_sentence << EXP("%s_message_get_%s(&%s_msg, input_msg, i);", {input_symbol->get_symbol_value(), input_kvproperty->_name, user_symbol->get_symbol_value()});
						if_sentence_3 = IF("%s_msg == NULL", {user_symbol->get_symbol_value()})
						*if_sentence_3 << EXP("yar_pack_push_null(packager);");
						*for_sentence << if_sentence_3;
						else_sentence_3 = std::make_shared<ElseSentence>();
						*else_sentence_3 << YarSourceGenerator::pack_map_generate(user_symbol, "packager"s);
						*for_sentence << else_sentence_3;
						*if_sentence_2 << for_sentence;
                                        break;
					default:
						throw "unsupport type";
					break;
                                        }
				break;
				case TokenID::Type::USER:
					user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, input_kvproperty->_key.get_addtion()[0]));
                                        if(user_symbol == nullptr)
                                        {
						throw "some message undefine";
                                        }
                                        *if_sentence_2 << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
                                        *if_sentence_2 << EXP("%s_message_get_%s(&%s_msg, input_msg);", {input_symbol->get_symbol_value(), input_kvproperty->_name, user_symbol->get_symbol_value()});
					*if_sentence_2 << YarSourceGenerator::pack_map_generate(user_symbol, "packager"s);
				break;
				}
			}
			*if_sentence_2 << EXP("client = yar_client_init(hostname);");
			if_sentence_3 = IF("client");
			*if_sentence_3 << EXP("int persistent = 1;");
			*if_sentence_3 << EXP("yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);");
			*if_sentence_3 << EXP("yar_response *response = client->call(client, \"yar_%s_%s_handler\", 1, &packager);", {symbol->get_symbol_value(), kvproperty->_name});
			auto if_sentence_4 = IF("response");
			*if_sentence_4 << EXP("struct %s_message* output_msg = %s_message_create();", {output_symbol->get_symbol_value(), output_symbol->get_symbol_value()});
			*if_sentence_4 << EXP("const yar_data* parameters = yar_response_get_response(response);");
			*if_sentence_4 << EXP("yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);");
			auto dowhile_sentence = DOWHILE("yar_unpack_iterator_next(it_map)");
			std::shared_ptr<Sentence> dowhile_sentence_2 = nullptr;
			*dowhile_sentence << EXP("struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);");                         
			*dowhile_sentence << EXP("uint32_t strlength = kv_data->key.via.str.size;");
			*dowhile_sentence << EXP("char* buffer = (char*)malloc(strlength + 1);");
			*dowhile_sentence << EXP("memset(buffer, 0, strlength + 1);");
			*dowhile_sentence << EXP("memcpy(buffer, kv_data->key.via.str.ptr, strlength);");
			*dowhile_sentence << EXP("yar_unpack_iterator_next(it_map);");
			for(auto output_kvproperty : output_symbol->get_properties())
			{
				auto if_sentence_5 = IF("strcmp(buffer, \"%s\") == 0", {output_kvproperty->_name});
				std::shared_ptr<Sentence> if_sentence_6 = nullptr;
				std::shared_ptr<Sentence> else_sentence_6 = nullptr;
				switch(output_kvproperty->_key.get_id().get_type())
				{
				case TokenID::Type::INT64:
					*if_sentence_5 << EXP("%s_message_set_%s(output_msg, kv_data->val.via.i64);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
				break;
				case TokenID::Type::FLOAT64:
					*if_sentence_5 << EXP("%s_message_set_%s(output_msg, kv_data->val.via.f64);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
				break;
				case TokenID::Type::STRING:
					*if_sentence_5 << EXP("uint32_t val_strlength = kv_data->val.via.str.size;");
					*if_sentence_5 << EXP("char* str = (char*)malloc(val_strlength + 1);");
					*if_sentence_5 << EXP("memset(str, 0, val_strlength + 1);");
					*if_sentence_5 << EXP("memcpy(str, kv_data->val.via.str.ptr, val_strlength);");
					*if_sentence_5 << EXP("%s_message_set_%s(output_msg, str);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
					*if_sentence_5 << EXP("free(str);");
				break;
				case TokenID::Type::BOOLEAN:
					*if_sentence_5 << EXP("%s_message_set_%s(output_msg, kv_data->val.via.boolean);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
				break;
				case TokenID::Type::ARRAY:
					*if_sentence_5 << EXP("const yar_data* %s_data = yar_unpack_iterator_current(it_map);", {output_kvproperty->_name});
					*if_sentence_5 << EXP("yar_unpack_iterator* %s_it_array = yar_unpack_iterator_init(%s_data);", {output_kvproperty->_name, output_kvproperty->_name});
					switch(TokenID::from_str_to_id(output_kvproperty->_key.get_addtion()[0]).get_type())
					{
					case TokenID::Type::INT64:
						*if_sentence_5 << EXP("int index = 0;");
						dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("%s value = 0;", {INT64_t});
						*dowhile_sentence_2 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("yar_unpack_data_value(array_value, &value);");
						*dowhile_sentence_2 << EXP("%s_message_set_%s(output_msg, value, index);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("index++;");
						*if_sentence_5 << dowhile_sentence_2;
						*if_sentence_5 << EXP("yar_unpack_iterator_free(%s_it_array);", {output_kvproperty->_name});
					break;
					case TokenID::Type::FLOAT64:
						*if_sentence_5 << EXP("int index = 0;");
						dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("%s value = 0;", {FLOAT64_t});
						*dowhile_sentence_2 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("yar_unpack_data_value(array_value, &value);");
						*dowhile_sentence_2 << EXP("%s_message_set_%s(output_msg, value, index);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("index++;");
						*if_sentence_5 << EXP("yar_unpack_iterator_free(%s_it_array);", {output_kvproperty->_name});
					break;
					case TokenID::Type::STRING:
						*if_sentence_5 << EXP("int index = 0;");
						dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("%s value = NULL;", {STRING_t});
						*dowhile_sentence_2 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("msgpack_object* obj = (msgpack_object*)array_value;");
						*dowhile_sentence_2 << EXP("int length = obj->via.str.size;");
						*dowhile_sentence_2 << EXP("value = (char*)malloc(length + 1);");
						*dowhile_sentence_2 << EXP("memset(value, 0, length + 1);");
						*dowhile_sentence_2 << EXP("memcpy(value, obj->via.str.ptr, length);");
						*dowhile_sentence_2 << EXP("%s_message_set_%s(output_msg, value, index);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("free(value);");
						*dowhile_sentence_2 << EXP("index++;");
						*if_sentence_5 << dowhile_sentence_2;
						*if_sentence_5 << EXP("yar_unpack_iterator_free(%s_it_array);", {output_kvproperty->_name});
					break;
					case TokenID::Type::BOOLEAN:
						*if_sentence_5 << EXP("int index = 0;");
						dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("%s value = 0;", {BOOLEAN_t});
						*dowhile_sentence_2 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("struct msgpack_object* obj = (struct msgpack_object*)array_value;");
						*dowhile_sentence_2 << EXP("value = obj->via.boolean;");
						*dowhile_sentence_2 << EXP("%s_message_set_%s(output_msg, value, index);", {output_symbol->get_symbol_value(), output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("index++;");
						*if_sentence_5 << dowhile_sentence_2;
						*if_sentence_5 << EXP("yar_unpack_iterator_free(%s_it_array);", {output_kvproperty->_name});
					break;
					case TokenID::Type::ARRAY:
						throw "unsupport array<array>";
					break;
					case TokenID::Type::USER:
						user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, output_kvproperty->_key.get_addtion()[0]));
						if(user_symbol == nullptr)
						{
							throw "some message undefine";
						}
						*if_sentence_5 << EXP("int index = 0;");
						dowhile_sentence_2 = DOWHILE("yar_unpack_iterator_next(%s_it_array)", {output_kvproperty->_name});
						*dowhile_sentence_2 << EXP("struct %s_message* %s_msg = NULL;", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
						*dowhile_sentence_2 << EXP("uint dummy = 0;");
						*dowhile_sentence_2 << EXP("const yar_data* array_value = yar_unpack_iterator_current(%s_it_array);", {output_kvproperty->_name});
						if_sentence_6 = IF("yar_unpack_data_type(array_value, &dummy) == YAR_DATA_NULL");
						*if_sentence_6 << EXP("//pass");
						*dowhile_sentence_2 << if_sentence_6;
						else_sentence_6 = std::make_shared<ElseSentence>();
						*else_sentence_6 << EXP("%s_msg = %s_message_create();", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
						*else_sentence_6 << YarSourceGenerator::unpack_map_generate(user_symbol, "array_value"s);
						*else_sentence_6 << EXP("%s_message_set_%s(output_msg, %s_msg, index);", {output_symbol->get_symbol_value(), output_kvproperty->_name, user_symbol->get_symbol_value()});
						*dowhile_sentence_2 << else_sentence_6;
						*dowhile_sentence_2 << EXP("index++;");
						*if_sentence_5 << dowhile_sentence_2;
						*if_sentence_5 << EXP("yar_unpack_iterator_free(%s_it_array);", {output_kvproperty->_name});
					break;
					default:
						throw "unsupport type";
					break;
					}
				break;
				case TokenID::Type::USER:
					user_symbol = SymbolTable::Instance()->find(SymbolID(SymbolID::Type::MESSAGE, output_kvproperty->_key.get_addtion()[0]));
					if(user_symbol == nullptr)
					{
						throw "some message undefine";
					}
					*if_sentence_5 << EXP("struct %s_message* %s_msg = %s_message_create();", {user_symbol->get_symbol_value(), user_symbol->get_symbol_value(), user_symbol->get_symbol_value()});
					*if_sentence_5 << EXP("const yar_data* %s_yar_data = yar_unpack_iterator_current(it_map);", {user_symbol->get_symbol_value()});
					*if_sentence_5 << YarSourceGenerator::unpack_map_generate(user_symbol, user_symbol->get_symbol_value() + "_yar_data"s);
					*if_sentence_5 << EXP("%s_message_set_%s(output_msg, %s_msg);", {output_symbol->get_symbol_value(), output_kvproperty->_name, user_symbol->get_symbol_value()});
				break;
				default:
					throw "unsupport type";
				break;
				}
				*dowhile_sentence << if_sentence_5;
			}
			*dowhile_sentence << EXP("free(buffer);");
			*if_sentence_4 << dowhile_sentence;
			*if_sentence_4 << EXP("yar_unpack_iterator_free(it_map);");
			*if_sentence_4 << EXP("yar_response_free(response);");
			*if_sentence_4 << EXP("free(response);");
			*if_sentence_4 << EXP("yar_client_destroy(client);");
			*if_sentence_4 << EXP("yar_pack_free(packager);");
			*if_sentence_4 << EXP("packager = NULL;");
			*if_sentence_4 << EXP("return output_msg;");
			*if_sentence_3 << if_sentence_4;
			*if_sentence_2 << if_sentence_3;
			*if_sentence << if_sentence_2;
			*func_sentence << if_sentence;
			*func_sentence << EXP("return NULL;");
		}
	}
	*res_sentence << func_sentence;
	return res_sentence;
}

std::shared_ptr<Sentence> ClientHeaderGenerator::generate()
{
	auto res_sentence = EXP("void* yar_protoc_call(char* hostname, char* group, char* func, void* input);");
	return res_sentence;
}
