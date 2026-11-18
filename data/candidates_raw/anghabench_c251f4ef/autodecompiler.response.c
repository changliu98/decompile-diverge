__attribute__((used)) static inline char *hcfs2string(int hcfs_state)
{
	char *s;

	switch (hcfs_state) {
	case OHCI_HCF_RESET:
		s = "reset";
		break;
	case OHCI_HCF_RESUME:
		s = "resume";
		break;
	case OHCI_HCF_OPER:
		s = "operational";
		break;
	case OHCI_HCF_SUSPEND:
		s = "suspend";
		break;
	default:
		s = "?";
	}

	return s;
}