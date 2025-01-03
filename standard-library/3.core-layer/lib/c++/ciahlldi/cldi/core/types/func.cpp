
/* Implementing: cldi-core: types/func */
#include <ciahlldi/cldi/core/types/func.h>



namespace ciahlldi::cldi::core::types
{
	/* ----------------------------------- */
	/* class bool_supplier: supplier<bool> */

		const bool_supplier bool_supplier::nullclass {};

		bool_supplier::bool_supplier( bool (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class char_supplier: supplier<char> */

		const char_supplier char_supplier::nullclass {};

		char_supplier( char (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class short_supplier: supplier<short> */

		const short_supplier short_supplier::nullclass {};

		short_supplier::short_supplier( short (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class int_supplier: supplier<int> */

		const int_supplier int_supplier::nullclass {};

		int_supplier::int_supplier( bool (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class long_supplier: supplier<long> */

		const long_supplier long_supplier::nullclass {};

		long_supplier::long_supplier( long (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class float_supplier: supplier<float> */

		const float_supplier float_supplier::nullclass {};

		float_supplier::float_supplier( float (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class double_supplier: supplier<double> */

		const double_supplier double_supplier::nullclass {};

		double_supplier::double_supplier( double (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class address_supplier: supplier<void*> */

		const address_supplier address_supplier::nullclass {};

		address_supplier::address_supplier( void* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class intptr_supplier: supplier<int*> */

		const intptr_supplier intptr_supplier::nullclass {};

		intptr_supplier::intptr_supplier( int* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class charptr_supplier: supplier<char*> */

		const charptr_supplier charptr_supplier::nullclass {};

		charptr_supplier::charptr_supplier( char* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class caddress_supplier: supplier<const void*> */

		const caddress_supplier caddress_supplier::nullclass {};

		caddress_supplier::caddress_supplier( const void* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class cintptr_supplier: supplier<const int*> */

		const cintptr_supplier cintptr_supplier::nullclass {};

		cintptr_supplier::cintptr_supplier( const int* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
	/* class ccharptr_supplier: supplier<const char*> */

		const ccharptr_supplier ccharptr_supplier::nullclass {};

		ccharptr_supplier::ccharptr_supplier( const char* (*const addr) (void)=nullptr ):
			calling_address(addr), last_result(false) {}

	/* ----------------------------------- */
}

