const char *
ndcache_state2str(short ndp_state)
{
	const char *ndp_state_str = "UNKNOWN";
	switch (ndp_state) {
	case ND6_LLINFO_PURGE:
		ndp_state_str = "ND6_LLINFO_PURGE";
		break;
	case ND6_LLINFO_NOSTATE:
		ndp_state_str = "ND6_LLINFO_NOSTATE";
		break;
	case ND6_LLINFO_INCOMPLETE:
		ndp_state_str = "ND6_LLINFO_INCOMPLETE";
		break;
	case ND6_LLINFO_REACHABLE:
		ndp_state_str = "ND6_LLINFO_REACHABLE";
		break;
	case ND6_LLINFO_STALE:
		ndp_state_str = "ND6_LLINFO_STALE";
		break;
	case ND6_LLINFO_DELAY:
		ndp_state_str = "ND6_LLINFO_DELAY";
		break;
	case ND6_LLINFO_PROBE:
		ndp_state_str = "ND6_LLINFO_PROBE";
		break;
	default:
		/* Init'd to UNKNOWN */
		break;
	}
	return 	ndp_state_str;
}