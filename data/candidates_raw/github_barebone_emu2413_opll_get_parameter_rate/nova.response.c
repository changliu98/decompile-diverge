int func0(struct pcap_sf *psf) {
    int ret;
    if (psf->signature & 0x01) {
        if (psf->version == 0x00) {
            ret = 0;
        } else {
            ret = psf->sf.sf_version;
        }
    } else {
        unsigned char *p = (unsigned char *)psf->sf.sf_version;
        if (p - (unsigned char *)psf < 4) {
            ret = *(int *)p;
        } else {
            ret = psf->sf.sf_version;
        }
    }
    return ret;
}