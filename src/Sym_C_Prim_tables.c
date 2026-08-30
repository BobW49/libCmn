// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "sym_c_prim.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Sym_C_Prim_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Sym_C_Prim_index[42] = {
		38, 3, 6, 1, 2, 14, 15, 28, 
		29, 16, 17, 24, 25, 39, 40, 7, 
		8, 18, 19, 30, 31, 9, 12, 20, 
		23, 32, 35, 10, 11, 21, 22, 33, 
		34, 41, 42, 4, 5, 26, 27, 36, 
		37, 13, 
	};

	static
	const
	uint32_t	cSym_C_Prim_index = 42;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Sym_C_Prim_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Sym_C_Prim_entry	Sym_C_Prim_entries[] = {
		{"SYM_C_PRIM_CHAR", "", "CHAR", 3},
		{"SYM_C_PRIM_CHAR_PTR", "", "CHAR_PTR", 4},
		{"SYM_C_PRIM_CODE_PTR", "Label in Code Segment", "CODE_PTR", 1},
		{"SYM_C_PRIM_ENUM", "", "ENUM", 35},
		{"SYM_C_PRIM_ENUM_PTR", "", "ENUM_PTR", 36},
		{"SYM_C_PRIM_FUNC_PTR", "Subroutine Entry in Code Segment", "FUNC_PTR", 2},
		{"SYM_C_PRIM_INT", "", "INT", 15},
		{"SYM_C_PRIM_INT_PTR", "", "INT_PTR", 16},
		{"SYM_C_PRIM_LONG", "", "LONG", 21},
		{"SYM_C_PRIM_LONGLONG", "", "LONGLONG", 27},
		{"SYM_C_PRIM_LONGLONG_PTR", "", "LONGLONG_PTR", 28},
		{"SYM_C_PRIM_LONG_PTR", "", "LONG_PTR", 22},
		{"SYM_C_PRIM_MACRO", "", "MACRO", 41},
		{"SYM_C_PRIM_SCHAR", "", "SCHAR", 5},
		{"SYM_C_PRIM_SCHAR_PTR", "", "SCHAR_PTR", 6},
		{"SYM_C_PRIM_SHORT", "", "SHORT", 9},
		{"SYM_C_PRIM_SHORT_PTR", "", "SHORT_PTR", 10},
		{"SYM_C_PRIM_SINT", "", "SINT", 17},
		{"SYM_C_PRIM_SINT_PTR", "", "SINT_PTR", 18},
		{"SYM_C_PRIM_SLONG", "", "SLONG", 23},
		{"SYM_C_PRIM_SLONGLONG", "", "SLONGLONG", 29},
		{"SYM_C_PRIM_SLONGLONG_PTR", "", "SLONGLONG_PTR", 30},
		{"SYM_C_PRIM_SLONG_PTR", "", "SLONG_PTR", 24},
		{"SYM_C_PRIM_SSHORT", "", "SSHORT", 11},
		{"SYM_C_PRIM_SSHORT_PTR", "", "SSHORT_PTR", 12},
		{"SYM_C_PRIM_STRUCT", "", "STRUCT", 37},
		{"SYM_C_PRIM_STRUCT_PTR", "", "STRUCT_PTR", 38},
		{"SYM_C_PRIM_UCHAR", "", "UCHAR", 7},
		{"SYM_C_PRIM_UCHAR_PTR", "", "UCHAR_PTR", 8},
		{"SYM_C_PRIM_UINT", "", "UINT", 19},
		{"SYM_C_PRIM_UINT_PTR", "", "UINT_PTR", 20},
		{"SYM_C_PRIM_ULONG", "", "ULONG", 25},
		{"SYM_C_PRIM_ULONGLONG", "", "ULONGLONG", 31},
		{"SYM_C_PRIM_ULONGLONG_PTR", "", "ULONGLONG_PTR", 32},
		{"SYM_C_PRIM_ULONG_PTR", "", "ULONG_PTR", 26},
		{"SYM_C_PRIM_UNION", "", "UNION", 39},
		{"SYM_C_PRIM_UNION_PTR", "", "UNION_PTR", 40},
		{"SYM_C_PRIM_UNKNOWN", "", "UNKNOWN", 0},
		{"SYM_C_PRIM_USHORT", "", "USHORT", 13},
		{"SYM_C_PRIM_USHORT_PTR", "", "USHORT_PTR", 14},
		{"SYM_C_PRIM_VOID", "", "VOID", 33},
		{"SYM_C_PRIM_VOID_PTR", "", "VOID_PTR", 34},
	};

	static
	const
	uint32_t	cSym_C_Prim_offset = 0;
	static
	const
	uint32_t	cSym_C_Prim_entries = 42;









