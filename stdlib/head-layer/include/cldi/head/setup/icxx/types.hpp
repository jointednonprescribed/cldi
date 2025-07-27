
#ifndef _cldi_head__setup_TYPES_HPP
#define _cldi_head__setup_TYPES_HPP 1

#ifndef _cldi_head__setup_TYPES_H
#	include "../types.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	using pid_t = ::cldipid_t;
	using gid_t = ::cldigid_t;
	using oid_t = ::cldioid_t;

	inline pid_t (&GetCurrentPID)() = ::cldiGetCurrentPID;
	inline gid_t (&GetCurrentGID)() = ::cldiGetCurrentGID;
	inline oid_t (&GetCurrentOID)() = ::cldiGetCurrentOID;

	using floatmax_t    = ::cldifpm_t;
	using fpm_t         = ::cldifpm_t;
	constexpr fpm_t FPM_MANT_DIG = CLDIFPM_MANT_DIG;
	constexpr fpm_t FPM_DIG = CLDIFPM_DIG;
	constexpr fpm_t FPM_MIN_EXP = CLDIFPM_MIN_EXP;
	constexpr fpm_t FPM_MIN_10_EXP = CLDIFPM_MIN_10_EXP;
	constexpr fpm_t FPM_MAX_EXP = CLDIFPM_MAX_EXP;
	constexpr fpm_t FPM_MAX_10_EXP = CLDIFPM_MAX_10_EXP;
	constexpr fpm_t FPM_MAX = CLDIFPM_MAX;
	constexpr fpm_t FPM_EPSILON = CLDIFPM_EPSILON;
	constexpr fpm_t FPM_MIN = CLDIFPM_MIN;

	using TYPE_TEMPL= ::CLDI_TYPE_TEMPL;
	using TYPE_TEMPLATE = ::CLDI_TYPE_TEMPL;
	constexpr TYPE_TEMPL NULL_TYPE = ::CLDI_NULL_TYPE;
	constexpr TYPE_TEMPL INTEGER_TYPE = ::CLDI_INTEGER_TYPE;
	constexpr TYPE_TEMPL INT_TYPE = ::CLDI_INTEGER_TYPE;
	constexpr TYPE_TEMPL FLOAT_TYPE = ::CLDI_FLOAT_TYPE;
	constexpr TYPE_TEMPL PTR_TYPE = ::CLDI_PTR_TYPE;
	constexpr TYPE_TEMPL CSTR_TYPE = ::CLDI_CSTR_TYPE;
	constexpr TYPE_TEMPL STR_TYPE = ::CLDI_STR_TYPE;
	constexpr TYPE_TEMPL WSTR_TYPE = ::CLDI_WSTR_TYPE;
	constexpr TYPE_TEMPL STRUCT_TYPE = ::CLDI_STRUCT_TYPE;

	using _gtypeinfo_t  = ::clditypeinfo_t;
	template <typename _T>
	class typeinfo_t
	{
	protected:
		const _gtypeinfo_t generic;

	public:

		/* Detect the correct type template from the given type argument. */
		constexpr static TYPE_TEMPL FindTypeTemplate()
		{
			if (std::is_integral_v<_T>) {
				return TYPE_TEMPL_INT;
			} else if (std::is_floating_point_v<_T>) {
				return TYPE_TEMPL_FLOAT;
			} else if (std::is_pointer_v<_T>) {
				return TYPE_TEMPL_PTR;
			} else if (std::is_class_v<_T>) {
				return TYPE_TEMPL_STRUCT;
			} else { 
				return TYPE_TEMPL_NULL;
			}
		}
		/* Store detected template from type argument in public static constexpr
		.  variable. */
		constexpr static TYPE_TEMPL TEMPLATE = FindTypeTemplate();

		/* Sole Constructor: Use detected options for the given type argument. */
		typeinfo_t():
			generic({.size=(std::is_void<_T>::value)? 0 : sizeof(_T), .templ=TEMPLATE})
		{}

		size_t Size() const
		{
			return generic.size;
		}
		TYPE_TEMPL Template() const
		{
			return generic.templ;
		}

		/* Compare to another typeinfo_t object. */
		constexpr bool operator ==(const typeinfo_t<_T> &rhv) const
		{
			return generic.size == rhv.generic.size && generic.templ == rhv.generic.templ;
		}
		/* Compare to another typeinfo_t object (inequality). */
		constexpr bool operator !=(const typeinfo_t<_T> &rhv) const
		{
			return generic.size != rhv.generic.size || generic.templ != rhv.generic.templ;
		}
		/* Compare to another typeinfo_t object (greater than). */
		constexpr bool operator >(const typeinfo_t<_T> &rhv) const
		{
			return generic.size > rhv.generic.size;
		}
		/* Compare to another typeinfo_t object (less than). */
		constexpr bool operator <(const typeinfo_t<_T> &rhv) const
		{
			return generic.size < rhv.generic.size;
		}
		/* Compare to another typeinfo_t object (greater than or equal to). */
		constexpr bool operator >=(const typeinfo_t<_T> &rhv) const
		{
			return generic.size >= rhv.generic.size;
		}
		/* Compare to another typeinfo_t object (less than or equal to). */
		constexpr bool operator <=(const typeinfo_t<_T> &rhv) const
		{
			return generic.size <= rhv.generic.size;
		}

		/* Compare to a generic type info object. */
		constexpr bool operator ==(const _gtypeinfo_t &rhv) const
		{
			return generic.size == rhv.size && generic.templ == rhv.templ;
		}
		/* Compare to a generic type info object (inequality). */
		constexpr bool operator !=(const _gtypeinfo_t &rhv) const
		{
			return generic.size != rhv.size || generic.templ != rhv.templ;
		}
		/* Compare to a generic type info object (greater than). */
		constexpr bool operator >(const _gtypeinfo_t &rhv) const
		{
			return generic.size > rhv.size;
		}
		/* Compare to a generic type info object (less than). */
		constexpr bool operator <(const _gtypeinfo_t &rhv) const
		{
			return generic.size < rhv.size;
		}
		/* Compare to a generic type info object (greater than or equal to). */
		constexpr bool operator >=(const _gtypeinfo_t &rhv) const
		{
			return generic.size >= rhv.size;
		}
		/* Compare to a generic type info object (less than or equal to). */
		constexpr bool operator <=(const _gtypeinfo_t &rhv) const
		{
			return generic.size <= rhv.size;
		}
	};
	/* Type Info Constants */
	constexpr typeinfo_t<void> NullTypeInfo;
	constexpr typeinfo_t<char> CharTypeInfo;
	constexpr typeinfo_t<const char*> CStrTypeInfo;
	constexpr typeinfo_t<const char*> StrTypeInfo;
	constexpr typeinfo_t<wchar_t> WCharTypeInfo;
	constexpr typeinfo_t<const wchar_t*> WStrTypeInfo;
	constexpr typeinfo_t<short> ShortTypeInfo;
	constexpr typeinfo_t<int> IntTypeInfo;
	constexpr typeinfo_t<long> LongTypeInfo;
	constexpr typeinfo_t<long long> LLongTypeInfo;
	constexpr typeinfo_t<size_t> SizeTypeInfo;
	constexpr typeinfo_t<float> FloatTypeInfo;
	constexpr typeinfo_t<double> DoubleTypeInfo;
	constexpr typeinfo_t<cldifpm_t> FPMTypeInfo;
#if CLDI_LDBL_ENABLED == true
	constexpr typeinfo_t<long double> LDoubleTypeInfo;
#endif
	constexpr typeinfo_t<const void*> PtrTypeInfo;

	template <typename _T1, typename _T2>
	class pair
	{
		_T1 m1;
		_T2 m2;

	public:

		pair(_T1 a1, _T2 a2)
		{
			m1 = a1;
			m2 = a2;
		}
		pair(const pair<_T1, _T2> &rhv)
		{
			m1 = rhv.m1;
			m2 = rhv.m2;
		}

		operator pair<_T2,_T1>() const
		{
			return pair<_T1,_T1>(*this);
		}

		auto operator =(const pair<_T1, _T2> &rhv)
		{
			m1 = rhv.m1;
			m2 = rhv.m2;
		}

		bool operator ==(const pair<_T1, _T2> &rhv) const
		{
			return m1 == rhv.m1 && m2 == rhv.m2;
		}
		bool operator ==(const _T1 &rhv) const
		{
			return m1 == rhv;
		}

		_T1& Former() const
		{
			return m1;
		}
		_T2& Latter() const
		{
			return m2;
		}

		typeinfo_t<_T1> GetFormerTypeInfo() const
		{
			return typeinfo_t<_T1>();
		}
		typeinfo_t<_T2> GetLatterTypeInfo() const
		{
			return typeinfo_t<_T2>();
		}

		void SetFormer(const _T1 &former)
		{
			m1 = former;
		}
		void SetLatter(const _T2 &latter)
		{
			m2 = latter;
		}
		void SetPair(const _T1 &former, const _T2 &latter)
		{
			m1 = former;
			m2 = latter;
		}
	};
}



#endif // CLDI_C_ONLY == false

#endif // _cldi_head__setup_TYPES_HPP
