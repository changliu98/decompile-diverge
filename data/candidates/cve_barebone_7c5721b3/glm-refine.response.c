Address *new_address(const char *hostname_or_ip)
{
    struct sockaddr_storage ss;
    char ip_buf[262];
    const char *port_str;
    size_t ip_len;
    unsigned int port_num;

    if (!hostname_or_ip)
        return NULL;

    // 1. Try parsing as an IPv6 address
    memset(&ss, 0, sizeof(ss));
    if (inet_pton(AF_INET6, hostname_or_ip, &((struct sockaddr_in6 *)&ss)->sin6_addr) == 1)
    {
        ss.ss_family = AF_INET6;
        return new_address_sa((struct sockaddr *)&ss, sizeof(struct sockaddr_in6));
    }

    // 2. Try parsing as a Unix domain socket
    memset(&ss, 0, sizeof(ss));
    if (!strncmp("unix:", hostname_or_ip, 5))
    {
        if (strlen(hostname_or_ip) < 0x6C) // 108 bytes (UNIX_PATH_MAX)
        {
            struct sockaddr_un *un = (struct sockaddr_un *)&ss;
            un->sun_family = AF_UNIX;
            strncpy(un->sun_path, hostname_or_ip + 5, 0x6B);
            return new_address_sa((struct sockaddr *)un, strlen(un->sun_path) + 3);
        }
        return NULL;
    }

    // 3. Try parsing as "IP:Port" or "Hostname:Port"
    port_str = strrchr(hostname_or_ip, ':');
    if (port_str && is_numeric(port_str + 1))
    {
        ip_len = port_str - hostname_or_ip;
        port_num = atoi(port_str + 1);
        
        if (ip_len < 0x106 && port_num <= 0xFFFF)
        {
            strncpy(ip_buf, hostname_or_ip, ip_len);
            ip_buf[ip_len] = '\0';
            
            Address *addr = new_address(ip_buf);
            if (addr)
                address_set_port(addr, port_num);
            return addr;
        }
    }

    // 4. Try parsing as Wildcard ("*")
    if (!strcmp("*", hostname_or_ip))
    {
        Address *addr = (Address *)malloc(0x18); // 24 bytes
        if (addr)
        {
            addr->type = ADDR_TYPE_WILDCARD;
            addr->len = 0;
            address_set_port(addr, 0);
        }
        return addr;
    }

    // 5. Try parsing as an IPv4 address
    memset(&ss, 0, sizeof(ss));
    if (inet_pton(AF_INET, hostname_or_ip, &((struct sockaddr_in *)&ss)->sin_addr) == 1)
    {
        ss.ss_family = AF_INET;
        return new_address_sa((struct sockaddr *)&ss, sizeof(struct sockaddr_in));
    }

    // 6. Try parsing as "[IPv6]:Port" format
    memset(&ss, 0, sizeof(ss));
    if (hostname_or_ip[0] == '[')
    {
        port_str = strchr(hostname_or_ip, ']');
        if (port_str)
        {
            ip_len = port_str - hostname_or_ip - 1;
            strncpy(ip_buf, hostname_or_ip + 1, ip_len);
            ip_buf[ip_len] = '\0';
            
            if (inet_pton(AF_INET6, ip_buf, &((struct sockaddr_in6 *)&ss)->sin6_addr) == 1)
            {
                ss.ss_family = AF_INET6;
                return new_address_sa((struct sockaddr *)&ss, sizeof(struct sockaddr_in6));
            }
        }
    }

    // 7. Try parsing as a Hostname
    if (valid_hostname(hostname_or_ip))
    {
        size_t len = strlen(hostname_or_ip);
        Address *addr = (Address *)malloc(len + 19); // 16-byte header + 2 extra bytes + string
        if (addr)
        {
            addr->type = ADDR_TYPE_HOSTNAME;
            addr->port = 0;
            addr->len = len;
            memcpy(addr->data, hostname_or_ip, len);
            addr->data[len] = '\0';
            
            // Convert hostname to lowercase
            for (char *c = addr->data; *c; ++c)
                *c = tolower(*c);
        }
        return addr;
    }

    // 8. Fallback
    return NULL;
}