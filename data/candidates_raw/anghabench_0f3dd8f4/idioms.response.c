char *usb_chg_type_to_string(unsigned int type)
{
  char *str = "USB_CHG_TYPE_UNKNOWN";
  switch (type) {
    case 0x80:
      str = "USB_CHG_TYPE_VBUS";
      break;
    case 0x81:
      str = "USB_CHG_TYPE_UNKNOWN";
      break;
    case 0x82:
      str = "USB_CHG_TYPE_PROPRIETARY";
      break;
    case 0x83:
      str = "USB_CHG_TYPE_PD";
      break;
    case 0x84:
      str = "USB_CHG_TYPE_OTHER";
      break;
    case 0x85:
      str = "USB_CHG_TYPE_NONE";
      break;
    case 0x86:
      str = "USB_CHG_TYPE_C";
      break;
    case 0x87:
      str = "USB_CHG_TYPE_BC12_SDP";
      break;
    case 0x88:
      str = "USB_CHG_TYPE_BC12_DCP";
      break;
    case 0x89:
      str = "USB_CHG_TYPE_BC12_CDP";
      break;
  }
  return str;
}