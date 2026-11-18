static const char *cros_ec_usb_power_type_string(unsigned int type) {
  const char *type_str;
  switch (type) {
    case USB_CHG_TYPE_NONE:
      type_str = "USB_CHG_TYPE_NONE";
      break;
    case USB_CHG_TYPE_VBUS:
      type_str = "USB_CHG_TYPE_VBUS";
      break;
    case USB_CHG_TYPE_C:
      type_str = "USB_CHG_TYPE_C";
      break;
    case USB_CHG_TYPE_PD:
      type_str = "USB_CHG_TYPE_PD";
      break;
    case USB_CHG_TYPE_BC12_SDP:
      type_str = "USB_CHG_TYPE_BC12_SDP";
      break;
    case USB_CHG_TYPE_BC12_DCP:
      type_str = "USB_CHG_TYPE_BC12_DCP";
      break;
    case USB_CHG_TYPE_BC12_CDP:
      type_str = "USB_CHG_TYPE_BC12_CDP";
      break;
    case USB_CHG_TYPE_PROPRIETARY:
      type_str = "USB_CHG_TYPE_PROPRIETARY";
      break;
    case USB_CHG_TYPE_OTHER:
      type_str = "USB_CHG_TYPE_OTHER";
      break;
    case USB_CHG_TYPE_UNKNOWN:
      type_str = "USB_CHG_TYPE_UNKNOWN";
      break;
    default:
      type_str = "USB_CHG_TYPE_UNKNOWN";
      break;
  }
  return type_str;
}