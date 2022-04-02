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
