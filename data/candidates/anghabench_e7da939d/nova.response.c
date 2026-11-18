static const struct bpf_func_proto *
test_to_str(enum bpf_func_id func_id)
{
	const struct bpf_func_proto *func_proto;
	enum bpf_func_id alias = func_id;

	switch (func_id) {
	
	case BPF_FUNC_skb_load_bytes:
		alias = BPF_FUNC_skb_load_bytes_deprecated;
		
	case BPF_FUNC_skb_load_bytes_deprecated:
		func_proto = &skb_load_bytes_proto;
		break;
	
	case BPF_FUNC_skb_load_bytes_windex:
		alias = BPF_FUNC_skb_load_bytes_windex_deprecated;
		
	case BPF_FUNC_skb_load_bytes_windex_deprecated:
		func_proto = &skb_load_bytes_windex_proto;
		break;
	default:
		func_proto = &skb_load_bytes_windex_proto;
		break;
	}

	return func_proto;
}