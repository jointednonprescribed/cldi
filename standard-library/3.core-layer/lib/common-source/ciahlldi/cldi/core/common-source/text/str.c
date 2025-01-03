
#ifndef _cldi_core_commonsrc__text_STR_C
#define _cldi_core_commonsrc__text_STR_C 1

/* Implementation For: cldi-core: text/str */
#include <ciahlldi/cldi/core/text/str.h>

/* Requires: cldi-core: sysfuncs/memory */
#include <ciahlldi/cldi/core/sysfuncs/memory.h>

/* Requires: cldi-portable: text/str */
#include <ciahlldi/cldi/portable/text/str.h>



CLDISTRHANDLE _cldiInitStrNull(cldistr* self)
{
	if (self != NULL) {
		self->modifiable_state_address = NULL;
		self->current_character_type   = CLDI_CHARTYPE_NONE;
		self->initialized_length       = 0;
	}
	return CLDISTRHANDLE_NULL;
}
CLDISTRHANDLE _cldiInitStrStateRaw(
	cldistr* self, CLDISTAT * err,
	CLDI_CHARTYPE     __typ,
	size_t        __len,
	const void *const __str,
	bool              __cp,
	size_t        __ext
){
	CLDISTAT errv;
	if (err == NULL)
		err = &errv;
	*err = CLDI_SUCCESS;

	size_t size = 0, len = 0;
	const char *char_mask = NULL;
	CLDISTAT e = CLDI_SUCCESS;

	if (__typ <= CLDI_CHARTYPE_NONE || __len == 0 || __str == NULL)
		/* ERR: NULL ARGUMENTS: EITHER STRING, LENGTH, OR TYPE. */
		*err = CLDI_NULL_ARG;
		/* Return null handle as a fallback. */
		goto _l_return_null;

	if (self->_valid == CLDISTR_VALID_ID && self->_init &&
			self->modifiable_state_address != NULL && self->initialized_length != 0) {
		e = cldiDropStr(self);
		if (e != CLDI_SUCCESS) {
			*err = e;
			/* Return null handle as a fallback. */
			goto _l_return_null;
		}
	}

	if (__cp) cldiGenerateStringCharacterMaskEx(&char_mask, &size, &len, __typ, __str);
	else      cldiStringSizeEx(&size, &len, __typ, __str);
	if (size == 0) {
		*err = CLDI_INADEQUATE_ATTRIBUTE;
		/* Return null handle as a fallback. */
		goto _l_return_null;
	}

	char * origin_addr;
	e = cldiRequestTextMemoryEx(&origin_addr, size);
	if (e != CLDI_SUCCESS) {
		*err = e;
		/* Return null handle as a fallback. */
		goto _l_return_null;
	}

	e = cldiCopyBytes(size, origin_addr, __str);
	if (e != CLDI_SUCCESS) {
		cldiDropMemory(origin_addr);
		*err = e;
		/* Return null handle as a fallback. */
		goto _l_return_null;
	} else
		cldiClaimMemory(origin_addr);

	if (__cp && self != NULL) {
		char * modifiable_addr;
		e = cldiRequestTextMemoryEx(&modifiable_addr, (__ext==0)? size: size + (__ext * cldiSizeofChartype(__typ)));
		if (e != CLDI_SUCCESS) {
			*err = e;
			/* Fallback to initializing self with null members (if self is not a nullptr). */
			goto _l_m_init_null;
		}

		e = cldiCopyBytes(size, modifiable_addr, __str);
		if (e != CLDI_SUCCESS) {
			cldiDropMemory(modifiable_addr);
			*err = e;
			/* Fallback to initializing self with null members (if self is not a nullptr). */
			goto _l_m_init_null;
		} else
			cldiClaimMemory(modifiable_addr);

		self->modifiable_state_address = modifiable_addr;
		self->initialized_length       = len;
		self->current_character_type   = __typ;
	} else if (self != NULL) {
		self->current_character_type   = CLDI_CHARTYPE_NONE;
		self->modifiable_state_address = NULL;
		self->initialized_length       = 0;
	}

_l_return_early:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oDEFAULT,
		.type=__typ,
		.address=origin_addr,
		.char_count=len
	};
_l_m_init_null:
	self->current_character_type   = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length       = 0;
	goto _l_return_early;
_l_return_null:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oNULLV_DEFAULT,
		.address=NULL,
		.char_count=0,
		.type=__typ
	};
}
CLDISTRHANDLE _cldiInitStrRelCopy(
	cldistr* self, CLDISTAT* err,
	const cldistr* __from,
	size_t     __ext
){
	CLDISTAT errv, e=CLDI_SUCCESS;
	if (err == NULL)
		err = &errv;
	*err = CLDI_SUCCESS;

	CLDI_CHARTYPE origin_type;
	cldihalf      origin_data;
	char         *origin_addr;
	size_t    origin_len;

	if (__from != NULL) {
		if (__from->origin._valid == CLDISTRHANDLE_VALID_ID && __from->origin._init == true) {
			origin_type = __from->origin.type;
			origin_addr = cldiBorrowMemory(__from->origin.address);
			origin_len  = __from->origin.char_count;
			origin_data = CLDISTRHANDLE_oDEFAULT;
		} else {
			origin_type = CLDI_CHARTYPE_NONE;
			origin_addr = NULL;
			origin_len  = 0;
			origin_data = CLDISTRHANDLE_oNULLV_DEFAULT;
		}
		if (self != NULL && __from->_valid == CLDISTR_VALID_ID && __from->_init == true) {
			if (self->_valid == CLDISTR_VALID_ID && self->modifiable_state_address != NULL)
				cldiDropStrData(self);
			size_t    m_len  = __from->initialized_length, m_size;
			CLDI_CHARTYPE m_type = (CLDI_CHARTYPE) __from->current_character_type;
			char         *f_addr = __from->modifiable_state_address, *m_addr=NULL;
			if (f_addr == NULL)
				self->modifiable_state_address = NULL;
			else {
				e = cldiStringSizeEx(&m_size, &m_len, m_type, f_addr);
				if (e != CLDI_SUCCESS) {
					/* If function fails to get full string size, report error and
					.  jump to _l_m_init_null. */
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiRequestTextMemoryEx(&m_addr, (__ext==0)? m_size: m_size + (__ext*cldiSizeofChartype(m_type)));
				/* If function fails to get full string size, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiCopyBytes(m_size, m_addr, f_addr);
				/* If function fails copy string data, drop memory, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					cldiDropMemory(m_addr);
					*err = e;
					goto _l_m_init_null;
				} else cldiClaimMemory(m_addr);

				self->modifiable_state_address = m_addr;
			}
			if (__from->_chmsk == NULL)
				self->_chmsk = NULL;
			else {
				/* Try to copy the character mask from the variable `__from`. */
				e = cldiNewMemBlockCopyEx(
					&(self->_chmsk),
					__from->_chmsk
				);
				/* If function fails to copy the character mask of __from to a new
				.  memory block, output that error, and jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
			}
			self->current_character_type = m_type;
			self->initialized_length = m_len;
		} else goto _l_m_init_null;
	}

/* A label for the return statement itself, so the default value can be returned early, without
.  being re-encoded elsewhere in the function. */
_l_return_early:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=origin_data,
		.type=origin_type,
		.address=origin_addr,
		.char_count=origin_len
	};
/* A label for parts of this function that fail to initialize the modifiable members of the,
.  class and want to set those to null while still returning using the _l_return_early label,
.  so that this code does not have to be re-encoded elsewhere in the function. */
_l_m_init_null:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
	goto _l_return_early;
/* A label for the same as above, failures to initialize the modifiable members of the class,
.  but this code will continue on to the _l_return_null area (as intended), and will return
.  null class data instead. This label exists so that the code within doesn't have to be
.  re-encoded elsewhere in the function. */
_l_m_init_null_fail:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
/* Label for when the method fails before obtaining origin state data, so it must return null
.  data instead, this label exists so that the code within doesn't have to be re-encoded
.  elsewhere in the function. */
_l_return_null:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oNULLV_DEFAULT,
		.type=CLDI_CHARTYPE_NONE,
		.address=NULL,
		.char_count=0
	};
}
CLDISTRHANDLE _cldiInitStrParent(
	cldistr* self, CLDISTAT* err,
	const cldistr* __from
){
	CLDISTAT errv, e=CLDI_SUCCESS;
	if (err == NULL)
		err = &errv;
	*err = CLDI_SUCCESS;

	CLDI_CHARTYPE origin_type;
	cldihalf      origin_data;
	char         *origin_addr;
	size_t    origin_len;

	if (__from != NULL) {
		if (__from->origin._valid == CLDISTRHANDLE_VALID_ID && __from->origin._init == true) {
			origin_type = __from->origin.type;
			origin_addr = cldiBorrowMemory(__from->origin.address);
			origin_len  = __from->origin.char_count;
			origin_data = CLDISTRHANDLE_oDEFAULT;
		} else {
			origin_type = CLDI_CHARTYPE_NONE;
			origin_addr = NULL;
			origin_len  = 0;
			origin_data = CLDISTRHANDLE_oNULLV_DEFAULT;
		}
		if (self != NULL && __from->_valid == CLDISTR_VALID_ID && __from->_init == true) {
			if (self->_valid == CLDISTR_VALID_ID && self->modifiable_state_address != NULL)
				cldiDropStrData(self);
			size_t    m_len  = __from->initialized_length, m_size;
			CLDI_CHARTYPE m_type = (CLDI_CHARTYPE) __from->current_character_type;
			char         *f_addr = __from->modifiable_state_address, *m_addr=NULL;
			if (f_addr == NULL)
				self->modifiable_state_address = NULL;
			else {
				e = cldiStringSizeEx(&m_size, &m_len, m_type, f_addr);
				if (e != CLDI_SUCCESS) {
					/* If function fails to get full string size, report error and
					.  jump to _l_m_init_null. */
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiRequestTextMemoryEx(&m_addr, (__ext==0)? m_size: m_size + (__ext*cldiSizeofChartype(m_type)));
				/* If function fails to get full string size, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiCopyBytes(m_size, m_addr, f_addr);
				/* If function fails copy string data, drop memory, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					cldiDropMemory(m_addr);
					*err = e;
					goto _l_m_init_null;
				} else cldiClaimMemory(m_addr);

				self->modifiable_state_address = m_addr;
			}
			if (__from->_chmsk == NULL)
				self->_chmsk = NULL;
			else {
				/* Try to copy the character mask from the variable `__from`. */
				e = cldiNewMemBlockCopyEx(
					&(self->_chmsk),
					__from->_chmsk
				);
				/* If function fails to copy the character mask of __from to a new
				.  memory block, output that error, and jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
			}
			self->current_character_type = m_type;
			self->initialized_length = m_len;
		} else goto _l_m_init_null;
	}

/* A label for the return statement itself, so the default value can be returned early, without
.  being re-encoded elsewhere in the function. */
_l_return_early:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=origin_data,
		.type=origin_type,
		.address=origin_addr,
		.char_count=origin_len
	};
/* A label for parts of this function that fail to initialize the modifiable members of the,
.  class and want to set those to null while still returning using the _l_return_early label,
.  so that this code does not have to be re-encoded elsewhere in the function. */
_l_m_init_null:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
	goto _l_return_early;
/* A label for the same as above, failures to initialize the modifiable members of the class,
.  but this code will continue on to the _l_return_null area (as intended), and will return
.  null class data instead. This label exists so that the code within doesn't have to be
.  re-encoded elsewhere in the function. */
_l_m_init_null_fail:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
/* Label for when the method fails before obtaining origin state data, so it must return null
.  data instead, this label exists so that the code within doesn't have to be re-encoded
.  elsewhere in the function. */
_l_return_null:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oNULLV_DEFAULT,
		.type=CLDI_CHARTYPE_NONE,
		.address=NULL,
		.char_count=0
	};
}
CLDISTRHANDLE _cldiInitStrChild(
	cldistr* self, CLDISTAT* err,
	const cldistr* __from,
	bool           __cp,
	size_t     __ext
){
	CLDISTAT errv, e=CLDI_SUCCESS;
	if (err == NULL)
		err = &errv;
	*err = CLDI_SUCCESS;

	CLDI_CHARTYPE origin_type;
	cldihalf      origin_data;
	char         *origin_addr;
	size_t    origin_len;

	if (__from != NULL) {
		if (__from->origin._valid == CLDISTRHANDLE_VALID_ID && __from->origin._init == true) {
			origin_type = __from->origin.type;
			origin_addr = cldiBorrowMemory(__from->origin.address);
			origin_len  = __from->origin.char_count;
			origin_data = CLDISTRHANDLE_oDEFAULT;
		} else {
			origin_type = CLDI_CHARTYPE_NONE;
			origin_addr = NULL;
			origin_len  = 0;
			origin_data = CLDISTRHANDLE_oNULLV_DEFAULT;
		}
		if (self != NULL && __from->_valid == CLDISTR_VALID_ID && __from->_init == true) {
			if (self->_valid == CLDISTR_VALID_ID && self->modifiable_state_address != NULL)
				cldiDropStrData(self);
			size_t    m_len  = __from->initialized_length, m_size;
			CLDI_CHARTYPE m_type = (CLDI_CHARTYPE) __from->current_character_type;
			char         *f_addr = __from->modifiable_state_address, *m_addr=NULL;
			if (f_addr == NULL)
				self->modifiable_state_address = NULL;
			else {
				e = cldiStringSizeEx(&m_size, &m_len, m_type, f_addr);
				if (e != CLDI_SUCCESS) {
					/* If function fails to get full string size, report error and
					.  jump to _l_m_init_null. */
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiRequestTextMemoryEx(&m_addr, (__ext==0)? m_size: m_size + (__ext*cldiSizeofChartype(m_type)));
				/* If function fails to get full string size, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiCopyBytes(m_size, m_addr, f_addr);
				/* If function fails copy string data, drop memory, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					cldiDropMemory(m_addr);
					*err = e;
					goto _l_m_init_null;
				} else cldiClaimMemory(m_addr);

				self->modifiable_state_address = m_addr;
			}
			if (__from->_chmsk == NULL)
				self->_chmsk = NULL;
			else {
				/* Try to copy the character mask from the variable `__from`. */
				e = cldiNewMemBlockCopyEx(
					&(self->_chmsk),
					__from->_chmsk
				);
				/* If function fails to copy the character mask of __from to a new
				.  memory block, output that error, and jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
			}
			self->current_character_type = m_type;
			self->initialized_length = m_len;
		} else goto _l_m_init_null;
	}

/* A label for the return statement itself, so the default value can be returned early, without
.  being re-encoded elsewhere in the function. */
_l_return_early:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=origin_data,
		.type=origin_type,
		.address=origin_addr,
		.char_count=origin_len
	};
/* A label for parts of this function that fail to initialize the modifiable members of the,
.  class and want to set those to null while still returning using the _l_return_early label,
.  so that this code does not have to be re-encoded elsewhere in the function. */
_l_m_init_null:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
	goto _l_return_early;
/* A label for the same as above, failures to initialize the modifiable members of the class,
.  but this code will continue on to the _l_return_null area (as intended), and will return
.  null class data instead. This label exists so that the code within doesn't have to be
.  re-encoded elsewhere in the function. */
_l_m_init_null_fail:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
/* Label for when the method fails before obtaining origin state data, so it must return null
.  data instead, this label exists so that the code within doesn't have to be re-encoded
.  elsewhere in the function. */
_l_return_null:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oNULLV_DEFAULT,
		.type=CLDI_CHARTYPE_NONE,
		.address=NULL,
		.char_count=0
	};
}
CLDISTRHANDLE _cldiInitStrSibling(
	cldistr* self, CLDISTAT* err,
	const cldistr* __from,
	bool           __cp,
	size_t     __ext
){
	CLDISTAT errv, e=CLDI_SUCCESS;
	if (err == NULL)
		err = &errv;
	*err = CLDI_SUCCESS;

	CLDI_CHARTYPE origin_type;
	cldihalf      origin_data;
	char         *origin_addr;
	size_t    origin_len;

	if (__from != NULL) {
		if (__from->origin._valid == CLDISTRHANDLE_VALID_ID && __from->origin._init == true) {
			origin_type = __from->origin.type;
			origin_addr = cldiBorrowMemory(__from->origin.address);
			origin_len  = __from->origin.char_count;
			origin_data = CLDISTRHANDLE_oDEFAULT;
		} else {
			origin_type = CLDI_CHARTYPE_NONE;
			origin_addr = NULL;
			origin_len  = 0;
			origin_data = CLDISTRHANDLE_oNULLV_DEFAULT;
		}
		if (self != NULL && __from->_valid == CLDISTR_VALID_ID && __from->_init == true) {
			if (self->_valid == CLDISTR_VALID_ID && self->modifiable_state_address != NULL)
				cldiDropStrData(self);
			size_t    m_len  = __from->initialized_length, m_size;
			CLDI_CHARTYPE m_type = (CLDI_CHARTYPE) __from->current_character_type;
			char         *f_addr = __from->modifiable_state_address, *m_addr=NULL;
			if (f_addr == NULL)
				self->modifiable_state_address = NULL;
			else {
				e = cldiStringSizeEx(&m_size, &m_len, m_type, f_addr);
				if (e != CLDI_SUCCESS) {
					/* If function fails to get full string size, report error and
					.  jump to _l_m_init_null. */
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiRequestTextMemoryEx(&m_addr, (__ext==0)? m_size: m_size + (__ext*cldiSizeofChartype(m_type)));
				/* If function fails to get full string size, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
				e = cldiCopyBytes(m_size, m_addr, f_addr);
				/* If function fails copy string data, drop memory, report error and
				.  jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					cldiDropMemory(m_addr);
					*err = e;
					goto _l_m_init_null;
				} else cldiClaimMemory(m_addr);

				self->modifiable_state_address = m_addr;
			}
			if (__from->_chmsk == NULL)
				self->_chmsk = NULL;
			else {
				/* Try to copy the character mask from the variable `__from`. */
				e = cldiNewMemBlockCopyEx(
					&(self->_chmsk),
					__from->_chmsk
				);
				/* If function fails to copy the character mask of __from to a new
				.  memory block, output that error, and jump to _l_m_init_null. */
				if (e != CLDI_SUCCESS) {
					*err = e;
					goto _l_m_init_null;
				}
			}
			self->current_character_type = m_type;
			self->initialized_length = m_len;
		} else goto _l_m_init_null;
	}

/* A label for the return statement itself, so the default value can be returned early, without
.  being re-encoded elsewhere in the function. */
_l_return_early:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=origin_data,
		.type=origin_type,
		.address=origin_addr,
		.char_count=origin_len
	};
/* A label for parts of this function that fail to initialize the modifiable members of the,
.  class and want to set those to null while still returning using the _l_return_early label,
.  so that this code does not have to be re-encoded elsewhere in the function. */
_l_m_init_null:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
	goto _l_return_early;
/* A label for the same as above, failures to initialize the modifiable members of the class,
.  but this code will continue on to the _l_return_null area (as intended), and will return
.  null class data instead. This label exists so that the code within doesn't have to be
.  re-encoded elsewhere in the function. */
_l_m_init_null_fail:
	self->current_character_type = CLDI_CHARTYPE_NONE;
	self->modifiable_state_address = NULL;
	self->initialized_length = 0;
/* Label for when the method fails before obtaining origin state data, so it must return null
.  data instead, this label exists so that the code within doesn't have to be re-encoded
.  elsewhere in the function. */
_l_return_null:
	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._init=true,
		._data=CLDISTRHANDLE_oNULLV_DEFAULT,
		.type=CLDI_CHARTYPE_NONE,
		.address=NULL,
		.char_count=0
	};
}



#endif /* _cldi_core_commonsrc__text_STR_C */
