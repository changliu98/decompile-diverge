static int xen_pcibios_err_to_errno(int err) {
  int ret;
  switch (err) {
    case XEN_PCIBIOS_SUCCESS:
      ret = PCIBIOS_SUCCESSFUL;
      break;
    case XEN_PCIBIOS_DEVICE_NOT_FOUND:
      ret = PCIBIOS_DEVICE_NOT_FOUND;
      break;
    case XEN_PCIBIOS_BAD_REGISTER_NUMBER:
      ret = PCIBIOS_BAD_REGISTAR;
      break;
    case XEN_PCIBIOS_FUNC_NOT_SUPPORTED:
      ret = PCIBIOS_FUNC_NOT_SUPPORTED;
      break;
    case XEN_PCIBIOS_BAD_VENDOR_ID:
      ret = PCIBIOS_VENDOR_NOT_FOUND;
      break;
    default:
      ret = err;
      break;
  }
  return ret;
}