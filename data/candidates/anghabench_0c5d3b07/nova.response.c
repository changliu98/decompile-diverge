static const struct bpf_func_proto *
get_priority_string(enum bpf_func_id func_id)
{
	const struct bpf_func_proto *func_proto;
	size_t id = func_id;

	switch (id) {
	case BPF_FUNC_perf_event_output:
		func_proto = &bpf_perf_event_output_proto;
		break;
	case BPF_FUNC_get_stackid:
	case BPF_FUNC_get_stackid_links:
	case BPF_FUNC_stack_storage_diff:
	case BPF_FUNC_stack_restore:
		func_proto = &bpf_stack_proto;
		break;
	case BPF_FUNC_skb_store_bytes:
		func_proto = &bpf_skb_store_bytes_proto;
		break;
	default:
		func_proto = &bpf_func_proto_unsupported;
		break;
	}

	return func_proto;
}