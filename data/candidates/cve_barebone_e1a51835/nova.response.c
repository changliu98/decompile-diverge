static void aodv_extension(struct snd_usb_midi_out_endpoint *ep,
				  uint8_t *buffer, int buffer_length)
{
	if (buffer[0] == 0x01) {
		uint8_t *buf = buffer;
		while (buf < ep->max_transfer - 6) {
			if (buf < ep->head || buf > ep->tail - 6)
				break;
			if (buffer_length < 7)
				break;
			buf += 6;
			snd_usbmidi_input_data(ep, &usb_midi_input_trigger,
					       (buf[0] << 24) |
					       (buf[1] << 16) |
					       (buf[2] << 8) |
					       buf[3]);
		}
	} else {
		snd_usbmidi_input_data(ep, &usb_midi_input_trigger,
				       (buffer[0] << 24) |
				       (buffer[1] << 16) |
				       (buffer[2] << 8) |
				       buffer[3]);
	}
	snd_usbmidi_input_data(ep, &usb_midi_input_trigger, 0);
}