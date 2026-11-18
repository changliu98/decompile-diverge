/*
 * Converts MPTCP socket option level and name to a human-readable string.
 *
 * @param level The socket option level (e.g., IPPROTO_MPTCP, IPPROTO_TCP).
 * @param optname The specific socket option identifier.
 * @return A static string representing the option name, or "unknown" if not found.
 */
char * mptcp_sopt2str(int opt_level, int opt_identifier)
{
    /* Check for MPTCP-specific options (level 0xad) */
    if (opt_level == 0xad) {
        switch (opt_identifier) {
        case 0x89: return "SO_USELOOPBACK";
        case 0x8a: return "SO_TYPE";
        case 0x8b: return "SO_TRAFFIC_CLASS_DBG";
        case 0x8c: return "SO_TRAFFIC_CLASS";
        case 0x8d: return "SO_SNDTIMEO";
        case 0x8e: return "SO_SNDLOWAT";
        case 0x8f: return "SO_SNDBUF";
        case 0x90: return "SO_RESTRICTIONS";
        case 0x91: return "SO_RECV_TRAFFIC_CLASS";
        case 0x92: return "SO_RECV_ANYIF";
        case 0x93: return "SO_RCVTIMEO";
        case 0x94: return "SO_RCVLOWAT";
        case 0x95: return "SO_RCVBUF";
        case 0x96: return "SO_RANDOMPORT";
        case 0x97: return "SO_PRIVILEGED_TRAFFIC_CLASS";
        case 0x98: return "SO_PEERLABEL";
        case 0x99: return "SO_OPPORTUNISTIC";
        case 0x9a: return "SO_NWRITE";
        case 0x9b: return "SO_NREAD";
        case 0x9c: return "SO_NOWAKEFROMSLEEP";
        case 0x9d: return "SO_NOSIGPIPE";
        case 0x9e: return "SO_NOAPNFALLBK";
        case 0x9f: return "SO_NOADDRERR";
        case 0xa0: return "SO_NKE";
        case 0xa1: return "SO_CELLFALLBACK";
        case 0xa2: return "SO_LINGER_SEC";
        case 0xa3: return "SO_LINGER";
        case 0xa4: return "SO_LABEL";
        case 0xa5: return "SO_KEEPALIVE";
        case 0xa6: return "SO_ISDEFUNCT";
        case 0xa7: return "SO_FLUSH";
        case 0xa8: return "SO_ERROR";
        case 0xa9: return "SO_DELEGATED_UUID";
        case 0xaa: return "SO_DELEGATED";
        case 0xab: return "SO_DEFUNCTOK";
        case 0xac: return "SO_DEBUG";
        }
    /* Check for TCP-specific options (level 0xb1) */
    } else if (opt_level == 0xb1) {
        switch (opt_identifier) {
        case 0x80: return "TCP_RXT_CONNDROPTIME";
        case 0x81: return "NOTSENT_LOWAT";
        case 0x82: return "TCP_NODELAY";
        case 0x83: return "TCP_KEEPINTVL";
        case 0x84: return "TCP_KEEPCNT";
        case 0x85: return "TCP_KEEPALIVE";
        case 0x86: return "TCP_CONNECTIONTIMEOUT";
        case 0x87: return "ADAPTIVE_WRITE_TIMEOUT";
        case 0x88: return "ADAPTIVE_READ_TIMEOUT";
        case 0xae: return "PERSIST_TIMEOUT";
        case 0xaf: return "MPTCP_SERVICE_TYPE";
        case 0xb0: return "MPTCP_ALTERNATE_PORT";
        }
    }
    /* Return default string for unrecognized options */
    return "unknown";
}