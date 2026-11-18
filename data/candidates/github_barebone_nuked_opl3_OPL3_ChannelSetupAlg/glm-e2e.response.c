void OPL3_ChannelSetupAlg(struct OPL3_Channel *channel) {
    if (channel->ch_type == 3) {
        if (channel->ch_type == 7 || channel->ch_type == 8) {
            channel->slots[0]->conn = &opl3_null_slot;
            channel->slots[1]->conn = &opl3_null_slot;
        } else {
            if ((channel->cha & 1) == 0) {
                channel->slots[0]->conn = &channel->slots[0][1];
                channel->slots[1]->conn = &channel->slots[0][0];
            } else {
                channel->slots[0]->conn = &channel->slots[0][1];
                channel->slots[1]->conn = &opl3_null_slot;
            }
        }
    } else {
        if ((channel->cha & 8) != 0) {
            return;
        }
        if (channel->cha & 4) {
            channel->pair->mod2 = &opl3_null_slot;
            channel->pair->mod3 = &opl3_null_slot;
            channel->pair->mod4 = &opl3_null_slot;
            channel->pair->mod5 = &opl3_null_slot;
            
            switch (channel->alg & 3) {
                case 0:
                    channel->pair->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->pair->slots[1]->conn = &channel->pair->slots[0][0];
                    channel->slots[0]->conn = &channel->slots[0][1];
                    channel->slots[1]->conn = &channel->slots[0][0];
                    channel->mod2 = &channel->slots[0][1];
                    channel->mod3 = &opl3_null_slot;
                    channel->mod4 = &opl3_null_slot;
                    channel->mod5 = &opl3_null_slot;
                    break;
                case 1:
                    channel->pair->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->pair->slots[1]->conn = &channel->pair->slots[0][0];
                    channel->slots[0]->conn = &opl3_null_slot;
                    channel->slots[1]->conn = &channel->slots[0][1];
                    channel->mod2 = &channel->slots[0][1];
                    channel->mod3 = &opl3_null_slot;
                    channel->mod4 = &opl3_null_slot;
                    channel->mod5 = &opl3_null_slot;
                    break;
                case 2:
                    channel->pair->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->pair->slots[1]->conn = &opl3_null_slot;
                    channel->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->slots[1]->conn = &channel->slots[0][0];
                    channel->mod2 = &channel->pair->slots[0][1];
                    channel->mod3 = &opl3_null_slot;
                    channel->mod4 = &opl3_null_slot;
                    channel->mod5 = &opl3_null_slot;
                    break;
                case 3:
                    channel->pair->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->pair->slots[1]->conn = &opl3_null_slot;
                    channel->slots[0]->conn = &channel->pair->slots[0][1];
                    channel->slots[1]->conn = &opl3_null_slot;
                    channel->mod2 = &channel->pair->slots[0][1];
                    channel->mod3 = &channel->slots[0][1];
                    channel->mod4 = &opl3_null_slot;
                    channel->mod5 = &opl3_null_slot;
                    break;
            }
        } else {
            if ((channel->cha & 1) == 0) {
                channel->slots[0]->conn = &channel->slots[0][1];
                channel->slots[1]->conn = &channel->slots[0][0];
                channel->mod2 = &channel->slots[0][1];
                channel->mod3 = &opl3_null_slot;
                channel->mod4 = &opl3_null_slot;
                channel->mod5 = &opl3_null_slot;
            } else {
                channel->slots[0]->conn = &channel->slots[0][1];
                channel->slots[1]->conn = &opl3_null_slot;
                channel->mod2 = &channel->slots[0][1];
                channel->mod3 = &channel->slots[0][1];
                channel->mod4 = &opl3_null_slot;
                channel->mod5 = &opl3_null_slot;
            }
        }
    }
}