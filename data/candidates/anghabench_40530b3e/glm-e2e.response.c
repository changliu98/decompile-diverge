int xen_pcibios_err_to_errno(int err) {
    int ret;
    
    // Check if err is between 0 and 4 (inclusive)
    // The assembly does: err - 0x80, then subtracts 4 and checks if it's above 0 (unsigned)
    // This is equivalent to checking if (err - 0x80) is in the range [0, 4]
    if ((unsigned int)(err - 0x80) <= 4) {
        switch (err) {
            case 0x80:
                ret = XEN_PCI_ERR_success;
                break;
            case 0x81:
                ret = XEN_PCI_ERR_dev_not_found;
                break;
            case 0x82:
                ret = XEN_PCI_ERR_invalid_offset;
                break;
            case 0x83:
                ret = XEN_PCI_ERR_not_implemented;
                break;
            case 0x84:
                ret = XEN_PCI_ERR_access_denied;
                break;
        }
    } else {
        ret = err;
    }
    
    return ret;
}