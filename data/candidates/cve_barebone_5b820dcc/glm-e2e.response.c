int libusb_udev_select_interface(void* udev, uint8_t interface_number, uint8_t alternate_setting) {
    int result = 0;
    int need_set = 0;
    
    struct libusb_device_dummy* dev = (struct libusb_device_dummy*)udev;
    struct libusb_device_handle_dummy* handle = NULL;
    struct libusb_config_descriptor_dummy* config_desc = NULL;
    struct libusb_interface_descriptor_dummy** interfaces = NULL;
    
    if (!dev || !dev->handle) {
        return -1;
    }
    
    handle = (struct libusb_device_handle_dummy*)dev->handle;
    config_desc = (struct libusb_config_descriptor_dummy*)dev->config_desc;
    
    if (config_desc) {
        interfaces = config_desc->interface_array;
        if (interfaces) {
            WLog_Print((wLog*)handle->something, 2, "interface %d alt_setting %d", interfaces[interface_number]->bAlternateSetting, alternate_setting);
            if (interfaces[interface_number]->bAlternateSetting != alternate_setting) {
                need_set = 1;
            }
        }
    }
    
    if (need_set) {
        result = libusb_set_interface_alt_setting((libusb_device_handle*)dev->handle, interface_number, alternate_setting);
        log_libusb_result_((wLog*)handle->something, 4, "libusb_set_interface_alt_setting %d", result);
    }
    
    return result;
}