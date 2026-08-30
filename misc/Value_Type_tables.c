// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "value_types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Value_Type_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Value_Type_index[22] = {
		22, 1, 4, 5, 10, 7, 8, 9, 
		21, 18, 19, 20, 11, 12, 13, 14, 
		17, 15, 16, 2, 3, 6, 
	};

	static
	const
	uint32_t	cValue_Type_index = 22;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Value_Type_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Value_Type_entry	Value_Type_entries[] = {
		{"VALUE_TYPE_ASTR", "", "ASTR", 1},
		{"VALUE_TYPE_DATA", "", "DATA", 19},
		{"VALUE_TYPE_DATA_FREE", "", "DATA_FREE", 20},
		{"VALUE_TYPE_DOUBLE", "", "DOUBLE", 2},
		{"VALUE_TYPE_FALSE", "", "FALSE", 3},
		{"VALUE_TYPE_HIGHEST", "", "HIGHEST", 21},
		{"VALUE_TYPE_INT16", "", "INT16", 5},
		{"VALUE_TYPE_INT32", "", "INT32", 6},
		{"VALUE_TYPE_INT64", "", "INT64", 7},
		{"VALUE_TYPE_INT8", "", "INT8", 4},
		{"VALUE_TYPE_MONEY64", "", "MONEY64", 12},
		{"VALUE_TYPE_NODE", "", "NODE", 13},
		{"VALUE_TYPE_NULL", "", "NULL", 14},
		{"VALUE_TYPE_OBJECT", "", "OBJECT", 15},
		{"VALUE_TYPE_STR", "UTF-8 String", "STR", 17},
		{"VALUE_TYPE_SYM", "", "SYM", 18},
		{"VALUE_TYPE_TRUE", "", "TRUE", 16},
		{"VALUE_TYPE_UINT16", "", "UINT16", 9},
		{"VALUE_TYPE_UINT32", "", "UINT32", 10},
		{"VALUE_TYPE_UINT64", "", "UINT64", 11},
		{"VALUE_TYPE_UINT8", "", "UINT8", 8},
		{"VALUE_TYPE_UNKNOWN", "", "UNKNOWN", 0},
	};

	static
	const
	uint32_t	cValue_Type_offset = 0;
	static
	const
	uint32_t	cValue_Type_entries = 22;









