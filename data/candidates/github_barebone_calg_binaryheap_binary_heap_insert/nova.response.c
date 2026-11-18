static int binary_heap_insert(struct bpf_object *obj, const char *name)
{
	size_t i, j;
	int ret;

	if (obj->nr_relocations >= obj->relocations_cap) {
		size_t new_cap = obj->relocations_cap * 2;
		struct bpf_relocation *new_relocs;

		new_relocs = realloc(obj->relocations,
				     new_cap * sizeof(struct bpf_relocation));
		if (!new_relocs) {
			ret = 0;
			goto out;
		}

		obj->relocations_cap = new_cap;
		obj->relocations = new_relocs;
	}

	i = obj->nr_relocations;
	obj->nr_relocations++;

	
	for (j = i; j > 0; j--) {
		if (strcmp(obj->relocations[j - 1].name, name) < 0)
			break;
		obj->relocations[j] = obj->relocations[j - 1];
	}

	obj->relocations[j].name = name;
	ret = 1;
out:
	return ret;
}