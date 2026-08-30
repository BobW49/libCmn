// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "sym_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			Sym_ClassToEnum (
		uint32_t		value
	)
	{
		if (value >= cSym_Class_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (Sym_Class_index[value]) {
			return Sym_Class_entries[Sym_Class_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			Sym_ClassToName (
		uint32_t		value
	)
	{
		if (value >= cSym_Class_index) {
			return NULL;
		}
		if (Sym_Class_index[value]) {
			return Sym_Class_entries[Sym_Class_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "sym_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		Sym_EnumToClass (
		char			*pDescA
	)
	{
		const
		Sym_Class_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)Sym_Class_entries,
						cSym_Class_entries,
						sizeof(Sym_Class_entry),
						offsetof(Sym_Class_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






