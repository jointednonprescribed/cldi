

/* Setup for cldi-core.                    */
#include <ciahlldi/cldi/core/setup.h>

/* Implementing: cldi-core: text/chartypes */
#include <ciahlldi/cldi/core/text/chartypes.h>



namespace ciahlldi::cldi
{
	/* ---     class CHARTYPE --- */

		const CHARTYPE CHARTYPE::NONE          = CHARTYPE(CLDI_CHARTYPE_NONE);
		const CHARTYPE CHARTYPE::INVALID       = CHARTYPE(CLDI_CHARTYPE_INVALID);

		const CHARTYPE CHARTYPE::ASCII         = CHARTYPE(CLDI_CHARTYPE_ASCII);
		const CHARTYPE CHARTYPE::UTF8          = CHARTYPE(CLDI_CHARTYPE_UTF8);
		const CHARTYPE CHARTYPE::UTF16         = CHARTYPE(CLDI_CHARTYPE_UTF16);
		const CHARTYPE CHARTYPE::UTF32         = CHARTYPE(CLDI_CHARTYPE_UTF32);

		const CHARTYPE CHARTYPE::ASCII_INVALID = CHARTYPE(CLDI_CHARTYPE_ASCII_INVALID);
		const CHARTYPE CHARTYPE::UTF8_INVALID  = CHARTYPE(CLDI_CHARTYPE_UTF8_INVALID);
		const CHARTYPE CHARTYPE::UTF16_INVALID = CHARTYPE(CLDI_CHARTYPE_UTF16_INVALID);
		const CHARTYPE CHARTYPE::UTF32_INVALID = CHARTYPE(CLDI_CHARTYPE_UTF32_INVALID);

		CHARTYPE::CHARTYPE(int type_value):
			CHARTYPE::CHARTYPE((CLDI_CHARTYPE) type_value)
		{}

		CHARTYPE::CHARTYPE(CLDI_CHARTYPE type_value=CLDI_CHARTYPE_NONE)
		{
			type = type_value;
		}

		size_t CHARTYPE::SizeOf() const
		{
			return CLDI_CHARTYPE_SIZEOF(type);
		}

		bool CHARTYPE::IsValid() const
		{
			return CLDI_CHARTYPE_ISVALID(type);
		}
		bool CHARTYPE::IsInvalid() const
		{
			return CLDI_CHARTYPE_ISINVALID(type);
		}

		CHARTYPE CHARTYPE::ValidOf() const
		{
			return CHARTYPE(CLDI_CHARTYPE_VALIDOF(type));
		}
		CHARTYPE CHARTYPE::InvalidOf() const
		{
			return CHARTYPE(CLDI_CHARTYPE_INVALIDOF(type));
		}


	/* --- end class CHARTYPE --- */
}


