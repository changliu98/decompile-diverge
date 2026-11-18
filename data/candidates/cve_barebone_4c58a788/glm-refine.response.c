define ESP_ERR_INVALID_SIZE 260

esp_err_t __cdecl usb_class_request_get_descriptor(hid_device_t *hid_device, const hid_class_request_t *req)
{
  usb_device_info_t dev_info;
  esp_err_t ret;
  size_t ctrl_size;
  usb_transfer_t *ctrl_xfer;
  usb_setup_packet_t *setup;

  // 1. Null checks (Note: ctrl_xfer is dereferenced before its own null check)
  if (!hid_device || !hid_device->ctrl_xfer || !req || !req->data)
    return ESP_ERR_INVALID_ARG;

  ctrl_xfer = hid_device->ctrl_xfer;
  ctrl_size = ctrl_xfer->data_buffer_size;

  // 2. Lock the HID device
  ret = hid_device_try_lock(hid_device, 0x1388u);
  if (ret)
    return ret;

  // 3. Reallocate transfer buffer if it's too small
  if (ctrl_size < req->wLength + 8)
  {
    usb_host_device_info(hid_device->dev_hdl, &dev_info);
    usb_host_transfer_free(ctrl_xfer);
    ret = usb_host_transfer_alloc(req->wLength + 8, 0, &hid_device->ctrl_xfer);
    if (ret)
      return ret;
    
    // Update local pointer to the newly allocated transfer buffer
    ctrl_xfer = hid_device->ctrl_xfer;
  }

  // 4. Populate the USB setup packet
  setup = (usb_setup_packet_t *)ctrl_xfer->data_buffer;
  setup->bmRequestType = 0x81; // -127 as unsigned char
  setup->bRequest = req->bRequest;
  setup->wValue = req->wValue;
  setup->wIndex = req->wIndex;
  setup->wLength = req->wLength;

  // 5. Execute the control transfer
  ret = hid_control_transfer(hid_device, req->wLength + 8, 0x1388u);
  if (!ret)
  {
    // 6. Process the response payload
    ctrl_xfer->actual_num_bytes -= 8; // Subtract the 8-byte setup packet header size
    if (ctrl_xfer->actual_num_bytes > req->wLength)
    {
      ret = ESP_ERR_INVALID_SIZE;
    }
    else
    {
      // Copy the actual payload back to the requester's buffer
      memcpy(req->data, ctrl_xfer->data_buffer + 8, ctrl_xfer->actual_num_bytes);
    }
  }

  // 7. Unlock and return
  hid_device_unlock(hid_device);
  return ret;
}