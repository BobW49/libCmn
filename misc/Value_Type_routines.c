// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "value_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			Value_TypeToEnum (
		uint32_t		value
	)
	{
		if (value >= cValue_Type_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (Value_Type_index[value]) {
			return Value_Type_entries[Value_Type_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			Value_TypeToName (
		uint32_t		value
	)
	{
		if (value >= cValue_Type_index) {
			return NULL;
		}
		if (Value_Type_index[value]) {
			return Value_Type_entries[Value_Type_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "value_types.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		Value_EnumToType (
		char			*pDescA
	)
	{
		const
		Value_Type_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)Value_Type_entries,
						cValue_Type_entries,
						sizeof(Value_Type_entry),
						offsetof(Value_Type_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






