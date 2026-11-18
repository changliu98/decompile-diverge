void nm_writel(u32 data, void *addr)
{
	*(volatile u32 *)addr = data;
}