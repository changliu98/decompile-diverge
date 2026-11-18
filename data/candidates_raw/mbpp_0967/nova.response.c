static struct pci_driver *func0(char *id) {
    int i, j, k, l;
    struct pci_driver *drv;
    char *driver_id[5] = {
        PCI_VENDOR_ID_INTEL,
        PCI_VENDOR_ID_NVIDIA,
        PCI_VENDOR_ID_VIA,
        PCI_VENDOR_ID_ATI,
        PCI_VENDOR_ID_S3,
    };

    for (i = 0; i < 5; i++) {
        int found[40];
        memset(found, 0, sizeof(found));
        for (j = 0;; j++) {
            if (id[j] == '\0')
                break;
            for (k = 0; k < 10; k++) {
                if (id[j] == driver_id[i][k]) {
                    if (found[k] == 0) {
                        found[k] = 1;
                        i++;
                    }
                    break;
                }
            }
        }
    }

    if (i < 6)
        drv = &amd_driver;
    else
        drv = &i82875p_driver;

    return drv;
}