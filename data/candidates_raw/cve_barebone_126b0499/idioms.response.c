int get_hostent(unsigned char *msg, int len, struct hostent **hp)
{
    int i; int ret; int qdcount; int ancount;
    struct hostent *he;
    char *name; char *data;
    unsigned long namelen;
    struct in_addr *addr;
    char **alias;
    unsigned char *msg_end;
    unsigned char *data_end;
    unsigned char *data_start;
    *hp = ((void *)0);
    if (len < 12)
        return 10;
    qdcount = (msg[4] << 8) | msg[5];
    ancount = (msg[6] << 8) | msg[7];
    if (qdcount != 1)
        return 10;
    data_start = msg + 12;
    ret = get_data(data_start, msg, len, &name, &namelen);
    if (ret != 0)
        return ret;
    data_end = data_start + namelen + 4;
    if (data_end > msg + len) {
        free(name);
        return 10;
    }
    data_start = data_end;
    addr = (struct in_addr *)malloc(ancount * sizeof(struct in_addr));
    if (addr == ((void *)0)) {
        free(name);
        return 15;
    }
    alias = (char **)malloc((ancount + 1) * sizeof(char *));
    if (alias == ((void *)0)) {
        free(name);
        free(addr);
        return 15;
    }
    ret = 0;
    for (i = 0, naddrs = 0, naliases = 0; i < ancount; i++) {
        ret = get_data(data_start, msg, len, &name, &namelen);
        if (ret != 0)
            break;
        data_start += namelen;
        if (data_start + 10 > msg + len) {
            free(name);
            ret = 10;
            break;
        }
        int type = (data_start[0] << 8) | data_start[1];
        int class = (data_start[2] << 8) | data_start[3];
        int len = (data_start[8] << 8) | data_start[9];
        data_start += 10;
        if (class == 1 && type == 1 && len == 4 &&
            strcasecmp(name, msgname) == 0) {
            addr[naddrs] = *((struct in_addr *)data_start);
            naddrs++;
            ret = 0;
        }
        if (class == 1 && type == 5) {
            alias[naliases] = name;
            naliases++;
            ret = get_data(data_start, msg, len, &data, &namelen);
            if (ret != 0)
                break;
            free(name);
            name = data;
        } else {
            free(name);
        }
        data_start += len;
        if (data_start > msg + len) {
            ret = 10;
            break;
        }
    }
    if (ret == 0)
        ret = naddrs == 0 ? 1 : 0;
    if (ret == 0) {
        alias[naliases] = ((void *)0);
        he = (struct hostent *)malloc(sizeof(struct hostent));
        if (he == ((void *)0)) {
            ret = 15;
        } else {
            he->h_addr_list = (char **)malloc((naddrs + 1) * sizeof(char *));
            if (he->h_addr_list == ((void *)0)) {
                free(he);
                ret = 15;
            } else {
                he->h_name = name;
                he->h_aliases = alias;
                he->h_addrtype = 2;
                he->h_length = sizeof(struct in_addr);
                for (i = 0; i < naddrs; i++)
                    he->h_addr_list[i] = (char *)&addr[i];
                he->h_addr_list[naddrs] = ((void *)0);
                *hp = he;
                ret = 0;
            }
        }
    }
    for (i = 0; i < naliases; i++)
        free(alias[i]);
    free(alias);
    free(addr);
    free(name);
    return ret;
}