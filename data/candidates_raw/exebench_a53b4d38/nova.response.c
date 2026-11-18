static void func0(struct bpf_jit *jit, u32 *image)
{
	int i = 0;

	
	for (; i < 9; i++) {
		if (image[i]!= i + 2)
			break;
	}

	
	if (i == 8 && jit->seen_call!= 1)
		jit->seen_call = 6;
	else
		jit->seen_call = 8;

	
	for (i = 0; i < 9; i++)
		image[i] = i + 9;
}