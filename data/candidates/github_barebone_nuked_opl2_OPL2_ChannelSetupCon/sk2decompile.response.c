static void OPL2_ChannelSetupCon(opl2_chip_t *chip) {
  if (chip->type == 1) {
    if (chip->rom_type == 7 || chip->rom_type == 8) {
      chip->pch[0].patch->samples = &chip->chip->dummy_sample;
      chip->pch[1].patch->samples = &chip->chip->dummy_sample;
    } else {
      if (chip->connect == 0) {
        chip->pch[0].patch->samples = &chip->pch[0].sample_a;
        chip->pch[1].patch->samples = &chip->pch[0].sample_b;
      } else if (chip->connect == 1) {
        chip->pch[0].patch->samples = &chip->pch[0].sample_a;
        chip->pch[1].patch->samples = &chip->chip->dummy_sample;
      }
    }
  } else {
    if (chip->connect == 0) {
      chip->pch[0].patch->samples = &chip->pch[0].sample_a;
      chip->pch[1].patch->samples = &chip->pch[0].sample_b;
    } else if (chip->connect == 1) {
      chip->pch[0].patch->samples = &chip->pch[0].sample_a;
      chip->pch[1].patch->samples = &chip->chip->dummy_sample;
    }
  }
}