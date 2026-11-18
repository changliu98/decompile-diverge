static void OPL3_ChannelSetupAlg(opl3_chip *chip) {
  if (chip->chip_type == 3) {
    if (chip->chip_num == 7 || chip->chip_num == 8) {
      chip->ch[0]->conn = &chip->shared->dummy;
      chip->ch[1]->conn = &chip->shared->dummy;
    } else {
      if ((chip->conn_type & 1) == 0) {
        chip->ch[0]->conn = &chip->ch[0]->conn_a;
        chip->ch[1]->conn = &chip->ch[0]->conn_b;
      } else if ((chip->conn_type & 1) == 1) {
        chip->ch[0]->conn = &chip->ch[0]->conn_a;
        chip->ch[1]->conn = &chip->shared->dummy;
      }
    }
  } else {
    if ((chip->conn_type & 8) == 0) {
      if ((chip->conn_type & 4) == 0) {
        if ((chip->conn_type & 1) == 0) {
          chip->ch[0]->conn = &chip->ch[0]->conn_a;
          chip->ch[1]->conn = &chip->ch[0]->conn_b;
          chip->conn[0] = &chip->ch[1]->conn_b;
          chip->conn[1] = &chip->shared->dummy;
          chip->conn[2] = &chip->shared->dummy;
          chip->conn[3] = &chip->shared->dummy;
        } else if ((chip->conn_type & 1) == 1) {
          chip->ch[0]->conn = &chip->ch[0]->conn_a;
          chip->ch[1]->conn = &chip->shared->dummy;
          chip->conn[0] = &chip->ch[0]->conn_b;
          chip->conn[1] = &chip->ch[1]->conn_b;
          chip->conn[2] = &chip->shared->dummy;
          chip->conn[3] = &chip->shared->dummy;
        }
      } else {
        chip->ch_pair->conn[0] = &chip->shared->dummy;
        chip->ch_pair->conn[1] = &chip->shared->dummy;
        chip->ch_pair->conn[2] = &chip->shared->dummy;
        chip->ch_pair->conn[3] = &chip->shared->dummy;
        switch (chip->conn_type & 3) {
          case 0:
            chip->ch_pair->ch[0]->conn = &chip->ch_pair->ch[0]->conn_a;
            chip->ch_pair->ch[1]->conn = &chip->ch_pair->ch[0]->conn_b;
            chip->ch[0]->conn = &chip->ch_pair->ch[1]->conn_b;
            chip->ch[1]->conn = &chip->ch[0]->conn_b;
            chip->conn[0] = &chip->ch_pair->ch[1]->conn_b;
            chip->conn[1] = &chip->shared->dummy;
            chip->conn[2] = &chip->shared->dummy;
            chip->conn[3] = &chip->shared->dummy;
            break;
          case 1:
            chip->ch_pair->ch[0]->conn = &chip->ch_pair->ch[0]->conn_a;
            chip->ch_pair->ch[1]->conn = &chip->ch_pair->ch[0]->conn_b;
            chip->ch[0]->conn = &chip->shared->dummy;
            chip->ch[1]->conn = &chip->ch[0]->conn_b;
            chip->conn[0] = &chip->ch_pair->ch[1]->conn_b;
            chip->conn[1] = &chip->ch[1]->conn_b;
            chip->conn[2] = &chip->shared->dummy;
            chip->conn[3] = &chip->shared->dummy;
            break;
          case 2:
            chip->ch_pair->ch[0]->conn = &chip->ch_pair->ch[0]->conn_a;
            chip->ch_pair->ch[1]->conn = &chip->shared->dummy;
            chip->ch[0]->conn = &chip->ch_pair->ch[1]->conn_b;
            chip->ch[1]->conn = &chip->ch[0]->conn_b;
            chip->conn[0] = &chip->ch_pair->ch[0]->conn_b;
            chip->conn[1] = &chip->ch[1]->conn_b;
            chip->conn[2] = &chip->shared->dummy;
            chip->conn[3] = &chip->shared->dummy;
            break;
          case 3:
            chip->ch_pair->ch[0]->conn = &chip->ch_pair->ch[0]->conn_a;
            chip->ch_pair->ch[1]->conn = &chip->shared->dummy;
            chip->ch[0]->conn = &chip->ch_pair->ch[1]->conn_b;
            chip->ch[1]->conn = &chip->shared->dummy;
            chip->conn[0] = &chip->ch_pair->ch[0]->conn_b;
            chip->conn[1] = &chip->ch[0]->conn_b;
            chip->conn[2] = &chip->ch[1]->conn_b;
            chip->conn[3] = &chip->shared->dummy;
            break;
        }
      }
    }
  }
}