#include "SymbolGenerator.h"
#include "SentenceHelper.h"
#include "GeneratorFactory.h"
#include "FileManager.h"

std::shared_ptr<Sentence> MessageGenerator::generate()
{
	auto message_sentence_ptr = STRUCT("%s_message", {_symbol->get_symbol_value()});
	for(auto kvproperty : _symbol->get_properties())
	{
		auto property_generate_ptr = GeneratorFactory::Instance()->create_generator(_file_id, kvproperty);
		*message_sentence_ptr << property_generate_ptr->generate();
	}
	return message_sentence_ptr;	
}
