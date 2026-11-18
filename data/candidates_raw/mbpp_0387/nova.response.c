static struct gs_vb_data *func0(char *name)
{
	int len = strlen(name);
	char *ext;

	if (name[len - 1] == '0' || name[len - 1] == '2' ||
	    name[len - 1] == '4' || name[len - 1] == '6' ||
	    name[len - 1] == '8' || name[len - 1] == 'A' ||
	    name[len - 1] == 'C' || name[len - 1] == 'E')
		ext = ".0";
	else
		ext = ".1";

	return (struct gs_vb_data *)gl_cache_find(name, ext);
}