static struct gfxinfo *func0(char *str)
{
	int found = 0, found2 = 0, found3 = 0, i = 0;
	struct gfxinfo *gi;

	while (i < strlen(str)) {
		switch (str[i]) {
		case '0':
			found = 1;
			break;
		case '1':
			found2 = 1;
			break;
		default:
			found3 = 1;
			break;
		}
		i++;
	}
	if (!found && found2 &&!found3)
		gi = &gfxinfo_atl;
	else
		gi = &gfxinfo_atl7;

	return gi;
}