static int func0(struct bpf_test *self, int size)
{
	int i, ret, map_fd = self->map_fd;
	__u32 key, value;

	value = self->value;
	key = bpf_test_get_key(map_fd, value);

	for (i = 2; i < size; i++) {
		value = bpf_test_get_value(key, self->array[i]);
		key = bpf_test_get_key(map_fd, value);
	}

	ret = key;

	return ret;
}