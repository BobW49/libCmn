// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "genitem_types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the GenItem_Type_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	GenItem_Type_index[3] = {
		2, 1, 3, 
	};

	static
	const
	uint32_t	cGenItem_Type_index = 3;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} GenItem_Type_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	GenItem_Type_entry	GenItem_Type_entries[] = {
		{"GENITEM_TYPE_ENUM", "", "ENUM", 1},
		{"GENITEM_TYPE_OBJECT", "", "OBJECT", 0},
		{"GENITEM_TYPE_PROPERTY", "", "PROPERTY", 2},
	};

	static
	const
	uint32_t	cGenItem_Type_offset = 0;
	static
	const
	uint32_t	cGenItem_Type_entries = 3;









