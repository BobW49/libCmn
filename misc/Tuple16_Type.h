// vi:nu:et:sts=4 ts=4 sw=4


	/*
	 * *** 16-bit Tuple Types ***
	 * *** End of Defined Types ***
	 */

	/* The following enum was generated from:
	 * "Tuple16_Types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	typedef enum Tuple16_Type_e {
		TUPLE16_TYPE_UNKNOWN=0,
		TUPLE16_TYPE_BASE=1,
		TUPLE16_TYPE_DOUBLE=2,
		TUPLE16_TYPE_FALSE=3,
		TUPLE16_TYPE_INT8=4,
		TUPLE16_TYPE_INT16=5,
		TUPLE16_TYPE_INT32=6,
		TUPLE16_TYPE_INT64=7,
		TUPLE16_TYPE_NULL=8,
		TUPLE16_TYPE_OBJECT=9,                             // Object Reference
		TUPLE16_TYPE_OPCODE=10,                            // Opcode Reference
		TUPLE16_TYPE_PTR=11,                               // Pointer Reference
		TUPLE16_TYPE_SYMBOL=12,                            // Symbol Reference
		TUPLE16_TYPE_TOKEN=13,
		TUPLE16_TYPE_TRUE=14,
		TUPLE16_TYPE_UTF8=15,                              // UTF-8 String
		TUPLE16_TYPE_UTF32=16,                             // UTF-32 String (ie WCHAR_T)
		TUPLE16_TYPE_HIGHEST=17,
	} TUPLE16_TYPES;




