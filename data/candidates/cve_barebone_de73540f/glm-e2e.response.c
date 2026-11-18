int lldp_private_8023_print(printer_func *printer, const uint8_t *tptr, uint32_t tlen) {
    int status = 0;
    
    if (tlen < 4) {
        return status;
    }
    
    uint8_t subtype = tptr[3];
    printer_func func = *printer;
    
    func(printer, "\n\t  %s subtype (0x%02x)", 
         tok2str(lldp_8023_subtype_values, "unknown", subtype), subtype);
    
    switch (subtype - 1) {
        case 0:
            if (tlen < 9) {
                return status;
            }
            func(printer, "\n\t    %s advertised (%b)", 
                 bittok2str(lldp_8023_autonegotiation_values, "none", tptr[4]), 
                 tptr[4]);
            func(printer, "\n\t    PMD capabilities %s advertised (%x)", 
                 bittok2str(lldp_pmd_capability_values, "none", (tptr[5] << 8) | tptr[6]), 
                 (tptr[5] << 8) | tptr[6]);
            func(printer, "\n\t    MAU type %s (0x%x)", 
                 tok2str(lldp_mau_types_values, "unknown", (tptr[7] << 8) | tptr[8]), 
                 (tptr[7] << 8) | tptr[8]);
            break;
            
        case 1:
            if (tlen < 7) {
                return status;
            }
            func(printer, "\n\t    MDI power support [%s], power pair %s, power class %s", 
                 bittok2str(lldp_mdi_values, "none", tptr[4]), 
                 tok2str(lldp_mdi_power_pairs_values, "unknown", tptr[5]), 
                 tok2str(lldp_mdi_power_class_values, "unknown", tptr[6]));
            break;
            
        case 2:
            if (tlen < 9) {
                return status;
            }
            func(printer, "\n\t    aggregation %s, aggregation port ID %u", 
                 bittok2str(lldp_aggregation_values, "none", tptr[4]), 
                 (tptr[5] << 24) | (tptr[6] << 16) | (tptr[7] << 8) | tptr[8]);
            break;
            
        case 3:
            func(printer, "\n\t    MTU size %u", 
                 (tptr[4] << 8) | tptr[5]);
            break;
            
        default:
            status = 1;
            break;
    }
    
    return status;
}