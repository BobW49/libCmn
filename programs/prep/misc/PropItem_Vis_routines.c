// vi:nu:et:sts=4 ts=4 sw=4

//#include		<Misc.h>


	/* The following routine was generated from:
	 * "propitem_vis.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum value, return its character format.
	const
	char *			PropItem_VisToEnum (
		uint32_t		value
	)
	{
		if (value >= cPropItem_Vis_index) {
			return "<<<Unknown Enum Value>>>";
		}
		if (PropItem_Vis_index[value]) {
			return PropItem_Vis_entries[PropItem_Vis_index[value] - 1].pEnum;
		} else {
			return "<<<Unknown Enum Value>>>";
		}
	}

	// Given an enum value, return its name.
	const
	char *			PropItem_VisToName (
		uint32_t		value
	)
	{
		if (value >= cPropItem_Vis_index) {
			return NULL;
		}
		if (PropItem_Vis_index[value]) {
			return PropItem_Vis_entries[PropItem_Vis_index[value] - 1].pName;
		} else {
			return NULL;
		}
	}




	/* The following routine was generated from:
	 * "propitem_vis.txt"
	 * If you want to change it, you
	 * should alter the above file and
	 * regenerate using genEnum!
	 */

	// Given an enum description, return its value + 1 or
	// 0 for not found.
	const
	uint32_t		PropItem_EnumToVis (
		char			*pDescA
	)
	{
		const
		PropItem_Vis_entry	*pEntry = NULL;
		uint32_t		value = 0;

		if (pDescA) {
			pEntry = Misc_SearchBinaryStrA(
						pDescA,
						(void *)PropItem_Vis_entries,
						cPropItem_Vis_entries,
						sizeof(PropItem_Vis_entry),
						offsetof(PropItem_Vis_entry, pEnum)
				);
			if (pEntry) {
				value = pEntry->value;
			}
		}
		return value;
	}






