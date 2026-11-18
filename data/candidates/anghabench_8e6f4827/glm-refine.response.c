const char *__cdecl mptcp_sopt2str(int level, int optname)
{
  if (level == 173)
  {
    switch (optname)
    {
      case 137: return "SO_USELOOPBACK";
      case 138: return "SO_TYPE";
      case 139: return "SO_TRAFFIC_CLASS_DBG";
      case 140: return "SO_TRAFFIC_CLASS";
      case 141: return "SO_SNDTIMEO";
      case 142: return "SO_SNDLOWAT";
      case 143: return "SO_SNDBUF";
      case 144: return "SO_RESTRICTIONS";
      case 145: return "SO_RECV_TRAFFIC_CLASS";
      case 146: return "SO_RECV_ANYIF";
      case 147: return "SO_RCVTIMEO";
      case 148: return "SO_RCVLOWAT";
      case 149: return "SO_RCVBUF";
      case 150: return "SO_RANDOMPORT";
      case 151: return "SO_PRIVILEGED_TRAFFIC_CLASS";
      case 152: return "SO_PEERLABEL";
      case 153: return "SO_OPPORTUNISTIC";
      case 154: return "SO_NWRITE";
      case 155: return "SO_NREAD";
      case 156: return "SO_NOWAKEFROMSLEEP";
      case 157: return "SO_NOSIGPIPE";
      case 158: return "SO_NOAPNFALLBK";
      case 159: return "SO_NOADDRERR";
      case 160: return "SO_NKE";
      case 161: return "SO_CELLFALLBACK";
      case 162: return "SO_LINGER_SEC";
      case 163: return "SO_LINGER";
      case 164: return "SO_LABEL";
      case 165: return "SO_KEEPALIVE";
      case 166: return "SO_ISDEFUNCT";
      case 167: return "SO_FLUSH";
      case 168: return "SO_ERROR";
      case 169: return "SO_DELEGATED_UUID";
      case 170: return "SO_DELEGATED";
      case 171: return "SO_DEFUNCTOK";
      case 172: return "SO_DEBUG";
      default:  return "unknown";
    }
  }
  else if (level == 177)
  {
    switch (optname)
    {
      case 128: return "TCP_RXT_CONNDROPTIME";
      case 129: return "NOTSENT_LOWAT";
      case 130: return "TCP_NODELAY";
      case 131: return "TCP_KEEPINTVL";
      case 132: return "TCP_KEEPCNT";
      case 133: return "TCP_KEEPALIVE";
      case 134: return "TCP_CONNECTIONTIMEOUT";
      case 135: return "ADAPTIVE_WRITE_TIMEOUT";
      case 136: return "ADAPTIVE_READ_TIMEOUT";
      case 174: return "PERSIST_TIMEOUT";
      case 175: return "MPTCP_SERVICE_TYPE";
      case 176: return "MPTCP_ALTERNATE_PORT";
      default:  return "unknown";
    }
  }
  
  return "unknown";
}