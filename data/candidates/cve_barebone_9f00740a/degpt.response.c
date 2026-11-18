void get_conn_text(conn *connection, int address_family, char *output_buffer, sockaddr *socket_address)
{
    char address_string[4096];
    const char *protocol_name = "?";
    unsigned short port_number = 0;

    // Initialize addr_text to empty string
    address_string[0] = '\0';

    // Handle AF_UNIX (address family 1)
    if (address_family == 1) {
        strncpy(address_string, socket_address->sa_data, 0xfff);
        address_string[0xfff] = '\0';
        protocol_name = "unix";
    }
    // Handle AF_INET (address family 2)
    else if (address_family == 2) {
        inet_ntop(2, socket_address->sa_data + 2, address_string, 0xfff);
        port_number = ntohs(*(uint16_t *)socket_address->sa_data);
        protocol_name = (connection->transport == udp_transport) ? "udp" : "tcp";
    }
    // Handle AF_INET6 (address family 10)
    else if (address_family == 10) {
        address_string[0] = '[';
        address_string[1] = '\0';
        if (inet_ntop(10, socket_address->sa_data + 6, address_string + 1, 0xffe) != NULL) {
            strcat(address_string, "]");
        }
        port_number = ntohs(*(uint16_t *)socket_address->sa_data);
        protocol_name = (connection->transport == udp_transport) ? "udp6" : "tcp6";
    }

    // If addr_text is empty or too short, use a placeholder
    if (strlen(address_string) < 2) {
        sprintf(address_string, "<AF %d>", address_family);
    }

    // Format the final address string with protocol name and port
    if (port_number == 0) {
        sprintf(output_buffer, "%s:%s", protocol_name, address_string);
    }
    else {
        sprintf(output_buffer, "%s:%s:%u", protocol_name, address_string, port_number);
    }
}