int __cdecl libusb_udev_select_interface(IUDEVICE *idev, BYTE InterfaceNumber, BYTE AlternateSetting)
{
  MSUSB_INTERFACE_DESCRIPTOR **MsInterfaces;
  MSUSB_CONFIG_DESCRIPTOR *MsConfig;
  URBDRC_PLUGIN *urbdrc;
  int diff = 0;
  int error = 0;

  if (!idev || !idev->urbdrc)
    return -1;

  urbdrc = idev->urbdrc;
  MsConfig = idev->MsConfig;

  if (MsConfig)
  {
    MsInterfaces = MsConfig->MsInterfaces;
    if (MsInterfaces)
    {
      WLog_Print(
        urbdrc->log,
        WLOG_WARN,
        "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)",
        InterfaceNumber,
        MsInterfaces[InterfaceNumber]->AlternateSetting,
        AlternateSetting);
      
      diff = (MsInterfaces[InterfaceNumber]->AlternateSetting != AlternateSetting);
    }

    if (diff)
    {
      error = libusb_set_interface_alt_setting(idev->handle, InterfaceNumber, AlternateSetting);
      log_libusb_result_(urbdrc->log, WLOG_ERROR, "libusb_set_interface_alt_setting", error);
    }
  }

  return error;
}