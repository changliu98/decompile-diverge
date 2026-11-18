int
prot2perm(int prot)
{
	int perm = 0;

	if (prot & 0x1)
		perm |= 0x4;
	if (prot & 0x2)
		perm |= 0x2;
	if (prot & 0x4)
		perm |= 0x1;
	return (perm);
}