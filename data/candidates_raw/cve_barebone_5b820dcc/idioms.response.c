int iodev_set_interface(struct iodev_handle *iodev, unsigned char InterfaceNumber, unsigned char AlternateSetting)
{
  int ret = 0;
  int diff = 0;
  struct urbdrc_handle *urbdrc = ((void *)0);
  struct MSUSB_CONFIG_DESCRIPTOR *MsConfig = ((void *)0);
  struct MSUSB_INTERFACE_DESCRIPTOR **MsInterfaces = ((void *)0);
  if (iodev == ((void *)0) || iodev->urbdrc == ((void *)0))
    return -1;
  urbdrc = iodev->urbdrc;
  MsConfig = iodev->MsConfig;
  if (MsConfig == ((void *)0))
    goto exit;
  MsInterfaces = MsConfig->MsInterfaces;
  if (MsInterfaces == ((void *)0))
    goto exit;
  iodev_log(urbdrc->log, 2, "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)",
    InterfaceNumber,
    MsInterfaces[InterfaceNumber]->AlternateSetting,
    AlternateSetting);
  if (MsInterfaces[InterfaceNumber]->AlternateSetting == AlternateSetting)
    goto exit;
  diff = 1;
exit:
  if (diff) {
    ret = libusb_set_interface_alt_setting(iodev->devh, InterfaceNumber, AlternateSetting);
    iodev_log(urbdrc->log, 4, "libusb_set_interface_alt_setting", ret);
  }
  return ret;
}