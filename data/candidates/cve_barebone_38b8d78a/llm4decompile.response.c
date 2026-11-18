int nfs_lookup_reply(char *pkt, int len)
{
    rpc_t rpc_pkt;
    int i;

    memcpy(&rpc_pkt, pkt, len);


    if (ntohl(rpc_pkt.u.call.id) > rpc_id)
        return -1;


    if (ntohl(rpc_pkt.u.call.id) < rpc_id)
        return -124;


    if (rpc_pkt.u.call.rpcvers != 0 ||
        rpc_pkt.u.call.prog != 0 ||
        rpc_pkt.u.call.proc != 0 ||
        rpc_pkt.u.reply.data[0] != 0) {


        switch (ntohl(rpc_pkt.u.call.proc)) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                if (ntohl(rpc_pkt.u.reply.data[0]) == 3) {
                    supported_nfs_versions &= 0xfe;
                    return -2;
                }
                printf("*** ERROR: NFS version not supported\n");
                printf("\n\n");
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }
        return -1;
    }


    if (supported_nfs_versions & 0x01) {
        for (i = 0; i < 32; i++)
            filefh[i] = *(((char *)&rpc_pkt) + 28 + i);
    }
    else {
        filefh3_length = ntohl(*(((u_long *)&rpc_pkt) + 8));
        if (filefh3_length > 64)
            filefh3_length = 64;
        memcpy(filefh, ((char *)&rpc_pkt) + 28, filefh3_length);
    }

    return 0;
}