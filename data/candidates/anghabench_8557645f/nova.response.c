static const struct bpf_func_proto *
ata_err_string(u32 config)
{
	const struct bpf_func_proto *table;

	if (config & BPF_FUNC_FLAG_PER_CPU)
		table = &bpf_per_cpu_func_proto;
	else if (config & BPF_FUNC_FLAG_RDONLY_MEM)
		table = &bpf_readonly_mem_func_proto;
	else if (config & BPF_FUNC_FLAG_WRONLY_MEM)
		table = &bpf_writeonly_mem_func_proto;
	else if (config & BPF_FUNC_FLAG_RDONLY_ARG)
		table = &bpf_readonly_arg_func_proto;
	else if (config & BPF_FUNC_FLAG_WRONLY_ARG)
		table = &bpf_writeonly_arg_func_proto;
	else if (config & BPF_FUNC_FLAG_RDONLY_ARG_NO_ALLOC)
		table = &bpf_readonly_arg_no_alloc_func_proto;
	else if (config & BPF_FUNC_FLAG_WRONLY_ARG_NO_ALLOC)
		table = &bpf_writeonly_arg_no_alloc_func_proto;
	else if (config & BPF_FUNC_FLAG_RDONLY_ARG_ALLOC)
		table = &bpf_readonly_arg_alloc_func_proto;
	else if (config & BPF_FUNC_FLAG_WRONLY_ARG_ALLOC)
		table = &bpf_writeonly_arg_alloc_func_proto;
	else if (config & BPF_FUNC_FLAG_RDONLY_ARG_ALLOC_NO_ALLOC)
		table = &bpf_readonly_arg_alloc_no_alloc_func_proto;
	else if (config & BPF_FUNC_FLAG_WRONLY_ARG_ALLOC_NO_ALLOC)
		table = &bpf_writeonly_arg_alloc_