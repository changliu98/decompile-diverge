static void func0(struct pci_dev *dev)
{
	dev->class &= 0xfffffff0;
	dev->class |= 0x00000001;
}