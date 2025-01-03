
#ifndef _cldi_portable__text_IMPL_CHARTYPE_CLASSWRAPPER_HPP
#	include "../../../setup.h"
#	if !defined(__cplusplus) || __CLDI_no_cpp > false
#		define _cldi_portable__text_IMPL_CHARTYPE_CLASSWRAPPER_HPP 0
#	else
#		define _cldi_portable__text_IMPL_CHARTYPE_CLASSWRAPPER_HPP 1

#include "../../../NS_DECL.hpp"

#include "CHARTYPE.h"



namespace cldi
{
	namespace portable
	{
		class Chartype
		{
		public:
			const _CLDICHARTYPE value;

		#if __cplusplus >= 202002L
			using enum _CLDICHARTYPE;
		#endif

			constexpr Chartype(_CLDICHARTYPE chartype=CLDI_CHARTYPE_NONE):
				value(chartype)
			{}

			explicit  operator bool() const = delete;
			constexpr operator _CLDICHARTYPE() const
			{
				return this->value;
			}

			constexpr bool operator ==(_CLDICHARTYPE other) const
			{
				return this->value == other;
			}
			constexpr bool operator !=(_CLDICHARTYPE other) const
			{
				return this->value != other;
			}
			constexpr bool operator <=(_CLDICHARTYPE other) const
			{
				return this->GetIdentifier() <= Chartype::GetIdentifier(other);
			}
			constexpr bool operator >=(_CLDICHARTYPE other) const
			{
				return this->GetIdentifier() >= Chartype::GetIdentifier(other);
			}
			constexpr bool operator <(_CLDICHARTYPE other) const
			{
				return this->GetIdentifier() < Chartype::GetIdentifier(other);
			}
			constexpr bool operator >(_CLDICHARTYPE other) const
			{
				return this->GetIdentifier() > Chartype::GetIdentifier(other);
			}

			constexpr bool operator ==(int size) const
			{
				/* Equivalent to: this->SizeOf() <operator> size */
				return ((static_cast<char>(this->value) & 0x07) + 1) == size;
			}
			constexpr bool operator !=(int size) const
			{
				return ((static_cast<char>(this->value) & 0x07) + 1) != size;
			}
			constexpr bool operator <=(int size) const
			{
				return ((static_cast<char>(this->value) & 0x07) + 1) <= size;
			}
			constexpr bool operator >=(int size) const
			{
				return ((static_cast<char>(this->value) & 0x07) + 1) >= size;
			}
			constexpr bool operator <(int size) const
			{
				return ((static_cast<char>(this->value) & 0x07) + 1) < size;
			}
			constexpr bool operator >(int size) const
			{
				return ((static_cast<char>(this->value) & 0x07) + 1) > size;
			}

			static const char* GetName(_CLDICHARTYPE type);
			static const char* ToString(_CLDICHARTYPE type);
			const char* GetName() const;
			const char* ToString() const;

			constexpr _CLDICHARTYPE Get() const
			{
				return this->value;
			}

			/* Get the true size of a given character type. */
			static constexpr int SizeOf(_CLDICHARTYPE type)
			{
				return static_cast<int>(static_cast<char>(type) & 0x07) + 1;
			}
			constexpr int SizeOf() const
			{
				return static_cast<int>(static_cast<char>(this->value) & 0x07) + 1;
			}
			/* Get the identifier value of the type. */
			static constexpr int GetIdentifier(_CLDICHARTYPE type)
			{
				return (type >= CLDI_CHARTYPE_NONE)?
					static_cast<int>( (static_cast<signed char>(type) & 0xf8) >> 3 ) :
					static_cast<int>(
						( ((static_cast<signed char>(type) & 0xf8)*(-1)) >> 3 ) * -1 );
			}
			constexpr int GetIdentifier() const
			{
				return (this->value >= CLDI_CHARTYPE_NONE)?
					static_cast<int>( (static_cast<signed char>(this->value) & 0xf8) >> 3 ) :
					static_cast<int>(
						( ((static_cast<signed char>(this->value) & 0xf8)*(-1)) >> 3 ) * -1 );
			}

			/* Whether or not a given character type is invalid. */
			static constexpr bool IsInvalid(_CLDICHARTYPE type)
			{
				return static_cast<signed char>(type) <= 0;
			}
			constexpr bool IsInvalid() const
			{
				return static_cast<signed char>(this->value) <= 0;
			}
			/* Whether or not a given character type is valid. */
			static constexpr bool IsValid(_CLDICHARTYPE type)
			{
				return static_cast<signed char>(type) > 0;
			}
			constexpr bool IsValid() const
			{
				return static_cast<signed char>(this->value) > 0;
			}

			/* Get the valid counterpart to the passed character type. */
			static _CLDICHARTYPE GetValidOf(_CLDICHARTYPE invalid);
			_CLDICHARTYPE        GetValidOf() const;
			/* Get the invalid counterpart to the passed character type. */
			static _CLDICHARTYPE GetInvalidOf(_CLDICHARTYPE valid);
			_CLDICHARTYPE        GetInvalidOf() const;
			/* Check if one type can be converted into another. */
			static bool          CanConvertTo(_CLDICHARTYPE conv_from, _CLDICHARTYPE conv_to);
			bool                 CanConvertTo(CLDI_CHARTYPE conv_to) const;
		};
	}
}


#	endif
#endif /* _cldi_portable__text_IMPL_CHARTYPE_CLASSWRAPPER_HPP */
