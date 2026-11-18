static void func0(struct pci_dev *dev)
{
	unsigned short vendor;

	vendor = 0xffff;
	dev->vendor = vendor;
}