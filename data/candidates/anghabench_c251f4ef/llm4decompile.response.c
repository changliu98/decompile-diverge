const char *hcfs2string(int state)
{
	const char *s;
	switch (state) {
	case HCFS_STATE_OPERATIONAL:
		s = "operational";
		break;
	case HCFS_STATE_SUSPEND:
		s = "suspend";
		break;
	case HCFS_STATE_RESUME:
		s = "resume";
		break;
	case HCFS_STATE_RESET:
		s = "reset";
		break;
	default:
		s = "?";
		break;
	}
	return s;
}