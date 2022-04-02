#include "PropertyGenerator.h"
#include "FileManager.h"
#include "SentenceHelper.h"

using namespace std::string_literals;

std::shared_ptr<Sentence> MessagePropertyGenerator::generate()
{
	std::shared_ptr<Sentence> sentence = std::make_shared<Sentence>();
	int align_old = 0;
	std::string type_str;
	switch(_kvproperty->_key.get_id().get_type())
	{
	case TokenID::Type::INT64:
		*sentence << EXP("%s %s;", {INT64_t, _kvproperty->_name});
	break;
	case TokenID::Type::FLOAT64:
		*sentence << EXP("%s %s;", {FLOAT64_t, _kvproperty->_name});
	break;
	case TokenID::Type::STRING:
		*sentence << EXP("%s %s;", {STRING_t, _kvproperty->_name});
	break;
	case TokenID::Type::BOOLEAN:
		*sentence << EXP("%s %s;", {BOOLEAN_t, _kvproperty->_name});
	break;
	case TokenID::Type::ARRAY:
		align_old = sentence->get_align();
		FileManager::Instance()->get_file(_file_id)->write(generate_array());
		sentence->set_align(align_old);

		type_str = static_cast<std::string>(_kvproperty->_key);
		*sentence << EXP("struct %s* %s;", {type_str, _kvproperty->_name});
	break;
	default:
	break;
	}
	return sentence;
}

std::shared_ptr<Sentence> MessagePropertyGenerator::generate_array()
{
	auto res_sentence_ptr = EXP("");
	std::string type_str = static_cast<std::string>(_kvproperty->_key);
	auto struct_sentence_ptr = STRUCT(type_str);
	*struct_sentence_ptr << EXP("int size;");
	switch(TokenID::from_str_to_id(_kvproperty->_key.get_addtion().front()).get_type())
	{
	case TokenID::Type::INT64:
		*struct_sentence_ptr << EXP("%s* value;",{INT64_t});
		*res_sentence_ptr << struct_sentence_ptr;

		*res_sentence_ptr << EXP("struct %s* %s_create(int size);", {type_str, type_str});
		*res_sentence_ptr << EXP("int %s_get(%s* value, struct %s* array, int index);", {type_str, INT64_t, type_str});
		*res_sentence_ptr << EXP("int %s_set(struct %s* array, %s value, int index);", {type_str, type_str, INT64_t});
		*res_sentence_ptr << EXP("void %s_free(struct %s* array);", {type_str, type_str});
	break;
	case TokenID::Type::FLOAT64:
		*struct_sentence_ptr << EXP("%s* value;", {FLOAT64_t});
		*res_sentence_ptr << struct_sentence_ptr;

		*res_sentence_ptr << EXP("struct %s* %s_create(int size);", {type_str, type_str});
		*res_sentence_ptr << EXP("int %s_get(%s* value, struct %s* array, int index);", {type_str, FLOAT64_t, type_str});
		*res_sentence_ptr << EXP("int %s_set(struct %s* array, %s value, int index);", {type_str, type_str, FLOAT64_t});
		*res_sentence_ptr << EXP("void %s_free(struct %s* array);", {type_str, type_str});
	break;
	}	
	return res_sentence_ptr;
}
