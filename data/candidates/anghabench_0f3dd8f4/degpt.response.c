/**
 * Converts a USB charger type code to its corresponding string representation.
 *
 * @param type The numeric code representing the USB charger type.
 * @return A static string describing the charger type, or "USB_CHG_TYPE_UNKNOWN" if the type is unrecognized.
 */
char * cros_ec_usb_power_type_string(uint charger_type)
{
    switch(charger_type) {
    case 0x80:
        return "USB_CHG_TYPE_VBUS";
    case 0x82:
        return "USB_CHG_TYPE_PROPRIETARY";
    case 0x83:
        return "USB_CHG_TYPE_PD";
    case 0x84:
        return "USB_CHG_TYPE_OTHER";
    case 0x85:
        return "USB_CHG_TYPE_NONE";
    case 0x86:
        return "USB_CHG_TYPE_C";
    case 0x87:
        return "USB_CHG_TYPE_BC12_SDP";
    case 0x88:
        return "USB_CHG_TYPE_BC12_DCP";
    case 0x89:
        return "USB_CHG_TYPE_BC12_CDP";
    default:
        return "USB_CHG_TYPE_UNKNOWN";
    }
}