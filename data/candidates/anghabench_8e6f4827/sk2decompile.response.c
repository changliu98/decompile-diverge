static const char *mptcp_sopt2str(int level, int optname) {
  const char *str;
  if (level == 0xad) {
    switch (optname) {
      case 0x89:
        str = "SO_USELOOPBACK";
        break;
      case 0x8a:
        str = "SO_TYPE";
        break;
      case 0x8b:
        str = "SO_TRAFFIC_CLASS_DBG";
        break;
      case 0x8c:
        str = "SO_TRAFFIC_CLASS";
        break;
      case 0x8d:
        str = "SO_SNDTIMEO";
        break;
      case 0x8e:
        str = "SO_SNDLOWAT";
        break;
      case 0x8f:
        str = "SO_SNDBUF";
        break;
      case 0x90:
        str = "SO_RESTRICTIONS";
        break;
      case 0x91:
        str = "SO_RECV_TRAFFIC_CLASS";
        break;
      case 0x92:
        str = "SO_RECV_ANYIF";
        break;
      case 0x93:
        str = "SO_RCVTIMEO";
        break;
      case 0x94:
        str = "SO_RCVLOWAT";
        break;
      case 0x95:
        str = "SO_RCVBUF";
        break;
      case 0x96:
        str = "SO_RANDOMPORT";
        break;
      case 0x97:
        str = "SO_PRIVILEGED_TRAFFIC_CLASS";
        break;
      case 0x98:
        str = "SO_PEERLABEL";
        break;
      case 0x99:
        str = "SO_OPPORTUNISTIC";
        break;
      case 0x9a:
        str = "SO_NWRITE";
        break;
      case 0x9b:
        str = "SO_NREAD";
        break;
      case 0x9c:
        str = "SO_NOWAKEFROMSLEEP";
        break;
      case 0x9d:
        str = "SO_NOSIGPIPE";
        break;
      case 0x9e:
        str = "SO_NOAPNFALLBK";
        break;
      case 0x9f:
        str = "SO_NOADDRERR";
        break;
      case 0xa0:
        str = "SO_NKE";
        break;
      case 0xa1:
        str = "SO_CELLFALLBACK";
        break;
      case 0xa2:
        str = "SO_LINGER_SEC";
        break;
      case 0xa3:
        str = "SO_LINGER";
        break;
      case 0xa4:
        str = "SO_LABEL";
        break;
      case 0xa5:
        str = "SO_KEEPALIVE";
        break;
      case 0xa6:
        str = "SO_ISDEFUNCT";
        break;
      case 0xa7:
        str = "SO_FLUSH";
        break;
      case 0xa8:
        str = "SO_ERROR";
        break;
      case 0xa9:
        str = "SO_DELEGATED_UUID";
        break;
      case 0xaa:
        str = "SO_DELEGATED";
        break;
      case 0xab:
        str = "SO_DEFUNCTOK";
        break;
      case 0xac:
        str = "SO_DEBUG";
        break;
      default:
        str = "unknown";
        break;
    }
  } else if (level == 0xb1) {
    switch (optname) {
      case 0x80:
        str = "TCP_RXT_CONNDROPTIME";
        break;
      case 0x81:
        str = "NOTSENT_LOWAT";
        break;
      case 0x82:
        str = "TCP_NODELAY";
        break;
      case 0x83:
        str = "TCP_KEEPINTVL";
        break;
      case 0x84:
        str = "TCP_KEEPCNT";
        break;
      case 0x85:
        str = "TCP_KEEPALIVE";
        break;
      case 0x86:
        str = "TCP_CONNECTIONTIMEOUT";
        break;
      case 0x87:
        str = "ADAPTIVE_WRITE_TIMEOUT";
        break;
      case 0x88:
        str = "ADAPTIVE_READ_TIMEOUT";
        break;
      case 0xb2:
        str = "PERSIST_TIMEOUT";
        break;
      case 0xb3:
        str = "MPTCP_SERVICE_TYPE";
        break;
      case 0xb4:
        str = "MPTCP_ALTERNATE_PORT";
        break;
      default:
        str = "unknown";
        break;
    }
  } else {
    str = "unknown";
  }
  return str;
}