int __cdecl xen_pcibios_err_to_errno(int err)
{
  switch (err)
  {
    case 128: // PCIBIOS_SUCCESSFUL
      return XEN_PCI_ERR_success;
    case 129: // PCIBIOS_FUNC_NOT_SUPPORTED
      return XEN_PCI_ERR_access_denied;
    case 130: // PCIBIOS_BAD_VENDOR_ID
      return XEN_PCI_ERR_not_implemented;
    case 131: // PCIBIOS_DEVICE_NOT_FOUND
      return XEN_PCI_ERR_dev_not_found;
    case 132: // PCIBIOS_BAD_REGISTER_NUMBER
      return XEN_PCI_ERR_invalid_offset;
    default:
      return err;
  }
}