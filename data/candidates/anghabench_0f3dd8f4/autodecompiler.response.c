__attribute__((used)) static const char *cros_ec_usb_power_type_string(unsigned int type)
{
	const char *str;

	switch (type) {
	case USB_CHG_TYPE_NONE:
		str = "USB_CHG_TYPE_NONE";
		break;
	case USB_CHG_TYPE_PD:
		str = "USB_CHG_TYPE_PD";
		break;
	case USB_CHG_TYPE_PROPRIETARY:
		str = "USB_CHG_TYPE_PROPRIETARY";
		break;
	case USB_CHG_TYPE_C:
		str = "USB_CHG_TYPE_C";
		break;
	case USB_CHG_TYPE_BC12_DCP:
		str = "USB_CHG_TYPE_BC12_DCP";
		break;
	case USB_CHG_TYPE_BC12_CDP:
		str = "USB_CHG_TYPE_BC12_CDP";
		break;
	case USB_CHG_TYPE_BC12_SDP:
		str = "USB_CHG_TYPE_BC12_SDP";
		break;
	case USB_CHG_TYPE_OTHER:
		str = "USB_CHG_TYPE_OTHER";
		break;
	case USB_CHG_TYPE_VBUS:
		str = "USB_CHG_TYPE_VBUS";
		break;
	case USB_CHG_TYPE_UNKNOWN:
		str = "USB_CHG_TYPE_UNKNOWN";
	default:
		str = "UNKNOWN";
	}

	return str;
}