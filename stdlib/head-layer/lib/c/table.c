


/* Implementing cldi-head: table.h */
#include <cldi/head/table.h>



const char CLDIERRMSG_TABLE_FAIL_COPY_DATA[] =
	"Failed to copy the input data to a new memory block.";
const char CLDIERRMSG_TABLE_FAIL_BORROW_DATA[] =
	"Failed to borrow the specified data.";
const char CLDIERRMSG_TABLE_FAIL_CREATE_TABLE_UNEXP[] =
	"Failed to create the described table (unexpected error).";
const char CLDIERRMSG_TABLE_FAIL_GET_ACCESS[] =
	"Failed to get non-const access to table data.";
const char CLDIERRMSG_TABLE_FAIL_GET_CONST_ACCESS[] =
	"Failed to get const access to table data.";
const char CLDIERRMSG_TABLE_INCOMPATIBLE_TYPE[] =
	"The type introduced is incompatible as a table value.";


clditable_t* cldiInitTable(clditable_t *self) CLDINOEXCEPT
{
	cldiInitMemref(&self->data);
	self->rows = 0;
	self->cols = 0;

	return self;
}
clditable_t* cldiInitTableCopy(clditable_t *self, const clditable_t *copy_of)
{
	CLDI_ECTRL;

	cldiInitMemrefCopy(&self->data, &copy_of->data);
	CLDI_CATCH
		cldiAddTraceback(cldiInitTableCopy, CLDIERRMSG_TABLE_FAIL_COPY_DATA);

	self->rows = copy_of->rows;
	self->cols = copy_of->cols;

	return self;
}
clditable_t* cldiInitTableBorrowed(clditable_t *self, const clditable_t *borrow)
{
	CLDI_ECTRL;

	cldiInitMemrefBorrowed(&self->data, &borrow->data);
	CLDI_CATCH
		cldiAddTraceback(cldiInitTableBorrowed, CLDIERRMSG_TABLE_FAIL_BORROW_DATA);
	
	self->rows = borrow->rows;
	self->cols = borrow->cols;

	return self;
}
clditable_t* cldiInitTableCols(
	clditable_t         *self,
	size_t               colc,
	const clditypeinfo_t types[],
	const char         **names
){
	CLDI_ECTRL;

	/* .table_start:
	 *    Row pre2: clditypeinfo_t structures for each column to store their
	 *              type.
	 *    Row pre1: `const char*` values to the end of the memory block where
	 *              column names are stored (if any).
	 *    Row 0+:   Entered table data.
	 */
	cldiInitMemref(&self->data);
	self->rows = 0;
	self->cols = 0;
	cldiTableCreate(self, colc, CLDI_DEFAULT_TABLE_SIZE, types, names);
	CLDI_CATCH
		cldiAddTraceback(cldiInitTableCols, CLDIERRMSG_TABLE_FAIL_CREATE_TABLE_UNEXP);

	return self;
}
clditable_t* cldiInitTableColsN(
	clditable_t         *self,
	size_t               colc,
	size_t               rowc,
	const clditypeinfo_t types[],
	const char         **names
){
	CLDI_ECTRL;

	/* .table_start:
	 *    Row pre2: clditypeinfo_t structures for each column to store their
	 *              type.
	 *    Row pre1: `const char*` values to the end of the memory block where
	 *              column names are stored (if any).
	 *    Row 0+:   Entered table data.
	 */
	cldiInitMemref(&self->data);
	self->rows = 0;
	self->cols = 0;
	cldiTableCreate(self, colc, rowc, types, names);
	CLDI_CATCH
		cldiAddTraceback(cldiInitTableCols, CLDIERRMSG_TABLE_FAIL_CREATE_TABLE_UNEXP);

	return self;
}
clditable_t* cldiInitTableData(
	clditable_t         *self,
	size_t               colc,
	size_t               rowc,
	const clditypeinfo_t types[],
	const char         **names,
	...
){
	CLDI_ECTRL;

	clditypeinfo_t te;
	for (size_t i = 0; i < colc; i++) {
		te = types[i];
		if (
			te.templ == CLDI_STRUCT_TYPE ||
			((te.size  == 1 || te.size == 2) && te.templ != CLDI_INT_TYPE) ||
		#if CLDI_LDBL_ENABLED == true
			(te.size == sizeof(long double) && te.templ != CLDI_FLOAT_TYPE) ||
		#endif
		#if CLDI_PLATFORM32 == true
			(te.size == 8 && (
				te.templ == CLDI_PTR_TYPE  ||
				te.templ == CLDI_CSTR_TYPE ||
				te.templ == CLDI_WSTR_TYPE
			))
		#else
			(te.size == 4 && (
				te.templ == CLDI_PTR_TYPE  ||
				te.templ == CLDI_CSTR_TYPE ||
				te.templ == CLDI_WSTR_TYPE
			))
		#endif
		) goto incompatible_type;
	}

	/* .table_start:
	 *    Column pre2: `clditypeinfo_t` structures for each column to store their
	 *                 type.
	 *    Column pre1: `const char*` values to the end of the memory block where
	 *                 column names are stored (if any).
	 *    Column 0+:   Entered table data.
	 * Values are grouped by column because items in the same columns will be the
	 * same type.
	 */
	cldiInitMemref(&self->data);
	self->rows = 0;
	self->cols = 0;
	cldiTableCreate(self, colc, rowc, types, names);
	CLDI_CATCH
		cldiAddTraceback(cldiInitTableCols, CLDIERRMSG_TABLE_FAIL_CREATE_TABLE_UNEXP);

	void *data = cldiMemrefGetAddress(self);
	CLDI_CATCH {
		cldiAddTraceback(cldiInitTableData, CLDIERRMSG_TABLE_FAIL_GET_ACCESS);
		return self;
	}

	clditypeinfo_t *coltypes = (clditypeinfo_t*) data;
	void           *colcurs  = &coltypes[colc];
	const char    **colnames = (const char**) colcurs;
	colcurs = &colnames[colc];

	va_list va;
	va_start(va, colc);

	clditypeinfo_t t;
	for (size_t i = 0; i < colc; i++) {
		t = types[i];
		if (t.templ == CLDI_STRUCT_TYPE)
		incompatible_type:
			cldithrowf(cldiInitTableData, CLDI_EINCOMPATIBLE_TYPE, CLDIERRMSG_TABLE_INCOMPATIBLE_TYPE);
			goto error_case;
		switch (t.size) {
		#if CLDI_LDBL_ENABLED == true
			case sizeof(long double):
				const long double *a = va_arg(va, const long double*);
				long double       *d = (long double*) colcurs;

				if (a != NULL)
					for (size_t j = 0; j < rowc; j++) {
						d[j] = a[j];
					}
				else
					for (size_t j = 0; j < rowc; j++)
						d[j] = 0;

				colcurs = &d[rowc];

				break;
		#endif
			case 1:
				const char *a = va_arg(va, const char*);
				char       *d = (char*) colcurs;
				
				if (a != NULL)
				for (size_t j = 0; j < rowc; j++) {
					d[j] = a[j];
				}
				else
				for (size_t j = 0; j < rowc; j++)
				d[j] = 0;
				
				colcurs = &d[rowc];
				
				break;

			case 2:
				const uint16_t *a = va_arg(va, const uint16_t*);
				uint16_t       *d = (uint16_t*) colcurs;

				if (a != NULL)
					for (size_t j = 0; j < rowc; j++) {
						d[j] = a[j];
					}
				else
					for (size_t j = 0; j < rowc; j++)
						d[j] = 0;

				colcurs = &d[rowc];

				break;
			case 4:
				switch (t.templ) {
				#if CLDI_PLATFORM32 == true
					case CLDI_PTR_TYPE:
						const void  **a = va_arg(va, const void**);
						void        **d = (void**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;

					case CLDI_CSTR_TYPE:
						const char  **a = va_arg(va, const char**);
						char        **d = (char**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;

					case CLDI_WSTR_TYPE:
						const wchar_t  **a = va_arg(va, const wchar_t**);
						wchar_t        **d = (wchar_t**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = NULL;

						colcurs = &d[rowc];

						break;
				#endif

					default: goto incompatible_type;

					case CLDI_INT_TYPE:
						const uint32_t *a = va_arg(va, const uint32_t*);
						uint32_t       *d = (uint32_t*) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;

					case CLDI_FLOAT_TYPE:
						const float *a = va_arg(va, const float*);
						float       *d = (float*) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;
				}
				break;

			case 8:
				switch (t.templ) {
				#if CLDI_PLATFORM32 == false
					case CLDI_PTR_TYPE:
						const void  **a = va_arg(va, const void**);
						void        **d = (void**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;
					
					case CLDI_CSTR_TYPE:
						const char  **a = va_arg(va, const char**);
						char        **d = (char**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;

					case CLDI_WSTR_TYPE:
						const wchar_t  **a = va_arg(va, const wchar_t**);
						wchar_t        **d = (wchar_t**) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;
				#endif

					default: goto incompatible_type;

					case CLDI_INT_TYPE:
						const uint64_t *a = va_arg(va, const uint64_t*);
						uint64_t       *d = (uint64_t*) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;

					case CLDI_FLOAT_TYPE:
						const double *a = va_arg(va, const double*);
						double       *d = (double*) colcurs;

						if (a != NULL)
							for (size_t j = 0; j < rowc; j++) {
								d[j] = a[j];
							}
						else
							for (size_t j = 0; j < rowc; j++)
								d[j] = 0;

						colcurs = &d[rowc];

						break;
				}
				break;
		}
	}

error_case:
	va_end(va);

	return self;
}


