const char *
mptcp_event_to_str(uint32_t event)
{
	const char *c = "UNDEFINED";
	switch (event) {
	case MPCE_CLOSE:
		c = "MPCE_CLOSE";
		break;
	case MPCE_RECV_DATA_ACK:
		c = "MPCE_RECV_DATA_ACK";
		break;
	case MPCE_RECV_DATA_FIN:
		c = "MPCE_RECV_DATA_FIN";
		break;
	}
	return (c);
}