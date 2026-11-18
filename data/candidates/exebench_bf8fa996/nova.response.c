static int test_and_set(struct usb_usbvision *usbvision)
{
	int retval = usbvision->streaming;

	usbvision->streaming = 1;
	return retval;
}