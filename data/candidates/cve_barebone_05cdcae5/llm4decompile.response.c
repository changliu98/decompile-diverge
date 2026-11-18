ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(char *ipstr, char *mask_or_numbits,
        char *gateway, char *dnn, char *ifname)
{
    int rv;
    ogs_pfcp_dev_t *dev = NULL;
    ogs_pfcp_subnet_t *subnet = NULL;

    do { if (!(ifname)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "ifname", 180); abort(); } } while (0);

    dev = ogs_pfcp_dev_find_by_ifname(ifname);
    if (!dev)
        dev = ogs_pfcp_dev_add(ifname);
    do { if (!(dev)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "dev", 185); abort(); } } while (0);

    pool_alloc(&subnet);
    do { if (!(subnet)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "subnet", 188); abort(); } } while (0);

    memset(subnet, 0, sizeof(*subnet));
    subnet->dev = dev;
    subnet->family = 0;

    if (ipstr && mask_or_numbits) {
        rv = ogs_ipsubnet(&subnet->gw, ipstr, NULL);
        do { if (!(rv == 0)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 196); abort(); } } while (0);

        rv = ogs_ipsubnet(&subnet->sub, ipstr, mask_or_numbits);
        do { if (!(rv == 0)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 199); abort(); } } while (0);

        subnet->family = subnet->gw.family;
    }

    if (gateway) {
        rv = ogs_ipsubnet(&subnet->gw, gateway, NULL);
        do { if (!(rv == 0)) { fprintf(PTR_stderr_00103ff8, "ogs_assert failed: %s (line %d)\n", "rv == OGS_OK", 206); abort(); } } while (0);
    }

    if (dnn)
        strcpy(subnet->dnn, dnn);

    ogs_list_add(&subnet_list, subnet);

    return subnet;
}