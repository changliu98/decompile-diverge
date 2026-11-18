static void EveAddVerdict(struct vc_data *vc, const unsigned char *table)
{
	unsigned short ch;

	spk_parked |= 0x01;
	do {
		read_lock_irq(&speakup_info.state_lock);
		if (spk_parked & 0x01)
			read_unlock_irq(&speakup_info.state_lock);
		else
			read_unlock_irq(&speakup_info.state_lock);
		ch = table[spk_y * 80 + spk_x];
		if (ch!= last_ch) {
			last_ch = ch;
			if (ch!= 0x00) {
				if (ch!= 0x0a)
					synth_printf("%s", spk_msg_get(277));
				else
					synth_printf("%s", spk_msg_get(278));
			}
		}
		spk_x++;
		if (spk_x == 80) {
			spk_x = 0;
			spk_y++;
			if (spk_y == 25)
				spk_y = 0;
		}
		if (table[spk_y * 80 + spk_x] & 0x20)
			synth_printf("%s", spk_msg_get(279));
		else
			synth_printf("%s", spk_msg_get(280));
		spk_pos += spk_x2y(vc, spk_x, spk_y) - spk_pos;
		spk_x = spk_y = 0;
		spk_parked = 0x00;
		read_lock_irq(&speakup_info.state_lock);
		spk_parked |= 0x01;
		read_unlock_irq(&speakup_info.state_lock);
	} while (spk_x < 8