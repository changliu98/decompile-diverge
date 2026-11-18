int FABSQ(void *arg, void *data)
{
 struct ifinfomsg *rt = data;
 struct sios_rtnl_rtnl *rtnl = arg;
 rtnl->ifindex = rt->ifi_index & ~0x80000000UL;
 rtnl->iftype = rt->ifi_type;
 return 1;
}