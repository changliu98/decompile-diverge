static int func0(struct snd_usb_midi_out_endpoint *ep,
				  uint8_t *buffer, int buffer_length)
{
	uint8_t *buf = buffer;
	int err;

	while (1) {
		if (snd_rawmidi_transmit_peek(buf, 1)!= buffer_length) {
			err = 0;
			break;
		}
		if ((buf[3] & 0x02) == 0) {
			err = 0;
			break;
		}
		if (buf[3] & 0x10) {
			err = 0;
			break;
		}
		if (buf[3] & 0x04) {
			buf = snd_rawmidi_transmit_peek_read(buf,
							     &snd_usb_midi_out_endpoint_iface,
							     snd_rawmidi_transmit_peek_length(buf));
			continue;
		}
		if (buf[3] & 0x08) {
			buf = snd_rawmidi_transmit_peek_read(buf,
							     &snd_usb_midi_out_endpoint_iface,
							     snd_rawmidi_transmit_peek_length(buf));
			continue;
		}
		err = 1;
		break;
	}

	while (snd_rawmidi_transmit_peek_length(buf) == buffer_length) {
		snd_rawmidi_transmit_read(buf, &snd_usb_midi_out_endpoint_iface,
					  snd_rawmidi_transmit_peek_length(buf));
		buf += 2;
	}

	return err;
}