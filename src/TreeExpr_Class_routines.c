// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "TreeExpr_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			TreeExpr_ClassToEnum (
		uint32_t		value
	)
	{
		if (value >= cTreeExpr_Class_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (TreeExpr_Class_index[value]) {
			return TreeExpr_Class_entries[TreeExpr_Class_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			TreeExpr_ClassToName (
		uint32_t		value
	)
	{
		if (value >= cTreeExpr_Class_index) {
			return NULL;
		}
		if (TreeExpr_Class_index[value]) {
			return TreeExpr_Class_entries[TreeExpr_Class_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "TreeExpr_classes.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		TreeExpr_EnumToClass (
		char			*pDescA
	)
	{
		const
		TreeExpr_Class_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)TreeExpr_Class_entries,
						cTreeExpr_Class_entries,
						sizeof(TreeExpr_Class_entry),
						offsetof(TreeExpr_Class_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






