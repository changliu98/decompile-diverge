__attribute__((used)) static int is_special_type(int type)
{
	unsigned char val;
	type &= 0x0f;
	val = (type == SNDRV_SFNT_PAT_TYPE_GUS) ? 1 :
		(type == SNDRV_SFNT_PAT_TYPE_MAP) ? 1 : 0;
	return val & 1;
}