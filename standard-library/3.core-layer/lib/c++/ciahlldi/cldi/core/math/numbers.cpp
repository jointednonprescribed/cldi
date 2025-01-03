
/* Implementing: cldi-core: math/numbers */
#include <ciahlldi/cldi/core/math/numbers.h>



namespace ciahlldi::cldi::core::types
{
	/* class num */

		num::num(void)
		{
			this->type      = TYPE_WHOLE;
			this->sign      = POSITIVE;
			this->raw_value = 0;
		}

		num::num(num __cpy)
		{
			*this = __cpy;
		}
		num::num(cldiNum __cpy)
		{
			this->type      = __cpy.type;
			this->sign      = __cpy.sign;
			this->raw_value = __cpy.raw_value;
		}
		num::num(const num& __cpy)
		{
			this->type      = __cpy->GetTypeFlag();
			this->sign      = __cpy->GetSign();
			this->raw_value = __cpy->GetBits();
		}
		num::num(const cldiNum * __cpy)
		{
			this->type      = __cpy->type;
			this->sign      = __cpy->sign;
			this->raw_value = __cpy->raw_value;
		}

		num::num(sizew_t wrap)
		{
			this->type        = TYPE_WHOLE;
			this->sign        = UNSIGNED;
			this->raw_value   = (long) wrap;
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
		}
		num::num(ssizew_t wrap)
		{
			this->type        = TYPE_WHOLE;
			this->sign        = (wrap >= 1)? POSITIVE : NEGATIVE;
			this->raw_value   = (long) (wrap*(-1));
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
		}

		num::num(long wrap, bool __u=false)
		{
			const bool negative = (!__u) && wrap < 0;

			this->type = TYPE_WHOLE;

			if (__u)      goto set_unsigned;
			if (negative) goto negative;
		set_positive:
			this->sign      = POSITIVE;
			goto set_value;
		set_negative:
			this->sign      = NEGATIVE;
			this->raw_value = (uintmax_t) (wrap*(-1));
			goto set_finish;
		set_unsigned:
			this->sign      = UNSIGNED;
		set_value:
			this->raw_value = (uintmax_t) wrap;
		set_finish:
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
			return;
		}
		num::num(int wrap, bool __u=false)
		{
			const bool negative = (!__u) && wrap < 0;

			this->type = TYPE_WHOLE;

			if (__u)      goto set_unsigned;
			if (negative) goto negative;
		set_positive:
			this->sign      = POSITIVE;
			goto set_value;
		set_negative:
			this->sign      = NEGATIVE;
			this->raw_value = (uintmax_t) (wrap*(-1));
			goto set_finish;
		set_unsigned:
			this->sign      = UNSIGNED;
		set_value:
			this->raw_value = (uintmax_t) wrap;
		set_finish:
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
			return;
		}
		num::num(short wrap, bool __u=false)
		{
			const bool negative = (!__u) && wrap < 0;

			this->type = TYPE_WHOLE;

			if (__u)      goto set_unsigned;
			if (negative) goto negative;
		set_positive:
			this->sign      = POSITIVE;
			goto set_value;
		set_negative:
			this->sign      = NEGATIVE;
			this->raw_value = (uintmax_t) (wrap*(-1));
			goto set_finish;
		set_unsigned:
			this->sign      = UNSIGNED;
		set_value:
			this->raw_value = (uintmax_t) wrap;
		set_finish:
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
			return;
		}
		num::num(char wrap, bool __u=false)
		{
			const bool negative = (!__u) && wrap < 0;

			this->type = TYPE_WHOLE;

			if (__u)      goto set_unsigned;
			if (negative) goto negative;
		set_positive:
			this->sign      = POSITIVE;
			goto set_value;
		set_negative:
			this->sign      = NEGATIVE;
			this->raw_value = (long) (wrap*(-1));
			goto set_finish;
		set_unsigned:
			this->sign      = UNSIGNED;
		set_value:
			this->raw_value = (long) wrap;
		set_finish:
		#if __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
			this->higher_bits = 0;
		#endif
			return;
		}

		num::num(float wrap)
		{
			this->type = TYPE_RATIONAL;
			this->sign = (wrap >= 0)? POSITIVE : NEGATIVE;

			const double wrap_c = (double) wrap;

			const void *const p1 = (const void*) &wrap_c;
			const long *const p2 = (const long*) p1;

		#if __CLDI_ARCHSIZE < CLDI_PLATFORM_64BIT
			this->higher_bits = p2[0];
			this->raw_value   = p2[1];
		#else
			this->raw_value = *p2;
		#endif
		}
		num::num(double wrap)
		{
			make.type = TYPE_RATIONAL;
			make.sign = (wrap >= 0)? POSITIVE : NEGATIVE;

			const void *const p1 = (const void*) &wrap;
			const long *const p2 = (const long*) p1;

		#if __CLDI_ARCHSIZE < CLDI_PLATFORM_64BIT
			make.higher_bits = p2[0];
			make.raw_value   = p2[1];
		#else
			make.raw_value = *p2;
		#endif
		}

		num num::MakeIrrational(double representable_bits)
		{
			num make;

			make.type = TYPE_IRRATIONAL;
			make.sign = (representable_bits >= 0)? POSITIVE : NEGATIVE;

			const void *const p1 = (const void*) &representable_bits;
			const long *const p2 = (const long*) p1;

		#if __CLDI_ARCHSIZE < CLDI_PLATFORM_64BIT
			make.higher_bits = p2[0];
			make.raw_value   = p2[1];
		#else
			make.raw_value = *p2;
		#endif

			return make;
		}

	/* end class num */
}


