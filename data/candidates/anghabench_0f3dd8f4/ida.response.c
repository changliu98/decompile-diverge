const char *__cdecl cros_ec_usb_power_type_string(unsigned int type)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( type )
  {
    case 0x80u:
      v2 = "USB_CHG_TYPE_VBUS";
      break;
    case 0x81u:
      v2 = "USB_CHG_TYPE_UNKNOWN";
      break;
    case 0x82u:
      v2 = "USB_CHG_TYPE_PROPRIETARY";
      break;
    case 0x83u:
      v2 = "USB_CHG_TYPE_PD";
      break;
    case 0x84u:
      v2 = "USB_CHG_TYPE_OTHER";
      break;
    case 0x85u:
      v2 = "USB_CHG_TYPE_NONE";
      break;
    case 0x86u:
      v2 = "USB_CHG_TYPE_C";
      break;
    case 0x87u:
      v2 = "USB_CHG_TYPE_BC12_SDP";
      break;
    case 0x88u:
      v2 = "USB_CHG_TYPE_BC12_DCP";
      break;
    case 0x89u:
      v2 = "USB_CHG_TYPE_BC12_CDP";
      break;
    default:
      v2 = "USB_CHG_TYPE_UNKNOWN";
      break;
  }
  return v2;
}