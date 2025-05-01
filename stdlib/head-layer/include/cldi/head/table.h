
#pragma cldic module head:table
#ifndef _cldi_head__TABLE_H
#define _cldi_head__TABLE_H 1

#include "iter.h"
#pragma cldic require head:iter

#ifdef __cplusplus
extern "C" {
#endif



/* Table type */
typedef struct _CLDITABLE
{
	cldimemref data;
	size_t rows, cols, cursr, cursc;
} clditable_t;

/* Table Cursor type */
typedef void *clditablecurs_t;
/* Const Table Cursor type */
typedef const void *clditableccurs_t;

/* Methods associated with tables: */

#define CLDI_DEFAULT_TABLE_SIZE 10

/* Construct as blank (null) instance. */
clditable_t* cldiInitTable(clditable_t *self) CLDINOEXCEPT;
/* Construct as a copy of another. */
clditable_t* cldiInitTableCopy(clditable_t *self, const clditable_t *copy_of);
/* Construct by borrowing another. */
clditable_t* cldiInitTableBorrowed(clditable_t *self, const clditable_t *borrow);
/* Construct with just column information, with `CLDI_DEFAULT_TABLE_SIZE` rows
.  by default.  */
// Any of these initialization/allocation methods can take in NULL for the argument
// `colnames`, but if a non-null value is supplied, then it must contains only
// non-null string references.
clditable_t* cldiInitTableCols(
	clditable_t         *self,
	size_t               colcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames
);
/* Construct with column information, and a certain amount of empty rows. */
clditable_t* cldiInitTableNCols(
	clditable_t         *self,
	size_t               colcount,
	size_t               rowcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames
);
/* Construct with column information, and a certain number of rows, initialized
.  from variadic array arguments each containing all values in each column. */
clditable_t* cldiInitTableData(
	clditable_t         *self,
	size_t               colcount,
	size_t               rowcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames,
	...
	/* The only supported input for these variadic arguments in a series equal
	.  in length to `rowcount` of arrays, each exactly of the type generically
	.  inferrable from the type info object entered (structure types are not
	.  allowed as table values), and in the exact same order as the type info
	.  objects they align with in `coltypes`. */
);
/* Allocate a table object in the heap. */
cldimemref cldiNewTable();
cldimemref cldiNewTableCopy(const clditable_t *copy_of);
cldimemref cldiNewTableBorrowed(const clditable_t *borrow);
cldimemref cldiNewTableCols(
	size_t               colcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames
);
cldimemref cldiNewTableNCols(
	size_t               colcount,
	size_t               rowcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames
);
cldimemref cldiNewTableData(
	size_t               colcount,
	size_t               rowcount,
	const clditypeinfo_t coltypes[],
	const char         **colnames,
	...
	/* The only supported input for these variadic arguments in a series equal
	.  in length to `rowcount` of arrays, each exactly of the type generically
	.  inferrable from the type info object entered (structure types are not
	.  allowed as table values), and in the exact same order as the type info
	.  objects they align with in `coltypes`. */
);

/* Get the name of a column by index. */
const char* cldiTableGetColName(const clditable_t *self, ssize_t coln);
/* Get the index of a column by name. */
ssize_t cldiTableGetColNum(const clditable_t *self, const char *colname);

/* Get the type of a column by index. */
const clditypeinfo_t* cldiTableGetColType(const clditable_t *self, ssize_t coln);
/* Get the type of a column by name. */
const clditypeinfo_t* cldiTableGetColTypeS(const clditable_t *self, const char *colname);

/* Get the type of the column the cursor is currently inside of. */
const clditypeinfo_t* cldiTableGetCursorType(const clditable_t *self);
/* Get the index of the column the cursor is currently inside of. */
ssize_t               cldiTableGetCursorCol(const clditable_t *self);
/* Get the index of the row the cursor is currently inside of. */
ssize_t               cldiTableGetCursorRow(const clditable_t *self);
/* Get the current cursor position (expiring value). */
clditablecurs_t       cldiTableCursor(clditable_t *self);
clditableccurs_t      cldiTableConstCursor(const clditable_t *self);
/* Set the cursor to the origin (0, 0). */
clditableccurs_t      cldiTableSetCursToOrigin(clditable_t *self);
/* Set the cursor to the very end. */
clditableccurs_t      cldiTableSetCursToEnd(clditable_t *self);
/* Set the cursor to some point in the table. */
clditableccurs_t      cldiTableSetCurs(clditable_t *self, ssize_t row, ssize_t col);
clditableccurs_t      cldiTableSetCursS(clditable_t *self, ssize_t row, const char *col);

/* Increment the cursor by one cell. */
clditableccurs_t      cldiTableIncCell(clditable_t *self);
/* Decrement the cursor by one cell. */
clditableccurs_t      cldiTableDecCell(clditable_t *self);
/* Increment the cursor by n cells. */
clditableccurs_t      cldiTableIncCellN(clditable_t *self, ssize_t n);
/* Decrement the cursor by n cells. */
clditableccurs_t      cldiTableDecCellN(clditable_t *self, ssize_t n);

/* Increment the cursor by one column (cycle back to first column after the end). */
clditableccurs_t      cldiTableIncCol(clditable_t *self);
/* Decrement the cursor by one column (cycle back to last column after decrementing
.  from the first). */
clditableccurs_t      cldiTableDecCol(clditable_t *self);
/* Increment the cursor by n columns. */
clditableccurs_t      cldiTableIncColN(clditable_t *self, ssize_t n);
/* Decrement the cursor by n columns. */
clditableccurs_t      cldiTableDecColN(clditable_t *self, ssize_t n);

/* Increment the cursor by one row (cycle back to first row after the end). */
clditableccurs_t      cldiTableIncRow(clditable_t *self);
/* Decrement the cursor by one row (cycle back to last row after decrementing
.  from the first). */
clditableccurs_t      cldiTableDecRow(clditable_t *self);
/* Increment the cursor by n rows. */
clditableccurs_t      cldiTableIncRowN(clditable_t *self, ssize_t n);
/* Decrement the cursor by n rows. */
clditableccurs_t      cldiTableDecRowN(clditable_t *self, ssize_t n);

/* Create an empty table with column types, names (optional), and a total column
.  and row count. */
CLDISTAT  cldiTableCreate(
	clditable_t         *self,
	size_t               colc,
	size_t               rowc,
	const clditypeinfo_t types[],
	const char          *names[]
);



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__TABLE_H
