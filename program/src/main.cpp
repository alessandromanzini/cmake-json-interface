#include <iostream>
#include <iomanip>
#include <fstream>
#include <functions.h>
#include <Windows.h>

int main( )
{
	// Set console output to UTF-8
	SetConsoleOutputCP( CP_UTF8 );

	// Set the path and dynamically parse the JSON file
	const auto file_path{ "./Content/pokedex.json" };
	std::ifstream file{ file_path };
	auto parsed = json::parse( file );

	parsed["pokemon"].foreach( []( json::json_parser& pokemon )
	{
		std::cout << std::right << std::setw( 3 ) << std::setfill( '0' ) << pokemon["id"].get<int64_t>( ) << " - " 
			<< std::left << std::setw( 30 ) << std::setfill( '_' ) << pokemon["name"].get<std::string>( ) << "types: ";
		
		pokemon["type"].foreach( []( json::json_parser& type )
		{
			std::cout << type.get<std::string>( ) << " ";
		} );

		std::cout << std::endl;
	} );

	// Stop the console from closing
	std::cin.ignore( );
	return 0;
}
