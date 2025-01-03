
#ifndef _cldi_core__types_FUNC_H
#define _cldi_core__types_FUNC_H 1

/* Setup CLDI module "core" */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/head/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}

namespace ciahlldi
{
	namespace cldi
	{
		namespace core
		{
			namespace types
			{
				template <typename _TypR, size_t _ArgC=0>
				/*abstract*/ class iCallable
				{
					/* The return type itself should be able to fit in a register (max integer size),
					.  if it can't fit, use a ptr. */
					static_assert(
						sizeof(_TypR) <= 8,
						"ERROR: CLDI: Return type for ciahlldi::cldi::core::types::iCallable must be 8 "
						"bytes or smaller (Type can't fit in register)."
					);
				public:
					static constexpr size_t ARG_COUNT        = _ArgC;
					static constexpr size_t RETURN_TYPE_SIZE = sizeof(_TypR);

					virtual _TypR Call(va_list * args) =0;
				};

				/* --- Functional type Patterns --- */

				/* Function type that returns a result and takes some arguments using a va_list,
				.  va_list only allows certain types to be extracted as arguments, so for more
				.  specific functionality, including support for those unsupported types, use a
				.  more specific function type derivitive that is defined below. */
				template <typename _TypR, size_t _ArgC>
				class function: public iCallable<_TypR, _ArgC>
				{
				protected:
					_TypR last_result;
				public:
					_TypR (*const calling_address) (va_list*);

					function( _TypR (*const addr) (va_list*)=nullptr ):
						calling_address(addr) {}

					virtual _TypR Call(va_list * forced_args=nullptr)
					{
						_TypR result = this->calling_address();
						this->last_result = result;
						return result;
					}

					virtual _TypR GetLastResult(void) const
					{
						return this->last_result;
					}
				};
				/* Alias for function: "va_function" */
				template <typename _TypR, size_t _ArgC>
				using va_function = function<_TypR,_ArgC>;

				/* Function type that takes no arguments, but produces a result. */
				template <typename _TypR>
				class supplier: public iCallable<_TypR>
				{
				protected:
					_TypR last_result;
				public:
					_TypR (*const calling_address)();

					supplier( _TypR (*const addr)()=nullptr ):
						calling_address(addr) {}

					virtual _TypR Call()
					{
						_TypR result = this->calling_address();
						this->last_result = result;
						return result;
					}

					virtual _TypR GetLastResult(void) const
					{
						return this->last_result;
					}
				};

				/* Function type that returns nothing, but takes some arguments using a va_list,
				.  va_list only allows certain types to be extracted as arguments, so for more
				.  static functionality, including support for those unsupported types, use a
				.  static consumer that is defined below, each one will NOT be a template class,
				.  and they will provide static utilization of function calls. */
				template <size_t _ArgC>
				class consumer: iCallable<void, _ArgC>
				{
				public:
					void (*const calling_address) (va_list*);

					consumer( void (*const addr)(va_list*)=nullptr ):
						calling_address(addr) {}

					virtual void Call(va_list * args)
					{
						this->calling_address(args);
					}
				};
				/* Alias for consumer: "va_consumer". */
				template <size_t _ArgC>
				using va_consumer = consumer<_ArgC>;

				/* Function type that takes no arguments and returns no result, just
				.  execution. */
				class subroutine: public iCallable<void, 0>
				{
				protected:
					/* --- Instance Members --- */
					void (*const calling_address) ();

				public:
					/* --- Constructors/Destructors --- */

					subroutine( void (*const addr) ()=nullptr );

					virtual void Call();
				};

				/* --- Static Suppliers --- */

				/* - Supplier of a boolean value. */
				class bool_supplier: supplier<bool>
				{
				public:
					/* Reference to null instance of this class. */
					extern static const bool_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					bool_supplier( bool (*const addr) (void)=nullptr );
				};
				/* Null instance value */
				extern const bool_supplier BOOL_SUPPLIER_NULL;

				/* - Supplier of a character value. */
				class char_supplier: supplier<char>
				{
				public:
					/* Null instance of this class. */
					extern static const char_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					char_supplier( char (*const addr) (void)=nullptr );
				};
				/* - Supplier of a short integer. */
				class short_supplier: supplier<short>
				{
				public:
					/* Null instance of this class. */
					extern static const short_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					short_supplier( short (*const addr) (void)=nullptr );
				};
				/* - Supplier of an int. */
				class int_supplier: supplier<int>
				{
				public:
					/* Null instance of this class. */
					extern static const int_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					int_supplier( int (*const addr) (void)=nullptr );
				};
				/* - Supplier of a long integer. */
				class long_supplier: supplier<long>
				{
				public:
					/* Null instance of this class. */
					extern static const long_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					long_supplier( long (*const addr) (void)=nullptr );
				};
				/* Null instance values */
				extern const char_supplier  CHAR_SUPPLIER_NULL;
				extern const short_supplier SHORT_SUPPLIER_NULL;
				extern const int_supplier   INT_SUPPLIER_NULL;
				extern const long_supplier  LONG_SUPPLIER_NULL;

				/* - Supplier of a float. */
				class float_supplier: supplier<float>
				{
				public:
					/* Null instance of this class. */
					extern static const float_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					float_supplier( float (*const addr) (void)=nullptr );
				};
				/* - Supplier of a double-precision float. */
				class double_supplier: supplier<double>
				{
				public:
					/* Null instance of this class. */
					extern static const double_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					double_supplier( double (*const addr) (void)=nullptr );
				};
				/* Null instance values */
				extern const float_supplier  FLOAT_SUPPLIER_NULL;
				extern const double_supplier DOUBLE_SUPPLIER_NULL;

				/* - Supplier of a memory address (void *). */
				class address_supplier: supplier<void*>
				{
				public:
					/* Null instance of this class. */
					extern static const address_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					address_supplier( void* (*const addr) (void)=nullptr );
				};
				/* - Supplier of a integer address (int *). */
				class intptr_supplier: supplier<int*>
				{
				public:
					/* Null instance of this class. */
					extern static const intptr_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					intptr_supplier( int* (*const addr) (void)=nullptr );
				};
				/* - Supplier of a character address or string (char *). */
				class charptr_supplier: supplier<char*>
				{
				public:
					/* Null instance of this class. */
					extern static const charptr_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					charptr_supplier( char* (*const addr) (void)=nullptr );
				};
				/* - Supplier of a const memory address (const void *). */
				class raddress_supplier: supplier<const void*>
				{
				public:
					/* Null instance of this class. */
					extern static const raddress_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					raddress_supplier( const void* (*const addr) (void)=nullptr );
				};
				/* - Supplier of a const integer address (const int *). */
				class rintptr_supplier: supplier<const int*>
				{
				public:
					/* Null instance of this class. */
					extern static const rintptr_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					rintptr_supplier( const int* (*const addr) (void)=nullptr );
				};
				/* - Supplier of a const character address or const string (const char *). */
				class rcharptr_supplier: supplier<const char*>
				{
				public:
					/* Null instance of this class. */
					extern static const rcharptr_supplier &const nullclass;

					/* Initializing as null is allowed with this type (just pass nullptr, which is the
					.  default argument). */
					rcharptr_supplier( const char* (*const addr) (void)=nullptr );
				};
				/* Null instance values */
				extern const address_supplier  ADDRESS_SUPPLIER_NULL;
				extern const intptr_supplier   INTPTR_SUPPLIER_NULL;
				extern const charptr_supplier  CHARPTR_SUPPLIER_NULL;
				extern const raddress_supplier RADDRESS_SUPPLIER_NULL;
				extern const rintptr_supplier  RINTPTR_SUPPLIER_NULL;
				extern const rcharptr_supplier RCHARPTR_SUPPLIER_NULL;
			}
		}
	}
}

#endif

#endif /* _cldi_core__types_FUNC_H */
