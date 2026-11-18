static int hexagon_v6_op(struct net *net, struct ip_tunnel_net *itn,
			  struct ip_tunnel_parm *parms,
			  struct net_device *dev, int oif, int link,
			  struct ip_tunnel_encap *ipencap)
{
	struct ip_tunnel_encap tnl_encap;
	int err;

	memset(&tnl_encap, 0, sizeof(tnl_encap));

	err = ip_tunnel_encap_init(dev, &tnl_encap);

	itn->ipencap = tnl_encap;

	if (err > 0) {
		itn->ipencap.link = link;
		err = ip_tunnel_encap_register(net, &itn->ipencap, parms->i_flags);
	} else {
		itn->ipencap.link = err;
		err = ip_tunnel_encap_register(net, &itn->ipencap, parms->i_flags);
	}

	return err;
}