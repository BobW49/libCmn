// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "Tuple16_Types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			Tuple16_TypeToEnum (
		uint32_t		value
	)
	{
		if (value >= cTuple16_Type_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (Tuple16_Type_index[value]) {
			return Tuple16_Type_entries[Tuple16_Type_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			Tuple16_TypeToName (
		uint32_t		value
	)
	{
		if (value >= cTuple16_Type_index) {
			return NULL;
		}
		if (Tuple16_Type_index[value]) {
			return Tuple16_Type_entries[Tuple16_Type_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "Tuple16_Types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		Tuple16_EnumToType (
		char			*pDescA
	)
	{
		const
		Tuple16_Type_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)Tuple16_Type_entries,
						cTuple16_Type_entries,
						sizeof(Tuple16_Type_entry),
						offsetof(Tuple16_Type_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






