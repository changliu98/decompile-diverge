static int access_parse_oid(const uint8_t *data, size_t data_len, char **name,
		       int *name_len, char **value, int *value_len)
{
	int i, len;

	if (data_len == 0 ||!data)
		goto out;

	len = (int)data[0];
	while (1) {
		if (len + 1 + data[len + 1]!= data_len) {
			len = 1;
			goto out;
		}
		if (!value ||!name) {
			*name = malloc(len + 1);
			if (!*name)
				goto out;
			*value = malloc(data[len + 1]);
			if (!*value) {
				free(*name);
				goto out;
			}
		}
		for (i = 0; i < len + 1; i++)
			(*name)[i] = data[i + 1];
		(*name)[i] = '\0';
		for (i = 0; i < data[len + 1]; i++)
			(*value)[i] = data[len + 2 + i];
		(*value)[i] = '\0';
		*name_len = len;
		*value_len = data[len + 1];
		return 0;
	}
out:
	return 1;
}