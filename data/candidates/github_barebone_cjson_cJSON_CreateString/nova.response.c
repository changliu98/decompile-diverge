static struct mem_region *cJSON_CreateString(const char *name)
{
	struct mem_region *region;

	region = zalloc("memory_region");
	if (region) {
		region->size = 16;
		region->name = kstrdup_to_upper(name, &region_kstr_ops);
		if (!region->name) {
			free(region);
			region = NULL;
		}
	}

	return region;
}