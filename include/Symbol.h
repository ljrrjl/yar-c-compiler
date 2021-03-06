#pragma once
#include "Property.h"
#include "ProtocException.h"
#include <algorithm>

class Symbol
{
public:
	Symbol(const std::string& name, const TokenID& id): _svalue(name), _id(id){}
	TokenID get_token_id() { return _id; }
	const std::string& get_symbol_value() { return _svalue; }
	const std::vector<std::shared_ptr<KVProperty> >& get_properties() { return _properties; }
	Symbol& operator<<(std::shared_ptr<KVProperty> property)
	{
		try{
			if(!insert_property(property))
			{
				throw ProtocException("in message '" + _svalue + "': '" + property->_name + "' redefined");
			}
		}catch(const ProtocException& e){
			std::cerr << e.what() << std::endl;
		}
		return *this;
	}
private:
	TokenID _id;
	std::string _svalue;
	std::vector <std::shared_ptr<KVProperty> > _properties;
	bool insert_property(std::shared_ptr<KVProperty> property)
	{
		bool have_same_property = false;
		std::for_each(_properties.begin(), _properties.end(), [&property,&have_same_property](const std::shared_ptr<KVProperty>& pro) {
			if (*property < *pro || *pro < *property)
			{
				//pass
			}
			else
				have_same_property = true;
			});
		if (!have_same_property)
		{
			_properties.emplace_back(property);
			return true;
		}
		return false;
	}
};
