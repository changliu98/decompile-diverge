char * mptcp_sopt2str(int level,int optname)

{
  int optname_local;
  int level_local;
  char *local_10;
  
  if (level == 0xad) {
    switch(optname) {
    case 0x89:
      local_10 = "SO_USELOOPBACK";
      return local_10;
    case 0x8a:
      local_10 = "SO_TYPE";
      return local_10;
    case 0x8b:
      local_10 = "SO_TRAFFIC_CLASS_DBG";
      return local_10;
    case 0x8c:
      local_10 = "SO_TRAFFIC_CLASS";
      return local_10;
    case 0x8d:
      local_10 = "SO_SNDTIMEO";
      return local_10;
    case 0x8e:
      local_10 = "SO_SNDLOWAT";
      return local_10;
    case 0x8f:
      local_10 = "SO_SNDBUF";
      return local_10;
    case 0x90:
      local_10 = "SO_RESTRICTIONS";
      return local_10;
    case 0x91:
      local_10 = "SO_RECV_TRAFFIC_CLASS";
      return local_10;
    case 0x92:
      local_10 = "SO_RECV_ANYIF";
      return local_10;
    case 0x93:
      local_10 = "SO_RCVTIMEO";
      return local_10;
    case 0x94:
      local_10 = "SO_RCVLOWAT";
      return local_10;
    case 0x95:
      local_10 = "SO_RCVBUF";
      return local_10;
    case 0x96:
      local_10 = "SO_RANDOMPORT";
      return local_10;
    case 0x97:
      local_10 = "SO_PRIVILEGED_TRAFFIC_CLASS";
      return local_10;
    case 0x98:
      local_10 = "SO_PEERLABEL";
      return local_10;
    case 0x99:
      local_10 = "SO_OPPORTUNISTIC";
      return local_10;
    case 0x9a:
      local_10 = "SO_NWRITE";
      return local_10;
    case 0x9b:
      local_10 = "SO_NREAD";
      return local_10;
    case 0x9c:
      local_10 = "SO_NOWAKEFROMSLEEP";
      return local_10;
    case 0x9d:
      local_10 = "SO_NOSIGPIPE";
      return local_10;
    case 0x9e:
      local_10 = "SO_NOAPNFALLBK";
      return local_10;
    case 0x9f:
      local_10 = "SO_NOADDRERR";
      return local_10;
    case 0xa0:
      local_10 = "SO_NKE";
      return local_10;
    case 0xa1:
      local_10 = "SO_CELLFALLBACK";
      return local_10;
    case 0xa2:
      local_10 = "SO_LINGER_SEC";
      return local_10;
    case 0xa3:
      local_10 = "SO_LINGER";
      return local_10;
    case 0xa4:
      local_10 = "SO_LABEL";
      return local_10;
    case 0xa5:
      local_10 = "SO_KEEPALIVE";
      return local_10;
    case 0xa6:
      local_10 = "SO_ISDEFUNCT";
      return local_10;
    case 0xa7:
      local_10 = "SO_FLUSH";
      return local_10;
    case 0xa8:
      local_10 = "SO_ERROR";
      return local_10;
    case 0xa9:
      local_10 = "SO_DELEGATED_UUID";
      return local_10;
    case 0xaa:
      local_10 = "SO_DELEGATED";
      return local_10;
    case 0xab:
      local_10 = "SO_DEFUNCTOK";
      return local_10;
    case 0xac:
      local_10 = "SO_DEBUG";
      return local_10;
    }
  }
  else if (level == 0xb1) {
    switch(optname) {
    case 0x80:
      local_10 = "TCP_RXT_CONNDROPTIME";
      return local_10;
    case 0x81:
      local_10 = "NOTSENT_LOWAT";
      return local_10;
    case 0x82:
      local_10 = "TCP_NODELAY";
      return local_10;
    case 0x83:
      local_10 = "TCP_KEEPINTVL";
      return local_10;
    case 0x84:
      local_10 = "TCP_KEEPCNT";
      return local_10;
    case 0x85:
      local_10 = "TCP_KEEPALIVE";
      return local_10;
    case 0x86:
      local_10 = "TCP_CONNECTIONTIMEOUT";
      return local_10;
    case 0x87:
      local_10 = "ADAPTIVE_WRITE_TIMEOUT";
      return local_10;
    case 0x88:
      local_10 = "ADAPTIVE_READ_TIMEOUT";
      return local_10;
    default:
      break;
    case 0xae:
      local_10 = "PERSIST_TIMEOUT";
      return local_10;
    case 0xaf:
      local_10 = "MPTCP_SERVICE_TYPE";
      return local_10;
    case 0xb0:
      local_10 = "MPTCP_ALTERNATE_PORT";
      return local_10;
    }
  }
  local_10 = "unknown";
  return local_10;
}