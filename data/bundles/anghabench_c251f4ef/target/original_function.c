char *hcfs2string(int state)
{
	switch (state) {
	case OHCI_USB_RESET:
		return "reset";
	case OHCI_USB_RESUME:
		return "resume";
	case OHCI_USB_OPER:
		return "operational";
	case OHCI_USB_SUSPEND:
		return "suspend";
	}
	return "?";
}