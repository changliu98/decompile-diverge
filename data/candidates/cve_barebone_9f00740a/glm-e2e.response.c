void get_conn_text(int *arg1, int arg2, char *out_buf, void *addr_struct) {
    char ip_str[4112]; 
    char *proto_str = "udp";
    unsigned short port = 0;
    int arg2_copy = arg2;

    ip_str[0] = '\0';

    switch (arg2_copy) {
        case 1:
            strncpy(ip_str, (char *)addr_struct + 2, 0xfff);
            ((char *)addr_struct)[0xfff + 2] = '\0';
            proto_str = "unix";
            break;
            
        case 2:
            inet_ntop(arg2, (char *)addr_struct + 4, ip_str, 0xfff);
            port = ntohs(*((unsigned short *)addr_struct + 1));
            proto_str = (*arg1 == 2) ? "tcp" : "udp";
            break;
            
        case 10:
            ip_str[0] = '[';
            ip_str[1] = '\0';
            if (inet_ntop(arg2, (char *)addr_struct + 8, ip_str + 1, 0xffe) != NULL) {
                strcat(ip_str, "]");
            }
            port = ntohs(*((unsigned short *)addr_struct + 1));
            proto_str = (*arg1 == 2) ? "tcp6" : "udp6";
            break;
    }

    if (strlen(ip_str) < 2) {
        sprintf(ip_str, "AF=%d", arg2);
    }

    if (port != 0) {
        sprintf(out_buf, "%s:%s-%d", proto_str, ip_str, port);
    } else {
        sprintf(out_buf, "%s:%s", proto_str, ip_str);
    }
}