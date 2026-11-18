static const struct bpf_func_proto *
get_level_str(enum bpf_func_id func_id)
{
	const struct bpf_func_proto *p;
	size_t off = func_id - BPF_FUNC_sk_storage_get;

	switch (func_id) {
#ifdef __NR_getuid32
	case BPF_FUNC_getuid32:
		return &bpf_sk_storage_get_proto_getuid32;
#endif
#ifdef __NR_getuid
	case BPF_FUNC_getuid:
		return &bpf_sk_storage_get_proto_getuid;
#endif
	case BPF_FUNC_get_local_storage:
		return &bpf_sk_storage_get_proto_get_local_storage;
	case BPF_FUNC_sk_storage_get:
		return &bpf_sk_storage_get_proto_sk_storage_get;
	case BPF_FUNC_sk_storage_get_current_uid_gid:
		return &bpf_sk_storage_get_proto_sk_storage_get_current_uid_gid;
	case BPF_FUNC_sk_storage_delete:
		return &bpf_sk_storage_get_proto_sk_storage_delete;
	case BPF_FUNC_sk_storage_delete_current_uid_gid:
		return &bpf_sk_storage_get_proto_sk_storage_delete_current_uid_gid;
	case BPF_FUNC_sk_storage_get_socket_cookie:
		return &bpf_sk_storage_get_proto_sk_storage_get_socket_cookie;
	case BPF_FUNC_sk_storage_get_socket_uid_gid:
		return &bpf_sk_storage_get_proto_sk_storage_get_socket_uid_gid;
	case BPF_FUNC_sk_storage_get_socket_listen_port:
		return &bpf_sk_storage_get_proto_sk_storage_get_socket_listen_port