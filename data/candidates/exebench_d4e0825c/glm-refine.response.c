int __cdecl unix_socketpair(int domain, int type, int protocol, int sv[2])
{
    return socketpair(domain, type, protocol, sv);
}