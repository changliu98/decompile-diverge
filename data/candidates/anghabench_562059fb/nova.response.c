static struct bpf_prog *selectOpName(enum bpf_prog_type type)
{
	enum bpf_attach_type attach_type = type;
	struct bpf_prog *prog;

	switch (type) {
	case BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		prog = &cgroup_sock_addr_prog;
		break;
	case BPF_PROG_TYPE_CGROUP_SOCK_OPS:
		prog = &cgroup_sock_ops_prog;
		break;
	case BPF_PROG_TYPE_CGROUP_SKB_ADDR:
		prog = &cgroup_skb_addr_prog;
		break;
	default:
		prog = &cgroup_skb_ops_prog;
		break;
	}

	switch (attach_type) {
	case BPF_FLOW_DISSECTOR:
	case BPF_FLOW_DISSECTOR_INGRESS:
		prog = &cgroup_flow_dissector_prog;
		break;
	default:
		break;
	}

	return prog;
}