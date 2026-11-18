char * cros_ec_usb_power_type_string(uint type)

{
  uint type_local;
  char *local_10;
  
  switch(type) {
  case 0x80:
    local_10 = "USB_CHG_TYPE_VBUS";
    break;
  case 0x81:
    local_10 = "USB_CHG_TYPE_UNKNOWN";
    break;
  case 0x82:
    local_10 = "USB_CHG_TYPE_PROPRIETARY";
    break;
  case 0x83:
    local_10 = "USB_CHG_TYPE_PD";
    break;
  case 0x84:
    local_10 = "USB_CHG_TYPE_OTHER";
    break;
  case 0x85:
    local_10 = "USB_CHG_TYPE_NONE";
    break;
  case 0x86:
    local_10 = "USB_CHG_TYPE_C";
    break;
  case 0x87:
    local_10 = "USB_CHG_TYPE_BC12_SDP";
    break;
  case 0x88:
    local_10 = "USB_CHG_TYPE_BC12_DCP";
    break;
  case 0x89:
    local_10 = "USB_CHG_TYPE_BC12_CDP";
    break;
  default:
    local_10 = "USB_CHG_TYPE_UNKNOWN";
  }
  return local_10;
}