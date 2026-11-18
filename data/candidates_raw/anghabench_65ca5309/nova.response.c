static const struct bpf_func_proto *
func0(short func_id)
{
	const struct bpf_func_proto *builtin_proto;
	const struct bpf_func_proto * (*func_table)[];
	size_t j;

	builtin_proto = &bpf_builtins_common[0];
	func_table = &bpf_func_table[0];

	switch (func_id) {
	case BPF_FUNC_skb_load_bytes:
	case BPF_FUNC_skb_load_bytes_relative:
	case BPF_FUNC_skb_store_bytes:
	case BPF_FUNC_skb_load_bytes_ex:
	case BPF_FUNC_skb_store_bytes_ex:
	case BPF_FUNC_skb_load_bytes_relative_ex:
		j = func_id - BPF_FUNC_skb_load_bytes;
		builtin_proto = &bpf_builtins_skb[j];
		func_table = &bpf_func_skb_table[j];
		break;
	case BPF_FUNC_skb_change_head:
	case BPF_FUNC_skb_change_tail:
		j = func_id - BPF_FUNC_skb_change_head;
		builtin_proto = &bpf_builtins_skb_change[j];
		func_table = &bpf_func_skb_change_table[j];
		break;
	case BPF_FUNC_get_socket_cookie:
	case BPF_FUNC_get_socket_cookie_v6:
		j = func_id - BPF_FUNC_get_socket_cookie;
		builtin_proto = &bpf_builtins_get_socket_cookie[j];
		func_table = &bpf_func_get_socket_cookie_table[j];
		break;
	case BPF_FUNC_perf_event_output:
		j = func