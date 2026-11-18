int libusb_udev_select_interface(IUDEVICE *idev, unsigned char InterfaceNumber, unsigned char AlternateSetting)
{
 int result = 0;
 int need_set = 0;
 URBDRC_PLUGIN *urbdrc;
 UDEVICE *pdev;
 wLog *log;

 if (idev == NULL || idev->priv == NULL) {
  return -1;
 }
 urbdrc = (URBDRC_PLUGIN *) idev->priv;
 log = urbdrc->log;

 if (idev->MsConfig != NULL) {
  MsConfig = (MSUSB_CONFIG_DESCRIPTOR *) idev->MsConfig;
  MsInterfaces = (MSUSB_INTERFACE_DESCRIPTOR **) MsConfig->MsInterfaces;
  if (MsInterfaces != NULL) {
   WLog_Print(log, 2, "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)", InterfaceNumber, MsInterfaces[InterfaceNumber]->bAlternateSetting, AlternateSetting);
   if (MsInterfaces[InterfaceNumber]->bAlternateSetting != AlternateSetting) {
    need_set = 1;
   }
  }
 }

 if (need_set) {
  result = libusb_set_interface_alt_setting(idev->handle.libusb, InterfaceNumber, AlternateSetting);
  log_libusb_result_(log, 4, "libusb_set_interface_alt_setting", result);
 }

 return result;
}