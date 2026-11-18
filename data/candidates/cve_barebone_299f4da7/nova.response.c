static void handle_mlppp(struct bpf_verifier_env *env,
			   struct nfp_insn_meta *meta, int idx)
{
	struct nfp_insn_meta *prev;
	unsigned int off;

	if (!env->insn_aux_data)
		snprintf(env->err_msg, sizeof(env->err_msg),
			 "invalid jump at the end of program");

	prev = &env->prog->aux->insn_meta[0];
	off = (unsigned int)((u8 *)meta - (u8 *)prev);

	snprintf(env->err_msg, sizeof(env->err_msg),
		 "invalid jump at byte offset %d (%02x): %s",
		 off, meta->insn.code & 0xff, bpf_op(meta->insn.code));
}