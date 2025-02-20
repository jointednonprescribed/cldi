
#ifndef _cldi_head__FUNCTYPES_HPP
#define _cldi_head__FUNCTYPES_HPP 1

#ifndef _cldi_head__FUNCTYPES_H
#	include "../functypes.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	template <typename _Rt, typename ..._A>
	class function
	{
	public:

		_Rt (*const call)(_A...);

		virtual _Rt operator ()(_A... args) const
		{
			call(args...);
		}

		function():
			call(NULL)
		{}
		function(_Rt (*func)(_A...)):
			call(func)
		{}
		function(const function<_Rt, _A...> &callable):
			call(callable.call)
		{}

		typeinfo_t<_Rt> GetReturnTypeInfo() const
		{
			return typeinfo_t<_Rt>();
		}
	};

	template <typename ..._A>
	class consumer: public function<void, _A...>
	{
	public:

		consumer(void (*func)(_A...)=NULL):
			function<void, _A...>(func)
		{}
		consumer(function<void, _A...> callable):
			function<void, _A...>(callable.call)
		{}
	};

	template <typename _Rt>
	class supplier: public function<_Rt>
	{
	public:

		supplier(_Rt (*func)()=NULL):
			function<_Rt>(func)
		{}
		supplier(function<_Rt> callable):
			function<_Rt>(callable.call)
		{}
	};

	class subroutine: public function<void>
	{
	public:

		subroutine();
		subroutine(void (*func)());
		subroutine(function<void> callable);
	};
}



#endif // CLDI_C_ONLY == false

#endif // _cldi_head__FUNCTYPES_HPP
