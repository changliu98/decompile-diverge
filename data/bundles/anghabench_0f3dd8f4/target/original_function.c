const char *cros_ec_usb_power_type_string(unsigned int type)
{
	switch (type) {
	case USB_CHG_TYPE_NONE:
		return "USB_CHG_TYPE_NONE";
	case USB_CHG_TYPE_PD:
		return "USB_CHG_TYPE_PD";
	case USB_CHG_TYPE_PROPRIETARY:
		return "USB_CHG_TYPE_PROPRIETARY";
	case USB_CHG_TYPE_C:
		return "USB_CHG_TYPE_C";
	case USB_CHG_TYPE_BC12_DCP:
		return "USB_CHG_TYPE_BC12_DCP";
	case USB_CHG_TYPE_BC12_CDP:
		return "USB_CHG_TYPE_BC12_CDP";
	case USB_CHG_TYPE_BC12_SDP:
		return "USB_CHG_TYPE_BC12_SDP";
	case USB_CHG_TYPE_OTHER:
		return "USB_CHG_TYPE_OTHER";
	case USB_CHG_TYPE_VBUS:
		return "USB_CHG_TYPE_VBUS";
	case USB_CHG_TYPE_UNKNOWN:
		return "USB_CHG_TYPE_UNKNOWN";
	default:
		return "USB_CHG_TYPE_UNKNOWN";
	}
}