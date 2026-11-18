static void enable(struct pci_dev *dev)
{
	dev->no_msi = 1;
}