static void update_slots( OPLL_CH *CH )
{
 int ksr;
 OPLL_SLOT *SLOT;
 OPLL_SLOT *BSLOT;
 int i;

 CH->eg_timer++;
 for( i = 0; i < 19; i++ )
 {
  SLOT = &CH->SLOT[i];
  BSLOT = NULL;
  if( ((SLOT)->type == 0) ) BSLOT = &CH->SLOT[i+1];
  if( ((SLOT)->type == 1) ) BSLOT = &CH->SLOT[i-1];

  if( SLOT->state )
  {
   commit_slot_update(SLOT);
  }

  ksr = (CH->eg_timer&((1<<((CH)->ksr_shift&7))-1)) == 0 ? (CH->ksr&((1<<((CH)->ksr_shift&7))-1)) : 0;
  calc_envelope(SLOT,BSLOT,(unsigned short)(CH->eg_timer&((1<<((CH)->ksr_shift&7))-1)),ksr&1);
  calc_phase(SLOT,CH->pm_phase,CH->ksr&4);

 }
}