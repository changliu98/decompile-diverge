static int func0(struct usb_usbvision *usbvision)
{
	int retval = usbvision->streaming;

	usbvision->streaming = 1;
	return retval;
}