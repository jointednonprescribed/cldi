
/* Setup CLDI module "core".                  */
#include <ciahlldi/cldi/core/setup.h>

/* Implementing: cldi-core:     types/file-handle */
#include <ciahlldi/cldi/core/types/file-handle.h>

/* Requires:     cldi-adaptation: calls/filesystem  */
#include <ciahlldi/cldi/portable/calls/filesystem.h>
/* Requires:     cldi-adaptation: calls/memory      */
#include <ciahlldi/cldi/portable/calls/memory.h>

#ifdef __cplusplus
extern "C" {
#endif



const CldiFs_FILEPTR CldiFs_FILEPTR_NULL = {
	.file         = NULL,
	.filename     = NULL,
	.file_options = NULL,
	.clean_fn     = false,
	.clean_fo     = false
};


int CldiFs_fhOpen(CldiFs_FILEPTR * self, const char * __filename, int __fileopt)
{
	FILE
		* opened_file     = NULL;

	char
		* copied_fileinfo = NULL,
		* copied_filename = NULL;

	int
		error             = 0;

	bool
		binary_file       = false,
		update_mode       = false,
		create_new_mode   = false,
		public_mode       = false;

	size_t
		fileopt_start     = 0,
		fileinfo_size     = 0,

		fileopt_size      = 0,
		filename_size     = strlen(__filename) + 1;


	


	*self = {
		.file         = opened_file,
		.filename     = copied_filename,
		.file_options = copied_fileinfo,
		.clean_fn     = false,
		.clean_fo     = true
	};

	return error;
}

int CldiFs_fhClose(CldiFs_FILEPTR * file_handler)
{
	int close_file = fclose(file_handler->file);

	if (close_file == 0)
}



#ifdef __cplusplus
}
#endif
