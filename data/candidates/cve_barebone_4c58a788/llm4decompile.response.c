esp_err_t usb_class_request_get_descriptor(hid_device_t *hid_device, hid_class_request_t *req)
{
    esp_err_t err;
    usb_transfer_t *ctrl_xfer = hid_device->ctrl_xfer;
    size_t ctrl_size = ctrl_xfer->data_buffer_size;
    uint8_t *data_buffer;
    size_t size = req->wLength + 8;

    if (!hid_device || !hid_device->ctrl_xfer || !req || !req->data) {
        return ESP_ERR_INVALID_ARG;
    }

    err = hid_device_try_lock(hid_device, 5000);
    if (err) {
        return err;
    }

    if (size > ctrl_size) {
        usb_device_info_t dev_info;
        usb_host_device_info(hid_device->dev_hdl, &dev_info);
        usb_host_transfer_free(hid_device->ctrl_xfer);
        err = usb_host_transfer_alloc(size, 0, &hid_device->ctrl_xfer);
        if (err) {
            return err;
        }
    }

    data_buffer = ctrl_xfer->data_buffer;
    data_buffer[0] = 0x81;
    data_buffer[1] = req->bRequest;
    *(uint16_t *)&data_buffer[2] = req->wValue;
    *(uint16_t *)&data_buffer[4] = req->wIndex;
    *(uint16_t *)&data_buffer[6] = req->wLength;

    err = hid_control_transfer(hid_device, size, 5000);
    if (err) {
        goto out;
    }

    ctrl_xfer->actual_num_bytes -= 8;
    if (ctrl_xfer->actual_num_bytes > req->wLength) {
        err = ESP_ERR_INVALID_SIZE;
        goto out;
    }

    memcpy(req->data, ctrl_xfer->data_buffer + 8, ctrl_xfer->actual_num_bytes);

out:
    hid_device_unlock(hid_device);
    return err;
}