static void func0(struct pci_dev *dev)
{
	unsigned int bus_no;

	if (dev->bus->number == 1) {
		if (dev->devfn == 7 || dev->devfn == 8) {
			dev->resource[2].start = 0x01C00000;
			dev->resource[2].end = 0x01C00000;
		} else {
			bus_no = PCI_SLOT(dev->devfn);
			if (bus_no == 0) {
				dev->resource[2].start = 0x01C00000;
				dev->resource[2].end = 0x01C00000;
			} else if (bus_no == 1) {
				dev->resource[2].start = 0x01800000;
				dev->resource[2].end = 0x01800000;
			}
		}
	} else {
		bus_no = PCI_SLOT(dev->devfn);
		if (bus_no == 0) {
			dev->resource[2].start = 0x01C00000;
			dev->resource[2].end = 0x01C00000;
		} else if (bus_no == 1) {
			dev->resource[2].start = 0x01800000;
			dev->resource[2].end = 0x01800000;
		}
	}
}