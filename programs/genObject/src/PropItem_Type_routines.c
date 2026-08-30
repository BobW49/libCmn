// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "propitem_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			PropItem_TypeToEnum (
		uint32_t		value
	)
	{
		if (value >= cPropItem_Type_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (PropItem_Type_index[value]) {
			return PropItem_Type_entries[PropItem_Type_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			PropItem_TypeToName (
		uint32_t		value
	)
	{
		if (value >= cPropItem_Type_index) {
			return NULL;
		}
		if (PropItem_Type_index[value]) {
			return PropItem_Type_entries[PropItem_Type_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "propitem_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		PropItem_EnumToType (
		char			*pDescA
	)
	{
		const
		PropItem_Type_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)PropItem_Type_entries,
						cPropItem_Type_entries,
						sizeof(PropItem_Type_entry),
						offsetof(PropItem_Type_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






