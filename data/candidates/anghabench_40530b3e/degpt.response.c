/*
 * xen_pcibios_err_to_errno - Convert Xen PCI error codes to standard errno values.
 *
 * @err: The Xen PCI error code to convert.
 *
 * This function maps specific Xen PCI error codes (0x80-0x84) to their
 * corresponding XEN_PCI_ERR_* constants. For any other error code, it
 * returns the original value unchanged.
 *
 * Return: The converted error code or the original error code if not mapped.
 */
int xen_pcibios_err_to_errno(int xen_err_code)
{
	switch (xen_err_code) {
	case 0x80:
		/* Success */
		return XEN_PCI_ERR_success;
	case 0x81:
		/* Access denied */
		return XEN_PCI_ERR_access_denied;
	case 0x82:
		/* Not implemented */
		return XEN_PCI_ERR_not_implemented;
	case 0x83:
		/* Device not found */
		return XEN_PCI_ERR_dev_not_found;
	case 0x84:
		/* Invalid offset */
		return XEN_PCI_ERR_invalid_offset;
	default:
		/* Unmapped error code, return as-is */
		return xen_err_code;
	}
}