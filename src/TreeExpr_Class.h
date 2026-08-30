// vi:nu:et:sts=4 ts=4 sw=4


	/* The following enum was generated from:
	 * "TreeExpr_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	typedef enum TreeExpr_Class_e {
		TREEEXPR_CLASS_UNKNOWN=0,
		TREEEXPR_CLASS_ROOT=1,
		TREEEXPR_CLASS_ANY=2,                              // ?
		TREEEXPR_CLASS_KLEENE=3,                           // *
		TREEEXPR_CLASS_INTEGER=4,
		TREEEXPR_CLASS_STRING=5,
		TREEEXPR_CLASS_OPEN=6,                             // (
		TREEEXPR_CLASS_CLOSE=7,                            // )
		TREEEXPR_CLASS_ADD=32,                             // Bin Op +
		TREEEXPR_CLASS_AND=33,                             // Bin Op &
		TREEEXPR_CLASS_EQ=34,                              // Bin Op ==
		TREEEXPR_CLASS_CON_INT=35,                         // Integer Constant
		TREEEXPR_CLASS_CON_BOOL=36,                        // Logical Constant
		TREEEXPR_CLASS_CON_REAL=37,                        // Real Constant
		TREEEXPR_CLASS_DIV=38,                             // Bin Op /
		TREEEXPR_CLASS_EXPR_BOOL=39,
		TREEEXPR_CLASS_EXPR_INT=40,
		TREEEXPR_CLASS_EXPR_REAL=41,
		TREEEXPR_CLASS_GT=42,                              // Bin Op >
		TREEEXPR_CLASS_GTEQ=43,                            // Bin Op >=
		TREEEXPR_CLASS_LOG_AND=44,                         // Bin Op &&
		TREEEXPR_CLASS_LOG_NOT=45,                         // Unary Op !
		TREEEXPR_CLASS_LOG_OR=46,                          // Bin Op ||
		TREEEXPR_CLASS_LSHIFT=47,                          // Bin Op <<
		TREEEXPR_CLASS_LT=48,                              // Bin Op <
		TREEEXPR_CLASS_LTEQ=49,                            // Bin Op <=
		TREEEXPR_CLASS_MOD=50,                             // Bin Op %
		TREEEXPR_CLASS_MUL=51,                             // Bin Op *
		TREEEXPR_CLASS_NE=52,                              // Bin Op !=
		TREEEXPR_CLASS_NEG=53,                             // Unary Op -
		TREEEXPR_CLASS_NOT=54,                             // Unary Op ~
		TREEEXPR_CLASS_OR=55,                              // Bin Op |
		TREEEXPR_CLASS_PLUS=56,                            // Unary Op +
		TREEEXPR_CLASS_PREDEC=57,                          // Unary Op --value
		TREEEXPR_CLASS_PREINC=58,                          // Unary Op ++value
		TREEEXPR_CLASS_POSTDEC=59,                         // Unary Op value--
		TREEEXPR_CLASS_POSTINC=60,                         // Unary Op value++
		TREEEXPR_CLASS_RSHIFT=61,                          // Bin Op >>
		TREEEXPR_CLASS_SUB=62,                             // Bin Op -
		TREEEXPR_CLASS_SYM_BOOL=63,                        // Boolean Variable Symbol
		TREEEXPR_CLASS_SYM_INT=64,                         // Integer Variable Symbol
		TREEEXPR_CLASS_SYM_REAL=65,                        // Real Variable Symbol
		TREEEXPR_CLASS_SYM_REL=66,                         // Relative Variable Symbol (Based on Relative Addressing)
		TREEEXPR_CLASS_SYM_UNK=67,                         // Unknown type of Symbol
		TREEEXPR_CLASS_XOR=68,                             // Bin Op ^
	} TREEEXPR_CLASSS;




