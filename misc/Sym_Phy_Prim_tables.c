// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "sym_phy_prim.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the Sym_Phy_Prim_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	Sym_Phy_Prim_index[24] = {
		20, 4, 14, 1, 9, 16, 3, 11, 
		18, 24, 15, 22, 2, 10, 17, 6, 
		12, 21, 23, 5, 7, 8, 13, 19, 
		
	};

	static
	const
	uint32_t	cSym_Phy_Prim_index = 24;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} Sym_Phy_Prim_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	Sym_Phy_Prim_entry	Sym_Phy_Prim_entries[] = {
		{"SYM_PHY_PRIM_CHAR", "", "CHAR", 3},
		{"SYM_PHY_PRIM_DBLWORD", "", "DBLWORD", 12},
		{"SYM_PHY_PRIM_HALF", "", "HALF", 6},
		{"SYM_PHY_PRIM_LABEL", "Label in Code", "LABEL", 1},
		{"SYM_PHY_PRIM_POINTER", "", "POINTER", 19},
		{"SYM_PHY_PRIM_QUAD", "", "QUAD", 15},
		{"SYM_PHY_PRIM_REGISTER", "", "REGISTER", 20},
		{"SYM_PHY_PRIM_REGISTER_DOUBLE", "", "REGISTER_DOUBLE", 21},
		{"SYM_PHY_PRIM_SCHAR", "Signed Character", "SCHAR", 4},
		{"SYM_PHY_PRIM_SDBLWORD", "Signed Double-Word", "SDBLWORD", 13},
		{"SYM_PHY_PRIM_SHALF", "Signed Half-Word", "SHALF", 7},
		{"SYM_PHY_PRIM_SQUAD", "Signed Quad-Word", "SQUAD", 16},
		{"SYM_PHY_PRIM_STRUCT", "", "STRUCT", 22},
		{"SYM_PHY_PRIM_SUBR", "Subroutine in Code", "SUBR", 2},
		{"SYM_PHY_PRIM_SWORD", "Signed Word", "SWORD", 10},
		{"SYM_PHY_PRIM_UCHAR", "Unsigned Character", "UCHAR", 5},
		{"SYM_PHY_PRIM_UDBLWORD", "Unsigned Double-Word", "UDBLWORD", 14},
		{"SYM_PHY_PRIM_UHALF", "Unsigned Half-Word", "UHALF", 8},
		{"SYM_PHY_PRIM_UNION", "", "UNION", 23},
		{"SYM_PHY_PRIM_UNKNOWN", "", "UNKNOWN", 0},
		{"SYM_PHY_PRIM_UQUAD", "Unsigned Quad-Word", "UQUAD", 17},
		{"SYM_PHY_PRIM_UWORD", "Unsigned Word", "UWORD", 11},
		{"SYM_PHY_PRIM_VOID", "", "VOID", 18},
		{"SYM_PHY_PRIM_WORD", "", "WORD", 9},
	};

	static
	const
	uint32_t	cSym_Phy_Prim_offset = 0;
	static
	const
	uint32_t	cSym_Phy_Prim_entries = 24;









