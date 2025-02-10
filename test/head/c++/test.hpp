
constexpr int width = 30;
#define ppref(name, symbol) \
	cout << setw(width) << left << name; \
	cout << symbol << endl;

#include <iostream>
#include <iomanip>

#define CLDI_C_ONLY false
#define CLDI_INCLUDE_MATH true

#include <cldi/head.h>
