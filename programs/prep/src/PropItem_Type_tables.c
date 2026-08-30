// vi:nu:et:sts=4 ts=4 sw=4


	/* The following tables were generated from:
	 * "propitem_types.txt"
	 * If you want to change this enum, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// This table is in enum order and provides
	// the index + 1 into the PropItem_Type_entries
	// table. 0 means no enum entry.
	static
	const
	uint16_t	PropItem_Type_index[13] = {
		1, 4, 2, 3, 8, 5, 6, 7, 
		9, 13, 10, 11, 12, 
	};

	static
	const
	uint32_t	cPropItem_Type_index = 13;




	typedef struct {
		const
		char			*pEnum;
		char			*pDesc;
		char			*pName;
		uint32_t		value;
	} PropItem_Type_entry;

	// This table is in alphanumeric order to be searched
	// with a sequential or binary search by description.

	static
	const
	PropItem_Type_entry	PropItem_Type_entries[] = {
		{"PROPITEM_TYPE_ASTR", "", "ASTR", 0},
		{"PROPITEM_TYPE_FLAG16", "", "FLAG16", 2},
		{"PROPITEM_TYPE_FLAG32", "", "FLAG32", 3},
		{"PROPITEM_TYPE_FLAG8", "", "FLAG8", 1},
		{"PROPITEM_TYPE_INT16", "", "INT16", 5},
		{"PROPITEM_TYPE_INT32", "", "INT32", 6},
		{"PROPITEM_TYPE_INT64", "", "INT64", 7},
		{"PROPITEM_TYPE_INT8", "", "INT8", 4},
		{"PROPITEM_TYPE_OBJECT", "", "OBJECT", 8},
		{"PROPITEM_TYPE_UINT16", "", "UINT16", 10},
		{"PROPITEM_TYPE_UINT32", "", "UINT32", 11},
		{"PROPITEM_TYPE_UINT64", "", "UINT64", 12},
		{"PROPITEM_TYPE_UINT8", "", "UINT8", 9},
	};

	static
	const
	uint32_t	cPropItem_Type_offset = 0;
	static
	const
	uint32_t	cPropItem_Type_entries = 13;









