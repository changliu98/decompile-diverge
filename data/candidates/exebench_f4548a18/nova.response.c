static int increase_1(struct bpf_test *self)
{
	self->ret++;
	return -5;
}