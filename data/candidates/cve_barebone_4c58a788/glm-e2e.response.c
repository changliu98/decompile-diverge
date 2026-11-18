int usb_class_request_get_descriptor(struct usb_device *dev, struct usb_setup_packet *setup) {
    int ret = 0x102; // -254
    int status;
    struct usb_transfer *transfer;
    long buffer_size;
    struct usb_host_device_info info;
    int alloc_status;

    if (!dev || !dev->transfer || !setup || !setup->data) {
        return -254;
    }

    transfer = dev->transfer;
    buffer_size = dev->transfer->buffer_size; // inferred from offset 0x8

    status = hid_device_try_lock(dev, 5000); // 0x1388 = 5000
    if (status != 0) {
        return status;
    }

    if (buffer_size < (long)setup->wLength + 8) {
        usb_host_device_info(dev, &info);
        usb_host_transfer_free(transfer);
        alloc_status = usb_host_transfer_alloc(transfer, 0, setup->wLength + 8);
        if (alloc_status != 0) {
            return alloc_status;
        }
    }

    transfer->buffer[0] = 0x81;
    transfer->buffer[1] = setup->bmRequestType;
    *(unsigned short *)(transfer->buffer + 2) = setup->wValue;
    *(unsigned short *)(transfer->buffer + 4) = setup->wIndex;
    *(unsigned short *)(transfer->buffer + 6) = setup->wLength;

    ret = hid_control_transfer(dev, setup->wLength + 8, 5000);
    if (ret == 0) {
        transfer->actual_length -= 8;
        if (transfer->actual_length > setup->wLength) {
            ret = -252; // 0x104
        } else {
            memcpy(setup->data, transfer->buffer + 8, transfer->actual_length);
        }
    }

    hid_device_unlock(dev);
    return ret;
}