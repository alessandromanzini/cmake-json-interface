#pragma once
#include <fstream>
#include <JsonParser.hpp>

#if defined(USE_JSONCPP_JSON)
	#include <JsoncppJsonParserTool.hpp>
	namespace json
	{
		const std::string g_ToolName{ "JsonCpp" };
		using json_parser = JsonParser<JsoncppJsonParserTool, JsoncppJsonParserTool::data_t>;
	}
#elif defined(USE_SIMD_JSON)
	#include <SimdJsonParserTool.hpp>
	namespace json
	{
		const std::string g_ToolName{ "SimdJson" };
		using json_parser = JsonParser<SimdJsonParserTool, SimdJsonParserTool::data_t>;
	}

#elif defined(USE_NLOHMANN_JSON)
	#include <NlohmannJsonParserTool.hpp>
	namespace json
	{
		const std::string g_ToolName{ "NlohmannJson" };
		using json_parser = JsonParser<NlohmannJsonParserTool, NlohmannJsonParserTool::data_t>;
	}
#endif

namespace json
{
	void printParsingTool( );

	json_parser parse( std::ifstream& file );
}
