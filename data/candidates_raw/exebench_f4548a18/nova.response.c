static int func0(struct bpf_test *self)
{
	self->ret++;
	return -5;
}