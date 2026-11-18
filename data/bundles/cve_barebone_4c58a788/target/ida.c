esp_err_t __cdecl usb_class_request_get_descriptor(hid_device_t *hid_device, const hid_class_request_t *req)
{
  usb_setup_packet_t *setup; // [rsp+8h] [rbp-78h]
  esp_err_t err_rc__0; // [rsp+14h] [rbp-6Ch]
  usb_device_info_t dev_info; // [rsp+18h] [rbp-68h] BYREF
  esp_err_t err_rc_; // [rsp+4Ch] [rbp-34h]
  size_t ctrl_size; // [rsp+50h] [rbp-30h]
  usb_transfer_t *ctrl_xfer; // [rsp+58h] [rbp-28h]
  esp_err_t ret; // [rsp+64h] [rbp-1Ch]
  const hid_class_request_t *reqa; // [rsp+68h] [rbp-18h]
  hid_device_t *hid_devicea; // [rsp+70h] [rbp-10h]

  hid_devicea = hid_device;
  reqa = req;
  ctrl_xfer = hid_device->ctrl_xfer;
  ctrl_size = hid_device->ctrl_xfer->data_buffer_size;
  if ( !hid_device )
    return 258;
  if ( !hid_devicea->ctrl_xfer )
    return 258;
  if ( !reqa )
    return 258;
  if ( !reqa->data )
    return 258;
  err_rc_ = hid_device_try_lock(hid_devicea, 0x1388u);
  if ( err_rc_ )
    return err_rc_;
  if ( ctrl_size < reqa->wLength + 8 )
  {
    usb_host_device_info(hid_devicea->dev_hdl, &dev_info);
    usb_host_transfer_free(hid_devicea->ctrl_xfer);
    err_rc__0 = usb_host_transfer_alloc(reqa->wLength + 8, 0, &hid_devicea->ctrl_xfer);
    if ( err_rc__0 )
      return err_rc__0;
  }
  setup = (usb_setup_packet_t *)ctrl_xfer->data_buffer;
  setup->bmRequestType = -127;
  setup->bRequest = reqa->bRequest;
  setup->wValue = reqa->wValue;
  setup->wIndex = reqa->wIndex;
  setup->wLength = reqa->wLength;
  ret = hid_control_transfer(hid_devicea, reqa->wLength + 8, 0x1388u);
  if ( !ret )
  {
    ctrl_xfer->actual_num_bytes -= 8;
    if ( ctrl_xfer->actual_num_bytes > reqa->wLength )
      ret = 260;
    else
      memcpy(reqa->data, ctrl_xfer->data_buffer + 8, ctrl_xfer->actual_num_bytes);
  }
  hid_device_unlock(hid_devicea);
  return ret;
}