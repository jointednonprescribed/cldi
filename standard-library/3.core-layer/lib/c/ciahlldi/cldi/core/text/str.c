
/* Implementation For: cldi-core: text/str */
#include <ciahlldi/cldi/core/text/str.h>

/* Common Source Code: */
#include <ciahlldi/cldi/core/common-source/text/str.c>

/* Requires: cldi-portable: text/str */
#include <ciahlldi/cldi/portable/text/str.h>

/* Requires: cldi-core: sysfuncs/memory */
#include <ciahlldi/cldi/core/sysfuncs/memory.h>



const cldistr CLDISTR_NULL = {
	._valid = CLDISTR_VALID_ID,
	._init  = true,
	._data  = CLDISTR_oNULLABLE_MASK,
	._chmsk = NULL,
	.origin = {
		._valid     = CLDISTR_VALID_ID,
		._data      = CLDISTRHANDLE_oNULLABLE_MASK,
		.type       = CLDI_CHARTYPE_NONE,
		.address    = NULL,
		.char_count = 0
	},
	.current_character_type   = CLDI_CHARTYPE_NONE,
	.modifiable_state_address = NULL,
	.initialized_length       = 0
};


CLDISTAT _cldiCopyStrObject(cldistr *_cldi_restrict_ destination, const cldistr *_cldi_restrict_ source)
{
	void *dissolve;

	dissolve = &(destination->origin._valid);
	*(u32_t*)dissolve = source->origin._valid;

	destination->origin._init = source->origin._init;

	dissolve = &(destination->origin.type);
	*(i8_t*)dissolve = source->origin.type;

	dissolve = &(destination->origin._data);
	*(cldihalf*)dissolve = source->origin._data;

	dissolve = &(destination->origin.address);
	*(const char**)dissolve = source->origin.address;

	dissolve = &(destination->origin.char_count);
	*(size_t*)dissolve = source->origin.char_count;

	dissolve = &(destination->_valid);
	*(u32_t*)dissolve = source->_valid;

	destination->_data  = source->_data;
	destination->_init  = source->_init;
	destination->_chmsk = source->_chmsk;
	destination->current_character_type   = source->current_character_type;
	destination->modifiable_state_address = source->modifiable_state_address;
	destination->initialized_length       = source->initialized_length;

	return CLDI_SUCCESS;
}


CLDISTAT cldiDropStr(cldistr * __drop)
{
	if (__drop == NULL || __drop->_valid != CLDISTR_VALID_ID)
		return CLDI_NULL_ARG;

	CLDISTAT status;

	if (__drop->_chmsk != NULL) {
		status = cldiDropMemory(__drop->_chmsk);
		if (status != CLDI_SUCCESS)
			return status;
		else
			__drop->_chmsk = NULL;
	}

	if (__drop->modifiable_state_address != NULL) {
		status = cldiDropMemory(__drop->modifiable_state_address);
		if (status != CLDI_SUCCESS)
			return status;
		else
			__drop->modifiable_state_address = NULL;
	}

	if (!cldiStrHandleIsNull( &(__drop->origin) )) {
		status = cldiDropStrHandle( &(__drop->origin) );
		if (status != CLDI_SUCCESS)
			return status;
		else
			__drop->origin._init = false;
	}

	__drop->_init = false;
	__drop->_data &= CLDISTR_oNULLABLE_MASK;
	__drop->current_character_type = CLDI_CHARTYPE_NONE;
	__drop->initialized_length = 0;

	return CLDI_SUCCESS;
}
/* ONLY USE THIS ON OBJECT ALLOCATED USING THE 'cldiNewStrXXXX()' OR 'cldistr::New()',
.  METHODS NOT ON INSTANCES ON THE STACK, OR INSTANCES THAT WERE ALLOCATED USING THE 'new'
.  OPERATOR! */
CLDISTAT cldiDropStrObject(cldistr * __drop)
{
	if (__drop == NULL || __drop->_valid != CLDISTR_VALID_ID)
		return CLDI_NULL_ARG;

	CLDISTAT status;

	status = cldiDropStr(__drop);
	if (status != CLDI_SUCCESS)
		return status;

	if (__drop->_data & CLDISTR_oHEAP_ALLOCATED == CLDISTR_oHEAP_ALLOCATED) {
		status = cldiDropMemory(__drop);
		if (status != CLDI_SUCCESS)
			return status;
	}

	return CLDI_SUCCESS;
}

CLDISTAT cldiInitStr(cldistr * self)
{
	return cldiCopyBytes(sizeof(cldistr), self, &CLDISTR_NULL);
}
cldistr* cldiNewStr(void)
{
	CLDISTAT err = CLDI_SUCCESS;
	cldistr *allocate = NULL;

	err = cldiRequestMemoryEx(&allocate, sizeof(cldistr));
	if (err != CLDI_SUCCESS)
		return NULL;

	err = cldiCopyBytes(sizeof(cldistr), allocate, &CLDISTR_NULL);
	if (err != CLDI_SUCCESS) {
		cldiDropMemory(allocate);
		return NULL;
	} else {
		cldiClaimMemory(allocate);
		allocate->_data &= CLDISTR_oHEAP_ALLOCATED;
		return allocate;
	}
}
CLDISTAT cldiNewStrEx(cldistr** __out)
{
	CLDISTAT err = CLDI_SUCCESS;
	cldistr *allocate = NULL;

	err = cldiRequestMemoryEx(&allocate, sizeof(cldistr));
	if (err != CLDI_SUCCESS)
		return err;

	err = cldiCopyBytes(sizeof(cldistr), allocate, &CLDISTR_NULL);
	if (err != CLDI_SUCCESS) {
		cldiDropMemory(allocate);
		return err;
	} else {
		cldiClaimMemory(allocate);
		allocate->_data &= CLDISTR_oHEAP_ALLOCATED;
		*__out = allocate;
	}

	return CLDI_SUCCESS;
}

CLDISTAT cldiInitStrNewState(cldistr* self, CLDICHARTYPE __typ, size_t __len, const void *const __str)
{
	if (self == NULL)
		return CLDI_NULL_ARG;
	else if (__typ <= CLDI_CHARTYPE_NONE || __len == 0 || __str == NULL)
		return cldiInitStr(self);

	CLDISTAT e = CLDI_SUCCESS;

	if (self->_valid == CLDISTR_VALID_ID && self->_init &&
			self->modifiable_state_address != NULL && self->initialized_length != 0) {
		e = cldiDropStr(self);
		if (e != CLDI_SUCCESS)
			return e;
	}

	size_t size = 0, len = 0;
	cldiStringSizeEx(&size, &len, __typ, __str);
	if (len == 0)
		return CLDI_NULL_ARG;

	char * origin_addr;
	e = cldiRequestTextMemoryEx(&origin_addr, size);
	if (e != CLDI_SUCCESS)
		return e;

	e = cldiCopyBytes(size, origin_addr, __str);
	if (e != CLDI_SUCCESS) {
		cldiDropMemory(origin_addr);
		return e;
	} else
		cldiClaimMemory(origin_addr);

	void *dissolve = &(self->origin._valid);
	*(u32_t*)dissolve = CLDISTRHANDLE_VALID_ID;

	dissolve = &(self->origin.type);
	*(i8_t*)dissolve = __typ;

	dissolve = &(self->origin._data);
	*(cldihalf*)dissolve = CLDISTRHANDLE_oDEFAULT;

	dissolve = &(self->origin.address);
	*(const char**)dissolve = origin_addr;

	dissolve = &(self->origin.char_count);
	*(size_t*)dissolve = len;

	dissolve = &(self->_valid);
	*(u32_t*)dissolve = CLDISTR_VALID_ID;

	self->origin._init = true;
	self->_init        = true;
	self->_data        = CLDISTR_oNULLABLE_MASK;
	self->_chmsk       = NULL;
	self->current_character_type   = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length       = 0;

	return CLDI_SUCCESS;
}
CLDISTAT cldiInitStrExtendedState(cldistr* self, CLDICHARTYPE __typ, size_t __len, const void *const __str, size_t __ext)
{
	if (self == NULL)
		return CLDI_NULL_ARG;
	else if (__typ <= CLDI_CHARTYPE_NONE || __len == 0 || __str == NULL)
		return cldiInitStr(self);

	CLDISTAT e = CLDI_SUCCESS;

	if (self->_valid == CLDISTR_VALID_ID && self->_init &&
			self->modifiable_state_address != NULL && self->initialized_length != 0) {
		e = cldiDropStr(self);
		if (e != CLDI_SUCCESS)
			return e;
	}

	size_t size = 0, len = 0;
	const char *char_mask = NULL;
	cldiGenerateStrCharacterMaskEx(&char_mask, &size, &len, __typ, __str);
	if (len == 0)
		return CLDI_NULL_ARG;

	char * origin_addr;
	e = cldiRequestTextMemoryEx(&origin_addr, size);
	if (e != CLDI_SUCCESS)
		return e;

	e = cldiCopyBytes(size, origin_addr, __str);
	if (e != CLDI_SUCCESS) {
		cldiDropMemory(origin_addr);
		return e;
	} else
		cldiClaimMemory(origin_addr);

	char * modifiable_addr;
	size_t char_size = cldiSizeofChartype(__typ);
	e = cldiRequestTextMemoryEx(&modifiable_addr, size + (__ext * char_size));
	if (e != CLDI_SUCCESS)
		return e;

	e = cldiCopyBytes(size, modifiable_addr, __str);
	if (e != CLDI_SUCCESS) {
		cldiDropMemory(modifiable_addr);
		return e;
	} else
		cldiClaimMemory(modifiable_addr);

	void *dissolve = &(self->origin._valid);
	*(u32_t*)dissolve = CLDISTRHANDLE_VALID_ID;

	dissolve = &(self->origin.type);
	*(i8_t*)dissolve = __typ;

	dissolve = &(self->origin._data);
	*(cldihalf*)dissolve = CLDISTRHANDLE_oDEFAULT;

	dissolve = &(self->origin.address);
	*(const char**)dissolve = origin_addr;

	dissolve = &(self->origin.char_count);
	*(size_t*)dissolve = len;

	dissolve = &(self->_valid);
	*(u32_t*)dissolve = CLDISTR_VALID_ID;

	self->origin._init = true;
	self->_init        = true;
	self->_data        = CLDISTR_oDEFAULT;
	self->_chmsk       = char_mask;
	self->current_character_type   = __typ;
	self->modifiable_state_address = modifiable_addr;
	self->initialized_length       = len;

	return CLDI_SUCCESS;
}
CLDISTAT cldiInitStrNewCopy(cldistr* self, CLDICHARTYPE __typ, size_t __len, const void *const __str)
{
	return cldiInitStrExtendedState(self, __typ, __len, __str, 0);
}


