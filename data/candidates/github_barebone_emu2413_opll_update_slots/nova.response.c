static void update_slots(struct pci_dev *dev)
{
	int i;
	struct resource *r;
	struct resource *res = NULL;

	dev->resource_alignment++;
	for (i = 0; i < 19; i++) {
		r = &dev->resource[i];
		if (!r->parent)
			res = r;
		if (r->flags == 1)
			res = &dev->resource[i-1];
		if (r->sibling)
			pci_claim_resource(r);
		pci_adjust_resource(r, res, (unsigned short)dev->resource_alignment,
				    (dev->devfn & 1)!= 0, (dev->devfn & 4)!= 0);
		pci_assign_resource_flags(r, dev->irq, (dev->devfn & 4)!= 0);
	}
}