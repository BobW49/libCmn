// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "Tuple16_Types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Tuple16_Type_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Tuple16_Type_index[18] = {
		16, 1, 2, 3, 8, 5, 6, 7, 
		9, 10, 11, 12, 13, 14, 15, 18, 
		17, 4, 
	};

	static
	const
	uint32_t	cTuple16_Type_index = 18;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Tuple16_Type_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Tuple16_Type_entry	Tuple16_Type_entries[] = {
		{"TUPLE16_TYPE_BASE", "", "BASE", 1},
		{"TUPLE16_TYPE_DOUBLE", "", "DOUBLE", 2},
		{"TUPLE16_TYPE_FALSE", "", "FALSE", 3},
		{"TUPLE16_TYPE_HIGHEST", "", "HIGHEST", 17},
		{"TUPLE16_TYPE_INT16", "", "INT16", 5},
		{"TUPLE16_TYPE_INT32", "", "INT32", 6},
		{"TUPLE16_TYPE_INT64", "", "INT64", 7},
		{"TUPLE16_TYPE_INT8", "", "INT8", 4},
		{"TUPLE16_TYPE_NULL", "", "NULL", 8},
		{"TUPLE16_TYPE_OBJECT", "Object Reference", "OBJECT", 9},
		{"TUPLE16_TYPE_OPCODE", "Opcode Reference", "OPCODE", 10},
		{"TUPLE16_TYPE_PTR", "Pointer Reference", "PTR", 11},
		{"TUPLE16_TYPE_SYMBOL", "Symbol Reference", "SYMBOL", 12},
		{"TUPLE16_TYPE_TOKEN", "", "TOKEN", 13},
		{"TUPLE16_TYPE_TRUE", "", "TRUE", 14},
		{"TUPLE16_TYPE_UNKNOWN", "", "UNKNOWN", 0},
		{"TUPLE16_TYPE_UTF32", "UTF-32 String (ie WCHAR_T)", "UTF32", 16},
		{"TUPLE16_TYPE_UTF8", "UTF-8 String", "UTF8", 15},
	};

	static
	const
	uint32_t	cTuple16_Type_offset = 0;
	static
	const
	uint32_t	cTuple16_Type_entries = 18;









