static void func0(struct pci_dev *dev)
{
	dev->class &= 0xffff;
	dev->class <<= 2;
}