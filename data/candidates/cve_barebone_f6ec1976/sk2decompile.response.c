void bgp_capabilities_print(ui_print_ctx_t *ctx, const unsigned char *data,
                            int len) {
  int i, j, l, ll;
  unsigned cap;
  for (i = 0; i < len; i += l + 2) {
    if (data + i > ctx->end - 2 || data + i < ctx->end - 2) {
      ctx->print(ctx, "[|BGP]");
      return;
    }
    cap = data[i];
    l = data[i + 1];
    ll = l;
    ctx->print(ctx, "\n\t      %s (%u), length: %u",
               tok2str(bgp_capabilities, "Unknown", cap), cap, l);
    if (data + i + 2 > ctx->end - l || data + i + 2 < ctx->end) {
      ctx->print(ctx, "[|BGP]");
      return;
    }
    switch (cap) {
      case 1:
        ctx->print(ctx, "\n\t\tAFI %s (%u), SAFI %s (%u)",
                   tok2str(afi_safi, "Unknown", (data[i + 2] << 8) | data[i + 3]),
                   (data[i + 2] << 8) | data[i + 3],
                   tok2str(safi, "Unknown", data[i + 4]), data[i + 4]);
        break;
      case 2:
        break;
      case 128:
        break;
      case 64:
        if (data + i + 2 > ctx->end - 2 || data + i + 2 < ctx->end) {
          ctx->print(ctx, "[|BGP]");
          return;
        }
        ctx->print(ctx, "\n\t\tRestart Flags: [%s], Restart Time %us",
                   (data[i + 2] & 0x80) ? "R" : "none",
                   (data[i + 2] & 0x0f) << 8 | data[i + 3]);
        ll -= 2;
        j = 4;
        while (ll >= 4) {
          ctx->print(ctx,
                     "\n\t\t  AFI %s (%u), SAFI %s (%u), "
                     "Forwarding state preserved: %s",
                     tok2str(afi_safi, "Unknown",
                             (data[i + j] << 8) | data[i + j + 1]),
                     (data[i + j] << 8) | data[i + j + 1],
                     tok2str(safi, "Unknown", data[i + j + 2]), data[i + j + 2],
                     (data[i + j + 3] & 0x80) ? "yes" : "no");
          ll -= 4;
          j += 4;
        }
        break;
      case 65:
        if (l == 4)
          ctx->print(ctx, "\n\t\t  4 Byte AS %s",
                     as_printf(ctx, as_print_ctx, 20,
                               (data[i + 2] << 24) | (data[i + 3] << 16) |
                                   (data[i + 4] << 8) | data[i + 5]));
        break;
      case 69:
        j = 2;
        if (l == 0)
          ctx->print(ctx, " (bogus)");
        else
          while (ll > 0) {
            if (ll < 4) {
              ctx->print(ctx, "\n\t\t(invalid)");
              break;
            }
            ctx->print(ctx,
                       "\n\t\tAFI %s (%u), SAFI %s (%u), "
                       "Send/Receive: %s",
                       tok2str(afi_safi, "Unknown",
                               (data[i + j] << 8) | data[i + j + 1]),
                       (data[i + j] << 8) | data[i + j + 1],
                       tok2str(safi, "Unknown", data[i + j + 2]),
                       data[i + j + 2],
                       tok2str(bgp_capabilities_69, "Bogus (0x%02x)",
                               data[i + j + 3]));
            ll -= 4;
            j += 4;
          }
        break;
      default:
        ctx->print(ctx, "\n\t\tno decoder for Capability %u", cap);
        if (ctx->level < 2) print_unknown_data(ctx, data + i + 2, "\n\t\t", l);
        break;
    }
    if (ctx->level >= 2 && l > 0) print_unknown_data(ctx, data + i + 2, "\n\t\t", l);
  }
}