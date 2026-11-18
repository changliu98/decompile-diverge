static void triggers_bug(void *header)
{
	*(u32 *)header = 0xdeadbeef;
}