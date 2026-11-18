int cvmx_helper_get_ipd_port(int interface, int index) {
    int port;
    
    // The 'ja' instruction performs an unsigned comparison.
    // If interface > 5, it jumps to the default case.
    switch (interface) {
        case 0:
            port = index;
            break;
        case 1:
            port = index + 0x10;
            break;
        case 2:
            port = index + 0x20;
            break;
        case 3:
            port = index + 0x24;
            break;
        case 4:
            port = index + 0x28;
            break;
        case 5:
            port = index + 0x2c;
            break;
        default:
            port = -1;
            break;
    }
    
    return port;
}