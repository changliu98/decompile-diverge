void eap_print(struct netdissect_options *ndo, struct nbt_eapol *eapol, u_int length)
{
    struct eap_hdr *eap;
    int i;
    int eap_type; int eap_code; int eap_len;
    int eap_fast_ver; int eap_ttls_ver; int eap_aka_sub;
    int (*eapol_print)(struct netdissect_options *, char *, ...);
    int (*eap_print)(struct netdissect_options *, char *, ...);
    eap = (struct eap_hdr *)eapol->eapol_data;
    if (eapol->eapol_data + eapol->eapol_len - 4 > ndo->ndo_snapend ||
        eap + 1 > ndo->ndo_snapend - 4) {
        eapol_print = ndo->ndo_printf;
        eapol_print(ndo, "\n\t[|EAPOL]");
        return;
    }
    if (ndo->ndo_vflag < 1) {
        eapol_print = ndo->ndo_printf;
        eapol_print(ndo, "%s (%u) v%u, len %u",
            eap_type_string(eap_type_values, "unknown", eap->eap_type),
            eap->eap_type, eap->eap_ver,
            ntohs(eap->eap_len));
        return;
    }
    eapol_print = ndo->ndo_printf;
    eapol_print(ndo, "%s (%u) v%u, len %u",
        eap_type_string(eap_type_values, "unknown", eap->eap_type),
        eap->eap_type, eap->eap_ver,
        ntohll(eap->eap_len));
    eap = (struct eap_hdr *)(eapol->eapol_data + 4);
    if (eap->eap_type == 0) {
        eap_code = eap->eap_code;
        eap_len = ntohs(eap->eap_len);
        eapol_print = ndo->ndo_printf;
        eapol_print(ndo, ", %s (%u), id %u, len %u",
            eap_code_string(eap_code_values, "unknown", eap_code),
            eap_code, eap->eap_id, eap_len);
        if (ndo->ndo_snapend - eap_len < eapol->eapol_data ||
            eapol->eapol_data + eap_len - 1 < eapol->eapol_data) {
            eapol_print = ndo->ndo_printf;
            eapol_print(ndo, "\n\t[|EAP]");
            return;
        }
        if (eap_code < 3) {
            eap_type = eap->eap_data[0];
            eapol_print = ndo->ndo_printf;
            eapol_print(ndo, "\n\t\t Type %s (%u)",
                eap_type_string(eap_type_values, "unknown", eap_type),
                eap_type);
            switch (eap_type) {
            case 1:
                if (eap_len - 5 > 0) {
                    eapol_print = ndo->ndo_printf;
                    eapol_print(ndo, ", Identity: ");
                    eap_str(ndo, eap->eap_data + 5, eap_len - 5);
                }
                break;
            case 2:
                if (eap_len - 5 > 0) {
                    eapol_print = ndo->ndo_printf;
                    eapol_print(ndo, ", Notification: ");
                    eap_str(ndo, eap->eap_data + 5, eap_len - 5);
                }
                break;
            case 3:
                for (i = 5; i < eap_len; i++) {
                    eapol_print = ndo->ndo_printf;
                    eapol_print(ndo, " %s (%u),",
                        eap_type_string(eap_type_values, "unknown",
                        eapol->eapol_data[i]),
                        eapol->eapol_data[i]);
                }
                return;
            case 4:
            case 5:
            case 6:
                return;
            case 13:
                eapol_print = ndo->ndo_printf;
                eapol_print(ndo, " FASTv%u", eap->eap_data[0] & 0x07);
            case 18:
            case 21:
            case 23:
            case 43:
                eapol_print = ndo->ndo_printf;
                eapol_print(ndo, " flags [%s] 0x%02x,",
                    eap_tls_flags_string(eap_tls_flags_values, "none",
                    eapol->eapol_data[0]),
                    eapol->eapol_data[0]);
                if (eapol->eapol_data[0] & 0x80)
                    eapol_print = ndo->ndo_printf;
                    eapol_print(ndo, " len %u",
                        ntohll(eapol->eapol_data[1] << 32 |
                        eapol->eapol_data[2] << 16 |
                        eapol->eapol_data[3]));
                break;
            case 11:
                eapol_print = ndo->ndo_printf;
                eapol_print(ndo, " subtype [%s] 0x%02x,",
                    eap_aka_subtype_string(eap_aka_subtype_values, "unknown",
                    eapol->eapol_data[0]),
                    eapol->eapol_data[0]);
                return;
            default:
                return;
            }
        }
    }
}