// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "C_Expr_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the C_Expr_Class_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	C_Expr_Class_index[75] = {
		50, 40, 3, 23, 22, 43, 34, 4, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		1, 2, 14, 7, 5, 6, 8, 9, 
		10, 11, 12, 13, 15, 16, 17, 18, 
		19, 20, 21, 24, 25, 26, 27, 28, 
		29, 30, 31, 32, 33, 35, 36, 37, 
		38, 39, 41, 42, 44, 45, 46, 47, 
		48, 49, 51, 
	};

	static
	const
	uint32_t	cC_Expr_Class_index = 75;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} C_Expr_Class_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	C_Expr_Class_entry	C_Expr_Class_entries[] = {
		{"C_EXPR_CLASS_ADD", "Bin Op +", "ADD", 32},
		{"C_EXPR_CLASS_AND", "Bin Op &", "AND", 33},
		{"C_EXPR_CLASS_ANY", "?", "ANY", 2},
		{"C_EXPR_CLASS_CLOSE", ")", "CLOSE", 7},
		{"C_EXPR_CLASS_CON_BOOL", "Boolean Constant", "CON_BOOL", 36},
		{"C_EXPR_CLASS_CON_CHAR", "Character Constant", "CON_CHAR", 37},
		{"C_EXPR_CLASS_CON_INT", "Integer Constant", "CON_INT", 35},
		{"C_EXPR_CLASS_CON_REAL", "Real Constant", "CON_REAL", 38},
		{"C_EXPR_CLASS_CON_STRING", "Real Constant", "CON_STRING", 39},
		{"C_EXPR_CLASS_DEC_POST", "Unary Op value--", "DEC_POST", 40},
		{"C_EXPR_CLASS_DEC_PRE", "Unary Op --value", "DEC_PRE", 41},
		{"C_EXPR_CLASS_DIV", "Bin Op /", "DIV", 42},
		{"C_EXPR_CLASS_EOL", "End-of-Line", "EOL", 43},
		{"C_EXPR_CLASS_EQ", "Bin Op ==", "EQ", 34},
		{"C_EXPR_CLASS_EXPR_BOOL", "", "EXPR_BOOL", 44},
		{"C_EXPR_CLASS_EXPR_INT", "", "EXPR_INT", 45},
		{"C_EXPR_CLASS_EXPR_REAL", "", "EXPR_REAL", 46},
		{"C_EXPR_CLASS_GE", "Bin Op >=", "GE", 47},
		{"C_EXPR_CLASS_GT", "Bin Op >", "GT", 48},
		{"C_EXPR_CLASS_INC_POST", "Unary Op value++", "INC_POST", 49},
		{"C_EXPR_CLASS_INC_PRE", "Unary Op ++value", "INC_PRE", 50},
		{"C_EXPR_CLASS_INTEGER", "", "INTEGER", 4},
		{"C_EXPR_CLASS_KLEENE", "*", "KLEENE", 3},
		{"C_EXPR_CLASS_LE", "Bin Op <=", "LE", 51},
		{"C_EXPR_CLASS_LOG_AND", "Bin Op &&", "LOG_AND", 52},
		{"C_EXPR_CLASS_LOG_NOT", "Unary Op !", "LOG_NOT", 53},
		{"C_EXPR_CLASS_LOG_OR", "Bin Op ||", "LOG_OR", 54},
		{"C_EXPR_CLASS_LT", "Bin Op <", "LT", 55},
		{"C_EXPR_CLASS_MOD", "Bin Op %", "MOD", 56},
		{"C_EXPR_CLASS_MUL", "Bin Op *", "MUL", 57},
		{"C_EXPR_CLASS_NE", "Bin Op !=", "NE", 58},
		{"C_EXPR_CLASS_NEG", "Unary Op -", "NEG", 59},
		{"C_EXPR_CLASS_NOT", "Unary Op ~", "NOT", 60},
		{"C_EXPR_CLASS_OPEN", "(", "OPEN", 6},
		{"C_EXPR_CLASS_OR", "Bin Op |", "OR", 61},
		{"C_EXPR_CLASS_PAREN_LEFT", "(", "PAREN_LEFT", 62},
		{"C_EXPR_CLASS_PAREN_RIGHT", ")", "PAREN_RIGHT", 63},
		{"C_EXPR_CLASS_PLUS", "Unary Op +", "PLUS", 64},
		{"C_EXPR_CLASS_PTR", "Bin Op ->", "PTR", 65},
		{"C_EXPR_CLASS_ROOT", "", "ROOT", 1},
		{"C_EXPR_CLASS_SHIFT_LEFT", "Bin Op <<", "SHIFT_LEFT", 66},
		{"C_EXPR_CLASS_SHIFT_RIGHT", "Bin Op >>", "SHIFT_RIGHT", 67},
		{"C_EXPR_CLASS_STRING", "", "STRING", 5},
		{"C_EXPR_CLASS_SUB", "Bin Op -", "SUB", 68},
		{"C_EXPR_CLASS_SYM_BOOL", "Boolean Variable Symbol", "SYM_BOOL", 69},
		{"C_EXPR_CLASS_SYM_INT", "Integer Variable Symbol", "SYM_INT", 70},
		{"C_EXPR_CLASS_SYM_REAL", "Real Variable Symbol", "SYM_REAL", 71},
		{"C_EXPR_CLASS_SYM_REL", "Relative Variable Symbol", "SYM_REL", 72},
		{"C_EXPR_CLASS_SYM_UNK", "Unknown Symbol", "SYM_UNK", 73},
		{"C_EXPR_CLASS_UNKNOWN", "", "UNKNOWN", 0},
		{"C_EXPR_CLASS_XOR", "Bin Op ^", "XOR", 74},
	};

	static
	const
	uint32_t	cC_Expr_Class_offset = 0;
	static
	const
	uint32_t	cC_Expr_Class_entries = 51;









