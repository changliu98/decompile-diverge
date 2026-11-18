void ssdp_recv(int sock) {
    char buffer[0x200];
    struct sockaddr_in addr;
    socklen_t addr_len;
    ssize_t len;
    struct interface *iface;
    char *st_str, *st_start, *st_end;
    int i;

    memset(buffer, 0, sizeof(buffer));

    len = recvfrom(sock, buffer, 0x200, 0x40, &addr, &addr_len);
    if (len <= 0) {
        return;
    }

    buffer[len] = '\0';

    if (addr.sin_family != AF_INET) {
        return;
    }

    if (strstr(buffer, "M-SEARCH") == NULL) {
        return;
    }

    iface = find_outbound(&addr);
    if (iface == NULL) {
        syslog(LOG_DEBUG, "No outbound interface for %s", inet_ntoa(addr.sin_addr));
        return;
    }

    syslog(LOG_DEBUG, "Received M-SEARCH from %s", inet_ntoa(addr.sin_addr));

    st_str = strcasestr(buffer, "ST:");
    if (st_str == NULL) {
        syslog(LOG_DEBUG, "No ST: header in M-SEARCH");
        st_str = "ssdp:all";
        send_message(iface, st_str, &addr);
        return;
    }

    st_str = strchr(st_str, ':');
    if (st_str == NULL) {
        return;
    }
    st_str++;

    while (isspace((unsigned char)*st_str)) {
        st_str++;
    }

    st_end = strstr(st_str, "\r\n");
    if (st_end == NULL) {
        return;
    }
    *st_end = '\0';

    for (i = 0; supported_types[i] != NULL; i++) {
        if (strcmp(supported_types[i], st_str) == 0) {
            syslog(LOG_DEBUG, "Matched search type %s from %s:%d", st_str, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
            send_message(iface, st_str, &addr);
            return;
        }
    }

    syslog(LOG_DEBUG, "Unsupported search type %s from %s", st_str, inet_ntoa(addr.sin_addr));
}