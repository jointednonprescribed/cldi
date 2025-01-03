
#ifndef _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_ASSOCSR_H
#define _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_ASSOCSR_H 1

#include "../../../setup.h"

#include "cldierr_t.h"

#include "../../../"



int cldiInitErrBlankLong(cldierr_t* self, long long code);
int cldiInitErrBlankInt(cldierr_t* self, int code);
int cldiInitErrBlank(cldierr_t* self);
cldierr_t* cldiNewErrBlankLong(long long code);
cldierr_t* cldiNewErrBlankInt(int code);
cldierr_t* cldiNewErrBlank(void);

int cldiInitErrLong(cldierr_t* self, long long, const char *, const char *);
int cldiInitErrInt(cldierr_t* self, int, const char *, const char *);
int cldiInitErr(cldierr_t* self, const char *, const char *);
int cldiInitErrLongHDesc(cldierr_t* self, long long, const char *, CLDISTRHANDLE);
int cldiInitErrIntHDesc(cldierr_t* self, int, const char *, CLDISTRHANDLE);
int cldiInitErrHDesc(cldierr_t* self, const char *, CLDISTRHANDLE);
int cldiInitErrLongNamed(cldierr_t* self, long long, const char *);
int cldiInitErrIntNamed(cldierr_t* self, int, const char *);
int cldiInitErrNamed(cldierr_t* self, const char *);
cldierr_t* cldiNewErrLong(long long, const char *, const char *);
cldierr_t* cldiNewErrInt(int, const char *, const char *);
cldierr_t* cldiNewErr(const char *, const char *);
cldierr_t* cldiNewErrLongHDesc(long long, const char *, CLDISTRHANDLE);
cldierr_t* cldiNewErrIntHDesc(int, const char *, CLDISTRHANDLE);
cldierr_t* cldiNewErrHDesc(const char *, CLDISTRHANDLE);
cldierr_t* cldiNewErrLongNamed(long long, const char *);
cldierr_t* cldiNewErrIntNamed(int, const char *);
cldierr_t* cldiNewErrNamed(const char *);

int cldiInitErrLongW(cldierr_t* self, long long, const u16_t *, const u16_t *);
int cldiInitErrIntW(cldierr_t* self, int, const u16_t *, const u16_t *);
int cldiInitErrW(cldierr_t* self, const u16_t *, const u16_t *);
int cldiInitErrLongWHDesc(cldierr_t* self, long long, const u16_t *, CLDISTRHANDLE);
int cldiInitErrIntWHDesc(cldierr_t* self, int, const u16_t *, CLDISTRHANDLE);
int cldiInitErrWHDesc(cldierr_t* self, const u16_t *, CLDISTRHANDLE);
int cldiInitErrLongWNamed(cldierr_t* self, long long, const u16_t *);
int cldiInitErrIntWNamed(cldierr_t* self, int, const u16_t *);
int cldiInitErrWNamed(cldierr_t* self, const u16_t *);
cldierr_t* cldiNewErrLongW(long long, const u16_t *, const u16_t *);
cldierr_t* cldiNewErrIntW(int, const u16_t *, const u16_t *);
cldierr_t* cldiNewErrW(const u16_t *, const u16_t *);
cldierr_t* cldiNewErrLongWHDesc(long long, const u16_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrIntWHDesc(int, const u16_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrWHDesc(const u16_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrLongWNamed(long long, const u16_t *);
cldierr_t* cldiNewErrIntWNamed(int, const u16_t *);
cldierr_t* cldiNewErrWNamed(const u16_t *);

int cldiInitErrLongWW(cldierr_t* self, long long, const u32_t *, const u32_t *);
int cldiInitErrIntWW(cldierr_t* self, int, const u32_t *, const u32_t *);
int cldiInitErrWW(cldierr_t* self, const u32_t *, const u32_t *);
int cldiInitErrLongWWHDesc(cldierr_t* self, long long, const u32_t *, CLDISTRHANDLE);
int cldiInitErrIntWWHDesc(cldierr_t* self, int, const u32_t *, CLDISTRHANDLE);
int cldiInitErrWWHDesc(cldierr_t* self, const u32_t *, CLDISTRHANDLE);
int cldiInitErrLongWWNamed(cldierr_t* self, long long, const u32_t *);
int cldiInitErrIntWWNamed(cldierr_t* self, int, const u32_t *);
int cldiInitErrWWNamed(cldierr_t* self, const u32_t *);
cldierr_t* cldiNewErrLongWW(long long, const u32_t *, const u32_t *);
cldierr_t* cldiNewErrIntWW(int, const u32_t *, const u32_t *);
cldierr_t* cldiNewErrWW(const u32_t *, const u32_t *);
cldierr_t* cldiNewErrLongWWHDesc(long long, const u32_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrIntWWHDesc(int, const u32_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrWWHDesc(const u32_t *, CLDISTRHANDLE);
cldierr_t* cldiNewErrLongWWNamed(long long, const u32_t *);
cldierr_t* cldiNewErrIntWWNamed(int, const u32_t *);
cldierr_t* cldiNewErrWWNamed(const u32_t *);

int cldiInitErrLongH(cldierr_t* self, long long, CLDISTRHANDLE, CLDISTRHANDLE);
int cldiInitErrIntH(cldierr_t* self, int, CLDISTRHANDLE, CLDISTRHANDLE);
int cldiInitErrH(cldierr_t* self, CLDISTRHANDLE, CLDISTRHANDLE);
int cldiInitErrLongHNamed(cldierr_t* self, long long, CLDISTRHANDLE);
int cldiInitErrIntHNamed(cldierr_t* self, int, CLDISTRHANDLE);
int cldiInitErrHNamed(cldierr_t* self, CLDISTRHANDLE);
cldierr_t* cldiNewErrLongH(long long, CLDISTRHANDLE, CLDISTRHANDLE);
cldierr_t* cldiNewErrIntH(int, CLDISTRHANDLE, CLDISTRHANDLE);
cldierr_t* cldiNewErrH(CLDISTRHANDLE, CLDISTRHANDLE);
cldierr_t* cldiNewErrLongHNamed(long long, CLDISTRHANDLE);
cldierr_t* cldiNewErrIntHNamed(int, CLDISTRHANDLE);
cldierr_t* cldiNewErrHNamed(CLDISTRHANDLE);

int cldiDropErr(cldierr_t* drop);


CLDISTRHANDLE cldiErrGetName(const cldierr_t* get_from);
CLDISTRHANDLE cldiErrGetDescription(const cldierr_t* get_from);

long long     cldiErrGetCode(const cldierr_t* get_from);

int cldiThrowErr(cldierr_t* error);
int cldiThrowErrTo(cldierr_t* error, FILE* file);
int cldiThrowErrToHandle(cldierr_t* error, CLDIFILEHANDLE* file);
int cldiDumpErr(cldierr_t* error);
int cldiDumpErrTo(cldierr_t* error, FILE* file);
int cldiDumpErrToHandle(cldierr_t* error, CLDIFILEHANDLE* file);



#endif /* _cldi_portable__errhandling_throwers_IMPL_CLDIERR_T_ASSOCSR_H */
