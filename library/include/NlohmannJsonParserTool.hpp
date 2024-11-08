#include <fstream>
#include "nlohmann/json.hpp"

class NlohmannJsonParserTool final
{
public:
	typedef nlohmann::json data_t;

	NlohmannJsonParserTool( data_t& data, std::ifstream& file )
	{
		data = nlohmann::json::parse( file );
	}

	auto& Getter( data_t& data, const char* key )
	{
		return data[key];
	}

	template <typename get_t>
	get_t Getter( data_t& data )
	{
		return data.get<get_t>( );
	}

};
