struct ogs_pfcp_subnet *ogs_pfcp_subnet_add(char *ipstr, char *mask_or_numbits, char *gateway, char *dnn, char *ifname)
{
  int rv;
  char *ipstr_ = ipstr; char *mask_or_numbits_ = mask_or_numbits; char *gateway_ = gateway; char *dnn_ = dnn; char *ifname_ = ifname;
  struct ogs_pfcp_dev *dev = ((void *)0);
  struct ogs_pfcp_subnet *subnet = ((void *)0);
  do { if (!(ifname)) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "ifname", 180); abort(); } } while (0);
  dev = ogs_pfcp_dev_find_by_ifname(ifname_);
  if (!dev)
    dev = ogs_pfcp_dev_add(ifname_);
  do { if (!(dev)) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "dev", 185); abort(); } } while (0);
  do { if (!((subnet = (struct ogs_pfcp_subnet *)pool_alloc((&subnet)) != ((void *)0))) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "subnet", 188); abort(); } } while (0);
  memset(subnet, 0, sizeof(*subnet));
  subnet->family = 0;
  subnet->dev = dev;
  if (ipstr_ && mask_or_numbits_) {
    do { if (!((rv = ogs_ipsubnet(&subnet->gw, ipstr_, ((void *)0))) == (OGS_OK))) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 196); abort(); } } while (0);
    do { if (!((rv = ogs_ipsubnet(&subnet->sub, ipstr_, mask_or_numbits_)) == (OGS_OK))) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 199); abort(); } } while (0);
    subnet->family = subnet->gw.family;
  }
  if (gateway_) {
    do { if (!((rv = ogs_ipsubnet(&subnet->gw, gateway_, ((void *)0))) == (OGS_OK))) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 206); abort(); } } while (0);
  }
  if (dnn_)
    strcpy(subnet->dnn, dnn_);
  ogs_list_add(&subnet_list, subnet);
  return subnet;
}