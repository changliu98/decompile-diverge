static int usb_class_request_get_descriptor(hid_device_t *hid, hid_get_report_t *get_report)
{
    int err;
    usb_transfer_t *xfer = hid->control_xfer;
    size_t ctrl_size = hid->control_xfer->buffer_length;
    if ((hid == NULL)) { err = (258); goto fail; };
    if ((hid->control_xfer == NULL)) { err = (258); goto fail; };
    if ((get_report == NULL)) { err = (258); goto fail; };
    if ((get_report->data == NULL)) { err = (258); goto fail; };

    do { int __err = hid_device_try_lock(hid, 5000); if (__err) { err = __err; goto fail; } } while (0);

    if (ctrl_size < get_report->length + sizeof(hid_header_t))
    {
        usb_device_info_t info;
        usb_host_device_info(hid->dev_hdl, &info);
        usb_host_transfer_free(hid->control_xfer);
        err = usb_host_transfer_alloc(get_report->length + sizeof(hid_header_t), 0, hid->control_xfer);
        if (err != 0)
        {
            err = err;
            goto fail;
        }
        ctrl_size = get_report->length + sizeof(hid_header_t);
    }

    hid_header_t *header = (hid_header_t*)xfer->buffer;
    header->bmRequestType = 0x81;
    header->bReportID = get_report->report_id;
    header->wReportType = get_report->type;
    header->wIndex = get_report->interface_number;
    header->wLength = get_report->length;

    err = hid_control_transfer(hid, get_report->length + sizeof(hid_header_t), 5000);
    if (err == 0)
    {
        xfer->actual_length -= sizeof(hid_header_t);
        if (xfer->actual_length <= get_report->length)
        {
            memcpy(get_report->data, xfer->buffer + sizeof(hid_header_t), xfer->actual_length);
        }
        else
        {
            err = (260);
        }
    }
    hid_device_unlock(hid);
fail:
    return err;
}