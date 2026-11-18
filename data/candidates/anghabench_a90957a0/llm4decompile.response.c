const char *
mptcp_event_to_str(uint32_t event)
{
	const char *str = "UNDEFINED";
	switch (event) {
	case MPCE_RECV_DATA_ACK:
		str = "MPCE_RECV_DATA_ACK";
		break;
	case MPCE_RECV_DATA_FIN:
		str = "MPCE_RECV_DATA_FIN";
		break;
	case MPCE_CLOSE:
		str = "MPCE_CLOSE";
		break;
	}
	return (str);
}