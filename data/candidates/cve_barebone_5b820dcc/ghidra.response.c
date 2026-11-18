int libusb_udev_select_interface(IUDEVICE *idev,BYTE InterfaceNumber,BYTE AlternateSetting)

{
  undefined8 *puVar1;
  long lVar2;
  bool bVar3;
  MSUSB_INTERFACE_DESCRIPTOR **MsInterfaces;
  MSUSB_CONFIG_DESCRIPTOR *MsConfig;
  URBDRC_PLUGIN *urbdrc;
  UDEVICE *pdev;
  int diff;
  int error;
  BYTE AlternateSetting_local;
  BYTE InterfaceNumber_local;
  IUDEVICE *idev_local;
  int local_c;
  
  error = 0;
  bVar3 = false;
  if ((idev == (IUDEVICE *)0x0) || (*(long *)(idev + 0x10) == 0)) {
    local_c = -1;
  }
  else {
    puVar1 = *(undefined8 **)(idev + 0x10);
    if (*(long *)(idev + 8) != 0) {
      lVar2 = *(long *)(*(long *)(idev + 8) + 0x10);
      if (lVar2 != 0) {
        WLog_Print((wLog *)*puVar1,2,
                   "select Interface(%u) curr AlternateSetting(%u) new AlternateSetting(%u)",
                   (ulong)InterfaceNumber,
                   (ulong)*(byte *)(*(long *)(lVar2 + (ulong)InterfaceNumber * 8) + 5),
                   (ulong)AlternateSetting);
        bVar3 = *(BYTE *)(*(long *)(lVar2 + (ulong)InterfaceNumber * 8) + 5) != AlternateSetting;
      }
      if (bVar3) {
        error = libusb_set_interface_alt_setting
                          (*(LIBUSB_DEVICE_HANDLE **)idev,(uint)InterfaceNumber,
                           (uint)AlternateSetting);
        log_libusb_result_((wLog *)*puVar1,4,"libusb_set_interface_alt_setting",error);
      }
    }
    local_c = error;
  }
  return local_c;
}