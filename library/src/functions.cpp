#include <functions.h>
#include <iostream>

using namespace json;

void json::printParsingTool( )
{
	std::cout << "Parsing tool: " << g_ToolName << std::endl << std::endl;
}

json_parser json::parse( std::ifstream& file )
{
	printParsingTool( );
	return json_parser( file );
}
