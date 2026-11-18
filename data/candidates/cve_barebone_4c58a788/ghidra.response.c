esp_err_t usb_class_request_get_descriptor(hid_device_t *hid_device,hid_class_request_t *req)

{
  usb_transfer_t *puVar1;
  ulong uVar2;
  uint8_t *puVar3;
  esp_err_t eVar4;
  usb_setup_packet_t *setup;
  esp_err_t err_rc__1;
  usb_device_info_t dev_info;
  esp_err_t err_rc_;
  size_t ctrl_size;
  usb_transfer_t *ctrl_xfer;
  esp_err_t ret;
  hid_class_request_t *req_local;
  hid_device_t *hid_device_local;
  esp_err_t local_c;
  
  puVar1 = hid_device->ctrl_xfer;
  uVar2 = hid_device->ctrl_xfer->data_buffer_size;
  if (hid_device == (hid_device_t *)0x0) {
    local_c = 0x102;
  }
  else if (hid_device->ctrl_xfer == (usb_transfer_t *)0x0) {
    local_c = 0x102;
  }
  else if (req == (hid_class_request_t *)0x0) {
    local_c = 0x102;
  }
  else if (req->data == (uint8_t *)0x0) {
    local_c = 0x102;
  }
  else {
    local_c = hid_device_try_lock(hid_device,5000);
    if (local_c == 0) {
      if (uVar2 < (ulong)(long)(int)(req->wLength + 8)) {
        usb_host_device_info(hid_device->dev_hdl,&dev_info);
        usb_host_transfer_free(hid_device->ctrl_xfer);
        eVar4 = usb_host_transfer_alloc((long)(int)(req->wLength + 8),0,&hid_device->ctrl_xfer);
        if (eVar4 != 0) {
          return eVar4;
        }
      }
      puVar3 = puVar1->data_buffer;
      *puVar3 = 0x81;
      puVar3[1] = req->bRequest;
      *(uint16_t *)(puVar3 + 2) = req->wValue;
      *(uint16_t *)(puVar3 + 4) = req->wIndex;
      *(uint16_t *)(puVar3 + 6) = req->wLength;
      ret = hid_control_transfer(hid_device,(long)(int)(req->wLength + 8),5000);
      if (ret == 0) {
        puVar1->actual_num_bytes = puVar1->actual_num_bytes + -8;
        if ((int)(uint)req->wLength < puVar1->actual_num_bytes) {
          ret = 0x104;
        }
        else {
          memcpy(req->data,puVar1->data_buffer + 8,(long)puVar1->actual_num_bytes);
        }
      }
      hid_device_unlock(hid_device);
      local_c = ret;
    }
  }
  return local_c;
}