bool setsockopt_needs_rtnl(int socket_option)
{
    return (uint)(socket_option - 0x80U) < 0xc;
}