void print_address(struct conn *c, int af, char *addr, struct sockaddr *sa)
{
    char addr_text[4096];
    char *protoname;
    unsigned short port;
    addr_text[0] = '\0';
    protoname = "?";
    port = 0;
    switch (af) {
    case 1:
        inet_ntop(af, (void *) &sa->sa_data, addr_text, sizeof(addr_text)-1);
        addr_text[sizeof(addr_text)-1] = '\0';
        protoname = "unix";
        break;
    case 2:
        inet_ntop(af, (void *) &((struct sockaddr_in *) sa)->sin_addr,
                 addr_text, sizeof(addr_text)-1);
        port = get_port(((struct sockaddr_in *) sa)->sin_port);
        protoname = (c->transport == network_transport::tcp_transport ? "tcp" : "udp");
        break;
    case 10:
        strcpy(addr_text, "[");
        if (inet_ntop(af, (void *) &((struct sockaddr_in6 *) sa)->sin6_addr.__in6_u.__u6_addr8,
                     addr_text + 1, sizeof(addr_text)-2))
            strncat(addr_text, "]", sizeof(addr_text));
        port = get_port(((struct sockaddr_in6 *) sa)->sin6_port);
        protoname = (c->transport == network_transport::tcp_transport ? "tcp6" : "udp6");
        break;
    }
    if (strlen(addr_text) < 2)
        strncat(addr_text, " (AF %d)", sizeof(addr_text), af);
    if (port)
        strncat(addr, "%s:%s:%u", protoname, addr_text, port);
    else
        strncat(addr, "%s:%s", protoname, addr_text);
}