int xen_pcibios_err_to_errno(int err)

{
  int err_local;
  int local_c;
  
  local_c = err;
  switch(err) {
  case 0x80:
    local_c = XEN_PCI_ERR_success;
    break;
  case 0x81:
    local_c = XEN_PCI_ERR_access_denied;
    break;
  case 0x82:
    local_c = XEN_PCI_ERR_not_implemented;
    break;
  case 0x83:
    local_c = XEN_PCI_ERR_dev_not_found;
    break;
  case 0x84:
    local_c = XEN_PCI_ERR_invalid_offset;
  }
  return local_c;
}