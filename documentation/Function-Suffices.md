
# Function Suffices and Their Implied Meaning

## Extended ('Ex'):
	Extra arguments are taken and extra control is given. These functions are commonly the more "base" form and would sometimes be called directly by the other, more straight-forward functions.

## Error-Coded ('Ec'):
	An extra output argument is provided for exporting the return value to, the return
	value therefore becomes typed as `CLDISTAT` or some other error code supplier, and
	returns error status instead of its usual return value.

## Default Access ('D'):
	If any security-based or access-based control is given by the default version of the
	function through it's arguments, this variant would imply that argument is taken away
	in favor of providing a default security value.

## Wide Character ('Wc'):
	Uses wchar_t or string(s) thereof instead of char.

## UTF-16 Character ('W'):
	Uses char16_t or strings(s) thereof instead of char.

## UTF-32 Character ('Ww'):
	Uses char32_t or strings(s) thereof instead of char.

## Variable Encoding Characters ('Enc'):
	Uses long long to store the full value, and void*const to reference string(s) thereof,
	takes additional arguments for the length (size_t or ssize_t) of the encoded
	string, and the encoding type (CLDICHARTYPE) thereof.

