char *mptcp_sopt2str(int level, int optname)
{
    char *name = "unknown";
    switch (level) {
    case IPPROTO_IP:
        switch (optname) {
        case 137:
            name = "SO_USELOOPBACK";
            break;
        case 138:
            name = "SO_TYPE";
            break;
        case 139:
            name = "SO_TRAFFIC_CLASS_DBG";
            break;
        case 140:
            name = "SO_TRAFFIC_CLASS";
            break;
        case 141:
            name = "SO_SNDTIMEO";
            break;
        case 142:
            name = "SO_SNDLOWAT";
            break;
        case 143:
            name = "SO_SNDBUF";
            break;
        case 144:
            name = "SO_RESTRICTIONS";
            break;
        case 145:
            name = "SO_RECV_TRAFFIC_CLASS";
            break;
        case 146:
            name = "SO_RECV_ANYIF";
            break;
        case 147:
            name = "SO_RCVTIMEO";
            break;
        case 148:
            name = "SO_RCVLOWAT";
            break;
        case 149:
            name = "SO_RCVBUF";
            break;
        case 150:
            name = "SO_RANDOMPORT";
            break;
        case 151:
            name = "SO_PRIVILEGED_TRAFFIC_CLASS";
            break;
        case 152:
            name = "SO_PEERLABEL";
            break;
        case 153:
            name = "SO_OPPORTUNISTIC";
            break;
        case 154:
            name = "SO_NWRITE";
            break;
        case 155:
            name = "SO_NREAD";
            break;
        case 156:
            name = "SO_NOWAKEFROMSLEEP";
            break;
        case 157:
            name = "SO_NOSIGPIPE";
            break;
        case 158:
            name = "SO_NOAPNFALLBK";
            break;
        case 159:
            name = "SO_NOADDRERR";
            break;
        case 160:
            name = "SO_NKE";
            break;
        case 161:
            name = "SO_CELLFALLBACK";
            break;
        case 162:
            name = "SO_LINGER_SEC";
            break;
        case 163:
            name = "SO_LINGER";
            break;
        case 164:
            name = "SO_LABEL";
            break;
        case 165:
            name = "SO_KEEPALIVE";
            break;
        case 166:
            name = "SO_ISDEFUNCT";
            break;
        case 167:
            name = "SO_FLUSH";
            break;
        case 168:
            name = "SO_ERROR";
            break;
        case 169:
            name = "SO_DELEGATED_UUID";
            break;
        case 170:
            name = "SO_DELEGATED";
            break;
        case 171:
            name = "SO_DEFUNCTOK";
            break;
        case 172:
            name = "SO_DEBUG";
            break;
        default:
            break;
        }
        break;
    case IPPROTO_TCP:
        switch (optname) {
        case 128:
            name = "TCP_RXT_CONNDROPTIME";
            break;
        case 129:
            name = "NOTSENT_LOWAT";
            break;
        case 130:
            name = "TCP_NODELAY";
            break;
        case 131:
            name = "TCP_KEEPINTVL";
            break;
        case 132:
            name = "TCP_KEEPCNT";
            break;
        case 133:
            name = "TCP_KEEPALIVE";
            break;
        case 134:
            name = "TCP_CONNECTIONTIMEOUT";
            break;
        case 135:
            name = "ADAPTIVE_WRITE_TIMEOUT";
            break;
        case 136:
            name = "ADAPTIVE_READ_TIMEOUT";
            break;
        case 174:
            name = "PERSIST_TIMEOUT";
            break;
        case 175:
            name = "MPTCP_SERVICE_TYPE";
            break;
        case 176:
            name = "MPTCP_ALTERNATE_PORT";
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return name;
}