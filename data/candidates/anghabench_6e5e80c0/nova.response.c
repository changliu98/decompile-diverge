static inline struct adjust_stack_addr *adjust_stack_addr(struct adjust_stack_addr *p, unsigned int i)
{
	return (struct adjust_stack_addr *)((char *)p + i * sizeof(struct adjust_stack_addr));
}