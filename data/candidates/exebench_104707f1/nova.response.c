static void set_autofs_type_offset(struct pci_dev *dev)
{
	dev->dma_mask = 0x0000ffff;
}