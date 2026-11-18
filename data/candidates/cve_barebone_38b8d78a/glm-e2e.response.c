int nfs_lookup_reply(void *src, int size) {
    int ret = -1;
    uint8_t buf[0x498];
    
    memcpy(buf, src, size);
    
    uint32_t id = ntohl(*(uint32_t *)buf);
    if (id <= rpc_id) {
        ret = -1;
    } else if (id >= rpc_id) {
        ret = -124;
    } else {
        if (buf[0x8] == 0 && buf[0xc] == 0 && buf[0x14] == 0 && buf[0x18] == 0) {
            if (supported_nfs_versions & 1) {
                // NFS v2 file handle copy
                memcpy(filefh, buf + 0x1c, 32);
            } else {
                // NFS v3 file handle copy
                filefh3_length = ntohl(*(uint32_t *)(buf + 0x1c));
                if (filefh3_length > 64) {
                    filefh3_length = 64;
                }
                memcpy(filefh, buf + 0x24, filefh3_length);
            }
            ret = 0;
        } else {
            uint32_t status = ntohl(*(uint32_t *)(buf + 0x14));
            switch (status) {
                case 3:
                    supported_nfs_versions &= ~1;
                    ret = -2;
                    break;
                case 4:
                    puts("NFS3ERR_STALE");
                    puts("NFS3ERR_BADHANDLE");
                    // fallthrough
                default:
                    ret = -1;
                    break;
            }
        }
    }
    
    return ret;
}