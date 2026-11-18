int xen_pcibios_err_to_errno(int err)
{
	switch (err) {
	case PCIBIOS_MIN_IORESOURCE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_SUCCESS:
		err = XEN_PCI_ERR_success;
		break;
	case PCIBIOS_MIN_MEMORY:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_PORT:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_IRQ:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_DMA:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_IO:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IRQ:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_DMA:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IORESOURCE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_PORT:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_PREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_NONPREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_NONPREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_PREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO_EXPANSION_NONPREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO_EXPANSION_PREFETCHABLE:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO_EXPANSION_PREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_IO_EXPANSION_NONPREFETCHABLE_EXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_PREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_MIN_CARDBUS_MEMORY_EXPANSION_NONPREFETCHABLE_NONEXPANSION:
		err = XEN_PCI_ERR_not_implemented;
		break;
	case PCIBIOS_