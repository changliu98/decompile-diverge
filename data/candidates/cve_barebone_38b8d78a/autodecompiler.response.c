int nfs_lookup_reply(char *packet, int length)
{
    rpc_t rpc;
    int status;

    while (length > sizeof(rpc)) {
        memcpy(&rpc, packet, sizeof(rpc));
        if (ntohl(rpc.id) > rpc_id) {
            status = -1;
            break;
        }
        if (ntohl(rpc.id) < rpc_id) {
            status = -124;
            break;
        }

        while (rpc.xid == 0 || rpc.type != 0 || rpc.tcp_flag != 0 ||
                rpc.rpc_flag != 0) {
            switch (ntohl(rpc.rpc_flag)) {
                case 0:
                    status = -1;
                    break;
                case 2:
                    switch (ntohl(rpc.tcp_flag)) {
                        case 3:
                            status = -1;
                            break;
                        case 4:
                            status = -1;
                            break;
                        case 5:
                            status = -1;
                            break;
                        case 6:
                            status = -1;
                            break;
                        case 7:
                            status = -1;
                            break;
                        case 8:
                            status = -1;
                            break;
                        case 9:
                            status = -1;
                            break;
                        case 10:
                            status = -1;
                            break;
                        case 11:
                            status = -1;
                            break;
                        case 12:
                            status = -1;
                            break;
                        case 13:
                            status = -1;
                            break;
                        case 14:
                            status = -1;
                            break;
                        case 15:
                            status = -1;
                            break;
                        case 16:
                            status = -1;
                            break;
                        case 17:
                            status = -1;
                            break;
                        case 18:
                            status = -1;
                            break;
                        case 19:
                            status = -1;
                            break;
                        case 20:
                            status = -1;
                            break;
                        case 21:
                            status = -1;
                            break;
                        case 22:
                            status = -1;
                            break;
                        case 23:
                            status = -1;
                            break;
                        case 24:
                            status = -1;
                            break;
                        case 25:
                            status = -1;
                            break;
                        case 26:
                            status = -1;
                            break;
                        case 27:
                            status = -1;
                            break;
                        case 28:
                            status = -1;
                            break;
                       case 29:
                            status = -1;
                            break;
                        case 30:
                            status = -1;
                            break;
                        case 31:
                            status = -1;
                            break;
                        case 32:
                            status = -1;
                            break;
                        case 33:
                            status = -1;
                            break;
                        case 34:
                            status = -1;
                            break;
                        case 35:
                            status = -1;
                            break;
                        case 36:
                            status = -1;
                            break;
                        case 37:
alted_nfs_versions(supported_nfs_versions & ~1);
                            supported_nfs_versions &= ~1;
                            status = -2;
                            break;
                        case 38:
                            status = -1;
                            break;
                        case 39:
                            status = -1;
                            break;
                        case 40:
                            status = -1;
                            break;
                        case 41:
                            status = -1;
                            break;
                        case 42:
                            status = -1;
                            break;
                        case 43:
                            status = -1;
                            break;
                        case 44:
                            status = -1;
                            break;
                        case 45:
                            status = -1;
                            break;
                        case 46:
                            status = -1;
                            break;
                        case 47:
                            status = -1;
                            break;
                        case 48:
                            status = -1;
                            break;
                        case 49:
                            status = -1;
                            break;
                        case 50:
                            status = -1;
                            break;
                        case 51:
                            status = -1;
                            break;
                        case 52:
                            status = -1;
                            break;
                        case 53:
                            status = -1;
                            break;
                        case 54:
                            status = -1;
                            break;
                        case 55:
alted_nfs_versions(supported_nfs_versions & ~2);
                            supported_nfs_versions &= ~2;
                            status = -2;
                            break;
                        case 56:
                            status = -1;
                            break;
                        case 57:
                            status = -1;
                            break;
                        case 58:
                            status = -1;
                            break;
                        case 59:
                            status = -1;
                            break;
                        case 60:
                            status = -1;
                            break;
                        case 61:
                            status = -1;
                            break;
                        case 62:
                            status = -1;
                            break;
                        case 63:
                            status = -1;
                            break;
                        case 64:
                            status = -1;
                            break;
                        case 65:
                            status = -1;
                            break;
                        case 66:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 67:
                            status = -1;
                            break;
                        case 68:
alted_nfs_versions(supported_nfs_versions & ~4);
                            supported_nfs_versions &= ~4;
                            status = -4;
                            break;
                        case 69:
                            status = -1;
                            break;
                        case 70:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 71:
                            status = -1;
                            break;
                        case 72:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 73:
                            status = -1;
                            break;
                        case 74:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 75:
                            status = -1;
                            break;
                        case 76:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 77:
                            status = -1;
                            break;
                        case 78:
alted_nfs_versions(supported_nfs_versions & ~8);
                            supported_nfs_versions &= ~8;
                            status = -8;
                            break;
                        case 79:
                            status = -1;
                            break;
                        case 80:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 81:
                            status = -1;
                            break;
                        case 82:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 83:
                            status = -1;
                            break;
                        case 84:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 85:
alted_nfs_versions(supported_nfs_versions & ~16);
                            supported_nfs_versions &= ~16;
                            status = -16;
                            break;
                        case 86:
                            status = -1;
                            break;
                        case 87:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 88:
                            status = -1;
                            break;
                        case 89:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 90:
                            status = -1;
                            break;
                        case 91:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 92:
                            status = -1;
                            break;
                        case 93:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 94:
                            status = -1;
                            break;
                        case 95:
                            status = -1;
                            break;
                        case 96:
                            status = -1;
                            break;
                        case 97:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 98:
                            status = -1;
                            break;
                        case 99:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 100:
                            status = -1;
                            break;
                        case 101:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 102:
                            status = -1;
                            break;
                        case 103:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 104:
                            status = -1;
                            break;
                        case 105:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 106:
                            status = -1;
                            break;
                        case 107:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 108:
                            status = -1;
                            break;
                        case 109:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 110:
                            status = -1;
                            break;
                        case 111:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 112:
                            status = -1;
                            break;
                        case 113:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 114:
alted_nfs_versions(supported_nfs_versions & ~32);
                            supported_nfs_versions &= ~32;
                            status = -32;
                            break;
                        case 115:
                            status = -1;
                            break;
                        case 116:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 117:
                            status = -1;
                            break;
                        case 118:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 119:
                            status = -1;
                            break;
                        case 120:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 121:
                            status = -1;
                            break;
                        case 122:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 123:
                            status = -1;
                            break;
                        case 124:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 125:
                            status = -1;
                            break;
                        case 126:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 127:
                            status = -1;
                            break;
                        case 128:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 129:
                            status = -1;
                            break;
                        case 130:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 131:
                            status = -1;
                            break;
                        case 132:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 133:
                            status = -1;
                            break;
                        case 134:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 135:
                            status = -1;
                            break;
                        case 136:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 137:
                            status = -1;
                            break;
                        case 138:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 139:
                            status = -1;
                            break;
                        case 140:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 141:
                            status = -1;
                            break;
                        case 142:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 143:
                            status = -1;
                            break;
                        case 144:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 145:
                            status = -1;
                            break;
                        case 146:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 147:
                            status = -1;
                            break;
                        case 148:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 149:
                            status = -1;
                            break;
                        case 150:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 151:
                            status = -1;
                            break;
                        case 152:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 153:
                            status = -1;
                            break;
                        case 154:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 155:
                            status = -1;
                            break;
                        case 156:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 157:
                            status = -1;
                            break;
                        case 158:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 159:
                            status = -1;
                            break;
                        case 160:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 161:
                            status = -1;
                            break;
                        case 162:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 163:
                            status = -1;
                            break;
                        case 164:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 165:
                            status = -1;
                            break;
                        case 166:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 167:
                            status = -1;
                            break;
                        case 168:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 169:
                            status = -1;
                            break;
                        case 170:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 171:
                            status = -1;
                            break;
                        case 172:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 173:
                            status = -1;
                            break;
                        case 174:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 175:
                            status = -1;
                            break;
                        case 176:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 177:
                            status = -1;
                            break;
                        case 178:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 179:
                            status = -1;
                            break;
                        case 180:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 181:
                            status = -1;
                            break;
                        case 182:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 183:
                            status = -1;
                            break;
                        case 184:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 185:
                            status = -1;
                            break;
                        case 186:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 187:
                            status = -1;
                            break;
                        case 188:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 189:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 190:
                            status = -1;
                            break;
                        case 191:
                            status = -1;
                            break;
                        case 192:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 193:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 194:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 195:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 196:
                            status = -1;
                            break;
closesocket(sock);
                            exit__bench(1);
                        case 197:
                            status = -1;
                            break;
closesocket(sock);
                            exit