int xen_pci_err(int err)
{
    int ret;
    switch (err) {
    case 128:
        ret = XEN_PCI_ERR_success;
        break;
    case 129:
        ret = XEN_PCI_ERR_access_denied;
        break;
    case 130:
        ret = XEN_PCI_ERR_not_implemented;
        break;
    case 131:
        ret = XEN_PCI_ERR_dev_not_found;
        break;
    case 132:
        ret = XEN_PCI_ERR_invalid_offset;
        break;
    default:
        ret = err;
        break;
    }
    return ret;
}