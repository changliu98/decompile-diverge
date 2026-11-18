static const char *mptcp_event_to_str(int state)
{
	const char *cp;

	cp = "unknown";
	switch (state) {
	case SPA_STATE_ACTIVE:
		cp = "active";
		break;
	case SPA_STATE_REMOVE:
		cp = "removing";
		break;
	case SPA_STATE_OFFLINE:
		cp = "offline";
		break;
	}
	return (cp);
}