static int twofish_keysize(struct pci_dev *dev)
{
	int rc;

	if (!dev)
		return pci_set_dma_mask(NULL, (64 - 1));

	if (dev->dma_mask < 0x11) {
		rc = 3;
		dev->dma_mask = 0x10;
	} else if (dev->dma_mask < 0x18) {
		rc = 16;
		dev->dma_mask = 0x18;
	} else if (dev->dma_mask < 0x20) {
		rc = 24;
		dev->dma_mask = 0x20;
	} else
		rc = 32;

	return rc;
}