const char *
mptcp_sopt2str(int level, int optname)
{
	switch (level) {
	case SOL_SOCKET:
		switch (optname) {
		case SO_LINGER:
			return ("SO_LINGER");
		case SO_LINGER_SEC:
			return ("SO_LINGER_SEC");
		case SO_DEBUG:
			return ("SO_DEBUG");
		case SO_KEEPALIVE:
			return ("SO_KEEPALIVE");
		case SO_USELOOPBACK:
			return ("SO_USELOOPBACK");
		case SO_TYPE:
			return ("SO_TYPE");
		case SO_NREAD:
			return ("SO_NREAD");
		case SO_NWRITE:
			return ("SO_NWRITE");
		case SO_ERROR:
			return ("SO_ERROR");
		case SO_SNDBUF:
			return ("SO_SNDBUF");
		case SO_RCVBUF:
			return ("SO_RCVBUF");
		case SO_SNDLOWAT:
			return ("SO_SNDLOWAT");
		case SO_RCVLOWAT:
			return ("SO_RCVLOWAT");
		case SO_SNDTIMEO:
			return ("SO_SNDTIMEO");
		case SO_RCVTIMEO:
			return ("SO_RCVTIMEO");
		case SO_NKE:
			return ("SO_NKE");
		case SO_NOSIGPIPE:
			return ("SO_NOSIGPIPE");
		case SO_NOADDRERR:
			return ("SO_NOADDRERR");
		case SO_RESTRICTIONS:
			return ("SO_RESTRICTIONS");
		case SO_LABEL:
			return ("SO_LABEL");
		case SO_PEERLABEL:
			return ("SO_PEERLABEL");
		case SO_RANDOMPORT:
			return ("SO_RANDOMPORT");
		case SO_TRAFFIC_CLASS:
			return ("SO_TRAFFIC_CLASS");
		case SO_RECV_TRAFFIC_CLASS:
			return ("SO_RECV_TRAFFIC_CLASS");
		case SO_TRAFFIC_CLASS_DBG:
			return ("SO_TRAFFIC_CLASS_DBG");
		case SO_PRIVILEGED_TRAFFIC_CLASS:
			return ("SO_PRIVILEGED_TRAFFIC_CLASS");
		case SO_DEFUNCTOK:
			return ("SO_DEFUNCTOK");
		case SO_ISDEFUNCT:
			return ("SO_ISDEFUNCT");
		case SO_OPPORTUNISTIC:
			return ("SO_OPPORTUNISTIC");
		case SO_FLUSH:
			return ("SO_FLUSH");
		case SO_RECV_ANYIF:
			return ("SO_RECV_ANYIF");
		case SO_NOWAKEFROMSLEEP:
			return ("SO_NOWAKEFROMSLEEP");
		case SO_NOAPNFALLBK:
			return ("SO_NOAPNFALLBK");
		case SO_MARK_CELLFALLBACK:
			return ("SO_CELLFALLBACK");
		case SO_DELEGATED:
			return ("SO_DELEGATED");
		case SO_DELEGATED_UUID:
			return ("SO_DELEGATED_UUID");
#if NECP
		case SO_NECP_ATTRIBUTES:
			return ("SO_NECP_ATTRIBUTES");
		case SO_NECP_CLIENTUUID:
			return ("SO_NECP_CLIENTUUID");
#endif /* NECP */
		}

		break;
	case IPPROTO_TCP:
		switch (optname) {
		case TCP_NODELAY:
			return ("TCP_NODELAY");
		case TCP_KEEPALIVE:
			return ("TCP_KEEPALIVE");
		case TCP_KEEPINTVL:
			return ("TCP_KEEPINTVL");
		case TCP_KEEPCNT:
			return ("TCP_KEEPCNT");
		case TCP_CONNECTIONTIMEOUT:
			return ("TCP_CONNECTIONTIMEOUT");
		case TCP_RXT_CONNDROPTIME:
			return ("TCP_RXT_CONNDROPTIME");
		case PERSIST_TIMEOUT:
			return ("PERSIST_TIMEOUT");
		case TCP_NOTSENT_LOWAT:
			return ("NOTSENT_LOWAT");
		case TCP_ADAPTIVE_READ_TIMEOUT:
			return ("ADAPTIVE_READ_TIMEOUT");
		case TCP_ADAPTIVE_WRITE_TIMEOUT:
			return ("ADAPTIVE_WRITE_TIMEOUT");
		case MPTCP_SERVICE_TYPE:
			return ("MPTCP_SERVICE_TYPE");
		case MPTCP_ALTERNATE_PORT:
			return ("MPTCP_ALTERNATE_PORT");
		}

		break;
	}

	return ("unknown");
}