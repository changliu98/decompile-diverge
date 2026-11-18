char *
ctl2str3(int level, int ctl)
{
 char *str;

 switch (level) {
 case SOL_SOCKET:
  switch (ctl) {
  case SO_LINGER:
   str = "SO_LINGER";
   break;
  case SO_LINGER_SEC:
   str = "SO_LINGER_SEC";
   break;
  case SO_DEBUG:
   str = "SO_DEBUG";
   break;
  case SO_KEEPALIVE:
   str = "SO_KEEPALIVE";
   break;
  case SO_USELOOPBACK:
   str = "SO_USELOOPBACK";
   break;
  case SO_TYPE:
   str = "SO_TYPE";
   break;
  case SO_NREAD:
   str = "SO_NREAD";
   break;
  case SO_NWRITE:
   str = "SO_NWRITE";
   break;
  case SO_ERROR:
   str = "SO_ERROR";
   break;
  case SO_SNDBUF:
   str = "SO_SNDBUF";
   break;
  case SO_RCVBUF:
   str = "SO_RCVBUF";
   break;
  case SO_SNDLOWAT:
   str = "SO_SNDLOWAT";
   break;
  case SO_RCVLOWAT:
   str = "SO_RCVLOWAT";
   break;
  case SO_SNDTIMEO:
   str = "SO_SNDTIMEO";
   break;
  case SO_RCVTIMEO:
   str = "SO_RCVTIMEO";
   break;
  case SO_NKE:
   str = "SO_NKE";
   break;
  case SO_NOSIGPIPE:
   str = "SO_NOSIGPIPE";
   break;
  case SO_NOADDRERR:
   str = "SO_NOADDRERR";
   break;
  case SO_RESTRICTIONS:
   str = "SO_RESTRICTIONS";
   break;
  case SO_LABEL:
   str = "SO_LABEL";
   break;
  case SO_PEERLABEL:
   str = "SO_PEERLABEL";
   break;
  case SO_RANDOMPORT:
   str = "SO_RANDOMPORT";
   break;
  case SO_TRAFFIC_CLASS:
   str = "SO_TRAFFIC_CLASS";
   break;
  case SO_RECV_TRAFFIC_CLASS:
   str = "SO_RECV_TRAFFIC_CLASS";
   break;
  case SO_TRAFFIC_CLASS_DBG:
   str = "SO_TRAFFIC_CLASS_DBG";
   break;
  case SO_PRIVILEGED_TRAFFIC_CLASS:
   str = "SO_PRIVILEGED_TRAFFIC_CLASS";
   break;
  case SO_DEFUNCTOK:
   str = "SO_DEFUNCTOK";
   break;
  case SO_ISDEFUNCT:
   str = "SO_ISDEFUNCT";
   break;
  case SO_OPPORTUNISTIC:
   str = "SO_OPPORTUNISTIC";
   break;
  case SO_FLUSH:
   str = "SO_FLUSH";
   break;
  case SO_RECV_ANYIF:
   str = "SO_RECV_ANYIF";
   break;
  case SO_NOWAKEFROMSLEEP:
   str = "SO_NOWAKEFROMSLEEP";
   break;
  case SO_NOAPNFALLBK:
   str = "SO_NOAPNFALLBK";
   break;
  case SO_CELLFALLBACK:
   str = "SO_CELLFALLBACK";
   break;
  case SO_DELEGATED:
   str = "SO_DELEGATED";
   break;
  case SO_DELEGATED_UUID:
   str = "SO_DELEGATED_UUID";
   break;
  default:
   str = "unknown";
  }
  break;
 case IPPROTO_TCP:
  switch (ctl) {
  case TCP_NODELAY:
   str = "TCP_NODELAY";
   break;
  case TCP_KEEPALIVE:
   str = "TCP_KEEPALIVE";
   break;
  case TCP_KEEPINTVL:
   str = "TCP_KEEPINTVL";
   break;
  case TCP_KEEPCNT:
   str = "TCP_KEEPCNT";
   break;
  case TCP_CONNECTIONTIMEOUT:
   str = "TCP_CONNECTIONTIMEOUT";
   break;
  case TCP_RXT_CONNDROPTIME:
   str = "TCP_RXT_CONNDROPTIME";
   break;
  case PERSIST_TIMEOUT:
   str = "PERSIST_TIMEOUT";
   break;
  case NOTSENT_LOWAT:
   str = "NOTSENT_LOWAT";
   break;
  case ADAPTIVE_READ_TIMEOUT:
   str = "ADAPTIVE_READ_TIMEOUT";
   break;
  case ADAPTIVE_WRITE_TIMEOUT:
   str = "ADAPTIVE_WRITE_TIMEOUT";
   break;
  case MPTCP_SERVICE_TYPE:
   str = "MPTCP_SERVICE_TYPE";
   break;
  case MPTCP_ALTERNATE_PORT:
   str = "MPTCP_ALTERNATE_PORT";
   break;
  default:
   str = "unknown";
  }
  break;
 default:
  str = "unknown";
 }

 return (str);
}