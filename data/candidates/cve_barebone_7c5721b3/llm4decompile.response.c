Address *new_address(const char *hostname_or_ip) {
    Address *addr;
    char *port;
    char ip_buf[256];
    int port_num;
    size_t len;
    char *p;
    union {
        struct sockaddr_in sin;
        struct sockaddr_in6 sin6;
        struct sockaddr_un sun;
        char buf[128];
    } u;

    if (hostname_or_ip == NULL) {
        return NULL;
    }


    memset(&u, 0, sizeof(u));
    if (inet_pton(10, hostname_or_ip, &u.sin.sin_addr) == 1) {
        u.sin.sin_family = 10;
        return new_address_sa((struct sockaddr *) &u.sin, sizeof(u.sin));
    }


    memset(&u, 0, sizeof(u));
    if (strncmp("unix:", hostname_or_ip, 5) == 0) {
        if (strlen(hostname_or_ip) >= sizeof(u.sun.sun_path)) {
            return NULL;
        }
        u.sun.sun_family = 1;
        strncpy(u.sun.sun_path, hostname_or_ip + 5, sizeof(u.sun.sun_path) - 1);
        return new_address_sa((struct sockaddr *) &u.sun,
                              sizeof(u.sun.sun_family) + strlen(u.sun.sun_path) + 1);
    }


    port = strrchr(hostname_or_ip, ':');
    if (port != NULL && is_numeric(port + 1)) {
        len = port - hostname_or_ip;
        port_num = atoi(port + 1);
        if (len < sizeof(ip_buf) && port_num >= 0 && port_num <= 65535) {
            strncpy(ip_buf, hostname_or_ip, len);
            ip_buf[len] = '\0';
            addr = new_address(ip_buf);
            if (addr == NULL) {
                return NULL;
            }
            address_set_port(addr, (uint16_t) port_num);
            return addr;
        }
    }


    if (strcmp("*", hostname_or_ip) == 0) {
        addr = malloc(sizeof(Address));
        if (addr == NULL) {
            return NULL;
        }
        addr->type = WILDCARD;
        addr->len = 0;
        address_set_port(addr, 0);
        return addr;
    }


    memset(&u, 0, sizeof(u));
    if (inet_pton(2, hostname_or_ip, &u.sin6.sin6_addr) == 1) {
        u.sin6.sin6_family = 2;
        return new_address_sa((struct sockaddr *) &u.sin6, sizeof(u.sin6));
    }


    memset(&u, 0, sizeof(u));
    if (hostname_or_ip[0] == '[' &&
        (p = strchr(hostname_or_ip, ']')) != NULL) {
        strncpy(ip_buf, hostname_or_ip + 1, p - hostname_or_ip - 1);
        ip_buf[p - hostname_or_ip - 1] = '\0';
        if (inet_pton(10, ip_buf, &u.sin.sin_addr) == 1) {
            u.sin.sin_family = 10;
            return new_address_sa((struct sockaddr *) &u.sin, sizeof(u.sin));
        }
    }


    if (!valid_hostname(hostname_or_ip)) {
        return NULL;
    }


    len = strlen(hostname_or_ip);
    addr = malloc(sizeof(Address) + len + 1);
    if (addr == NULL) {
        return NULL;
    }
    addr->type = HOSTNAME;
    addr->port = 0;
    addr->len = len;
    memcpy(&addr->field_0x12, hostname_or_ip, len);
    ((char *) &addr->field_0x12)[addr->len] = '\0';
    for (p = (char *) &addr->field_0x12; *p != '\0'; p++) {
        *p = tolower(*p);
    }
    return addr;
}