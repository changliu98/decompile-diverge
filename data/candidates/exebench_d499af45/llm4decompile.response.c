void validate_rt_entry(struct rt_entry *rt)
{
	rt->rt_flags &= ~0x0020;
	rt->rt_flags &= ~0x0040;
	rt->rt_flags &= ~0x0080;
	rt->rt_flags |= 0x0001;
	rt->rt_flags |= 0x0002;
}