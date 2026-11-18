__attribute__((used)) static int xen_pcibios_err_to_errno(int err)
{
	int ret;

	switch (err) {
	case XEN_PCI_ERR_success:
		ret = XEN_PCI_ERR_success;
		break;
	case XEN_PCI_ERR_dev_not_found:
		ret = XEN_PCI_ERR_dev_not_found;
		break;
	case XEN_PCI_ERR_invalid_offset:
		ret = XEN_PCI_ERR_invalid_offset;
		break;
	case XEN_PCI_ERR_not_implemented:
		ret = XEN_PCI_ERR_not_implemented;
		break;
	case XEN_PCI_ERR_access_denied:
		ret = XEN_PCI_ERR_access_denied;
		break;
	default:
		ret = err;
	}

	return ret;
}