__attribute__((noinline))
static esp_err_t usb_class_request_get_descriptor(hid_device_t *hid_device, const hid_class_request_t *req)
{
    esp_err_t ret;
    usb_transfer_t *ctrl_xfer = hid_device->ctrl_xfer;
    const size_t ctrl_size = hid_device->ctrl_xfer->data_buffer_size;

    HID_RETURN_ON_INVALID_ARG(hid_device);
    HID_RETURN_ON_INVALID_ARG(hid_device->ctrl_xfer);
    HID_RETURN_ON_INVALID_ARG(req);
    HID_RETURN_ON_INVALID_ARG(req->data);

    HID_RETURN_ON_ERROR( hid_device_try_lock(hid_device, DEFAULT_TIMEOUT_MS),
                         "HID Device is busy by other task");

    if (ctrl_size < (USB_SETUP_PACKET_SIZE + req->wLength)) {
        usb_device_info_t dev_info;
        ESP_ERROR_CHECK(usb_host_device_info(hid_device->dev_hdl, &dev_info));
        // reallocate the ctrl xfer buffer for new length
        ESP_LOGD(TAG, "Change HID ctrl xfer size from %d to %d",
                 (int) ctrl_size,
                 (int) (USB_SETUP_PACKET_SIZE + req->wLength));

        usb_host_transfer_free(hid_device->ctrl_xfer);
        HID_RETURN_ON_ERROR( usb_host_transfer_alloc(USB_SETUP_PACKET_SIZE + req->wLength,
                                                     0,
                                                     &hid_device->ctrl_xfer),
                             "Unable to allocate transfer buffer for EP0");
    }

    usb_setup_packet_t *setup = (usb_setup_packet_t *)ctrl_xfer->data_buffer;

    setup->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN |
                           USB_BM_REQUEST_TYPE_TYPE_STANDARD |
                           USB_BM_REQUEST_TYPE_RECIP_INTERFACE;
    setup->bRequest = req->bRequest;
    setup->wValue = req->wValue;
    setup->wIndex = req->wIndex;
    setup->wLength = req->wLength;

    ret = hid_control_transfer(hid_device,
                               USB_SETUP_PACKET_SIZE + req->wLength,
                               DEFAULT_TIMEOUT_MS);

    if (ESP_OK == ret) {
        ctrl_xfer->actual_num_bytes -= USB_SETUP_PACKET_SIZE;
        if (ctrl_xfer->actual_num_bytes <= req->wLength) {
            memcpy(req->data, ctrl_xfer->data_buffer + USB_SETUP_PACKET_SIZE, ctrl_xfer->actual_num_bytes);
        } else {
            ret = ESP_ERR_INVALID_SIZE;
        }
    }

    hid_device_unlock(hid_device);

    return ret;
}