static void passByPointer(struct pci_dev *dev)
{
	dev->class &= 0xffff;
	dev->class <<= 2;
}