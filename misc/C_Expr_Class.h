// vi:nu:et:sts=4 ts=4 sw=4


	/* The following enum was generated from:
	 * "C_Expr_classes.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	typedef enum C_Expr_Class_e {
		C_EXPR_CLASS_UNKNOWN=0,
		C_EXPR_CLASS_ROOT=1,
		C_EXPR_CLASS_ANY=2,                                // ?
		C_EXPR_CLASS_KLEENE=3,                             // *
		C_EXPR_CLASS_INTEGER=4,
		C_EXPR_CLASS_STRING=5,
		C_EXPR_CLASS_OPEN=6,                               // (
		C_EXPR_CLASS_CLOSE=7,                              // )
		C_EXPR_CLASS_ADD=32,                               // Bin Op +
		C_EXPR_CLASS_AND=33,                               // Bin Op &
		C_EXPR_CLASS_EQ=34,                                // Bin Op ==
		C_EXPR_CLASS_CON_INT=35,                           // Integer Constant
		C_EXPR_CLASS_CON_BOOL=36,                          // Boolean Constant
		C_EXPR_CLASS_CON_CHAR=37,                          // Character Constant
		C_EXPR_CLASS_CON_REAL=38,                          // Real Constant
		C_EXPR_CLASS_CON_STRING=39,                        // Real Constant
		C_EXPR_CLASS_DEC_POST=40,                          // Unary Op value--
		C_EXPR_CLASS_DEC_PRE=41,                           // Unary Op --value
		C_EXPR_CLASS_DIV=42,                               // Bin Op /
		C_EXPR_CLASS_EOL=43,                               // End-of-Line
		C_EXPR_CLASS_EXPR_BOOL=44,
		C_EXPR_CLASS_EXPR_INT=45,
		C_EXPR_CLASS_EXPR_REAL=46,
		C_EXPR_CLASS_GE=47,                                // Bin Op >=
		C_EXPR_CLASS_GT=48,                                // Bin Op >
		C_EXPR_CLASS_INC_POST=49,                          // Unary Op value++
		C_EXPR_CLASS_INC_PRE=50,                           // Unary Op ++value
		C_EXPR_CLASS_LE=51,                                // Bin Op <=
		C_EXPR_CLASS_LOG_AND=52,                           // Bin Op &&
		C_EXPR_CLASS_LOG_NOT=53,                           // Unary Op !
		C_EXPR_CLASS_LOG_OR=54,                            // Bin Op ||
		C_EXPR_CLASS_LT=55,                                // Bin Op <
		C_EXPR_CLASS_MOD=56,                               // Bin Op %
		C_EXPR_CLASS_MUL=57,                               // Bin Op *
		C_EXPR_CLASS_NE=58,                                // Bin Op !=
		C_EXPR_CLASS_NEG=59,                               // Unary Op -
		C_EXPR_CLASS_NOT=60,                               // Unary Op ~
		C_EXPR_CLASS_OR=61,                                // Bin Op |
		C_EXPR_CLASS_PAREN_LEFT=62,                        // (
		C_EXPR_CLASS_PAREN_RIGHT=63,                       // )
		C_EXPR_CLASS_PLUS=64,                              // Unary Op +
		C_EXPR_CLASS_PTR=65,                               // Bin Op ->
		C_EXPR_CLASS_SHIFT_LEFT=66,                        // Bin Op <<
		C_EXPR_CLASS_SHIFT_RIGHT=67,                       // Bin Op >>
		C_EXPR_CLASS_SUB=68,                               // Bin Op -
		C_EXPR_CLASS_SYM_BOOL=69,                          // Boolean Variable Symbol
		C_EXPR_CLASS_SYM_INT=70,                           // Integer Variable Symbol
		C_EXPR_CLASS_SYM_REAL=71,                          // Real Variable Symbol
		C_EXPR_CLASS_SYM_REL=72,                           // Relative Variable Symbol
		C_EXPR_CLASS_SYM_UNK=73,                           // Unknown Symbol
		C_EXPR_CLASS_XOR=74,                               // Bin Op ^
	} C_EXPR_CLASSS;




