static inline int func0(int port, unsigned long reg, int data)
{
	outb(data & 0xFF, port);
	return data;
}