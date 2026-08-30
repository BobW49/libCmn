// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "Tuple_Types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Tuple_Type_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Tuple_Type_index[30] = {
		26, 1, 3, 12, 6, 8, 10, 14, 
		16, 18, 20, 22, 24, 29, 27, 2, 
		4, 13, 7, 9, 11, 15, 17, 19, 
		21, 23, 25, 30, 28, 5, 
	};

	static
	const
	uint32_t	cTuple_Type_index = 30;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Tuple_Type_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Tuple_Type_entry	Tuple_Type_entries[] = {
		{"TUPLE_TYPE_DOUBLE_16", "", "DOUBLE_16", 1},
		{"TUPLE_TYPE_DOUBLE_32", "", "DOUBLE_32", 15},
		{"TUPLE_TYPE_FALSE_16", "", "FALSE_16", 2},
		{"TUPLE_TYPE_FALSE_32", "", "FALSE_32", 16},
		{"TUPLE_TYPE_HIGHEST", "", "HIGHEST", 29},
		{"TUPLE_TYPE_INT16_16", "", "INT16_16", 4},
		{"TUPLE_TYPE_INT16_32", "", "INT16_32", 18},
		{"TUPLE_TYPE_INT32_16", "", "INT32_16", 5},
		{"TUPLE_TYPE_INT32_32", "", "INT32_32", 19},
		{"TUPLE_TYPE_INT64_16", "", "INT64_16", 6},
		{"TUPLE_TYPE_INT64_32", "", "INT64_32", 20},
		{"TUPLE_TYPE_INT8_16", "", "INT8_16", 3},
		{"TUPLE_TYPE_INT8_32", "", "INT8_32", 17},
		{"TUPLE_TYPE_NULL_16", "", "NULL_16", 7},
		{"TUPLE_TYPE_NULL_32", "", "NULL_32", 21},
		{"TUPLE_TYPE_OBJECT_16", "Object Reference", "OBJECT_16", 8},
		{"TUPLE_TYPE_OBJECT_32", "Object Reference", "OBJECT_32", 22},
		{"TUPLE_TYPE_OPCODE_16", "Opcode Reference", "OPCODE_16", 9},
		{"TUPLE_TYPE_OPCODE_32", "Opcode Reference", "OPCODE_32", 23},
		{"TUPLE_TYPE_PTR_16", "Pointer Reference", "PTR_16", 10},
		{"TUPLE_TYPE_PTR_32", "Pointer Reference", "PTR_32", 24},
		{"TUPLE_TYPE_SYMBOL_16", "Symbol Reference", "SYMBOL_16", 11},
		{"TUPLE_TYPE_SYMBOL_32", "Symbol Reference", "SYMBOL_32", 25},
		{"TUPLE_TYPE_TRUE_16", "", "TRUE_16", 12},
		{"TUPLE_TYPE_TRUE_32", "", "TRUE_32", 26},
		{"TUPLE_TYPE_UNKNOWN", "", "UNKNOWN", 0},
		{"TUPLE_TYPE_UTF32_16", "UTF-32 String (ie WCHAR_T)", "UTF32_16", 14},
		{"TUPLE_TYPE_UTF32_32", "UTF-32 String (ie WCHAR_T)", "UTF32_32", 28},
		{"TUPLE_TYPE_UTF8_16", "UTF-8 String", "UTF8_16", 13},
		{"TUPLE_TYPE_UTF8_32", "UTF-8 String", "UTF8_32", 27},
	};

	static
	const
	uint32_t	cTuple_Type_offset = 0;
	static
	const
	uint32_t	cTuple_Type_entries = 30;









