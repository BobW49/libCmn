// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "TreeExpr_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the TreeExpr_Class_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	TreeExpr_Class_index[69] = {
		44, 35, 3, 16, 15, 37, 28, 4, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		1, 2, 9, 6, 5, 7, 8, 10, 
		11, 12, 13, 14, 17, 18, 19, 20, 
		21, 22, 23, 24, 25, 26, 27, 29, 
		30, 33, 34, 31, 32, 36, 38, 39, 
		40, 41, 42, 43, 45, 
	};

	static
	const
	uint32_t	cTreeExpr_Class_index = 69;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} TreeExpr_Class_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	TreeExpr_Class_entry	TreeExpr_Class_entries[] = {
		{"TREEEXPR_CLASS_ADD", "Bin Op +", "ADD", 32},
		{"TREEEXPR_CLASS_AND", "Bin Op &", "AND", 33},
		{"TREEEXPR_CLASS_ANY", "?", "ANY", 2},
		{"TREEEXPR_CLASS_CLOSE", ")", "CLOSE", 7},
		{"TREEEXPR_CLASS_CON_BOOL", "Logical Constant", "CON_BOOL", 36},
		{"TREEEXPR_CLASS_CON_INT", "Integer Constant", "CON_INT", 35},
		{"TREEEXPR_CLASS_CON_REAL", "Real Constant", "CON_REAL", 37},
		{"TREEEXPR_CLASS_DIV", "Bin Op /", "DIV", 38},
		{"TREEEXPR_CLASS_EQ", "Bin Op ==", "EQ", 34},
		{"TREEEXPR_CLASS_EXPR_BOOL", "", "EXPR_BOOL", 39},
		{"TREEEXPR_CLASS_EXPR_INT", "", "EXPR_INT", 40},
		{"TREEEXPR_CLASS_EXPR_REAL", "", "EXPR_REAL", 41},
		{"TREEEXPR_CLASS_GT", "Bin Op >", "GT", 42},
		{"TREEEXPR_CLASS_GTEQ", "Bin Op >=", "GTEQ", 43},
		{"TREEEXPR_CLASS_INTEGER", "", "INTEGER", 4},
		{"TREEEXPR_CLASS_KLEENE", "*", "KLEENE", 3},
		{"TREEEXPR_CLASS_LOG_AND", "Bin Op &&", "LOG_AND", 44},
		{"TREEEXPR_CLASS_LOG_NOT", "Unary Op !", "LOG_NOT", 45},
		{"TREEEXPR_CLASS_LOG_OR", "Bin Op ||", "LOG_OR", 46},
		{"TREEEXPR_CLASS_LSHIFT", "Bin Op <<", "LSHIFT", 47},
		{"TREEEXPR_CLASS_LT", "Bin Op <", "LT", 48},
		{"TREEEXPR_CLASS_LTEQ", "Bin Op <=", "LTEQ", 49},
		{"TREEEXPR_CLASS_MOD", "Bin Op %", "MOD", 50},
		{"TREEEXPR_CLASS_MUL", "Bin Op *", "MUL", 51},
		{"TREEEXPR_CLASS_NE", "Bin Op !=", "NE", 52},
		{"TREEEXPR_CLASS_NEG", "Unary Op -", "NEG", 53},
		{"TREEEXPR_CLASS_NOT", "Unary Op ~", "NOT", 54},
		{"TREEEXPR_CLASS_OPEN", "(", "OPEN", 6},
		{"TREEEXPR_CLASS_OR", "Bin Op |", "OR", 55},
		{"TREEEXPR_CLASS_PLUS", "Unary Op +", "PLUS", 56},
		{"TREEEXPR_CLASS_POSTDEC", "Unary Op value--", "POSTDEC", 59},
		{"TREEEXPR_CLASS_POSTINC", "Unary Op value++", "POSTINC", 60},
		{"TREEEXPR_CLASS_PREDEC", "Unary Op --value", "PREDEC", 57},
		{"TREEEXPR_CLASS_PREINC", "Unary Op ++value", "PREINC", 58},
		{"TREEEXPR_CLASS_ROOT", "", "ROOT", 1},
		{"TREEEXPR_CLASS_RSHIFT", "Bin Op >>", "RSHIFT", 61},
		{"TREEEXPR_CLASS_STRING", "", "STRING", 5},
		{"TREEEXPR_CLASS_SUB", "Bin Op -", "SUB", 62},
		{"TREEEXPR_CLASS_SYM_BOOL", "Boolean Variable Symbol", "SYM_BOOL", 63},
		{"TREEEXPR_CLASS_SYM_INT", "Integer Variable Symbol", "SYM_INT", 64},
		{"TREEEXPR_CLASS_SYM_REAL", "Real Variable Symbol", "SYM_REAL", 65},
		{"TREEEXPR_CLASS_SYM_REL", "Relative Variable Symbol (Based on Relative Addressing)", "SYM_REL", 66},
		{"TREEEXPR_CLASS_SYM_UNK", "Unknown type of Symbol", "SYM_UNK", 67},
		{"TREEEXPR_CLASS_UNKNOWN", "", "UNKNOWN", 0},
		{"TREEEXPR_CLASS_XOR", "Bin Op ^", "XOR", 68},
	};

	static
	const
	uint32_t	cTreeExpr_Class_offset = 0;
	static
	const
	uint32_t	cTreeExpr_Class_entries = 45;









