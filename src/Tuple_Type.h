// vi:nu:et:sts=4 ts=4 sw=4


	/*
	 * *** 16-bit Tuple Types ***
	 * *** 32-bit Tuple Types ***
	 * *** End of System Defined Types ***
	 */

	/* The following enum was generated from:
	 * "Tuple_Types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	typedef enum Tuple_Type_e {
		TUPLE_TYPE_UNKNOWN=0,
		TUPLE_TYPE_DOUBLE_16=1,
		TUPLE_TYPE_FALSE_16=2,
		TUPLE_TYPE_INT8_16=3,
		TUPLE_TYPE_INT16_16=4,
		TUPLE_TYPE_INT32_16=5,
		TUPLE_TYPE_INT64_16=6,
		TUPLE_TYPE_NULL_16=7,
		TUPLE_TYPE_OBJECT_16=8,                            // Object Reference
		TUPLE_TYPE_OPCODE_16=9,                            // Opcode Reference
		TUPLE_TYPE_PTR_16=10,                              // Pointer Reference
		TUPLE_TYPE_SYMBOL_16=11,                           // Symbol Reference
		TUPLE_TYPE_TRUE_16=12,
		TUPLE_TYPE_UTF8_16=13,                             // UTF-8 String
		TUPLE_TYPE_UTF32_16=14,                            // UTF-32 String (ie WCHAR_T)
		TUPLE_TYPE_DOUBLE_32=15,
		TUPLE_TYPE_FALSE_32=16,
		TUPLE_TYPE_INT8_32=17,
		TUPLE_TYPE_INT16_32=18,
		TUPLE_TYPE_INT32_32=19,
		TUPLE_TYPE_INT64_32=20,
		TUPLE_TYPE_NULL_32=21,
		TUPLE_TYPE_OBJECT_32=22,                           // Object Reference
		TUPLE_TYPE_OPCODE_32=23,                           // Opcode Reference
		TUPLE_TYPE_PTR_32=24,                              // Pointer Reference
		TUPLE_TYPE_SYMBOL_32=25,                           // Symbol Reference
		TUPLE_TYPE_TRUE_32=26,
		TUPLE_TYPE_UTF8_32=27,                             // UTF-8 String
		TUPLE_TYPE_UTF32_32=28,                            // UTF-32 String (ie WCHAR_T)
		TUPLE_TYPE_HIGHEST=29,
	} TUPLE_TYPES;




