void ubik_print(struct netdissect_options *ndo, const uint8_t *bp) {
    uint32_t opcode = EXTRACT_32BITS(bp + 0x1c);
    bp += 0x20;

    ndo->printer(ndo, " ubik call %s", tok2str(ubik_req, "op#%d", opcode));

    switch (opcode) {
        case 0x2710: { // 10000
            uint32_t now = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " now %s", now ? "now" : "never");
            ndo->printer(ndo, " epoch");
            
            uint32_t t = EXTRACT_32BITS(bp);
            bp += 4;
            char tstr[256];
            time_t tt = t;
            struct tm *tm = localtime(&tt);
            strftime(tstr, 256, "%Y-%m-%d %H:%M:%S", tm);
            ndo->printer(ndo, " %s", tstr);
            ndo->printer(ndo, " tid");
            
            uint32_t tid1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t tid2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", tid1, tid2);
            ndo->printer(ndo, " vote");
            
            uint32_t v1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t v2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", v1, v2);
            break;
        }
        case 0x2713: { // 10003
            ndo->printer(ndo, " vote");
            uint32_t v = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", v);
            break;
        }
        case 0x4e20: // 20000
        case 0x4e21: // 20001
        case 0x4e27: // 20007
        case 0x4e2a: { // 20010
            ndo->printer(ndo, " tid");
            uint32_t t1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t t2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", t1, t2);
            break;
        }
        case 0x4e22: { // 20002
            ndo->printer(ndo, " tid");
            uint32_t t1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t t2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", t1, t2);
            ndo->printer(ndo, " file");
            
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", f1);
            ndo->printer(ndo, " pos");
            
            uint32_t p1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", p1);
            ndo->printer(ndo, " len");
            
            uint32_t l1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", l1);
            
            uint32_t l2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %s", tok2str(ubik_lock_types, "type#%d", l2));
            break;
        }
        case 0x4e23: { // 20003
            ndo->printer(ndo, " tid");
            uint32_t t1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t t2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", t1, t2);
            ndo->printer(ndo, " file");
            
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", f1);
            ndo->printer(ndo, " pos");
            
            uint32_t p1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", p1);
            break;
        }
        case 0x4e25: { // 20005
            ndo->printer(ndo, " file");
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", f1);
            break;
        }
        case 0x4e26: { // 20006
            ndo->printer(ndo, " file");
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", f1);
            ndo->printer(ndo, " pos");
            
            uint32_t p1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", p1);
            ndo->printer(ndo, " len");
            
            uint32_t l1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t l2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", l1, l2);
            break;
        }
        case 0x4e29: { // 20009
            ndo->printer(ndo, " tid");
            uint32_t t1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t t2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", t1, t2);
            ndo->printer(ndo, " file");
            
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", f1);
            ndo->printer(ndo, " pos");
            
            uint32_t p1 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d", p1);
            break;
        }
        case 0x4e2c: { // 20012
            ndo->printer(ndo, " tid");
            uint32_t t1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t t2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", t1, t2);
            ndo->printer(ndo, " file");
            
            uint32_t f1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t f2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", f1, f2);
            ndo->printer(ndo, " pos");
            
            uint32_t p1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t p2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", p1, p2);
            ndo->printer(ndo, " len");
            
            uint32_t l1 = EXTRACT_32BITS(bp);
            bp += 4;
            uint32_t l2 = EXTRACT_32BITS(bp);
            bp += 4;
            ndo->printer(ndo, " %d.%d", l1, l2);
            break;
        }
        default:
            break;
    }
}