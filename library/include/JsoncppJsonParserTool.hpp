#include <fstream>
#include "json/json.h"

class JsoncppJsonParserTool final
{
public:
	typedef Json::Value data_t;

	JsoncppJsonParserTool( data_t& data, std::ifstream& file )
	{
		Json::CharReaderBuilder readerBuilder;
		std::string errors;

		// If can't parse the JSON file, throw an exception
		if ( !Json::parseFromStream( readerBuilder, file, &data, &errors ) )
		{
			throw std::runtime_error( errors );
		}
	}

	auto& Getter( data_t& data, const char* key )
	{
		return data[key];
	}

	template <typename get_t>
	get_t Getter( data_t& data )
	{
		static_assert( "get_t not supported!" );
	}

	template<>
	int64_t Getter<int64_t>( data_t& data )
	{
		return data.asInt64( );
	}

	template<>
	std::string Getter<std::string>( data_t& data )
	{
		return std::move( data.asString( ) );
	}

};
