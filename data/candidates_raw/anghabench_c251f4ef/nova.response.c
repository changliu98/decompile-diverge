static const struct bpf_func_proto *
func0(enum bpf_func_id func_id)
{
	const struct bpf_func_proto *p;
	size_t off = func_id;

	switch (off) {
	
	case BPF_FUNC_perf_event_output:
	case BPF_FUNC_get_stackid:
	case BPF_FUNC_get_stack:
	case BPF_FUNC_perf_event_read_value:
	case BPF_FUNC_perf_event_read_value_arr:
		p = &bpf_perf_event_proto[off];
		break;
	
	case BPF_FUNC_get_stackid_link:
		p = &bpf_perf_event_proto[BPF_FUNC_get_stackid];
		break;
	case BPF_FUNC_get_stack_link:
		p = &bpf_perf_event_proto[BPF_FUNC_get_stack];
		break;
	case BPF_FUNC_perf_event_output_raw:
		p = &bpf_perf_event_proto[BPF_FUNC_perf_event_output];
		break;
	case BPF_FUNC_perf_event_read_value_raw:
		p = &bpf_perf_event_proto[BPF_FUNC_perf_event_read_value];
		break;
	case BPF_FUNC_perf_event_read_value_arr_raw:
		p = &bpf_perf_event_proto[BPF_FUNC_perf_event_read_value_arr];
		break;
	default:
		p = &bpf_perf_event_proto[BPF_FUNC_max];
		break;
	}
	return p;
}