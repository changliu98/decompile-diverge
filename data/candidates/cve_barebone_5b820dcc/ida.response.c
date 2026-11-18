int __cdecl libusb_udev_select_interface(IUDEVICE *idev, BYTE InterfaceNumber, BYTE AlternateSetting)
{
  MSUSB_INTERFACE_DESCRIPTOR **MsInterfaces; // [rsp+0h] [rbp-40h]
  MSUSB_CONFIG_DESCRIPTOR *MsConfig; // [rsp+8h] [rbp-38h]
  URBDRC_PLUGIN *urbdrc; // [rsp+10h] [rbp-30h]
  int diff; // [rsp+24h] [rbp-1Ch]
  int error; // [rsp+28h] [rbp-18h]

  error = 0;
  diff = 0;
  if ( !idev || !*((_QWORD *)idev + 2) )
    return -1;
  urbdrc = (URBDRC_PLUGIN *)*((_QWORD *)idev + 2);
  MsConfig = (MSUSB_CONFIG_DESCRIPTOR *)*((_QWORD *)idev + 1);
  if ( MsConfig )
  {
    MsInterfaces = MsConfig->MsInterfaces;
    if ( MsInterfaces )
    {
      WLog_Print(
        urbdrc->log,
        2u,
        "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)",
        InterfaceNumber,
        MsInterfaces[InterfaceNumber]->AlternateSetting,
        AlternateSetting);
      diff = MsInterfaces[InterfaceNumber]->AlternateSetting != AlternateSetting;
    }
    if ( diff )
    {
      error = libusb_set_interface_alt_setting(*(LIBUSB_DEVICE_HANDLE **)idev, InterfaceNumber, AlternateSetting);
      log_libusb_result_(urbdrc->log, 4u, "libusb_set_interface_alt_setting", error);
    }
  }
  return error;
}