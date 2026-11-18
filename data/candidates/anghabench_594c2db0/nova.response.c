static inline int REG_A5XX_RB_MRT_BUF_INFO(int irq)
{
	return 0x1402 + irq * 7;
}