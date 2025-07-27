
#ifndef _cldi_head__math_I128_H
#define _cldi_head__math_I128_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__MATH_H
#	include "../math.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



cldii128_t cldii128u(cldiu128_t a);                            // convert
cldii128_t cldii128fm(cldifpm_t a);
cldii128_t cldii128d(double a);
cldii128_t cldii128f(float a);
cldii128_t cldii128ll(signed long long a);
cldii128_t cldii128ull(unsigned long long a);
cldii128_t cldii128l(signed long a);
cldii128_t cldii128ul(unsigned long a);
cldii128_t cldii128i(signed int a);
cldii128_t cldii128ui(unsigned int a);
cldii128_t cldii128h(signed short a);
cldii128_t cldii128uh(unsigned short a);
cldii128_t cldii128hh(signed char a);
cldii128_t cldii128uhh(unsigned char a);
cldii128_t cldii128add(cldii128_t a, cldii128_t b);            // +  add
cldii128_t cldii128addu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128addfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128addd(cldii128_t a, double b);
cldii128_t cldii128addf(cldii128_t a, float b);
cldii128_t cldii128addll(cldii128_t a, signed long long b);
cldii128_t cldii128addull(cldii128_t a, unsigned long long b);
cldii128_t cldii128addl(cldii128_t a, signed long b);
cldii128_t cldii128addul(cldii128_t a, unsigned long b);
cldii128_t cldii128addi(cldii128_t a, signed int b);
cldii128_t cldii128addui(cldii128_t a, unsigned int b);
cldii128_t cldii128addh(cldii128_t a, signed short b);
cldii128_t cldii128adduh(cldii128_t a, unsigned short b);
cldii128_t cldii128addhh(cldii128_t a, signed char b);
cldii128_t cldii128adduhh(cldii128_t a, unsigned char b);
cldii128_t cldii128sub(cldii128_t a, cldii128_t b);            // -  subtract
cldii128_t cldii128subu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128subfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128subd(cldii128_t a, double b);
cldii128_t cldii128subf(cldii128_t a, float b);
cldii128_t cldii128subll(cldii128_t a, signed long long b);
cldii128_t cldii128subull(cldii128_t a, unsigned long long b);
cldii128_t cldii128subl(cldii128_t a, signed long b);
cldii128_t cldii128subul(cldii128_t a, unsigned long b);
cldii128_t cldii128subi(cldii128_t a, signed int b);
cldii128_t cldii128subui(cldii128_t a, unsigned int b);
cldii128_t cldii128subh(cldii128_t a, signed short b);
cldii128_t cldii128subuh(cldii128_t a, unsigned short b);
cldii128_t cldii128subhh(cldii128_t a, signed char b);
cldii128_t cldii128subuhh(cldii128_t a, unsigned char b);
cldii128_t cldii128mul(cldii128_t a, cldii128_t b);            // *  multiply
cldii128_t cldii128mulu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128mulfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128muld(cldii128_t a, double b);
cldii128_t cldii128mulf(cldii128_t a, float b);
cldii128_t cldii128mulll(cldii128_t a, signed long long b);
cldii128_t cldii128mulull(cldii128_t a, unsigned long long b);
cldii128_t cldii128mull(cldii128_t a, signed long b);
cldii128_t cldii128mulul(cldii128_t a, unsigned long b);
cldii128_t cldii128muli(cldii128_t a, signed int b);
cldii128_t cldii128mului(cldii128_t a, unsigned int b);
cldii128_t cldii128mulh(cldii128_t a, signed short b);
cldii128_t cldii128muluh(cldii128_t a, unsigned short b);
cldii128_t cldii128mulhh(cldii128_t a, signed char b);
cldii128_t cldii128muluhh(cldii128_t a, unsigned char b);
cldii128_t cldii128div(cldii128_t a, cldii128_t b);            // /  divide (floor divide)
cldii128_t cldii128divu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128divfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128divd(cldii128_t a, double b);
cldii128_t cldii128divf(cldii128_t a, float b);
cldii128_t cldii128divll(cldii128_t a, signed long long b);
cldii128_t cldii128divull(cldii128_t a, unsigned long long b);
cldii128_t cldii128divl(cldii128_t a, signed long b);
cldii128_t cldii128divul(cldii128_t a, unsigned long b);
cldii128_t cldii128divi(cldii128_t a, signed int b);
cldii128_t cldii128divui(cldii128_t a, unsigned int b);
cldii128_t cldii128divh(cldii128_t a, signed short b);
cldii128_t cldii128divuh(cldii128_t a, unsigned short b);
cldii128_t cldii128divhh(cldii128_t a, signed char b);
cldii128_t cldii128divuhh(cldii128_t a, unsigned char b);
cldii128_t cldii128mod(cldii128_t a, cldii128_t b);            // %  modulus
cldii128_t cldii128modu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128modfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128modd(cldii128_t a, double b);
cldii128_t cldii128modf(cldii128_t a, float b);
cldii128_t cldii128modll(cldii128_t a, signed long long b);
cldii128_t cldii128modull(cldii128_t a, unsigned long long b);
cldii128_t cldii128modl(cldii128_t a, signed long b);
cldii128_t cldii128modul(cldii128_t a, unsigned long b);
cldii128_t cldii128modi(cldii128_t a, signed int b);
cldii128_t cldii128modui(cldii128_t a, unsigned int b);
cldii128_t cldii128modh(cldii128_t a, signed short b);
cldii128_t cldii128moduh(cldii128_t a, unsigned short b);
cldii128_t cldii128modhh(cldii128_t a, signed char b);
cldii128_t cldii128moduhh(cldii128_t a, unsigned char b);
cldii128_t cldii128and(cldii128_t a, cldii128_t b);            // &  bitwise and
cldii128_t cldii128andu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128andfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128andd(cldii128_t a, double b);
cldii128_t cldii128andf(cldii128_t a, float b);
cldii128_t cldii128andll(cldii128_t a, signed long long b);
cldii128_t cldii128andull(cldii128_t a, unsigned long long b);
cldii128_t cldii128andl(cldii128_t a, signed long b);
cldii128_t cldii128andul(cldii128_t a, unsigned long b);
cldii128_t cldii128andi(cldii128_t a, signed int b);
cldii128_t cldii128andui(cldii128_t a, unsigned int b);
cldii128_t cldii128andh(cldii128_t a, signed short b);
cldii128_t cldii128anduh(cldii128_t a, unsigned short b);
cldii128_t cldii128andhh(cldii128_t a, signed char b);
cldii128_t cldii128anduhh(cldii128_t a, unsigned char b);
cldii128_t cldii128or(cldii128_t a, cldii128_t b);             // |  bitwise or
cldii128_t cldii128oru(cldii128_t a, cldiu128_t b);
cldii128_t cldii128orfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128ord(cldii128_t a, double b);
cldii128_t cldii128orf(cldii128_t a, float b);
cldii128_t cldii128orll(cldii128_t a, signed long long b);
cldii128_t cldii128orull(cldii128_t a, unsigned long long b);
cldii128_t cldii128orl(cldii128_t a, signed long b);
cldii128_t cldii128orul(cldii128_t a, unsigned long b);
cldii128_t cldii128ori(cldii128_t a, signed int b);
cldii128_t cldii128orui(cldii128_t a, unsigned int b);
cldii128_t cldii128orh(cldii128_t a, signed short b);
cldii128_t cldii128oruh(cldii128_t a, unsigned short b);
cldii128_t cldii128orhh(cldii128_t a, signed char b);
cldii128_t cldii128oruhh(cldii128_t a, unsigned char b);
cldii128_t cldii128xor(cldii128_t a, cldii128_t b);            // ^  bitwise xor
cldii128_t cldii128xoru(cldii128_t a, cldiu128_t b);
cldii128_t cldii128xorfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128xord(cldii128_t a, double b);
cldii128_t cldii128xorf(cldii128_t a, float b);
cldii128_t cldii128xorll(cldii128_t a, signed long long b);
cldii128_t cldii128xorull(cldii128_t a, unsigned long long b);
cldii128_t cldii128xorl(cldii128_t a, signed long b);
cldii128_t cldii128xorul(cldii128_t a, unsigned long b);
cldii128_t cldii128xori(cldii128_t a, signed int b);
cldii128_t cldii128xorui(cldii128_t a, unsigned int b);
cldii128_t cldii128xorh(cldii128_t a, signed short b);
cldii128_t cldii128xoruh(cldii128_t a, unsigned short b);
cldii128_t cldii128xorhh(cldii128_t a, signed char b);
cldii128_t cldii128xoruhh(cldii128_t a, unsigned char b);
cldii128_t cldii128bsr(cldii128_t a, cldii128_t b);            // >> bitshift right
cldii128_t cldii128bsru(cldii128_t a, cldiu128_t b);
cldii128_t cldii128bsrfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128bsrd(cldii128_t a, double b);
cldii128_t cldii128bsrf(cldii128_t a, float b);
cldii128_t cldii128bsrll(cldii128_t a, signed long long b);
cldii128_t cldii128bsrull(cldii128_t a, unsigned long long b);
cldii128_t cldii128bsrl(cldii128_t a, signed long b);
cldii128_t cldii128bsrul(cldii128_t a, unsigned long b);
cldii128_t cldii128bsri(cldii128_t a, signed int b);
cldii128_t cldii128bsrui(cldii128_t a, unsigned int b);
cldii128_t cldii128bsrh(cldii128_t a, signed short b);
cldii128_t cldii128bsruh(cldii128_t a, unsigned short b);
cldii128_t cldii128bsrhh(cldii128_t a, signed char b);
cldii128_t cldii128bsruhh(cldii128_t a, unsigned char b);
cldii128_t cldii128bsl(cldii128_t a, cldii128_t b);            // << bitshift left
cldii128_t cldii128bslu(cldii128_t a, cldiu128_t b);
cldii128_t cldii128bslfm(cldii128_t a, cldifpm_t b);
cldii128_t cldii128bsld(cldii128_t a, double b);
cldii128_t cldii128bslf(cldii128_t a, float b);
cldii128_t cldii128bslll(cldii128_t a, signed long long b);
cldii128_t cldii128bslull(cldii128_t a, unsigned long long b);
cldii128_t cldii128bsll(cldii128_t a, signed long b);
cldii128_t cldii128bslul(cldii128_t a, unsigned long b);
cldii128_t cldii128bsli(cldii128_t a, signed int b);
cldii128_t cldii128bslui(cldii128_t a, unsigned int b);
cldii128_t cldii128bslh(cldii128_t a, signed short b);
cldii128_t cldii128bsluh(cldii128_t a, unsigned short b);
cldii128_t cldii128bslhh(cldii128_t a, signed char b);
cldii128_t cldii128bsluhh(cldii128_t a, unsigned char b);

cldiu128_t cldiu128s(cldiu128_t a);                            // convert
cldiu128_t cldiu128fm(cldifpm_t a);
cldiu128_t cldiu128d(double a);
cldiu128_t cldiu128f(float a);
cldiu128_t cldiu128ll(signed long long a);
cldiu128_t cldiu128ull(unsigned long long a);
cldiu128_t cldiu128l(signed long a);
cldiu128_t cldiu128ul(unsigned long a);
cldiu128_t cldiu128i(signed int a);
cldiu128_t cldiu128ui(unsigned int a);
cldiu128_t cldiu128h(signed short a);
cldiu128_t cldiu128uh(unsigned short a);
cldiu128_t cldiu128hh(signed char a);
cldiu128_t cldiu128uhh(unsigned char a);
cldiu128_t cldiu128add(cldiu128_t a, cldiu128_t b);            // +  add
cldiu128_t cldiu128adds(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128addfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128addd(cldiu128_t a, double b);
cldiu128_t cldiu128addf(cldiu128_t a, float b);
cldiu128_t cldiu128addll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128addull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128addl(cldiu128_t a, signed long b);
cldiu128_t cldiu128addul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128addi(cldiu128_t a, signed int b);
cldiu128_t cldiu128addui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128addh(cldiu128_t a, signed short b);
cldiu128_t cldiu128adduh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128addhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128adduhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128sub(cldiu128_t a, cldiu128_t b);            // -  subtract
cldiu128_t cldiu128subs(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128subfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128subd(cldiu128_t a, double b);
cldiu128_t cldiu128subf(cldiu128_t a, float b);
cldiu128_t cldiu128subll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128subull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128subl(cldiu128_t a, signed long b);
cldiu128_t cldiu128subul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128subi(cldiu128_t a, signed int b);
cldiu128_t cldiu128subui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128subh(cldiu128_t a, signed short b);
cldiu128_t cldiu128subuh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128subhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128subuhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128mul(cldiu128_t a, cldiu128_t b);            // *  multiply
cldiu128_t cldiu128muls(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128mulfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128muld(cldiu128_t a, double b);
cldiu128_t cldiu128mulf(cldiu128_t a, float b);
cldiu128_t cldiu128mulll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128mulull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128mull(cldiu128_t a, signed long b);
cldiu128_t cldiu128mulul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128muli(cldiu128_t a, signed int b);
cldiu128_t cldiu128mului(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128mulh(cldiu128_t a, signed short b);
cldiu128_t cldiu128muluh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128mulhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128muluhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128div(cldiu128_t a, cldiu128_t b);            // /  divide (floor divide)
cldiu128_t cldiu128divs(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128divfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128divd(cldiu128_t a, double b);
cldiu128_t cldiu128divf(cldiu128_t a, float b);
cldiu128_t cldiu128divll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128divull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128divl(cldiu128_t a, signed long b);
cldiu128_t cldiu128divul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128divi(cldiu128_t a, signed int b);
cldiu128_t cldiu128divui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128divh(cldiu128_t a, signed short b);
cldiu128_t cldiu128divuh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128divhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128divuhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128mod(cldiu128_t a, cldiu128_t b);            // %  modulus
cldiu128_t cldiu128mods(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128modfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128modd(cldiu128_t a, double b);
cldiu128_t cldiu128modf(cldiu128_t a, float b);
cldiu128_t cldiu128modll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128modull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128modl(cldiu128_t a, signed long b);
cldiu128_t cldiu128modul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128modi(cldiu128_t a, signed int b);
cldiu128_t cldiu128modui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128modh(cldiu128_t a, signed short b);
cldiu128_t cldiu128moduh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128modhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128moduhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128and(cldiu128_t a, cldiu128_t b);            // &  bitwise and
cldiu128_t cldiu128ands(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128andfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128andd(cldiu128_t a, double b);
cldiu128_t cldiu128andf(cldiu128_t a, float b);
cldiu128_t cldiu128andll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128andull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128andl(cldiu128_t a, signed long b);
cldiu128_t cldiu128andul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128andi(cldiu128_t a, signed int b);
cldiu128_t cldiu128andui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128andh(cldiu128_t a, signed short b);
cldiu128_t cldiu128anduh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128andhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128anduhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128or(cldiu128_t a, cldiu128_t b);             // |  bitwise or
cldiu128_t cldiu128ors(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128orfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128ord(cldiu128_t a, double b);
cldiu128_t cldiu128orf(cldiu128_t a, float b);
cldiu128_t cldiu128orll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128orull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128orl(cldiu128_t a, signed long b);
cldiu128_t cldiu128orul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128ori(cldiu128_t a, signed int b);
cldiu128_t cldiu128orui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128orh(cldiu128_t a, signed short b);
cldiu128_t cldiu128oruh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128orhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128oruhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128xor(cldiu128_t a, cldiu128_t b);            // ^  bitwise xor
cldiu128_t cldiu128xors(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128xorfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128xord(cldiu128_t a, double b);
cldiu128_t cldiu128xorf(cldiu128_t a, float b);
cldiu128_t cldiu128xorll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128xorull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128xorl(cldiu128_t a, signed long b);
cldiu128_t cldiu128xorul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128xori(cldiu128_t a, signed int b);
cldiu128_t cldiu128xorui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128xorh(cldiu128_t a, signed short b);
cldiu128_t cldiu128xoruh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128xorhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128xoruhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128bsr(cldiu128_t a, cldiu128_t b);            // >> bitshift right
cldiu128_t cldiu128bsrs(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128bsrfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128bsrd(cldiu128_t a, double b);
cldiu128_t cldiu128bsrf(cldiu128_t a, float b);
cldiu128_t cldiu128bsrll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128bsrull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128bsrl(cldiu128_t a, signed long b);
cldiu128_t cldiu128bsrul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128bsri(cldiu128_t a, signed int b);
cldiu128_t cldiu128bsrui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128bsrh(cldiu128_t a, signed short b);
cldiu128_t cldiu128bsruh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128bsrhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128bsruhh(cldiu128_t a, unsigned char b);
cldiu128_t cldiu128bsl(cldiu128_t a, cldiu128_t b);            // << bitshift left
cldiu128_t cldiu128bsls(cldiu128_t a, cldii128_t b);
cldiu128_t cldiu128bslfm(cldiu128_t a, cldifpm_t b);
cldiu128_t cldiu128bsld(cldiu128_t a, double b);
cldiu128_t cldiu128bslf(cldiu128_t a, float b);
cldiu128_t cldiu128bslll(cldiu128_t a, signed long long b);
cldiu128_t cldiu128bslull(cldiu128_t a, unsigned long long b);
cldiu128_t cldiu128bsll(cldiu128_t a, signed long b);
cldiu128_t cldiu128bslul(cldiu128_t a, unsigned long b);
cldiu128_t cldiu128bsli(cldiu128_t a, signed int b);
cldiu128_t cldiu128bslui(cldiu128_t a, unsigned int b);
cldiu128_t cldiu128bslh(cldiu128_t a, signed short b);
cldiu128_t cldiu128bsluh(cldiu128_t a, unsigned short b);
cldiu128_t cldiu128bslhh(cldiu128_t a, signed char b);
cldiu128_t cldiu128bsluhh(cldiu128_t a, unsigned char b);

#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_I128_H
