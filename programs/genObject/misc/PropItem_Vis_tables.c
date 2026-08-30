// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "propitem_vis.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the PropItem_Vis_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	PropItem_Vis_index[4] = {
		1, 2, 3, 4, 
	};

	static
	const
	uint32_t	cPropItem_Vis_index = 4;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} PropItem_Vis_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	PropItem_Vis_entry	PropItem_Vis_entries[] = {
		{"PROPITEM_VIS_NONE", "", "NONE", 0},
		{"PROPITEM_VIS_PUBLIC", "", "PUBLIC", 1},
		{"PROPITEM_VIS_READ_ONLY", "", "READ_ONLY", 2},
		{"PROPITEM_VIS_WRITE_ONLY", "", "WRITE_ONLY", 3},
	};

	static
	const
	uint32_t	cPropItem_Vis_offset = 0;
	static
	const
	uint32_t	cPropItem_Vis_entries = 4;









