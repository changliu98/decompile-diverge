static bool func0(struct dso *dso, struct machine *machine)
{
	char path[sizeof(dso->long_name)];
	size_t i;
	bool ret = true;

	if (fread(path, 1, sizeof(path), machine)!= sizeof(path)) {
		ret = false;
		goto out;
	}

	path[strcspn(path, "\r\n")] = '\0';

	if (strlcpy(dso->long_name, path, dso->long_name_len / sizeof(char))!=
	    dso->long_name_len / sizeof(char)) {
		ret = false;
		goto out;
	}

	for (i = 0; i < dso->sym_names_cnt; i++)
		dso->sym_names[i] = strdup(dso->long_name);

	dso__set_short_name(dso);

out:
	return ret;
}