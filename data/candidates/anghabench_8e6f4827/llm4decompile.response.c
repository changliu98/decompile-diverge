const char *
mptcp_sopt2str(int level, int optname)
{
	const char *c;

	switch (level) {
	case IPPROTO_TCP:
		switch (optname) {
		case TCP_NODELAY:
			c = "TCP_NODELAY";
			break;
		case TCP_MAXSEG:
			c = "TCP_MAXSEG";
			break;
		case TCP_KEEPINTVL:
			c = "TCP_KEEPINTVL";
			break;
		case TCP_KEEPCNT:
			c = "TCP_KEEPCNT";
			break;
		case TCP_KEEPALIVE:
			c = "TCP_KEEPALIVE";
			break;
		case TCP_CONNECTIONTIMEOUT:
			c = "TCP_CONNECTIONTIMEOUT";
			break;
		case ADAPTIVE_READ_TIMEOUT:
			c = "ADAPTIVE_READ_TIMEOUT";
			break;
		case ADAPTIVE_WRITE_TIMEOUT:
			c = "ADAPTIVE_WRITE_TIMEOUT";
			break;
		case PERSIST_TIMEOUT:
			c = "PERSIST_TIMEOUT";
			break;
		case NOTSENT_LOWAT:
			c = "NOTSENT_LOWAT";
			break;
		case TCP_RXT_CONNDROPTIME:
			c = "TCP_RXT_CONNDROPTIME";
			break;
		default:
			c = "unknown";
			break;
		}
		break;
	case IPPROTO_MPTCP:
		switch (optname) {
		case MPTCP_ALTERNATE_PORT:
			c = "MPTCP_ALTERNATE_PORT";
			break;
		case MPTCP_SERVICE_TYPE:
			c = "MPTCP_SERVICE_TYPE";
			break;
		default:
			c = "unknown";
			break;
		}
		break;
	case 173:
		switch (optname) {
		case 138:
			c = "SO_DEBUG";
			break;
		case 139:
			c = "SO_DEFUNCTOK";
			break;
		case 140:
			c = "SO_DELEGATED";
			break;
		case 141:
			c = "SO_DELEGATED_UUID";
			break;
		case 142:
			c = "SO_ERROR";
			break;
		case 143:
			c = "SO_FLUSH";
			break;
		case 144:
			c = "SO_ISDEFUNCT";
			break;
		case 145:
			c = "SO_KEEPALIVE";
			break;
		case 146:
			c = "SO_LABEL";
			break;
		case 147:
			c = "SO_LINGER";
			break;
		case 148:
			c = "SO_LINGER_SEC";
			break;
		case 149:
			c = "SO_CELLFALLBACK";
			break;
		case 150:
			c = "SO_NKE";
			break;
		case 151:
			c = "SO_NOADDRERR";
			break;
		case 152:
			c = "SO_NOAPNFALLBK";
			break;
		case 153:
			c = "SO_NOSIGPIPE";
			break;
		case 154:
			c = "SO_NOWAKEFROMSLEEP";
			break;
		case 155:
			c = "SO_NREAD";
			break;
		case 156:
			c = "SO_NWRITE";
			break;
		case 157:
			c = "SO_OPPORTUNISTIC";
			break;
		case 158:
			c = "SO_PEERLABEL";
			break;
		case 159:
			c = "SO_PRIVILEGED_TRAFFIC_CLASS";
			break;
		case 160:
			c = "SO_RANDOMPORT";
			break;
		case 161:
			c = "SO_RCVBUF";
			break;
		case 162:
			c = "SO_RCVLOWAT";
			break;
		case 163:
			c = "SO_RCVTIMEO";
			break;
		case 164:
			c = "SO_RECV_ANYIF";
			break;
		case 165:
			c = "SO_RECV_TRAFFIC_CLASS";
			break;
		case 166:
			c = "SO_RESTRICTIONS";
			break;
		case 167:
			c = "SO_SNDBUF";
			break;
		case 168:
			c = "SO_SNDLOWAT";
			break;
		case 169:
			c = "SO_SNDTIMEO";
			break;
		case 170:
			c = "SO_TRAFFIC_CLASS";
			break;
		case 171:
			c = "SO_TRAFFIC_CLASS_DBG";
			break;
		case 172:
			c = "SO_TYPE";
			break;
		case 173:
			c = "SO_USELOOPBACK";
			break;
		default:
			c = "unknown";
			break;
		}
		break;
	default:
		c = "unknown";
		break;
	}
	return (c);
}