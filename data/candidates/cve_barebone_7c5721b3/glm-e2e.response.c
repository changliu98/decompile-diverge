void *new_address(const char *str) {
    struct sockaddr_storage ss;
    char buf[0x80];
    char host_buf[0x80];
    void *ret = NULL;

    if (str == NULL) {
        return NULL;
    }

    // 1. Try parsing as IPv6 without brackets
    memset(&ss, 0, sizeof(ss));
    if (inet_pton(AF_INET6, str, &ss.ss_family + 2) == 1) {
        ss.ss_family = AF_INET6;
        return new_address_sa(&ss, 28);
    }

    // 2. Try parsing as UNIX domain socket
    if (strncmp(str, "unix:", 5) == 0) {
        if (strlen(str) >= 0x6c) {
            return NULL;
        }
        // Set sun_family to AF_UNIX (1)
        *(short*)&ss = 1;
        strncpy((char*)&ss + 2, str + 5, 0x6b);
        int len = strlen((char*)&ss + 2) + 3;
        return new_address_sa(&ss, len);
    }

    // 3. Try parsing as IP with port (e.g., "192.168.1.1:80" or "[::1]:80")
    char *colon = strrchr(str, ':');
    if (colon != NULL && is_numeric(colon + 1)) {
        long host_len = colon - str;
        int port = atoi(colon + 1);
        
        if (host_len < 0x106 && port >= 0 && port <= 0xffff) {
            strncpy(host_buf, str, host_len);
            host_buf[host_len] = '\0';
            
            void *addr = new_address(host_buf);
            if (addr != NULL) {
                address_set_port(addr, (unsigned short)port);
            }
            return addr;
        }
    }

    // 4. Try parsing as "any" (wildcard address)
    if (strcmp(str, "any") == 0) {
        void *addr = malloc(24);
        if (addr != NULL) {
            *(int*)addr = 2; // AF_INET
            *(long long*)((char*)addr + 8) = 0;
            address_set_port(addr, 0);
        }
        return addr;
    }

    // 5. Try parsing as IPv4
    memset(&ss, 0, sizeof(ss));
    if (inet_pton(AF_INET, str, &ss.ss_family + 4) == 1) {
        ss.ss_family = AF_INET;
        return new_address_sa(&ss, 16);
    }

    // 6. Try parsing as bracketed IPv6 (e.g., "[::1]")
    memset(&ss, 0, sizeof(ss));
    if (str[0] == '[') {
        char *end_bracket = strchr(str, ']');
        if (end_bracket != NULL) {
            long host_len = end_bracket - str - 1;
            strncpy(host_buf, str + 1, host_len);
            host_buf[host_len] = '\0';
            
            if (inet_pton(AF_INET6, host_buf, &ss.ss_family + 8) == 1) {
                ss.ss_family = AF_INET6;
                return new_address_sa(&ss, 28);
            }
        }
    }

    // 7. Try parsing as a hostname
    if (valid_hostname(str)) {
        size_t len = strlen(str);
        hostname_addr_t *addr = malloc(len + 0x13);
        if (addr != NULL) {
            addr->family = 0;
            addr->port = 0;
            addr->len = len;
            memcpy((char*)addr + 0x12, str, len);
            ((char*)addr)[0x12 + len] = '\0';
            
            // Convert hostname to lowercase
            char *p = (char*)addr + 0x12;
            while (*p != '\0') {
                *p = tolower(*p);
                p++;
            }
            return addr;
        }
    }

    return NULL;
}