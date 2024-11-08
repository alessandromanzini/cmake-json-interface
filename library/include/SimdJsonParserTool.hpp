#include <fstream>
#include "simdjson.h"

class SimdJsonParserTool final
{
public:
	typedef simdjson::dom::element data_t;

	SimdJsonParserTool( data_t& data, std::ifstream& file )
	{
		// Get file size and resize the buffer
		std::streamsize size = file.tellg( );
		file.seekg( 0, std::ios::beg );

		// Read the file content into a buffer
		std::string buffer( ( std::istreambuf_iterator<char>( file ) ), std::istreambuf_iterator<char>( ) );
		if ( !file.read( buffer.data( ), size ) )
		{
			throw std::runtime_error( "Error reading the file!" );
		}

		// Parse the JSON with simdjson
		auto error = parser_.parse( buffer ).get( data );
		if ( error != simdjson::error_code::SUCCESS )
		{
			throw error;
		}
	}

	data_t Getter( data_t& data, const char* key )
	{
		return data[key];
		// return data.root( ).at_key( { key } );
	}

	template <typename get_t>
	get_t Getter( data_t& data )
	{
		static_assert( "get_t not supported!" );
	}

	template<>
	int64_t Getter<int64_t>( data_t& data )
	{
		return data.get_int64( ).take_value();
	}

	template<>
	std::string Getter<std::string>( data_t& data )
	{
		return { data.get_c_str( ).take_value( ) };
	}

private:
	simdjson::dom::parser parser_;

};

