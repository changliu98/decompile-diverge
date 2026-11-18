const char *__cdecl mptcp_sopt2str(int level, int optname)
{
  const char *v3; // [rsp+20h] [rbp-8h]

  if ( level == 173 )
  {
    switch ( optname )
    {
      case 137:
        v3 = "SO_USELOOPBACK";
        break;
      case 138:
        v3 = "SO_TYPE";
        break;
      case 139:
        v3 = "SO_TRAFFIC_CLASS_DBG";
        break;
      case 140:
        v3 = "SO_TRAFFIC_CLASS";
        break;
      case 141:
        v3 = "SO_SNDTIMEO";
        break;
      case 142:
        v3 = "SO_SNDLOWAT";
        break;
      case 143:
        v3 = "SO_SNDBUF";
        break;
      case 144:
        v3 = "SO_RESTRICTIONS";
        break;
      case 145:
        v3 = "SO_RECV_TRAFFIC_CLASS";
        break;
      case 146:
        v3 = "SO_RECV_ANYIF";
        break;
      case 147:
        v3 = "SO_RCVTIMEO";
        break;
      case 148:
        v3 = "SO_RCVLOWAT";
        break;
      case 149:
        v3 = "SO_RCVBUF";
        break;
      case 150:
        v3 = "SO_RANDOMPORT";
        break;
      case 151:
        v3 = "SO_PRIVILEGED_TRAFFIC_CLASS";
        break;
      case 152:
        v3 = "SO_PEERLABEL";
        break;
      case 153:
        v3 = "SO_OPPORTUNISTIC";
        break;
      case 154:
        v3 = "SO_NWRITE";
        break;
      case 155:
        v3 = "SO_NREAD";
        break;
      case 156:
        v3 = "SO_NOWAKEFROMSLEEP";
        break;
      case 157:
        v3 = "SO_NOSIGPIPE";
        break;
      case 158:
        v3 = "SO_NOAPNFALLBK";
        break;
      case 159:
        v3 = "SO_NOADDRERR";
        break;
      case 160:
        v3 = "SO_NKE";
        break;
      case 161:
        v3 = "SO_CELLFALLBACK";
        break;
      case 162:
        v3 = "SO_LINGER_SEC";
        break;
      case 163:
        v3 = "SO_LINGER";
        break;
      case 164:
        v3 = "SO_LABEL";
        break;
      case 165:
        v3 = "SO_KEEPALIVE";
        break;
      case 166:
        v3 = "SO_ISDEFUNCT";
        break;
      case 167:
        v3 = "SO_FLUSH";
        break;
      case 168:
        v3 = "SO_ERROR";
        break;
      case 169:
        v3 = "SO_DELEGATED_UUID";
        break;
      case 170:
        v3 = "SO_DELEGATED";
        break;
      case 171:
        v3 = "SO_DEFUNCTOK";
        break;
      case 172:
        v3 = "SO_DEBUG";
        break;
      default:
        return "unknown";
    }
  }
  else if ( level == 177 )
  {
    switch ( optname )
    {
      case 128:
        v3 = "TCP_RXT_CONNDROPTIME";
        break;
      case 129:
        v3 = "NOTSENT_LOWAT";
        break;
      case 130:
        v3 = "TCP_NODELAY";
        break;
      case 131:
        v3 = "TCP_KEEPINTVL";
        break;
      case 132:
        v3 = "TCP_KEEPCNT";
        break;
      case 133:
        v3 = "TCP_KEEPALIVE";
        break;
      case 134:
        v3 = "TCP_CONNECTIONTIMEOUT";
        break;
      case 135:
        v3 = "ADAPTIVE_WRITE_TIMEOUT";
        break;
      case 136:
        v3 = "ADAPTIVE_READ_TIMEOUT";
        break;
      case 174:
        v3 = "PERSIST_TIMEOUT";
        break;
      case 175:
        v3 = "MPTCP_SERVICE_TYPE";
        break;
      case 176:
        v3 = "MPTCP_ALTERNATE_PORT";
        break;
      default:
        return "unknown";
    }
  }
  else
  {
    return "unknown";
  }
  return v3;
}