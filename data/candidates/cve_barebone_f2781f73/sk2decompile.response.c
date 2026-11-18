void bgp_capabilities_print(uiOut *ui, const unsigned char *data, int length) {
  int i, j, k, l;
  unsigned cap;
  for (i = 0; i < length; i += l + 2) {
    if (ui->max_len - 2 < ui->max_len || data + i > ui->max_len - 2 ||
        data + i + 2 > ui->max_len - l) {
      ui->output(ui, "[|BGP]");
      return;
    }
    cap = data[i];
    l = data[i + 1];
    ui->output(ui, "\n\t      %s (%u), length: %u",
               tok2str(BgpCapabilities, "Unknown", cap), cap, l);
    switch (cap) {
      case 1:
        ui->output(ui, "\n\t\tAFI %s (%u), SAFI %s (%u)",
                   tok2str(AfiSafi, "Unknown", EXTRACT_16BITS(data + i + 2)),
                   EXTRACT_16BITS(data + i + 2),
                   tok2str(Safi, "Unknown", data[i + 5]));
        break;
      case 2:
        break;
      case 128:
        break;
      case 64:
        ui->output(ui, "\n\t\tRestart Flags: [%s], Restart Time %us",
                   (data[i + 2] & 0x80) ? "R" : "none",
                   EXTRACT_16BITS(data + i + 2) & 0x0fff);
        k = l - 2;
        j = 4;
        while (k >= 4) {
          ui->output(ui,
                     "\n\t\t  AFI %s (%u), SAFI %s (%u), "
                     "Forwarding state preserved: %s",
                     tok2str(AfiSafi, "Unknown", EXTRACT_16BITS(data + i + j)),
                     EXTRACT_16BITS(data + i + j),
                     tok2str(Safi, "Unknown", data[i + j + 2]),
                     data[i + j + 2], (data[i + j + 3] & 0x80) ? "yes" : "no");
          k -= 4;
          j += 4;
        }
        break;
      case 65:
        if (l == 4)
          ui->output(ui, "\n\t\t  4 Byte AS %s",
                     as_printf(ui, AS_FORMAT_4, 20, EXTRACT_32BITS(data + i + 2)));
        break;
      case 69:
        j = 2;
        if (l == 0)
          ui->output(ui, " (bogus)");
        else
          while (k > 0) {
            if (k < 4) {
              ui->output(ui, "\n\t\t(invalid)");
              break;
            }
            ui->output(ui,
                       "\n\t\tAFI %s (%u), SAFI %s (%u), "
                       "Send/Receive: %s",
                       tok2str(AfiSafi, "Unknown", EXTRACT_16BITS(data + i + j)),
                       EXTRACT_16BITS(data + i + j),
                       tok2str(Safi, "Unknown", data[i + j + 2]),
                       data[i + j + 2],
                       tok2str(BgpSendRecv, "Bogus (0x%02x)", data[i + j + 3]));
            k -= 4;
            j += 4;
          }
        break;
      default:
        ui->output(ui, "\n\t\tno decoder for Capability %u", cap);
        if (ui->verbosity < 2)
          print_unknown_data(ui, data + i + 2, "\n\t\t", l);
        break;
    }
    if (ui->verbosity >= 2 && l > 0)
      print_unknown_data(ui, data + i + 2, "\n\t\t", l);
  }
}