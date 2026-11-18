const char *mptcp_sopt2str(int level, int optname) {
    const char *str;

    switch (level) {
        case 0xad:
            switch (optname) {
                case 0x89:  str = "MPTCP_PM_CMD_ANNOUNCE"; break;
                case 0x8a:  str = "MPTCP_PM_CMD_REMOVE"; break;
                case 0x8b:  str = "MPTCP_PM_CMD_SUBFLOW_CREATE"; break;
                case 0x8c:  str = "MPTCP_PM_CMD_SUBFLOW_DESTROY"; break;
                case 0x8d:  str = "MPTCP_PM_CMD_SET_LIMITS"; break;
                case 0x8e:  str = "MPTCP_PM_CMD_GET_LIMITS"; break;
                case 0x8f:  str = "MPTCP_PM_CMD_SET_FLAGS"; break;
                case 0x90:  str = "MPTCP_PM_CMD_SET_ENDPOINTS"; break;
                case 0x91:  str = "MPTCP_PM_CMD_GET_ENDPOINTS"; break;
                case 0x92:  str = "MPTCP_PM_CMD_FLUSH_ENDPOINTS"; break;
                case 0x93:  str = "MPTCP_PM_CMD_ADD_ADDR"; break;
                case 0x94:  str = "MPTCP_PM_CMD_DEL_ADDR"; break;
                case 0x95:  str = "MPTCP_PM_CMD_GET_ADDR"; break;
                case 0x96:  str = "MPTCP_PM_CMD_SET_RESOURCES"; break;
                case 0x97:  str = "MPTCP_PM_CMD_GET_RESOURCES"; break;
                case 0x98:  str = "MPTCP_PM_CMD_SET_SCHED"; break;
                case 0x99:  str = "MPTCP_PM_CMD_GET_SCHED"; break;
                case 0x9a:  str = "MPTCP_PM_CMD_SET_BACKUP"; break;
                case 0x9b:  str = "MPTCP_PM_CMD_GET_BACKUP"; break;
                case 0x9c:  str = "MPTCP_PM_CMD_SET_FULLMESH"; break;
                case 0x9d:  str = "MPTCP_PM_CMD_GET_FULLMESH"; break;
                case 0x9e:  str = "MPTCP_PM_CMD_SET_NAT"; break;
                case 0x9f:  str = "MPTCP_PM_CMD_GET_NAT"; break;
                case 0xa0:  str = "MPTCP_PM_CMD_SET_RADDR"; break;
                case 0xa1:  str = "MPTCP_PM_CMD_GET_RADDR"; break;
                case 0xa2:  str = "MPTCP_PM_CMD_SET_RPORT"; break;
                case 0xa3:  str = "MPTCP_PM_CMD_GET_RPORT"; break;
                case 0xa4:  str = "MPTCP_PM_CMD_SET_RBACKUP"; break;
                case 0xa5:  str = "MPTCP_PM_CMD_GET_RBACKUP"; break;
                case 0xa6:  str = "MPTCP_PM_CMD_SET_RFULLMESH"; break;
                case 0xa7:  str = "MPTCP_PM_CMD_GET_RFULLMESH"; break;
                case 0xa8:  str = "MPTCP_PM_CMD_SET_RNAT"; break;
                case 0xa9:  str = "MPTCP_PM_CMD_GET_RNAT"; break;
                case 0xaa:  str = "MPTCP_PM_CMD_SET_RADDR6"; break;
                case 0xab:  str = "MPTCP_PM_CMD_GET_RADDR6"; break;
                case 0xac:  str = "MPTCP_PM_CMD_SET_RPORT6"; break;
                default:    str = "unknown"; break;
            }
            break;

        case 0xb1:
            switch (optname) {
                case 0x80:  str = "MPTCP_INFO"; break;
                case 0x81:  str = "MPTCP_TCPINFO"; break;
                case 0x82:  str = "MPTCP_SUBFLOW_ADDRS"; break;
                case 0x83:  str = "MPTCP_FULL_INFO"; break;
                case 0x84:  str = "MPTCP_STATS"; break;
                case 0x85:  str = "MPTCP_INFO_QUERY"; break;
                case 0x86:  str = "MPTCP_INFO_SET"; break;
                case 0x87:  str = "MPTCP_INFO_GET"; break;
                case 0x88:  str = "MPTCP_INFO_RESET"; break;
                case 0x89:  str = "MPTCP_INFO_LIST"; break;
                case 0x8a:  str = "MPTCP_INFO_EVENT"; break;
                case 0x8b:  str = "MPTCP_INFO_DIAG"; break;
                case 0x8c:  str = "MPTCP_INFO_METRICS"; break;
                case 0x8d:  str = "MPTCP_INFO_PATH_MANAGER"; break;
                case 0x8e:  str = "MPTCP_INFO_SCHEDULER"; break;
                case 0x8f:  str = "MPTCP_INFO_CONGESTION"; break;
                case 0x90:  str = "MPTCP_INFO_RWND"; break;
                case 0x91:  str = "MPTCP_INFO_RTT"; break;
                case 0x92:  str = "MPTCP_INFO_BYTES_SENT"; break;
                case 0x93:  str = "MPTCP_INFO_BYTES_RECEIVED"; break;
                case 0x94:  str = "MPTCP_INFO_BYTES_RETRANSMITTED"; break;
                case 0x95:  str = "MPTCP_INFO_BYTES_QUEUED"; break;
                case 0x96:  str = "MPTCP_INFO_BYTES_DELIVERED"; break;
                case 0x97:  str = "MPTCP_INFO_BYTES_DELIVERED_QUEUED"; break;
                case 0x98:  str = "MPTCP_INFO_BYTES_DELIVERED_RETRANS"; break;
                case 0x99:  str = "MPTCP_INFO_BYTES_RECEIVED_QUEUED"; break;
                case 0x9a:  str = "MPTCP_INFO_BYTES_RECEIVED_RETRANS"; break;
                case 0x9b:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED"; break;
                case 0x9c:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_QUEUED"; break;
                case 0x9d:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS"; break;
                case 0x9e:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED"; break;
                case 0x9f:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED"; break;
                case 0xa0:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED"; break;
                case 0xa1:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa2:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa3:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEued_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa4:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa5:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa6:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa7:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa8:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xa9:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xaa:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xab:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xac:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                case 0xb0:  str = "MPTCP_INFO_BYTES_RECEIVED_DELIVERED_RETRANS_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED_QUEUED"; break;
                default:    str = "unknown"; break;
            }
            break;

        default:
            str = "unknown";
            break;
    }

    return str;
}