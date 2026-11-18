int is_special_type(int type)
{
	int pat_type = type & 0x0f;
	return (pat_type == SNDRV_SFNT_PAT_TYPE_GUS ||
		pat_type == SNDRV_SFNT_PAT_TYPE_MAP);
}