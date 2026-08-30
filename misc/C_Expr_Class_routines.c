// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "C_Expr_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			C_Expr_ClassToEnum (
		uint32_t		value
	)
	{
		if (value >= cC_Expr_Class_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (C_Expr_Class_index[value]) {
			return C_Expr_Class_entries[C_Expr_Class_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			C_Expr_ClassToName (
		uint32_t		value
	)
	{
		if (value >= cC_Expr_Class_index) {
			return NULL;
		}
		if (C_Expr_Class_index[value]) {
			return C_Expr_Class_entries[C_Expr_Class_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "C_Expr_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		C_Expr_EnumToClass (
		char			*pDescA
	)
	{
		const
		C_Expr_Class_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)C_Expr_Class_entries,
						cC_Expr_Class_entries,
						sizeof(C_Expr_Class_entry),
						offsetof(C_Expr_Class_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






