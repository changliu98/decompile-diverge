void handle_ssdp(int s)
{
    int len;
    int slen;
    char buf[-1];
    struct sockaddr_storage from;
    ifsock *ifs;
    char *st;
    char *st_end;
    char *st_type;
    char *st_end2;
    unsigned long i;
    ssdp_init(buf, 0, sizeof(buf));
    len = read_ssdp(s, buf, sizeof(buf), 64, (struct sockaddr *)&from, &slen);
    if (len > 0) {
        buf[len] = '\0';
        if (from.ss_family == 2) {
            if (ssdp_is_msearch(buf, "M-SEARCH *")) {
                ifs = get_ifsock((struct sockaddr *)&from);
                if (ifs == ((void *)0)) {
                    log_print(7,"No matching socket for client %s",
                              ssdp_get_ipstr(((struct sockaddr *)&from)->ss_family == 2 ? ((struct sockaddr_in *)&from)->sin_addr : ((struct sockaddr_in6 *)&from)->sin6_addr));
                } else {
                    log_print(7,"Matching socket for client %s",
                              ssdp_get_ipstr(((struct sockaddr *)&from)->ss_family == 2 ? ((struct sockaddr_in *)&from)->sin_addr : ((struct sockaddr_in6 *)&from)->sin6_addr));
                    st = ssdp_get_header(buf, "\r\nST:");
                    if (st == ((void *)0)) {
                        log_print(7,"No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
                        ssdp_respond(ifs, "ssdp:all", (struct sockaddr *)&from);
                    } else {
                        st_end = ssdp_get_header_end(st, ':');
                        if (st_end == ((void *)0)) {
                        } else {
                            st_type = st_end + 1;
                            while (ssdp_is_ws(*st_type)) {
                                st_type++;
                            }
                            st_end2 = ssdp_get_header(st_type, "\r\n");
                            if (st_end2 == ((void *)0)) {
                            } else {
                                *st_end2 = '\0';
                                for (i = 0; supported_types[i]; i++) {
                                    if (ssdp_is_equal(supported_types[i], st_type)) {
                                    } else {
                                        log_print(7,"M-SEARCH * for unsupported ST: %s from %s",
                                                  st_type,
                                                  ssdp_get_ipstr(((struct sockaddr *)&from)->ss_family == 2 ? ((struct sockaddr_in *)&from)->sin_addr : ((struct sockaddr_in6 *)&from)->sin6_addr));
                                        ssdp_respond(ifs, st_type, (struct sockaddr *)&from);
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}