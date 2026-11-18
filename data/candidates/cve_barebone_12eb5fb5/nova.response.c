static int persistent_cache_read_entry_v3(struct bpf_map_info *info, struct bpf_map_info *new_info)
{
	struct bpf_map_info old_info;
	size_t size;
	void *new_value;
	int err;

	memset(&old_info, 0, sizeof(old_info));
	if (info)
		memcpy(&old_info, &info->map_meta, sizeof(old_info));

	memset(&new_info->map_meta, 0, sizeof(new_info->map_meta));
	if (new_info)
		memcpy(&new_info->map_meta, &info->map_meta,
		       sizeof(new_info->map_meta));

	if (read(info->fd, &old_info, sizeof(old_info))!= sizeof(old_info)) {
		err = -1;
		goto done;
	}

	new_info->map_meta.key_size = old_info.map_meta.key_size;
	new_info->map_meta.value_size = old_info.map_meta.value_size;
	new_info->map_meta.max_entries = old_info.map_meta.max_entries;

	size = new_info->map_meta.key_size * new_info->map_meta.max_entries;
	if (size > UINT_MAX) {
		err = -1;
		goto done;
	}
	new_info->map_meta.map_size = size;

	new_info->map_meta.numa_node = old_info.map_meta.numa_node;

	new_value = realloc(info->map_meta.value, new_info->map_meta.map_size);
	if (!new_value) {
		err = -1;
		goto done;
	}
	info->map_meta.value = new_value;

	err = 1;
done:
	if (err == 1)
		memcpy(info-