ogs_pfcp_subnet_t *__cdecl ogs_pfcp_subnet_add(
        const char *ipstr,
        const char *mask_or_numbits,
        const char *gateway,
        const char *dnn,
        const char *ifname)
{
  ogs_pfcp_subnet_t *subnet; // [rsp+0h] [rbp-40h] BYREF
  ogs_pfcp_dev_t *dev; // [rsp+8h] [rbp-38h]
  int rv; // [rsp+14h] [rbp-2Ch]
  const char *ifnamea; // [rsp+18h] [rbp-28h]
  const char *dnna; // [rsp+20h] [rbp-20h]
  const char *gatewaya; // [rsp+28h] [rbp-18h]
  const char *mask_or_numbitsa; // [rsp+30h] [rbp-10h]
  const char *ipstra; // [rsp+38h] [rbp-8h]

  ipstra = ipstr;
  mask_or_numbitsa = mask_or_numbits;
  gatewaya = gateway;
  dnna = dnn;
  ifnamea = ifname;
  dev = 0LL;
  subnet = 0LL;
  if ( !ifname )
  {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "ifname", 180LL);
    abort();
  }
  dev = ogs_pfcp_dev_find_by_ifname(ifnamea);
  if ( !dev )
    dev = ogs_pfcp_dev_add(ifnamea);
  if ( !dev )
  {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "dev", 185LL);
    abort();
  }
  pool_alloc(&subnet);
  if ( !subnet )
  {
    fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "subnet", 188LL);
    abort();
  }
  memset(subnet, 0, sizeof(ogs_pfcp_subnet_t));
  subnet->family = 0;
  subnet->dev = dev;
  if ( ipstra && mask_or_numbitsa )
  {
    rv = ogs_ipsubnet(&subnet->gw, ipstra, 0LL);
    if ( rv )
    {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 196LL);
      abort();
    }
    rv = ogs_ipsubnet(&subnet->sub, ipstra, mask_or_numbitsa);
    if ( rv )
    {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 199LL);
      abort();
    }
    subnet->family = subnet->gw.family;
  }
  if ( gatewaya )
  {
    rv = ogs_ipsubnet(&subnet->gw, gatewaya, 0LL);
    if ( rv )
    {
      fprintf(stderr, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 206LL);
      abort();
    }
  }
  if ( dnna )
    strcpy(subnet->dnn, dnna);
  ogs_list_add(&subnet_list, subnet);
  return subnet;
}