// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "sym_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Sym_Class_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Sym_Class_index[20] = {
		19, 1, 2, 3, 4, 5, 6, 7, 
		8, 9, 10, 11, 12, 13, 14, 15, 
		16, 17, 18, 20, 
	};

	static
	const
	uint32_t	cSym_Class_index = 20;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Sym_Class_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Sym_Class_entry	Sym_Class_entries[] = {
		{"SYM_CLASS_CON_ADDR", "Address Constant", "CON_ADDR", 1},
		{"SYM_CLASS_CON_INT", "Integer Constant", "CON_INT", 2},
		{"SYM_CLASS_CON_REAL", "Real Constant", "CON_REAL", 3},
		{"SYM_CLASS_CON_REL", "Relocatable Address Constant", "CON_REL", 4},
		{"SYM_CLASS_CON_STR", "String Constant", "CON_STR", 5},
		{"SYM_CLASS_ENUM", "", "ENUM", 6},
		{"SYM_CLASS_FUNC", "Function/Method/Subroutine", "FUNC", 7},
		{"SYM_CLASS_LABEL_CODE", "Code Label", "LABEL_CODE", 8},
		{"SYM_CLASS_LABEL_DATA", "Data Label", "LABEL_DATA", 9},
		{"SYM_CLASS_MACRO", "", "MACRO", 10},
		{"SYM_CLASS_REGISTER", "", "REGISTER", 11},
		{"SYM_CLASS_REGISTER_DOUBLE", "", "REGISTER_DOUBLE", 12},
		{"SYM_CLASS_SEG_CODE", "Code Segment", "SEG_CODE", 13},
		{"SYM_CLASS_SEG_DATA", "Data Segment", "SEG_DATA", 14},
		{"SYM_CLASS_SEG_EXTRA", "Extra Segment", "SEG_EXTRA", 15},
		{"SYM_CLASS_SEG_STACK", "Stack Segment", "SEG_STACK", 16},
		{"SYM_CLASS_STRUCT", "", "STRUCT", 17},
		{"SYM_CLASS_UNION", "", "UNION", 18},
		{"SYM_CLASS_UNKNOWN", "", "UNKNOWN", 0},
		{"SYM_CLASS_VOID", "", "VOID", 19},
	};

	static
	const
	uint32_t	cSym_Class_offset = 0;
	static
	const
	uint32_t	cSym_Class_entries = 20;









