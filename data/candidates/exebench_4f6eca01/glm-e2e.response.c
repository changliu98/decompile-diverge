struct IRQController {
    // 5 bytes of padding or previous fields
    unsigned char flag; 
    // ...
};

void clearIRQFlag(struct IRQController *ctrl) {
    ctrl->flag = 0x30;
}