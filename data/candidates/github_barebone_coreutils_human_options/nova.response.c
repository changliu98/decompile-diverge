static int human_options(const char *buf, size_t len, sd_dhcp_lease *lease) {
        int r;

        r = dhcp_option_parse_ip_addresses(buf, len, lease);

        if (!lease->subnet_mask) {
                lease->subnet_mask = sd_dhcp_lease_get_subnet_mask(lease);
                r = sizeof(sd_dhcp_lease_get_subnet_mask(lease));
        }

        return r;
}