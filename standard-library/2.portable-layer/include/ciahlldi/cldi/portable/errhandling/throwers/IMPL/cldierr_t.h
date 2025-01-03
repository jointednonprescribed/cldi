
#ifndef _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_H
#define _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_H 1

#include "../../../setup.h"

#include "../../../handles/text.h"



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
struct _cldierr_t
{
	const long long _code;

	const CLDISTRHANDLE _name, _desc;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	_cldierr_t(long long code=0ul);
	_cldierr_t(int code);
	static int Init(_cldierr_t& self, long long code=0ul);
	static int Init(_cldierr_t& self, int code);
	static _cldierr_t& New(long long code=0ul);
	static _cldierr_t& New(int code);

	_cldierr_t(long long code, const char * name, const char * description=NULL);
	_cldierr_t(int       code, const char * name, const char * description=NULL);
	_cldierr_t(const char * name, const char * description=NULL);
	_cldierr_t(long long code, const char * name, CLDISTRHANDLE description);
	_cldierr_t(int       code, const char * name, CLDISTRHANDLE description);
	_cldierr_t(const char * name, CLDISTRHANDLE description);
	static int Init(_cldierr_t& self, long long, const char *, const char * _=NULL);
	static int Init(_cldierr_t& self, int, const char *, const char * _=NULL);
	static int Init(_cldierr_t& self, const char *, const char * _=NULL);
	static int Init(_cldierr_t& self, long long, const char *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, int, const char *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, const char *, CLDISTRHANDLE);
	static _cldierr_t& New(long long, const char *, const char * _=NULL);
	static _cldierr_t& New(int, const char *, const char * _=NULL);
	static _cldierr_t& New(const char *, const char * _=NULL);
	static _cldierr_t& New(long long, const char *, CLDISTRHANDLE);
	static _cldierr_t& New(int, const char *, CLDISTRHANDLE);
	static _cldierr_t& New(const char *, CLDISTRHANDLE);

	_cldierr_t(long long code, const u16_t * name, const u16_t * description=NULL);
	_cldierr_t(int       code, const u16_t * name, const u16_t * description=NULL);
	_cldierr_t(const u16_t * name, const u16_t * description=NULL);
	_cldierr_t(long long code, const u16_t * name, CLDISTRHANDLE description);
	_cldierr_t(int       code, const u16_t * name, CLDISTRHANDLE description);
	_cldierr_t(const u16_t * name, CLDISTRHANDLE description);
	static int Init(_cldierr_t& self, long long, const u16_t *, const u16_t * _=NULL);
	static int Init(_cldierr_t& self, int, const u16_t *, const u16_t * _=NULL);
	static int Init(_cldierr_t& self, const u16_t *, const u16_t * _=NULL);
	static int Init(_cldierr_t& self, long long, const u16_t *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, int, const u16_t *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, const u16_t *, CLDISTRHANDLE);
	static _cldierr_t& New(long long, const u16_t *, const u16_t * _=NULL);
	static _cldierr_t& New(int, const u16_t *, const u16_t * _=NULL);
	static _cldierr_t& New(const u16_t *, const u16_t * _=NULL);
	static _cldierr_t& New(long long, const u16_t *, CLDISTRHANDLE);
	static _cldierr_t& New(int, const u16_t *, CLDISTRHANDLE);
	static _cldierr_t& New(const cldiU16 *, CLDISTRHANDLE);

	_cldierr_t(long long code, const u32_t * name, const u32_t * description=NULL);
	_cldierr_t(int       code, const u32_t * name, const u32_t * description=NULL);
	_cldierr_t(const u32_t * name, const u32_t * description=NULL);
	_cldierr_t(long long code, const u32_t * name, CLDISTRHANDLE description);
	_cldierr_t(int       code, const u32_t * name, CLDISTRHANDLE description);
	_cldierr_t(const u32_t * name, CLDISTRHANDLE description);
	static int Init(_cldierr_t& self, long long, const u32_t *, const u32_t * _=NULL);
	static int Init(_cldierr_t& self, int, const u32_t *, const u32_t * _=NULL);
	static int Init(_cldierr_t& self, const u32_t *, const u32_t * _=NULL);
	static int Init(_cldierr_t& self, long long, const u32_t *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, int, const u32_t *, CLDISTRHANDLE);
	static int Init(_cldierr_t& self, const u32_t *, CLDISTRHANDLE);
	static _cldierr_t& New(long long, const u32_t *, const u32_t * _=NULL);
	static _cldierr_t& New(int, const u32_t *, const u32_t * _=NULL);
	static _cldierr_t& New(const u32_t *, const u32_t * _=NULL);
	static _cldierr_t& New(long long, const u32_t *, CLDISTRHANDLE);
	static _cldierr_t& New(int, const u32_t *, CLDISTRHANDLE);
	static _cldierr_t& New(const u32_t *, CLDISTRHANDLE);

	_cldierr_t(long long code, CLDISTRHANDLE name, CLDISTRHANDLE description=CLDISTRHANDLE_NULL);
	_cldierr_t(int       code, CLDISTRHANDLE name, CLDISTRHANDLE description=CLDISTRHANDLE_NULL);
	_cldierr_t(CLDISTRHANDLE name, CLDISTRHANDLE description=CLDISTRHANDLE_NULL);
	static int Init(_cldierr_t& self, long long, CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);
	static int Init(_cldierr_t& self, int, CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);
	static int Init(_cldierr_t& self, CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);
	static _cldierr_t& New(long long, CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);
	static _cldierr_t& New(int, CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);
	static _cldierr_t& New(CLDISTRHANDLE, CLDISTRHANDLE _=CLDISTRHANDLE_NULL);

	~_cldierr_t();
	static int Drop(_cldierr_t& self);


	CLDISTRHANDLE GetErrorName() const;
	CLDISTRHANDLE GetDescription() const;

	long long     GetErrorCode() const;

	int           Throw();

#endif
};

typedef struct _cldierr_t cldierr_t;

#ifdef __cplusplus
#	if __CLDI_no_cpp > false
	}
#	else
	namespace cldi
	{
		namespace portable
		{
			using err_t = cldierr_t;
		}
		using portable::err_t;
	}
#	endif
#endif



#endif /* _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_H */
