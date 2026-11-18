void OPL2_ChannelSetupCon(struct OPL2_Channel *channel) {
    if (channel->channel_type == 1) {
        if (channel->con == 7 || channel->con == 8) {
            // Both operators output directly to the summing buffer
            channel->op1->connect_ptr = (char *)channel->unused_10 + 0x720;
            channel->op2->connect_ptr = (char *)channel->unused_10 + 0x720;
        } else {
            if (channel->feedback == 0) {
                // No feedback: Op1 outputs to Op2's input, Op2 outputs to the summing buffer
                channel->op1->connect_ptr = &channel->op2->padding_0[0x12];
                channel->op2->connect_ptr = &channel->op2->padding_0[0x10];
            } else if (channel->feedback == 1) {
                // Feedback 1: Op1 outputs to Op2's input, Op2 outputs to the summing buffer
                channel->op1->connect_ptr = &channel->op2->padding_0[0x12];
                channel->op2->connect_ptr = (char *)channel->unused_10 + 0x720;
            }
        }
    } else {
        if (channel->feedback == 0) {
            // No feedback: Op1 outputs to Op2's input, Op2 outputs to the summing buffer
            channel->op1->connect_ptr = &channel->op2->padding_0[0x12];
            channel->op2->connect_ptr = &channel->op2->padding_0[0x10];
        } else if (channel->feedback == 1) {
            // Feedback 1: Op1 outputs to Op2's input, Op2 outputs to the summing buffer
            channel->op1->connect_ptr = &channel->op2->padding_0[0x12];
            channel->op2->connect_ptr = (char *)channel->unused_10 + 0x720;
        }
    }
}