// vi:nu:et:sts=4 ts=4 sw=4


	/* The following enum was generated from:
	 * "sym_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	typedef enum Sym_Class_e {
		SYM_CLASS_UNKNOWN=0,
		SYM_CLASS_CON_ADDR=1,                              // Address Constant
		SYM_CLASS_CON_INT=2,                               // Integer Constant
		SYM_CLASS_CON_REAL=3,                              // Real Constant
		SYM_CLASS_CON_REL=4,                               // Relocatable Address Constant
		SYM_CLASS_CON_STR=5,                               // String Constant
		SYM_CLASS_ENUM=6,
		SYM_CLASS_FUNC=7,                                  // Function/Method/Subroutine
		SYM_CLASS_LABEL_CODE=8,                            // Code Label
		SYM_CLASS_LABEL_DATA=9,                            // Data Label
		SYM_CLASS_MACRO=10,
		SYM_CLASS_REGISTER=11,
		SYM_CLASS_REGISTER_DOUBLE=12,
		SYM_CLASS_SEG_CODE=13,                             // Code Segment
		SYM_CLASS_SEG_DATA=14,                             // Data Segment
		SYM_CLASS_SEG_EXTRA=15,                            // Extra Segment
		SYM_CLASS_SEG_STACK=16,                            // Stack Segment
		SYM_CLASS_STRUCT=17,
		SYM_CLASS_UNION=18,
		SYM_CLASS_VOID=19,
	} SYM_CLASSS;




