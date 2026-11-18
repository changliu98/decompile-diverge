void rdpsnd_virtual_channel_event_terminated(struct sway_seat *seat) {
	if (!seat) {
		return;
	}
	if (seat->seatop_instruction) {
		seatop_inject_event(seat->seatop_instruction, NULL);
	}
	if (seat->seatop_touch) {
		seatop_inject_event(seat->seatop_touch, -1);
		wl_list_remove(&seat->seatop_touch->link);
	}
	wl_list_remove(&seat->seatop_instruction->link);
	wl_list_remove(&seat->link);
	wl_event_source_timer_remove(seat->hide_cursor_timer, 1);
	free(seat->keyboard_group);
	free(seat->keyboard_section);
	seat->keyboard_mode = NULL;
	free(seat);
}