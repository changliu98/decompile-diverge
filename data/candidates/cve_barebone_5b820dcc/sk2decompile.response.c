int libusb_udev_select_interface(struct libusb_device *dev,
                                 unsigned char interface_number,
                                 unsigned char alternate_setting) {
  int r = 0;
  int need_select = 0;
  libusb_context *ctx;
  libusb_device_handle *dev_handle;
  libusb_interface_descriptor **interface_descriptors;
  if (dev == NULL || dev->os_priv == NULL) return -1;
  ctx = (libusb_context *)dev->os_priv;
  dev_handle = (libusb_device_handle *)dev->os_handle;
  if (dev_handle != NULL) {
    interface_descriptors = dev_handle->interface_descriptors;
    if (interface_descriptors != NULL) {
      WLog_Print(ctx->log_ctx, 2,
                 "select Interface(%u) curr AlternateSetting(%u) new "
                 "AlternateSetting(%u)",
                 interface_number,
                 interface_descriptors[interface_number]->bAlternateSetting,
                 alternate_setting)
          ;
      need_select = (interface_descriptors[interface_number]
                         ->bAlternateSetting != alternate_setting);
    }
    if (need_select) {
      r = libusb_set_interface_alt_setting(dev->ctx, interface_number,
                                           alternate_setting);
      log_libusb_result_(ctx->log_ctx, 4, "libusb_set_interface_alt_setting", r);
    }
  }
  return r;
}