static int
libusb_udev_select_interface(USB_DEV_HANDLE hDevice, unsigned char interfaceNumber,
                unsigned char alternateSetting)
{
 int rc = 0;
 int diff = 0;
 struct usb_dev_handle *devHandle = (struct usb_dev_handle *)hDevice;
 struct urbdrc *ctx = NULL;
 MSUSB_BULK *msusb = NULL;
 MSUSB_CONFIG *config = NULL;
 MSUSB_INTERFACE **interfaces = NULL;

 if (!devHandle || !devHandle->ctx)
 {
  rc = -1;
  goto fail;
 }

 ctx = devHandle->ctx;
 config = devHandle->config;

 if (config)
 {
  interfaces = config->interfaces;

  if (interfaces)
  {
   WLog_Print(ctx->log, 0x0002,
              "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)",
              interfaceNumber, interfaces[interfaceNumber]->alternateSetting,
              alternateSetting);

   if (interfaces[interfaceNumber]->alternateSetting != alternateSetting)
   {
    diff = 1;
   }
  }
  else
  {
   if (diff)
   {
    rc = libusb_set_interface_alt_setting(devHandle->handle, interfaceNumber, alternateSetting);
    log_libusb_result_(ctx->log, 0x0004, "libusb_set_interface_alt_setting", rc);
   }
  }
 }
 else
 {
  rc = rc;
 }

fail:
 return rc;
}