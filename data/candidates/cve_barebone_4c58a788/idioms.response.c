static esp_err_t usb_class_request_get_descriptor(struct hid_device *dev, struct hid_class_request *req)
{
    struct usb_device_info info;
    struct usb_transfer *ctrl = dev->ctrl_xfer;
    unsigned long ctrl_size = dev->ctrl_xfer->data_buffer_size;
    if (dev == ((void *)0))
        return (ESP_ERR_HID_INVALID_PARAM);
    if (dev->ctrl_xfer == ((void *)0))
        return (ESP_ERR_HID_INVALID_PARAM);
    if (req == ((void *)0))
        return (ESP_ERR_HID_INVALID_PARAM);
    if (req->data == ((void *)0))
        return (ESP_ERR_HID_INVALID_PARAM);
    esp_err_t err = hid_get_device_info(dev, 0x1388);
    if (err != (ESP_OK))
        return err;
    if (ctrl_size < (req->wLength + sizeof(struct usb_setup_packet))) {
        hid_get_device_info(dev->dev_hdl, &info);
        hid_transfer_free(dev->ctrl_xfer);
        err = hid_transfer_alloc(req->wLength + sizeof(struct usb_setup_packet), 0, &dev->ctrl_xfer);
        if (err != (ESP_OK))
            return err;
    }
    struct usb_setup_packet *setup = (struct usb_setup_packet *)ctrl->data_buffer;
    setup->bmRequestType = (0x80 | 0x40 | 0x01);
    setup->bRequest = req->bRequest;
    setup->wValue = req->wValue;
    setup->wIndex = req->wIndex;
    setup->wLength = req->wLength;
    err = hid_send_control_transfer(dev,
                                    sizeof(struct usb_setup_packet) + req->wLength,
                                    0x1388);
    if (err != (ESP_OK))
        goto fail;
    ctrl->actual_num_bytes -= sizeof(struct usb_setup_packet);
    if (ctrl->actual_num_bytes <= req->wLength)
        memmove(req->data,
                ctrl->data_buffer + sizeof(struct usb_setup_packet),
                ctrl->actual_num_bytes);
    else
        err = (ESP_ERR_HID_INVALID_RESPONSE);
fail:
    hid_transfer_free(dev);
    return err;
}