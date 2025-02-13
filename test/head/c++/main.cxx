
#include "test.hpp"

void settings_test()
{
	using namespace std;

	cout << "\nSettings Test:\n" << endl;

	ppref("WPERMIT_LEVEL", CLDI_WPERMIT_LEVEL);
	ppref("INCLUDE_MATH", CLDI_INCLUDE_MATH);
	ppref("C_ONLY", CLDI_C_ONLY);

	cout << "\nSettings Test Completed!\n" << endl;
}

void platform_test()
{
	using namespace std;

	cout << "\nPlatform Test:\n" << endl;

	ppref("PLATFORM_UNKNOWN", CLDI_PLATFORM_UNKNOWN);
	ppref("WINDOWS", CLDI_WINDOWS);
	ppref("LINUX", CLDI_LINUX);
	ppref("OSX", CLDI_OSX);
	ppref("BSD", CLDI_BSD);
	ppref("ANDROID", CLDI_ANDROID);
	ppref("IOS", CLDI_IOS);
	ppref("WASM", CLDI_WASM);

	ppref("UNKNOWN_COMPILER", CLDI_UNKNOWN_COMPILER);
	ppref("GCC", CLDI_GCC);
	ppref("MSVC", CLDI_MSVC);
	ppref("CLANG", CLDI_CLANG);
	ppref("WASM_COMPILER", CLDI_WASM_COMPILER);

	ppref("UNKNOWN_ARCHITECTURE", CLDI_UNKNOWN_ARCHITECTURE);
	ppref("X86", CLDI_X86);
	ppref("ARM", CLDI_ARM);
	ppref("POWERPC", CLDI_POWERPC);
	ppref("WASM_ARCH", CLDI_WASM_ARCH);

	ppref("PLATFORM_UNIXLIKE", CLDI_PLATFORM_UNIXLIKE);
	ppref("PLATFORM32", CLDI_PLATFORM32);
	ppref("PLATFORM", CLDI_PLATFORM);
	ppref("COMPILER", CLDI_COMPILER);
	ppref("ARCH", CLDI_ARCH);

	cout << "\nPlatform Test Completed!\n" << endl;
}

void stat_test()
{
	using namespace std;

	cout << "\nStat Test:\n" << endl;

	ppref("WDEFRAG_RECOMMENDED", CLDI_WDEFRAG_RECOMMENDED);

	ppref("SUCCESS", CLDI_SUCCESS);

	ppref("FALSE", CLDI_FALSE);

	ppref("EUNKNOWN", CLDI_EUNKNOWN);

	ppref("ENO_IMPL", CLDI_ENO_IMPL);

	ppref("EOUT_OF_MEMORY", CLDI_EOUT_OF_MEMORY);
	ppref("EDEFRAG_REQUIRED", CLDI_EDEFRAG_REQUIRED);

	ppref("ENULL_ATTR", CLDI_ENULL_ATTR);
	ppref("ENULL_ARG", CLDI_ENULL_ARG);
	ppref("ENULL_SELF", CLDI_ENULL_SELF);
	ppref("EINVALID_ATTR", CLDI_EINVALID_ATTR);
	ppref("EINVALID_ARG", CLDI_EINVALID_ARG);
	ppref("EINVALID_SELF", CLDI_EINVALID_SELF);

	ppref("ENO_ACCESS", CLDI_ENO_ACCESS);
	ppref("ENOT_READABLE", CLDI_ENOT_READABLE);
	ppref("ENOT_WRITABLE", CLDI_ENOT_WRITABLE);
	ppref("ENOT_EXECUTABLE", CLDI_ENOT_EXECUTABLE);
	ppref("ENONEXISTENT", CLDI_ENONEXISTENT);

	ppref("EINCOMPATIBLE_TYPE", CLDI_EINCOMPATIBLE_TYPE);

	cout << "\nStat Test Completed!\n" << endl;
}

void types_test()
{
	using namespace std;

	cout << "\nTypes Test:\n" << endl;

	cout << setw(width) << left << "GetCurrentPID()";
	cout << cldiGetCurrentPID() << '=' << cldi::GetCurrentPID() << '=' << getpid() << endl;

	cout << setw(width) << left << "LDBL_ENABLED(" << sizeof(cldifpm_t) << ')';
	cout << CLDI_LDBL_ENABLED << endl;

	ppref("NULL_TYPE", CLDI_NULL_TYPE);
	ppref("INTEGER_TYPE", CLDI_INTEGER_TYPE);
	ppref("FLOAT_TYPE", CLDI_FLOAT_TYPE);
	ppref("PTR_TYPE", CLDI_PTR_TYPE);
	ppref("STRUCT_TYPE", CLDI_STRUCT_TYPE);

	clditypeinfo_t ttt = cldiTypeInfoChar;
	cout << "clditypeinfo_t(char)\n\tsize: " << ttt.size << "\n\ttempl: " << ttt.templ << endl;

	cldi::typeinfo_t<void> ttv, ttv2;
	cldi::typeinfo_t<int> tti, tti2;
	cldi::typeinfo_t<float> ttf, ttf2;
	cout << "cldi::typeinfo_t<void>\n\tsize: " << ttv.Size() << "\n\ttempl: " << ttv.Template() << endl;
	cout << "cldi::typeinfo_t<int>\n\tsize: " << tti.Size() << "\n\ttempl: " << tti.Template() << endl;
	cout << "cldi::typeinfo_t<float>\n\tsize: " << ttf.Size() << "\n\ttempl: " << ttf.Template() << endl;
	cout << "cldi::typeinfo_t comparisons:\n\tvoid=void: " << (ttv == ttv2) << "\n\tint=int: " <<
		(tti == tti2) << "\n\tfloat=float: " << (ttf == ttf2) << endl;

	cldi::pair<int, float> p1(4, 65.9f);
	cldi::pair<int, float> p2(4, 65.9f);
	cldi::pair<int, int> pp1(4, 4), pp2(4, 4);
	cout << "cldi::pair comparisons:\n\tint,float=int,float: " << (p1 == p2) << "\n\tint,int=int,int: " <<
		(pp1 == pp2) << endl;

	cout << "\nTypes Test Completed!\n" << endl;
}


char dummySupplier()
{
	return 'm';
}
void dummyConsumer(int, float, bool)
{
	std::cout << "\ndummyConsumer()" << std::endl;
}
int dummyFunction(int i, float f, bool b)
{
	float r = f / float(i);

	if (b)
		r *= (-1.0f);

	return r;
}
void dummySubroutine()
{
	std::cout << "\ndummySubroutine()" << std::endl;
}
void functypes_test()
{
	using namespace std;

	cout << "\n'functypes' Test:\n" << endl;

	cldiTemplSupplier(char, supplier_t);
	cldiTemplConsumer(consumer_t, int, float, bool);
	cldiTemplFunction(int, function_t, int, float, bool);

	supplier_t       sp = dummySupplier;
	consumer_t       c  = dummyConsumer;
	function_t       f  = dummyFunction;
	cldisubroutine_t sr = dummySubroutine;

	cout << "supplier: " << sp() << endl;
	c(4, 6.557f, true);
	cout << "function: " << f(22, 19.1f, false) << endl;
	sr();

	cout << "\n'functypes' Tests Completed!\n" << endl;
}

void memory_test()
{

}


int main(void)
{
	using namespace std;

	cout << "Running Tests...\n\nRunning Setup Tests..." << endl;

	settings_test();
	platform_test();
	stat_test();
	types_test();

	cout << "\nCompleted Setup Tests!\n\nRunning Module Tests...\n" << endl;

	functypes_test();
	memory_test();

	cout << "\nCompleted Module Tests!\n\nTest Routine Completed!\n" << endl;

	return 0;
}
