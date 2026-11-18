/**
 * Get the IPD (Input Packet Delivery) port number for a given interface and port.
 *
 * @param interface The interface index (0-5).
 * @param port      The port number within the interface.
 * @return          The calculated IPD port number, or -1 if the interface is invalid.
 */
int cvmx_helper_get_ipd_port(int iface_idx, int port_num)
{
    switch (iface_idx) {
    case 0: return port_num;
    case 1: return port_num + 0x10;
    case 2: return port_num + 0x20;
    case 3: return port_num + 0x24;
    case 4: return port_num + 0x28;
    case 5: return port_num + 0x2c;
    default: return -1;
    }
}