bool __cdecl setsockopt_needs_rtnl(int optname)
{
    return optname >= 128 && optname <= 139;
}