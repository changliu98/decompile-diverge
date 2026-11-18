static void func0(struct cpuinfo_x86 *c)
{
	c->x86_model = c->x86_model - 0x80;
}