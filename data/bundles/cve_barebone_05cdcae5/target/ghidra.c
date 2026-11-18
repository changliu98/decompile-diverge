ogs_pfcp_subnet_t *
ogs_pfcp_subnet_add(char *ipstr,char *mask_or_numbits,char *gateway,char *dnn,char *ifname)

{
  ogs_pfcp_subnet_t *subnet;
  ogs_pfcp_dev_t *dev;
  int rv;
  char *ifname_local;
  char *dnn_local;
  char *gateway_local;
  char *mask_or_numbits_local;
  char *ipstr_local;
  
  dev = (ogs_pfcp_dev_t *)0x0;
  subnet = (ogs_pfcp_subnet_t *)0x0;
  ifname_local = ifname;
  dnn_local = dnn;
  gateway_local = gateway;
  mask_or_numbits_local = mask_or_numbits;
  ipstr_local = ipstr;
  if (ifname == (char *)0x0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n","ifname",0xb4);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  dev = ogs_pfcp_dev_find_by_ifname(ifname);
  if (dev == (ogs_pfcp_dev_t *)0x0) {
    dev = ogs_pfcp_dev_add(ifname_local);
  }
  if (dev == (ogs_pfcp_dev_t *)0x0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n",&DAT_0010202c,0xb9);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  pool_alloc(&subnet);
  if (subnet == (ogs_pfcp_subnet_t *)0x0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n","subnet",0xbc);
                    /* WARNING: Subroutine does not return */
    abort();
  }
  memset(subnet,0,0x1d8);
  subnet->family = 0;
  subnet->dev = dev;
  if ((ipstr_local != (char *)0x0) && (mask_or_numbits_local != (char *)0x0)) {
    rv = ogs_ipsubnet(&subnet->gw,ipstr_local,(char *)0x0);
    if (rv != 0) {
      fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n","rv == OGS_OK",0xc4)
      ;
                    /* WARNING: Subroutine does not return */
      abort();
    }
    rv = ogs_ipsubnet(&subnet->sub,ipstr_local,mask_or_numbits_local);
    if (rv != 0) {
      fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n","rv == OGS_OK",199);
                    /* WARNING: Subroutine does not return */
      abort();
    }
    subnet->family = (subnet->gw).family;
    rv = 0;
  }
  if (gateway_local != (char *)0x0) {
    rv = ogs_ipsubnet(&subnet->gw,gateway_local,(char *)0x0);
    if (rv != 0) {
      fprintf(*(FILE **)PTR_stderr_00103ff8,"ogs_assert failed: %s (line %d)\n","rv == OGS_OK",0xce)
      ;
                    /* WARNING: Subroutine does not return */
      abort();
    }
    rv = 0;
  }
  if (dnn_local != (char *)0x0) {
    strcpy(subnet->dnn,dnn_local);
  }
  ogs_list_add(&subnet_list,subnet);
  return subnet;
}