esp_err_t usb_class_request_get_descriptor(usb_class_handle_t *class_handle,
                                           usb_descriptor_request_t *request) {
  usb_transfer_t *ctrl_xfer = class_handle->ctrl_xfer;
  size_t ctrl_size = ctrl_xfer->size;
  esp_err_t ret;
  if (class_handle == NULL) {
    return 0x0102;
  }
  if (class_handle->ctrl_xfer == NULL) {
    return 0x0102;
  }
  if (request == NULL) {
    return 0x0102;
  }
  if (request->buffer == NULL) {
    return 0x0102;
  }
  ret = hid_device_try_lock(class_handle, 5000);
  if (ret != 0) {
    return ret;
  }
  if (ctrl_size < request->length + 8) {
    usb_host_device_info_t device_info;
    usb_host_device_info(class_handle->device_handle, &device_info);
    usb_host_transfer_free(class_handle->ctrl_xfer);
    ret = usb_host_transfer_alloc(request->length + 8, 0,
                                  &class_handle->ctrl_xfer);
    if (ret != 0) {
      return ret;
    }
  }
  usb_hid_control_request_t *ctrl_req =
      (usb_hid_control_request_t *)ctrl_xfer->buffer;
  ctrl_req->bmRequestType = 0x81;
  ctrl_req->bRequest = request->bRequest;
  ctrl_req->wValue = request->wValue;
  ctrl_req->wIndex = request->wIndex;
  ctrl_req->wLength = request->length;
  ret = hid_control_transfer(class_handle, request->length + 8, 5000);
  if (ret != 0) {
    hid_device_unlock(class_handle);
    return ret;
  }
  ctrl_xfer->actual_length -= 8;
  if (ctrl_xfer->actual_length <= request->length) {
    memcpy(request->buffer, ctrl_xfer->buffer + 8, ctrl_xfer->actual_length);
  } else {
    ret = 0x0104;
  }
  hid_device_unlock(class_handle);
  return ret;
}