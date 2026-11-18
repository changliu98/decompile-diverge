void ConvertND(struct nd_opt_hdr *ptr)
{
 int temp;
 struct nd_opt_mtu *nd_mtu;

 nd_opt=(struct nd_opt_hdr *)ptr;
 nd_mtu=(struct nd_opt_mtu *)ptr;

 temp=nd_opt->nd_opt_len;
 nd_opt->nd_opt_len=htonl(nd_opt->nd_opt_len);
 nd_mtu->nd_opt_mtu_len=htonl(nd_mtu->nd_opt_mtu_len);

}