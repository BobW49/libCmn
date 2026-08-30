// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "genitem_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			GenItem_TypeToEnum (
		uint32_t		value
	)
	{
		if (value >= cGenItem_Type_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (GenItem_Type_index[value]) {
			return GenItem_Type_entries[GenItem_Type_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			GenItem_TypeToName (
		uint32_t		value
	)
	{
		if (value >= cGenItem_Type_index) {
			return NULL;
		}
		if (GenItem_Type_index[value]) {
			return GenItem_Type_entries[GenItem_Type_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "genitem_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		GenItem_EnumToType (
		char			*pDescA
	)
	{
		const
		GenItem_Type_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)GenItem_Type_entries,
						cGenItem_Type_entries,
						sizeof(GenItem_Type_entry),
						offsetof(GenItem_Type_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






