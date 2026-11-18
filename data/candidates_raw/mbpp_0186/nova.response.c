static const struct bpf_func_proto *
func0(const struct bpf_prog *prog, const struct bpf_insn *insn)
{
	const struct bpf_func_proto *func_proto;
	struct bpf_line_info li;
	int err;

	err = bpf_find_line_info(prog, insn, NULL, &li);
	if (err) {
		func_proto = (void *)&bpf_unknown_tp_proto;
		goto out;
	}

	err = bpf_find_func_info(prog, &li, NULL, NULL, NULL);
	bpf_prog_put(li.func_info);
	if (err) {
		func_proto = (void *)&bpf_unknown_tp_proto;
		goto out;
	}

	func_proto = li.func_proto;
out:
	return func_proto;
}