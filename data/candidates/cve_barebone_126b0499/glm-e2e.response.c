int ares_parse_a_reply(const unsigned char *abuf, int alen, struct hostent **host) {
    int status = 0;
    char *qname = NULL;
    char *name = NULL;
    long len;
    unsigned short qdcount;
    unsigned short ancount;
    const unsigned char *aptr;
    int i;
    int count = 0;
    int cname_count = 0;
    int status_loop;
    struct in_addr *addrs = NULL;
    char **names = NULL;
    struct hostent *hostent = NULL;

    *host = NULL;

    if (alen < 12) {
        return 10; // ARES_E_BADRESP
    }

    // Parse DNS header counts
    qdcount = (abuf[4] << 8) | abuf[5];
    ancount = (abuf[6] << 8) | abuf[7];

    if (qdcount != 1) {
        return 10; // ARES_E_BADRESP
    }

    aptr = abuf + 12;
    status = ares_expand_name(aptr, abuf, alen, &qname, &len);
    if (status != 0) {
        return status;
    }

    aptr += len + 4; // Skip name and the 4-byte question footer (qtype + qclass)
    if (aptr > abuf + alen) {
        free(qname);
        return 10; // ARES_E_BADRESP
    }

    addrs = malloc(ancount * sizeof(struct in_addr));
    if (!addrs) {
        free(qname);
        return 15; // ARES_ENOMEM
    }

    names = malloc((ancount + 1) * sizeof(char *));
    if (!names) {
        free(qname);
        free(addrs);
        return 15; // ARES_ENOMEM
    }

    count = 0;
    cname_count = 0;
    status_loop = 0;

    for (i = 0; i < ancount; i++) {
        char *rr_name = NULL;
        unsigned short rr_type;
        unsigned short rr_class;
        unsigned short rr_len;

        status = ares_expand_name(aptr, abuf, alen, &rr_name, &len);
        if (status != 0) {
            status_loop = status;
            break;
        }

        aptr += len;
        if (aptr + 10 > abuf + alen) {
            free(rr_name);
            status_loop = 10; // ARES_E_BADRESP
            break;
        }

        rr_type = (aptr[0] << 8) | aptr[1];
        rr_class = (aptr[2] << 8) | aptr[3];
        rr_len = (aptr[8] << 8) | aptr[9];
        aptr += 10;

        if (rr_type == 1 && rr_class == 1 && rr_len == 4) { // A record, IN class, 4 bytes
            if (strcasecmp(rr_name, qname) == 0) {
                addrs[count] = *(struct in_addr *)aptr;
                count++;
                status_loop = 0;
            }
        } else if (rr_type == 5 && rr_class == 1) { // CNAME record, IN class
            names[cname_count++] = rr_name;
            status = ares_expand_name(aptr, abuf, alen, &name, &len);
            if (status != 0) {
                status_loop = status;
                break;
            }
            free(qname);
            qname = name;
        } else {
            free(rr_name);
        }

        aptr += rr_len;
        if (aptr > abuf + alen) {
            status_loop = 10; // ARES_E_BADRESP
            break;
        }
    }

    if (status_loop == 0 && count == 0) {
        status_loop = 1; // ARES_ENODATA
    }

    if (status_loop != 0) {
        for (i = 0; i < cname_count; i++) {
            free(names[i]);
        }
        free(names);
        free(addrs);
        free(qname);
        return status_loop;
    }

    names[cname_count] = NULL;

    hostent = malloc(sizeof(struct hostent));
    if (!hostent) {
        for (i = 0; i < cname_count; i++) {
            free(names[i]);
        }
        free(names);
        free(addrs);
        free(qname);
        return 15; // ARES_ENOMEM
    }

    hostent->h_addr_list = malloc((count + 1) * sizeof(char *));
    if (!hostent->h_addr_list) {
        free(hostent);
        for (i = 0; i < cname_count; i++) {
            free(names[i]);
        }
        free(names);
        free(addrs);
        free(qname);
        return 15; // ARES_ENOMEM
    }

    hostent->h_name = qname;
    hostent->h_aliases = names;
    hostent->h_addrtype = 2; // AF_INET
    hostent->h_length = 4;

    for (i = 0; i < count; i++) {
        hostent->h_addr_list[i] = (char *)&addrs[i];
    }
    hostent->h_addr_list[count] = NULL;

    *host = hostent;
    return 0; // ARES_SUCCESS
}