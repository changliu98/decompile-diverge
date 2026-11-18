static struct bpf_prog *func0(u32 ufd, bool post_send, int flags)
{
	struct bpf_prog *prog;

	if (!post_send)
		prog = &bpf_fail_prog.prog;
	else
		prog = &bpf_pass_prog.prog;

	return prog;
}