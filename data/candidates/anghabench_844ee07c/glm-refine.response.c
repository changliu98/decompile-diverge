int __cdecl cvmx_helper_get_ipd_port(int interface, int port)
{
    // Offsets corresponding to interfaces 0 through 5
    static const int offsets[] = { 0, 16, 32, 36, 40, 44 };

    if (interface >= 0 && interface <= 5) {
        return port + offsets[interface];
    }

    return -1;
}