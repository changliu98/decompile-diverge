void handle_PORT(ctrl_t *control_struct, char *port_command_string)
{
    sockaddr_in socket_address;
    char ip_address_buffer[16];
    int ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, port_byte_high, port_byte_low;
    int inet_conversion_result;

    // If an existing data connection is open, stop the watcher and close the socket
    if (0 < control_struct->data_sd) {
        uev_io_stop(&control_struct->data_watcher);
        close(control_struct->data_sd);
        control_struct->data_sd = -1;
    }
    // Parse the PORT command string into IP octets (a,b,c,d) and port bytes (e,f)
    __isoc99_sscanf(port_command_string, "%d,%d,%d,%d,%d,%d", &ip_octet_1, &ip_octet_2, &ip_octet_3, &ip_octet_4, &port_byte_high, &port_byte_low);
    // Construct the IP address string from the parsed octets
    sprintf(ip_address_buffer, "%d.%d.%d.%d", (ulong)(uint)ip_octet_1, (ulong)(uint)ip_octet_2, (ulong)(uint)ip_octet_3, (ulong)(uint)ip_octet_4);
    // Convert the IP address string to binary format
    inet_conversion_result = inet_aton(ip_address_buffer, (in_addr *)&socket_address.sin_addr);
    // If the IP address is invalid, send an error response
    if (inet_conversion_result == 0) {
        send_msg(control_struct->sd, "500 Illegal PORT command.\r\n");
    } else {
        // Store the valid IP address in the control structure
        strlcpy(control_struct->data_address, ip_address_buffer, 0x10);
        // Calculate the port number from the two bytes (e * 256 + f)
        control_struct->data_port = port_byte_high * 0x100 + port_byte_low;
        // Send success response to the client
        send_msg(control_struct->sd, "200 PORT command successful.\r\n");
    }
}