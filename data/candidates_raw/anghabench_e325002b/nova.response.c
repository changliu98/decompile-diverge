static const struct bpf_func_proto *
func0(enum bpf_func_id func_id)
{
	const struct bpf_func_proto *p;
	size_t off = func_id - BPF_FUNC_sk_storage_get;

	switch (func_id) {
#ifdef __NR_sk_storage_get
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto;
#endif
#ifdef __NR_sk_storage_delete
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_delete_proto;
#endif
#ifdef __NR_sk_storage_get_bulk
	case BPF_FUNC_sk_storage_get_bulk:
		return &bpf_sk_storage_get_bulk_proto;
#endif
#ifdef __NR_sk_storage_delete_bulk
	case BPF_FUNC_sk_storage_delete_bulk:
		return &bpf_sk_storage_delete_bulk_proto;
#endif
#ifdef __NR_sk_storage_map_create
	case BPF_FUNC_sk_storage_map_create:
		return &bpf_sk_storage_map_create_proto;
#endif
#ifdef __NR_sk_storage_map_delete
	case BPF_FUNC_sk_storage_map_delete:
		return &bpf_sk_storage_map_delete_proto;
#endif
#ifdef __NR_sk_storage_map_get
	case BPF_FUNC_sk_storage_map_get:
		return &bpf_sk_storage_map_get_proto;
#endif
#ifdef __NR_sk_storage_map_delete_bulk
	case BPF_FUNC_sk_storage_map_delete_bulk:
		return &bpf_sk_storage_map_delete_bulk_proto;
#endif
#ifdef __NR_sk_storage_map_get_bulk
	case BPF_FUNC_sk_storage_map_get_bulk: