int cvmx_helper_get_ipd_port(int interface, int port)
{
    int ipd_port = -1;
    switch (interface)
    {
        case 0:
            ipd_port = port;
            break;
        case 1:
            ipd_port = 16 + port;
            break;
        case 2:
            ipd_port = 32 + port;
            break;
        case 3:
            ipd_port = 36 + port;
            break;
        case 4:
            ipd_port = 40 + port;
            break;
        case 5:
            ipd_port = 44 + port;
            break;
    }
    return ipd_port;
}