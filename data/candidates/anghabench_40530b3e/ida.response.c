int __cdecl xen_pcibios_err_to_errno(int err)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( err )
  {
    case 128:
      v2 = XEN_PCI_ERR_success;
      break;
    case 129:
      v2 = XEN_PCI_ERR_access_denied;
      break;
    case 130:
      v2 = XEN_PCI_ERR_not_implemented;
      break;
    case 131:
      v2 = XEN_PCI_ERR_dev_not_found;
      break;
    case 132:
      v2 = XEN_PCI_ERR_invalid_offset;
      break;
    default:
      v2 = err;
      break;
  }
  return v2;
}