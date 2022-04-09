/**
 * @file src/PropertyGenerator.cc
 * @brief generate for Property
 * @details Generate Sentence for each Property in Symbol
 * @author jiarui.liu
 * @email jiarui-liu@qq.com
 * @version v0.1
 * @date 2022-04-06
 */

#include "PropertyGenerator.h"
#include "FileManager.h"
#include "SentenceHelper.h"

using namespace std::string_literals;

std::shared_ptr<Sentence> MessagePropertyHeaderGenerator::generate()
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
		*sentence << EXP("struct %s_message* %s;", {static_cast<std::string>(_kvproperty->_key), _kvproperty->_name});
	break;
	}

	return sentence;
}

std::shared_ptr<Sentence> MessagePropertyHeaderGenerator::generate_array()
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
	case TokenID::Type::STRING:
		*struct_sentence_ptr << EXP("%s* value;", {STRING_t});
		*res_sentence_ptr << struct_sentence_ptr;

		 *res_sentence_ptr << EXP("struct %s* %s_create(int size);", {type_str, type_str});
		 *res_sentence_ptr << EXP("int %s_get(%s* value, struct %s* array, int index);", {type_str, STRING_t, type_str});
		 *res_sentence_ptr << EXP("int %s_set(struct %s* array, %s value, int index);", {type_str, type_str, STRING_t});
		 *res_sentence_ptr << EXP("void %s_free(struct %s* array);", {type_str, type_str});
	break;
	case TokenID::Type::BOOLEAN:
		*struct_sentence_ptr << EXP("%s* value;", {BOOLEAN_t});
		*res_sentence_ptr << struct_sentence_ptr;

		*res_sentence_ptr << EXP("struct %s* %s_create(int size);", {type_str, type_str});
		*res_sentence_ptr << EXP("int %s_get(%s* value, struct %s* array, int index);", {type_str, BOOLEAN_t, type_str});
		*res_sentence_ptr << EXP("int %s_set(struct %s* array, %s value, int index);", {type_str, type_str, BOOLEAN_t});
		*res_sentence_ptr << EXP("void %s_free(struct %s* array);", {type_str, type_str});
	break;
	case TokenID::Type::ARRAY:
		throw "array<array> no support";
	break;
	default:
		*struct_sentence_ptr << EXP("struct %s_message** value;\n", {_kvproperty->_key.get_addtion().front()});
		*res_sentence_ptr << struct_sentence_ptr;

		*res_sentence_ptr << EXP("struct %s* %s_create(int size);", {type_str, type_str});
		*res_sentence_ptr << EXP("int %s_get(struct %s_message** value, struct %s* array, int index);", {type_str, _kvproperty->_key.get_addtion().front(), type_str});
		*res_sentence_ptr << EXP("int %s_set(struct %s* array, struct %s_message* value, int index);", {type_str, type_str, _kvproperty->_key.get_addtion().front()});
		*res_sentence_ptr << EXP("void %s_free(struct %s* array);", {type_str, type_str});
	break;
	}
	*res_sentence_ptr << EXP("int %s_size(struct %s* array);", {type_str, type_str});
	return res_sentence_ptr;
}

std::shared_ptr<Sentence> MessagePropertySourceGenerator::generate()
{
	switch(_kvproperty->_key.get_id().get_type())
	{
	case TokenID::Type::ARRAY:
		return generate_array();
	break;
	}
	return nullptr;
}

std::shared_ptr<Sentence> MessagePropertySourceGenerator::generate_array()
{
	auto res_sentence = EXP("");	
	std::shared_ptr<Sentence> func_sentence = nullptr;
	std::shared_ptr<Sentence> if_sentence = nullptr;
	std::shared_ptr<Sentence> if_if_sentence = nullptr;
	std::shared_ptr<Sentence> else_sentence = nullptr;
	std::shared_ptr<Sentence> for_sentence = nullptr;
	std::string type_str = static_cast<std::string>(_kvproperty->_key);
	switch(TokenID::from_str_to_id(_kvproperty->_key.get_addtion().front()).get_type())
	{
	case TokenID::Type::INT64:
		func_sentence = FUNC("struct %s* %s_create(int size)", {type_str, type_str});
		*func_sentence << EXP("struct %s* new_array = (struct %s*)malloc(sizeof(struct %s));", {type_str, type_str, type_str});
		*func_sentence << EXP("new_array->size = size;");
		*func_sentence << EXP("new_array->value = (%s*)malloc(sizeof(%s) * (new_array->size));", {INT64_t, INT64_t});
		*func_sentence << EXP("return new_array;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_get(%s* value, struct %s* array, int index)", {type_str, INT64_t, type_str});
		*func_sentence << EXP("%s* vvalue = (%s*)value;", {INT64_t, INT64_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("*vvalue = (array->value)[index];");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_set(struct %s* array, %s value, int index)", {type_str, type_str, INT64_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("array->value[index] = value;");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("void %s_free(struct %s* array)", {type_str, type_str});
		if_sentence = IF("array != NULL && array->value != NULL");
		*if_sentence << EXP("free(array->value);");
		*func_sentence << if_sentence;
		if_sentence = IF("array != NULL");
		*if_sentence << EXP("free(array);");
		*func_sentence << if_sentence;
		*res_sentence << func_sentence;
	break;
	case TokenID::Type::FLOAT64:
		func_sentence = FUNC("struct %s* %s_create(int size)", {type_str, type_str});
		*func_sentence << EXP("struct %s* new_array = (struct %s*)malloc(sizeof(struct %s));", {type_str, type_str, type_str});
		*func_sentence << EXP("new_array->size = size;");
		*func_sentence << EXP("new_array->value = (%s*)malloc(sizeof(%s) * (new_array->size));", {FLOAT64_t, FLOAT64_t});
		*func_sentence << EXP("return new_array;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_get(%s* value, struct %s* array, int index)", {type_str, FLOAT64_t, type_str});
		*func_sentence << EXP("%s* vvalue = (%s*)value;", {FLOAT64_t, FLOAT64_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("*vvalue = (array->value)[index];");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_set(struct %s* array, %s value, int index)", {type_str, type_str, FLOAT64_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("array->value[index] = value;");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("void %s_free(struct %s* array)", {type_str, type_str});
		if_sentence = IF("array != NULL && array->value != NULL");
		*if_sentence << EXP("free(array->value);");
		*func_sentence << if_sentence;
		if_sentence = IF("array != NULL");
		*if_sentence << EXP("free(array);");
		*func_sentence << if_sentence;
		*res_sentence << func_sentence;
	break;
	case TokenID::Type::STRING:
		func_sentence = FUNC("struct %s* %s_create(int size)", {type_str, type_str});
		*func_sentence << EXP("struct %s* new_array = (struct %s*)malloc(sizeof(struct %s));", {type_str, type_str, type_str});
		*func_sentence << EXP("new_array->size = size;");
		*func_sentence << EXP("new_array->value = (%s*)malloc(sizeof(%s) * (new_array->size));", {STRING_t, STRING_t});
		*func_sentence << EXP("memset(new_array->value, 0, sizeof(%s) * (new_array->size));", {STRING_t});
		*func_sentence << EXP("return new_array;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_get(%s* value, struct %s* array, int index)", {type_str, STRING_t, type_str});
		*func_sentence << EXP("%s* vvalue = (%s*)value;", {STRING_t, STRING_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("*vvalue = (array->value)[index];");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_set(struct %s* array, %s value, int index)", {type_str, type_str, STRING_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		if_sentence = IF("array->value[index] != NULL");
		*if_sentence << EXP("free(array->value[index]);");
		*func_sentence << if_sentence;
		*func_sentence << EXP("array->value[index] = (%s)malloc(strlen(value) + 1);", {STRING_t});
		*func_sentence << EXP("strcpy(array->value[index], value);");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("void %s_free(struct %s* array)", {type_str, type_str});
		*func_sentence << EXP("int i = 0;");
		if_sentence = IF("array != NULL");
		for_sentence = FOR("i = 0; i < array->size; i++");
		if_if_sentence = IF("array->value[i] != NULL");
		*if_if_sentence << EXP("free(array->value[i]);");
		*if_sentence << for_sentence;
		*if_sentence << EXP("free(array->value);");
		*if_sentence << EXP("free(array);");
		*func_sentence << if_sentence;
		*res_sentence << func_sentence;
	break;
	case TokenID::Type::BOOLEAN:
		func_sentence = FUNC("struct %s* %s_create(int size)", {type_str, type_str});
		*func_sentence << EXP("int buffer_size = size / 8;");
		if_sentence = IF("size % 8 != 0");
		*if_sentence << EXP("buffer_size++;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("struct %s* new_array = (struct %s*)malloc(sizeof(struct %s));", {type_str, type_str, type_str});
		*func_sentence << EXP("new_array->size = size;");
		*func_sentence << EXP("new_array->value = (%s*)malloc(buffer_size);", {BOOLEAN_t});
		*func_sentence << EXP("memset(new_array->value, 0, buffer_size);");
		*func_sentence << EXP("return new_array;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_get(%s* value, struct %s* array, int index)", {type_str, BOOLEAN_t, type_str});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("int offset = index / 8;");
		*func_sentence << EXP("int offset_bit = index % 8;");
		*func_sentence << EXP("%s one_byte = (array->value)[offset];", {BOOLEAN_t});
		*func_sentence << EXP("*value = (0x80 >> offset_bit) & one_byte;");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_set(struct %s* array, %s value, int index)", {type_str, type_str, BOOLEAN_t});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("int offset = index / 8;");
		*func_sentence << EXP("int offset_bit = index % 8;");
		if_sentence = IF("value");
		*if_sentence << EXP("array->value[offset] |= 0x80 >> offset_bit;");
		*func_sentence << if_sentence;
		else_sentence = std::make_shared<ElseSentence>();
		*else_sentence << EXP("array->value[offset] &= ~(0x80 >> offset_bit);");
		*func_sentence << else_sentence;
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("void %s_free(struct %s* array)", {type_str, type_str});
		if_sentence = IF("array != NULL && array->value != NULL");
		*if_sentence << EXP("free(array->value);");
		*func_sentence << if_sentence;
		if_sentence = IF("array != NULL");
		*if_sentence << EXP("free(array);");
		*func_sentence << if_sentence;
		*res_sentence << func_sentence;
	break;
	case TokenID::Type::ARRAY:
		throw "array<array> no support";
	break;
	default:
		func_sentence = FUNC("struct %s* %s_create(int size)", {type_str, type_str});
		*func_sentence << EXP("struct %s* new_array = (struct %s*)malloc(sizeof(struct %s));", {type_str, type_str, type_str});
		*func_sentence << EXP("new_array->size = size;");
		*func_sentence << EXP("new_array->value = (struct %s_message**)malloc(sizeof(struct %s_message*) * (new_array->size));", {_kvproperty->_key.get_addtion().front(), _kvproperty->_key.get_addtion().front()});
		*func_sentence << EXP("int i;");
		for_sentence = FOR("i = 0; i < size; i++");
		*for_sentence << EXP("new_array->value[i] = %s_message_create();", {_kvproperty->_key.get_addtion().front()});
		*func_sentence << for_sentence;
		*func_sentence << EXP("return new_array;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_get(struct %s_message** value, struct %s* array, int index)", {type_str, _kvproperty->_key.get_addtion().front(), type_str});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		*func_sentence << EXP("*value = (array->value)[index];");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("int %s_set(struct %s* array, struct %s_message* value, int index)", {type_str, type_str, _kvproperty->_key.get_addtion().front()});
		if_sentence = IF("index >= array->size");
		*if_sentence << EXP("return -1;");
		*func_sentence << if_sentence;
		if_sentence = IF("(array->value)[index] != NULL");
		*if_sentence << EXP("%s_message_free((array->value)[index]);", {_kvproperty->_key.get_addtion().front()});
		*func_sentence << if_sentence;
		*func_sentence << EXP("(array->value)[index] = value;");
		*func_sentence << EXP("return 0;");
		*res_sentence << func_sentence;

		func_sentence = FUNC("void %s_free(struct %s* array)", {type_str, type_str});
		*func_sentence << EXP("int i = 0;");
		if_sentence = IF("array != NULL");
		for_sentence = FOR("i = 0; i < array->size; i++");
		if_if_sentence = IF("array->value[i] != NULL");
		*if_if_sentence << EXP("%s_message_free(array->value[i]);", {_kvproperty->_key.get_addtion().front()});
		*for_sentence << if_if_sentence;
		*if_sentence << for_sentence;
		*if_sentence << EXP("free(array->value);");
		*if_sentence << EXP("free(array);");
		*func_sentence << if_sentence;
		*res_sentence << func_sentence;
	break;
	}
	func_sentence = FUNC("int %s_size(struct %s* array)", {type_str, type_str});
	if_sentence = IF("array != NULL");
	*if_sentence << EXP("return array->size;");
	*func_sentence << if_sentence;
	*func_sentence << EXP("return -1;");
	*res_sentence << func_sentence;
	return res_sentence;
}

std::shared_ptr<Sentence> RpcHeaderPropertyGenerator::generate()
{
	return nullptr;
}
