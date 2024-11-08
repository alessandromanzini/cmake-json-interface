#include <memory>
#include <functional>

// Static Polymorphism pattern
// Essentially, this class will wrap around the json data and provide an abstraction layer to access it.
// tool_t is the parser tool, data_t is the data type of the json.
// tool_t must have the following methods:
// - Constructor( data_t& data, std::ifstream& file )
// - Getter( data_t& data, const char* key )
// - Getter<GetterType>( data_t& data )
// tool_t will provide the access to the json data via specialized json methods,
// allowing to use different json_parsers (implementing specialized tools).
template <typename tool_t, typename data_t>
class JsonParser
{
public:
	JsonParser( std::ifstream& file )
	{
		tool_ptr_ = std::make_shared<tool_t>( data_, file );
	}

	// Constructor for nested json objects
	// avoids copying the data
	JsonParser( data_t& data, const std::shared_ptr<tool_t>& tool_ptr )
		: data_ref_( data ), tool_ptr_( tool_ptr )
	{
	}

	JsonParser( data_t&& data, const std::shared_ptr<tool_t>& tool_ptr )
		: data_( std::move( data ) ), tool_ptr_( tool_ptr )
	{
	}

#pragma region Operators
	// When trying to access nested json objects, the operator[] will return a new JsonParser object.
	// If the Getter returns a reference, we bind the reference to the new object.
	// If the Getter returns an expiring object, we will move it to the new JsonParser object.
	auto operator[]( const char* key )
	{
		return JsonParser<tool_t, data_t>{ tool_ptr_->Getter( data_ref_, key ), tool_ptr_ };
	}

#pragma endregion

#pragma region Getters
	template <typename GetterType>
	GetterType get( )
	{
		return tool_ptr_->Getter<GetterType>( data_ref_ );
	}

#pragma endregion

	// Iterates over the json array, while wrapping the elements in our JsonParser abstraction
	void foreach( const std::function<void( typename JsonParser<tool_t, data_t> )>& func )
	{
		for ( auto& element : data_ref_ )
		{
			func( JsonParser<tool_t, data_t>{ element, tool_ptr_ } );
		}
	}

private:
	data_t data_;
	data_t& data_ref_{ data_ };

	std::shared_ptr<tool_t> tool_ptr_;

};
