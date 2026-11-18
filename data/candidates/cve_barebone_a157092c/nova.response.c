static struct usb_device_index *get_register(int fd, int reset) {
    int i;
    struct usb_device_index *d;

    close(fd);

    d = malloc(sizeof(struct usb_device_index));
    if (!d) {
        return NULL;
    }

    d->bus = device_index->bus;
    d->address = device_index->address;
    d->iface_index = device_index->iface_index;

    if (reset) {
        if (d->iface_index == 0) {
            d->iface_index = 0;
        } else {
            d->iface_index = find_next_interface(d->iface_index);
            if (d->iface_index == 0) {
                goto error;
            }
        }

        for (i = 0; i < d->iface_index; i++) {
            d->ifaces[i] = find_next_iface(device_index->ifaces[i]);
        }
    }

    device_index = NULL;
    return d;

error:
    free(d);
    return NULL;
}