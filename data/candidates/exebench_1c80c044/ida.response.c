void __cdecl bn_mul_comba8(unsigned __int64 *r, unsigned __int64 *a, unsigned __int64 *b)
{
  int ht_62; // [rsp+0h] [rbp-850h]
  int ht_62a; // [rsp+0h] [rbp-850h]
  unsigned __int64 lt_62; // [rsp+8h] [rbp-848h]
  unsigned __int64 m1_62; // [rsp+10h] [rbp-840h]
  unsigned int m_62; // [rsp+18h] [rbp-838h]
  unsigned __int64 ht_61; // [rsp+20h] [rbp-830h]
  unsigned __int64 ht_61a; // [rsp+20h] [rbp-830h]
  unsigned __int64 lt_61; // [rsp+28h] [rbp-828h]
  unsigned __int64 m1_61; // [rsp+30h] [rbp-820h]
  unsigned int m_61; // [rsp+38h] [rbp-818h]
  unsigned __int64 ht_60; // [rsp+40h] [rbp-810h]
  unsigned __int64 ht_60a; // [rsp+40h] [rbp-810h]
  unsigned __int64 lt_60; // [rsp+48h] [rbp-808h]
  unsigned __int64 m1_60; // [rsp+50h] [rbp-800h]
  unsigned int m_60; // [rsp+58h] [rbp-7F8h]
  unsigned __int64 ht_59; // [rsp+60h] [rbp-7F0h]
  unsigned __int64 ht_59a; // [rsp+60h] [rbp-7F0h]
  unsigned __int64 lt_59; // [rsp+68h] [rbp-7E8h]
  unsigned __int64 m1_59; // [rsp+70h] [rbp-7E0h]
  unsigned int m_59; // [rsp+78h] [rbp-7D8h]
  unsigned __int64 ht_58; // [rsp+80h] [rbp-7D0h]
  unsigned __int64 ht_58a; // [rsp+80h] [rbp-7D0h]
  unsigned __int64 lt_58; // [rsp+88h] [rbp-7C8h]
  unsigned __int64 m1_58; // [rsp+90h] [rbp-7C0h]
  unsigned int m_58; // [rsp+98h] [rbp-7B8h]
  unsigned __int64 ht_57; // [rsp+A0h] [rbp-7B0h]
  unsigned __int64 ht_57a; // [rsp+A0h] [rbp-7B0h]
  unsigned __int64 lt_57; // [rsp+A8h] [rbp-7A8h]
  unsigned __int64 m1_57; // [rsp+B0h] [rbp-7A0h]
  unsigned int m_57; // [rsp+B8h] [rbp-798h]
  unsigned __int64 ht_56; // [rsp+C0h] [rbp-790h]
  unsigned __int64 ht_56a; // [rsp+C0h] [rbp-790h]
  unsigned __int64 lt_56; // [rsp+C8h] [rbp-788h]
  unsigned __int64 m1_56; // [rsp+D0h] [rbp-780h]
  unsigned int m_56; // [rsp+D8h] [rbp-778h]
  unsigned __int64 ht_55; // [rsp+E0h] [rbp-770h]
  unsigned __int64 ht_55a; // [rsp+E0h] [rbp-770h]
  unsigned __int64 lt_55; // [rsp+E8h] [rbp-768h]
  unsigned __int64 m1_55; // [rsp+F0h] [rbp-760h]
  unsigned int m_55; // [rsp+F8h] [rbp-758h]
  unsigned __int64 ht_54; // [rsp+100h] [rbp-750h]
  unsigned __int64 ht_54a; // [rsp+100h] [rbp-750h]
  unsigned __int64 lt_54; // [rsp+108h] [rbp-748h]
  unsigned __int64 m1_54; // [rsp+110h] [rbp-740h]
  unsigned int m_54; // [rsp+118h] [rbp-738h]
  unsigned __int64 ht_53; // [rsp+120h] [rbp-730h]
  unsigned __int64 ht_53a; // [rsp+120h] [rbp-730h]
  unsigned __int64 lt_53; // [rsp+128h] [rbp-728h]
  unsigned __int64 m1_53; // [rsp+130h] [rbp-720h]
  unsigned int m_53; // [rsp+138h] [rbp-718h]
  unsigned __int64 ht_52; // [rsp+140h] [rbp-710h]
  unsigned __int64 ht_52a; // [rsp+140h] [rbp-710h]
  unsigned __int64 lt_52; // [rsp+148h] [rbp-708h]
  unsigned __int64 m1_52; // [rsp+150h] [rbp-700h]
  unsigned int m_52; // [rsp+158h] [rbp-6F8h]
  unsigned __int64 ht_51; // [rsp+160h] [rbp-6F0h]
  unsigned __int64 ht_51a; // [rsp+160h] [rbp-6F0h]
  unsigned __int64 lt_51; // [rsp+168h] [rbp-6E8h]
  unsigned __int64 m1_51; // [rsp+170h] [rbp-6E0h]
  unsigned int m_51; // [rsp+178h] [rbp-6D8h]
  unsigned __int64 ht_50; // [rsp+180h] [rbp-6D0h]
  unsigned __int64 ht_50a; // [rsp+180h] [rbp-6D0h]
  unsigned __int64 lt_50; // [rsp+188h] [rbp-6C8h]
  unsigned __int64 m1_50; // [rsp+190h] [rbp-6C0h]
  unsigned int m_50; // [rsp+198h] [rbp-6B8h]
  unsigned __int64 ht_49; // [rsp+1A0h] [rbp-6B0h]
  unsigned __int64 ht_49a; // [rsp+1A0h] [rbp-6B0h]
  unsigned __int64 lt_49; // [rsp+1A8h] [rbp-6A8h]
  unsigned __int64 m1_49; // [rsp+1B0h] [rbp-6A0h]
  unsigned int m_49; // [rsp+1B8h] [rbp-698h]
  unsigned __int64 ht_48; // [rsp+1C0h] [rbp-690h]
  unsigned __int64 ht_48a; // [rsp+1C0h] [rbp-690h]
  unsigned __int64 lt_48; // [rsp+1C8h] [rbp-688h]
  unsigned __int64 m1_48; // [rsp+1D0h] [rbp-680h]
  unsigned int m_48; // [rsp+1D8h] [rbp-678h]
  unsigned __int64 ht_47; // [rsp+1E0h] [rbp-670h]
  unsigned __int64 ht_47a; // [rsp+1E0h] [rbp-670h]
  unsigned __int64 lt_47; // [rsp+1E8h] [rbp-668h]
  unsigned __int64 m1_47; // [rsp+1F0h] [rbp-660h]
  unsigned int m_47; // [rsp+1F8h] [rbp-658h]
  unsigned __int64 ht_46; // [rsp+200h] [rbp-650h]
  unsigned __int64 ht_46a; // [rsp+200h] [rbp-650h]
  unsigned __int64 lt_46; // [rsp+208h] [rbp-648h]
  unsigned __int64 m1_46; // [rsp+210h] [rbp-640h]
  unsigned int m_46; // [rsp+218h] [rbp-638h]
  unsigned __int64 ht_45; // [rsp+220h] [rbp-630h]
  unsigned __int64 ht_45a; // [rsp+220h] [rbp-630h]
  unsigned __int64 lt_45; // [rsp+228h] [rbp-628h]
  unsigned __int64 m1_45; // [rsp+230h] [rbp-620h]
  unsigned int m_45; // [rsp+238h] [rbp-618h]
  unsigned __int64 ht_44; // [rsp+240h] [rbp-610h]
  unsigned __int64 ht_44a; // [rsp+240h] [rbp-610h]
  unsigned __int64 lt_44; // [rsp+248h] [rbp-608h]
  unsigned __int64 m1_44; // [rsp+250h] [rbp-600h]
  unsigned int m_44; // [rsp+258h] [rbp-5F8h]
  unsigned __int64 ht_43; // [rsp+260h] [rbp-5F0h]
  unsigned __int64 ht_43a; // [rsp+260h] [rbp-5F0h]
  unsigned __int64 lt_43; // [rsp+268h] [rbp-5E8h]
  unsigned __int64 m1_43; // [rsp+270h] [rbp-5E0h]
  unsigned int m_43; // [rsp+278h] [rbp-5D8h]
  unsigned __int64 ht_42; // [rsp+280h] [rbp-5D0h]
  unsigned __int64 ht_42a; // [rsp+280h] [rbp-5D0h]
  unsigned __int64 lt_42; // [rsp+288h] [rbp-5C8h]
  unsigned __int64 m1_42; // [rsp+290h] [rbp-5C0h]
  unsigned int m_42; // [rsp+298h] [rbp-5B8h]
  unsigned __int64 ht_41; // [rsp+2A0h] [rbp-5B0h]
  unsigned __int64 ht_41a; // [rsp+2A0h] [rbp-5B0h]
  unsigned __int64 lt_41; // [rsp+2A8h] [rbp-5A8h]
  unsigned __int64 m1_41; // [rsp+2B0h] [rbp-5A0h]
  unsigned int m_41; // [rsp+2B8h] [rbp-598h]
  unsigned __int64 ht_40; // [rsp+2C0h] [rbp-590h]
  unsigned __int64 ht_40a; // [rsp+2C0h] [rbp-590h]
  unsigned __int64 lt_40; // [rsp+2C8h] [rbp-588h]
  unsigned __int64 m1_40; // [rsp+2D0h] [rbp-580h]
  unsigned int m_40; // [rsp+2D8h] [rbp-578h]
  unsigned __int64 ht_39; // [rsp+2E0h] [rbp-570h]
  unsigned __int64 ht_39a; // [rsp+2E0h] [rbp-570h]
  unsigned __int64 lt_39; // [rsp+2E8h] [rbp-568h]
  unsigned __int64 m1_39; // [rsp+2F0h] [rbp-560h]
  unsigned int m_39; // [rsp+2F8h] [rbp-558h]
  unsigned __int64 ht_38; // [rsp+300h] [rbp-550h]
  unsigned __int64 ht_38a; // [rsp+300h] [rbp-550h]
  unsigned __int64 lt_38; // [rsp+308h] [rbp-548h]
  unsigned __int64 m1_38; // [rsp+310h] [rbp-540h]
  unsigned int m_38; // [rsp+318h] [rbp-538h]
  unsigned __int64 ht_37; // [rsp+320h] [rbp-530h]
  unsigned __int64 ht_37a; // [rsp+320h] [rbp-530h]
  unsigned __int64 lt_37; // [rsp+328h] [rbp-528h]
  unsigned __int64 m1_37; // [rsp+330h] [rbp-520h]
  unsigned int m_37; // [rsp+338h] [rbp-518h]
  unsigned __int64 ht_36; // [rsp+340h] [rbp-510h]
  unsigned __int64 ht_36a; // [rsp+340h] [rbp-510h]
  unsigned __int64 lt_36; // [rsp+348h] [rbp-508h]
  unsigned __int64 m1_36; // [rsp+350h] [rbp-500h]
  unsigned int m_36; // [rsp+358h] [rbp-4F8h]
  unsigned __int64 ht_35; // [rsp+360h] [rbp-4F0h]
  unsigned __int64 ht_35a; // [rsp+360h] [rbp-4F0h]
  unsigned __int64 lt_35; // [rsp+368h] [rbp-4E8h]
  unsigned __int64 m1_35; // [rsp+370h] [rbp-4E0h]
  unsigned int m_35; // [rsp+378h] [rbp-4D8h]
  unsigned __int64 ht_34; // [rsp+380h] [rbp-4D0h]
  unsigned __int64 ht_34a; // [rsp+380h] [rbp-4D0h]
  unsigned __int64 lt_34; // [rsp+388h] [rbp-4C8h]
  unsigned __int64 m1_34; // [rsp+390h] [rbp-4C0h]
  unsigned int m_34; // [rsp+398h] [rbp-4B8h]
  unsigned __int64 ht_33; // [rsp+3A0h] [rbp-4B0h]
  unsigned __int64 ht_33a; // [rsp+3A0h] [rbp-4B0h]
  unsigned __int64 lt_33; // [rsp+3A8h] [rbp-4A8h]
  unsigned __int64 m1_33; // [rsp+3B0h] [rbp-4A0h]
  unsigned int m_33; // [rsp+3B8h] [rbp-498h]
  unsigned __int64 ht_32; // [rsp+3C0h] [rbp-490h]
  unsigned __int64 ht_32a; // [rsp+3C0h] [rbp-490h]
  unsigned __int64 lt_32; // [rsp+3C8h] [rbp-488h]
  unsigned __int64 m1_32; // [rsp+3D0h] [rbp-480h]
  unsigned int m_32; // [rsp+3D8h] [rbp-478h]
  unsigned __int64 ht_31; // [rsp+3E0h] [rbp-470h]
  unsigned __int64 ht_31a; // [rsp+3E0h] [rbp-470h]
  unsigned __int64 lt_31; // [rsp+3E8h] [rbp-468h]
  unsigned __int64 m1_31; // [rsp+3F0h] [rbp-460h]
  unsigned int m_31; // [rsp+3F8h] [rbp-458h]
  unsigned __int64 ht_30; // [rsp+400h] [rbp-450h]
  unsigned __int64 ht_30a; // [rsp+400h] [rbp-450h]
  unsigned __int64 lt_30; // [rsp+408h] [rbp-448h]
  unsigned __int64 m1_30; // [rsp+410h] [rbp-440h]
  unsigned int m_30; // [rsp+418h] [rbp-438h]
  unsigned __int64 ht_29; // [rsp+420h] [rbp-430h]
  unsigned __int64 ht_29a; // [rsp+420h] [rbp-430h]
  unsigned __int64 lt_29; // [rsp+428h] [rbp-428h]
  unsigned __int64 m1_29; // [rsp+430h] [rbp-420h]
  unsigned int m_29; // [rsp+438h] [rbp-418h]
  unsigned __int64 ht_28; // [rsp+440h] [rbp-410h]
  unsigned __int64 ht_28a; // [rsp+440h] [rbp-410h]
  unsigned __int64 lt_28; // [rsp+448h] [rbp-408h]
  unsigned __int64 m1_28; // [rsp+450h] [rbp-400h]
  unsigned int m_28; // [rsp+458h] [rbp-3F8h]
  unsigned __int64 ht_27; // [rsp+460h] [rbp-3F0h]
  unsigned __int64 ht_27a; // [rsp+460h] [rbp-3F0h]
  unsigned __int64 lt_27; // [rsp+468h] [rbp-3E8h]
  unsigned __int64 m1_27; // [rsp+470h] [rbp-3E0h]
  unsigned int m_27; // [rsp+478h] [rbp-3D8h]
  unsigned __int64 ht_26; // [rsp+480h] [rbp-3D0h]
  unsigned __int64 ht_26a; // [rsp+480h] [rbp-3D0h]
  unsigned __int64 lt_26; // [rsp+488h] [rbp-3C8h]
  unsigned __int64 m1_26; // [rsp+490h] [rbp-3C0h]
  unsigned int m_26; // [rsp+498h] [rbp-3B8h]
  unsigned __int64 ht_25; // [rsp+4A0h] [rbp-3B0h]
  unsigned __int64 ht_25a; // [rsp+4A0h] [rbp-3B0h]
  unsigned __int64 lt_25; // [rsp+4A8h] [rbp-3A8h]
  unsigned __int64 m1_25; // [rsp+4B0h] [rbp-3A0h]
  unsigned int m_25; // [rsp+4B8h] [rbp-398h]
  unsigned __int64 ht_24; // [rsp+4C0h] [rbp-390h]
  unsigned __int64 ht_24a; // [rsp+4C0h] [rbp-390h]
  unsigned __int64 lt_24; // [rsp+4C8h] [rbp-388h]
  unsigned __int64 m1_24; // [rsp+4D0h] [rbp-380h]
  unsigned int m_24; // [rsp+4D8h] [rbp-378h]
  unsigned __int64 ht_23; // [rsp+4E0h] [rbp-370h]
  unsigned __int64 ht_23a; // [rsp+4E0h] [rbp-370h]
  unsigned __int64 lt_23; // [rsp+4E8h] [rbp-368h]
  unsigned __int64 m1_23; // [rsp+4F0h] [rbp-360h]
  unsigned int m_23; // [rsp+4F8h] [rbp-358h]
  unsigned __int64 ht_22; // [rsp+500h] [rbp-350h]
  unsigned __int64 ht_22a; // [rsp+500h] [rbp-350h]
  unsigned __int64 lt_22; // [rsp+508h] [rbp-348h]
  unsigned __int64 m1_22; // [rsp+510h] [rbp-340h]
  unsigned int m_22; // [rsp+518h] [rbp-338h]
  unsigned __int64 ht_21; // [rsp+520h] [rbp-330h]
  unsigned __int64 ht_21a; // [rsp+520h] [rbp-330h]
  unsigned __int64 lt_21; // [rsp+528h] [rbp-328h]
  unsigned __int64 m1_21; // [rsp+530h] [rbp-320h]
  unsigned int m_21; // [rsp+538h] [rbp-318h]
  unsigned __int64 ht_20; // [rsp+540h] [rbp-310h]
  unsigned __int64 ht_20a; // [rsp+540h] [rbp-310h]
  unsigned __int64 lt_20; // [rsp+548h] [rbp-308h]
  unsigned __int64 m1_20; // [rsp+550h] [rbp-300h]
  unsigned int m_20; // [rsp+558h] [rbp-2F8h]
  unsigned __int64 ht_19; // [rsp+560h] [rbp-2F0h]
  unsigned __int64 ht_19a; // [rsp+560h] [rbp-2F0h]
  unsigned __int64 lt_19; // [rsp+568h] [rbp-2E8h]
  unsigned __int64 m1_19; // [rsp+570h] [rbp-2E0h]
  unsigned int m_19; // [rsp+578h] [rbp-2D8h]
  unsigned __int64 ht_18; // [rsp+580h] [rbp-2D0h]
  unsigned __int64 ht_18a; // [rsp+580h] [rbp-2D0h]
  unsigned __int64 lt_18; // [rsp+588h] [rbp-2C8h]
  unsigned __int64 m1_18; // [rsp+590h] [rbp-2C0h]
  unsigned int m_18; // [rsp+598h] [rbp-2B8h]
  unsigned __int64 ht_17; // [rsp+5A0h] [rbp-2B0h]
  unsigned __int64 ht_17a; // [rsp+5A0h] [rbp-2B0h]
  unsigned __int64 lt_17; // [rsp+5A8h] [rbp-2A8h]
  unsigned __int64 m1_17; // [rsp+5B0h] [rbp-2A0h]
  unsigned int m_17; // [rsp+5B8h] [rbp-298h]
  unsigned __int64 ht_16; // [rsp+5C0h] [rbp-290h]
  unsigned __int64 ht_16a; // [rsp+5C0h] [rbp-290h]
  unsigned __int64 lt_16; // [rsp+5C8h] [rbp-288h]
  unsigned __int64 m1_16; // [rsp+5D0h] [rbp-280h]
  unsigned int m_16; // [rsp+5D8h] [rbp-278h]
  unsigned __int64 ht_15; // [rsp+5E0h] [rbp-270h]
  unsigned __int64 ht_15a; // [rsp+5E0h] [rbp-270h]
  unsigned __int64 lt_15; // [rsp+5E8h] [rbp-268h]
  unsigned __int64 m1_15; // [rsp+5F0h] [rbp-260h]
  unsigned int m_15; // [rsp+5F8h] [rbp-258h]
  unsigned __int64 ht_14; // [rsp+600h] [rbp-250h]
  unsigned __int64 ht_14a; // [rsp+600h] [rbp-250h]
  unsigned __int64 lt_14; // [rsp+608h] [rbp-248h]
  unsigned __int64 m1_14; // [rsp+610h] [rbp-240h]
  unsigned int m_14; // [rsp+618h] [rbp-238h]
  unsigned __int64 ht_13; // [rsp+620h] [rbp-230h]
  unsigned __int64 ht_13a; // [rsp+620h] [rbp-230h]
  unsigned __int64 lt_13; // [rsp+628h] [rbp-228h]
  unsigned __int64 m1_13; // [rsp+630h] [rbp-220h]
  unsigned int m_13; // [rsp+638h] [rbp-218h]
  unsigned __int64 ht_12; // [rsp+640h] [rbp-210h]
  unsigned __int64 ht_12a; // [rsp+640h] [rbp-210h]
  unsigned __int64 lt_12; // [rsp+648h] [rbp-208h]
  unsigned __int64 m1_12; // [rsp+650h] [rbp-200h]
  unsigned int m_12; // [rsp+658h] [rbp-1F8h]
  unsigned __int64 ht_11; // [rsp+660h] [rbp-1F0h]
  unsigned __int64 ht_11a; // [rsp+660h] [rbp-1F0h]
  unsigned __int64 lt_11; // [rsp+668h] [rbp-1E8h]
  unsigned __int64 m1_11; // [rsp+670h] [rbp-1E0h]
  unsigned int m_11; // [rsp+678h] [rbp-1D8h]
  unsigned __int64 ht_10; // [rsp+680h] [rbp-1D0h]
  unsigned __int64 ht_10a; // [rsp+680h] [rbp-1D0h]
  unsigned __int64 lt_10; // [rsp+688h] [rbp-1C8h]
  unsigned __int64 m1_10; // [rsp+690h] [rbp-1C0h]
  unsigned int m_10; // [rsp+698h] [rbp-1B8h]
  unsigned __int64 ht_9; // [rsp+6A0h] [rbp-1B0h]
  unsigned __int64 ht_9a; // [rsp+6A0h] [rbp-1B0h]
  unsigned __int64 lt_9; // [rsp+6A8h] [rbp-1A8h]
  unsigned __int64 m1_9; // [rsp+6B0h] [rbp-1A0h]
  unsigned int m_9; // [rsp+6B8h] [rbp-198h]
  unsigned __int64 ht_8; // [rsp+6C0h] [rbp-190h]
  unsigned __int64 ht_8a; // [rsp+6C0h] [rbp-190h]
  unsigned __int64 lt_8; // [rsp+6C8h] [rbp-188h]
  unsigned __int64 m1_8; // [rsp+6D0h] [rbp-180h]
  unsigned int m_8; // [rsp+6D8h] [rbp-178h]
  unsigned __int64 ht_7; // [rsp+6E0h] [rbp-170h]
  unsigned __int64 ht_7a; // [rsp+6E0h] [rbp-170h]
  unsigned __int64 lt_7; // [rsp+6E8h] [rbp-168h]
  unsigned __int64 m1_7; // [rsp+6F0h] [rbp-160h]
  unsigned int m_7; // [rsp+6F8h] [rbp-158h]
  unsigned __int64 ht_6; // [rsp+700h] [rbp-150h]
  unsigned __int64 ht_6a; // [rsp+700h] [rbp-150h]
  unsigned __int64 lt_6; // [rsp+708h] [rbp-148h]
  unsigned __int64 m1_6; // [rsp+710h] [rbp-140h]
  unsigned int m_6; // [rsp+718h] [rbp-138h]
  unsigned __int64 ht_5; // [rsp+720h] [rbp-130h]
  unsigned __int64 ht_5a; // [rsp+720h] [rbp-130h]
  unsigned __int64 lt_5; // [rsp+728h] [rbp-128h]
  unsigned __int64 m1_5; // [rsp+730h] [rbp-120h]
  unsigned int m_5; // [rsp+738h] [rbp-118h]
  unsigned __int64 ht_4; // [rsp+740h] [rbp-110h]
  unsigned __int64 ht_4a; // [rsp+740h] [rbp-110h]
  unsigned __int64 lt_4; // [rsp+748h] [rbp-108h]
  unsigned __int64 m1_4; // [rsp+750h] [rbp-100h]
  unsigned int m_4; // [rsp+758h] [rbp-F8h]
  unsigned __int64 ht_3; // [rsp+760h] [rbp-F0h]
  unsigned __int64 ht_3a; // [rsp+760h] [rbp-F0h]
  unsigned __int64 lt_3; // [rsp+768h] [rbp-E8h]
  unsigned __int64 m1_3; // [rsp+770h] [rbp-E0h]
  unsigned int m_3; // [rsp+778h] [rbp-D8h]
  unsigned __int64 ht_2; // [rsp+780h] [rbp-D0h]
  unsigned __int64 ht_2a; // [rsp+780h] [rbp-D0h]
  unsigned __int64 lt_2; // [rsp+788h] [rbp-C8h]
  unsigned __int64 m1_2; // [rsp+790h] [rbp-C0h]
  unsigned int m_2; // [rsp+798h] [rbp-B8h]
  unsigned __int64 ht_1; // [rsp+7A0h] [rbp-B0h]
  unsigned __int64 ht_1a; // [rsp+7A0h] [rbp-B0h]
  unsigned __int64 lt_1; // [rsp+7A8h] [rbp-A8h]
  unsigned __int64 m1_1; // [rsp+7B0h] [rbp-A0h]
  unsigned int m_1; // [rsp+7B8h] [rbp-98h]
  unsigned __int64 ht_0; // [rsp+7C0h] [rbp-90h]
  unsigned __int64 ht_0a; // [rsp+7C0h] [rbp-90h]
  unsigned __int64 lt_0; // [rsp+7C8h] [rbp-88h]
  unsigned __int64 m1_0; // [rsp+7D0h] [rbp-80h]
  unsigned int m_0; // [rsp+7D8h] [rbp-78h]
  unsigned __int64 ht; // [rsp+7E0h] [rbp-70h]
  unsigned __int64 hta; // [rsp+7E0h] [rbp-70h]
  unsigned __int64 lt; // [rsp+7E8h] [rbp-68h]
  unsigned __int64 m1; // [rsp+7F0h] [rbp-60h]
  unsigned int m; // [rsp+7F8h] [rbp-58h]
  int c3; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3a; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3b; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3c; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3d; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3e; // [rsp+800h] [rbp-50h]
  int c3f; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3g; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3h; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3i; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3j; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3k; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3l; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3m; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3n; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3o; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3p; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3q; // [rsp+800h] [rbp-50h]
  int c3r; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3s; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3t; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3u; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3v; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3w; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3x; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3y; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3z; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3ba; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bb; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bc; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bd; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3be; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bf; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bg; // [rsp+800h] [rbp-50h]
  int c3bh; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bi; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bj; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bk; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bl; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bm; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bn; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bo; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bp; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bq; // [rsp+800h] [rbp-50h]
  int c3br; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bs; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bt; // [rsp+800h] [rbp-50h]
  unsigned __int64 c3bu; // [rsp+800h] [rbp-50h]
  unsigned __int64 c2; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2a; // [rsp+808h] [rbp-48h]
  int c2b; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2c; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2d; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2e; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2f; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2g; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2h; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2i; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2j; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2k; // [rsp+808h] [rbp-48h]
  int c2l; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2m; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2n; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2o; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2p; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2q; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2r; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2s; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2t; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2u; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2v; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2w; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2x; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2y; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2z; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2ba; // [rsp+808h] [rbp-48h]
  int c2bb; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bc; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bd; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2be; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bf; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bg; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bh; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bi; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bj; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bk; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bl; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bm; // [rsp+808h] [rbp-48h]
  int c2bn; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bo; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bp; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bq; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2br; // [rsp+808h] [rbp-48h]
  unsigned __int64 c2bs; // [rsp+808h] [rbp-48h]
  int c1; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1a; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1b; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1c; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1d; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1e; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1f; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1g; // [rsp+810h] [rbp-40h]
  int c1h; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1i; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1j; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1k; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1l; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1m; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1n; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1o; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1p; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1q; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1r; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1s; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1t; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1u; // [rsp+810h] [rbp-40h]
  int c1v; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1w; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1x; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1y; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1z; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1ba; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bb; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bc; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bd; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1be; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bf; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bg; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bh; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bi; // [rsp+810h] [rbp-40h]
  int c1bj; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bk; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bl; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bm; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bn; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bo; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bp; // [rsp+810h] [rbp-40h]
  unsigned __int64 c1bq; // [rsp+810h] [rbp-40h]
  int c1br; // [rsp+810h] [rbp-40h]
  unsigned __int64 t2ck; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cl; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cm; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2a; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cn; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2b; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2co; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2c; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cp; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2d; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cq; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2e; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cr; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2f; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cs; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2g; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ct; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2h; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cu; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2i; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cv; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2j; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cw; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2k; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cx; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2l; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cy; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2m; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cz; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2n; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2da; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2o; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2db; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2p; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dc; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2q; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dd; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2r; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2de; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2s; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2df; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2t; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dg; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2u; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dh; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2v; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2di; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2w; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dj; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2x; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dk; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2y; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dl; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2z; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dm; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ba; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dn; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bb; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2do; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bc; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dp; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bd; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dq; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2be; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dr; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bf; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ds; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bg; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dt; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bh; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2du; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bi; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dv; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bj; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dw; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bk; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dx; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bl; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dy; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bm; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2dz; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bn; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ea; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bo; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eb; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bp; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ec; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bq; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ed; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2br; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ee; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bs; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ef; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bt; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eg; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bu; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eh; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bv; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ei; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bw; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ej; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bx; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ek; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2by; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2el; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2bz; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2em; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ca; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2en; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cb; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eo; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cc; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ep; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cd; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eq; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ce; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2er; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cf; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2es; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2cg; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2et; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ch; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2eu; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ci; // [rsp+818h] [rbp-38h]
  unsigned __int64 t2ev; // [rsp+818h] [rbp-38h]
  int t2cj; // [rsp+818h] [rbp-38h]
  int t1; // [rsp+820h] [rbp-30h]
  int t1a; // [rsp+820h] [rbp-30h]
  int t1b; // [rsp+820h] [rbp-30h]
  int t1c; // [rsp+820h] [rbp-30h]
  int t1d; // [rsp+820h] [rbp-30h]
  int t1e; // [rsp+820h] [rbp-30h]
  int t1f; // [rsp+820h] [rbp-30h]
  int t1g; // [rsp+820h] [rbp-30h]
  int t1h; // [rsp+820h] [rbp-30h]
  int t1i; // [rsp+820h] [rbp-30h]
  int t1j; // [rsp+820h] [rbp-30h]
  int t1k; // [rsp+820h] [rbp-30h]
  int t1l; // [rsp+820h] [rbp-30h]
  int t1m; // [rsp+820h] [rbp-30h]
  int t1n; // [rsp+820h] [rbp-30h]
  int t1o; // [rsp+820h] [rbp-30h]
  int t1p; // [rsp+820h] [rbp-30h]
  int t1q; // [rsp+820h] [rbp-30h]
  int t1r; // [rsp+820h] [rbp-30h]
  int t1s; // [rsp+820h] [rbp-30h]
  int t1t; // [rsp+820h] [rbp-30h]
  int t1u; // [rsp+820h] [rbp-30h]
  int t1v; // [rsp+820h] [rbp-30h]
  int t1w; // [rsp+820h] [rbp-30h]
  int t1x; // [rsp+820h] [rbp-30h]
  int t1y; // [rsp+820h] [rbp-30h]
  int t1z; // [rsp+820h] [rbp-30h]
  int t1ba; // [rsp+820h] [rbp-30h]
  int t1bb; // [rsp+820h] [rbp-30h]
  int t1bc; // [rsp+820h] [rbp-30h]
  int t1bd; // [rsp+820h] [rbp-30h]
  int t1be; // [rsp+820h] [rbp-30h]
  int t1bf; // [rsp+820h] [rbp-30h]
  int t1bg; // [rsp+820h] [rbp-30h]
  int t1bh; // [rsp+820h] [rbp-30h]
  int t1bi; // [rsp+820h] [rbp-30h]
  int t1bj; // [rsp+820h] [rbp-30h]
  int t1bk; // [rsp+820h] [rbp-30h]
  int t1bl; // [rsp+820h] [rbp-30h]
  int t1bm; // [rsp+820h] [rbp-30h]
  int t1bn; // [rsp+820h] [rbp-30h]
  int t1bo; // [rsp+820h] [rbp-30h]
  int t1bp; // [rsp+820h] [rbp-30h]
  int t1bq; // [rsp+820h] [rbp-30h]
  int t1br; // [rsp+820h] [rbp-30h]
  int t1bs; // [rsp+820h] [rbp-30h]
  int t1bt; // [rsp+820h] [rbp-30h]
  int t1bu; // [rsp+820h] [rbp-30h]
  int t1bv; // [rsp+820h] [rbp-30h]
  int t1bw; // [rsp+820h] [rbp-30h]
  int t1bx; // [rsp+820h] [rbp-30h]
  int t1by; // [rsp+820h] [rbp-30h]
  int t1bz; // [rsp+820h] [rbp-30h]
  int t1ca; // [rsp+820h] [rbp-30h]
  int t1cb; // [rsp+820h] [rbp-30h]
  int t1cc; // [rsp+820h] [rbp-30h]
  int t1cd; // [rsp+820h] [rbp-30h]
  int t1ce; // [rsp+820h] [rbp-30h]
  int t1cf; // [rsp+820h] [rbp-30h]
  int t1cg; // [rsp+820h] [rbp-30h]
  int t1ch; // [rsp+820h] [rbp-30h]
  int t1ci; // [rsp+820h] [rbp-30h]
  int t1cj; // [rsp+820h] [rbp-30h]
  int t1ck; // [rsp+820h] [rbp-30h]
  unsigned __int64 bh_0; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0a; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0b; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0c; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0d; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0e; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0f; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0g; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0h; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0i; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0j; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0k; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0l; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0m; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0n; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0o; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0p; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0q; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0r; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0s; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0t; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0u; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0v; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0w; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0x; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0y; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0z; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0ba; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bb; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bc; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bd; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0be; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bf; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bg; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bh; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bi; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bj; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bk; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bl; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bm; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bn; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bo; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bp; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bq; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0br; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bs; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bt; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bu; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bv; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bw; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bx; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0by; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0bz; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0ca; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cb; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cc; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cd; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0ce; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cf; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cg; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0ch; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0ci; // [rsp+828h] [rbp-28h]
  unsigned __int64 bh_0cj; // [rsp+828h] [rbp-28h]
  unsigned int bh_0ck; // [rsp+828h] [rbp-28h]
  unsigned __int64 bl_0; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0a; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0b; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0c; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0d; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0e; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0f; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0g; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0h; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0i; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0j; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0k; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0l; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0m; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0n; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0o; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0p; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0q; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0r; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0s; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0t; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0u; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0v; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0w; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0x; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0y; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0z; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ba; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bb; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bc; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bd; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0be; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bf; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bg; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bh; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bi; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bj; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bk; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bl; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bm; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bn; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bo; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bp; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bq; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0br; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bs; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bt; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bu; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bv; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bw; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bx; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0by; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0bz; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ca; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cb; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cc; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cd; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ce; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cf; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cg; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ch; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ci; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0cj; // [rsp+830h] [rbp-20h]
  unsigned __int64 bl_0ck; // [rsp+830h] [rbp-20h]

  c3 = 0;
  t1 = (unsigned __int16)*a;
  t2ck = WORD1(*a);
  bl_0 = (unsigned __int16)*b;
  bh_0 = WORD1(*b);
  ht = t2ck * bh_0;
  m = t2ck * bl_0 + t1 * bh_0;
  if ( m < t2ck * bl_0 )
    ht += 0x10000LL;
  hta = ht + HIWORD(m);
  m1 = m << 16;
  lt = (unsigned int)(m1 + t1 * bl_0);
  if ( lt < m1 )
    ++hta;
  if ( (unsigned int)hta < hta )
    c3 = 1;
  *r = (unsigned int)lt;
  c1 = 0;
  t1a = (unsigned __int16)*a;
  t2cl = WORD1(*a);
  bl_0a = (unsigned __int16)b[1];
  bh_0a = WORD1(b[1]);
  ht_0 = t2cl * bh_0a;
  m_0 = t2cl * bl_0a + t1a * bh_0a;
  if ( m_0 < t2cl * bl_0a )
    ht_0 += 0x10000LL;
  ht_0a = ht_0 + HIWORD(m_0);
  m1_0 = m_0 << 16;
  lt_0 = (unsigned int)(m1_0 + t1a * bl_0a);
  if ( lt_0 < m1_0 )
    ++ht_0a;
  t2 = ht_0a;
  c2 = (unsigned int)(lt_0 + hta);
  if ( c2 < lt_0 )
    t2 = ht_0a + 1;
  c3a = (unsigned int)(t2 + c3);
  if ( c3a < t2 )
    c1 = 1;
  t1b = (unsigned __int16)a[1];
  t2cm = WORD1(a[1]);
  bl_0b = (unsigned __int16)*b;
  bh_0b = WORD1(*b);
  ht_1 = t2cm * bh_0b;
  m_1 = t2cm * bl_0b + t1b * bh_0b;
  if ( m_1 < t2cm * bl_0b )
    ht_1 += 0x10000LL;
  ht_1a = ht_1 + HIWORD(m_1);
  m1_1 = m_1 << 16;
  lt_1 = (unsigned int)(m1_1 + t1b * bl_0b);
  if ( lt_1 < m1_1 )
    ++ht_1a;
  t2a = ht_1a;
  c2a = (unsigned int)(lt_1 + c2);
  if ( c2a < lt_1 )
    t2a = ht_1a + 1;
  c3b = (unsigned int)(t2a + c3a);
  if ( c3b < t2a )
    ++c1;
  r[1] = c2a;
  c2b = 0;
  t1c = (unsigned __int16)a[2];
  t2cn = WORD1(a[2]);
  bl_0c = (unsigned __int16)*b;
  bh_0c = WORD1(*b);
  ht_2 = t2cn * bh_0c;
  m_2 = t2cn * bl_0c + t1c * bh_0c;
  if ( m_2 < t2cn * bl_0c )
    ht_2 += 0x10000LL;
  ht_2a = ht_2 + HIWORD(m_2);
  m1_2 = m_2 << 16;
  lt_2 = (unsigned int)(m1_2 + t1c * bl_0c);
  if ( lt_2 < m1_2 )
    ++ht_2a;
  t2b = ht_2a;
  c3c = (unsigned int)(lt_2 + c3b);
  if ( c3c < lt_2 )
    t2b = ht_2a + 1;
  c1a = (unsigned int)(t2b + c1);
  if ( c1a < t2b )
    c2b = 1;
  t1d = (unsigned __int16)a[1];
  t2co = WORD1(a[1]);
  bl_0d = (unsigned __int16)b[1];
  bh_0d = WORD1(b[1]);
  ht_3 = t2co * bh_0d;
  m_3 = t2co * bl_0d + t1d * bh_0d;
  if ( m_3 < t2co * bl_0d )
    ht_3 += 0x10000LL;
  ht_3a = ht_3 + HIWORD(m_3);
  m1_3 = m_3 << 16;
  lt_3 = (unsigned int)(m1_3 + t1d * bl_0d);
  if ( lt_3 < m1_3 )
    ++ht_3a;
  t2c = ht_3a;
  c3d = (unsigned int)(lt_3 + c3c);
  if ( c3d < lt_3 )
    t2c = ht_3a + 1;
  c1b = (unsigned int)(t2c + c1a);
  if ( c1b < t2c )
    ++c2b;
  t1e = (unsigned __int16)*a;
  t2cp = WORD1(*a);
  bl_0e = (unsigned __int16)b[2];
  bh_0e = WORD1(b[2]);
  ht_4 = t2cp * bh_0e;
  m_4 = t2cp * bl_0e + t1e * bh_0e;
  if ( m_4 < t2cp * bl_0e )
    ht_4 += 0x10000LL;
  ht_4a = ht_4 + HIWORD(m_4);
  m1_4 = m_4 << 16;
  lt_4 = (unsigned int)(m1_4 + t1e * bl_0e);
  if ( lt_4 < m1_4 )
    ++ht_4a;
  t2d = ht_4a;
  c3e = (unsigned int)(lt_4 + c3d);
  if ( c3e < lt_4 )
    t2d = ht_4a + 1;
  c1c = (unsigned int)(t2d + c1b);
  if ( c1c < t2d )
    ++c2b;
  r[2] = c3e;
  c3f = 0;
  t1f = (unsigned __int16)*a;
  t2cq = WORD1(*a);
  bl_0f = (unsigned __int16)b[3];
  bh_0f = WORD1(b[3]);
  ht_5 = t2cq * bh_0f;
  m_5 = t2cq * bl_0f + t1f * bh_0f;
  if ( m_5 < t2cq * bl_0f )
    ht_5 += 0x10000LL;
  ht_5a = ht_5 + HIWORD(m_5);
  m1_5 = m_5 << 16;
  lt_5 = (unsigned int)(m1_5 + t1f * bl_0f);
  if ( lt_5 < m1_5 )
    ++ht_5a;
  t2e = ht_5a;
  c1d = (unsigned int)(lt_5 + c1c);
  if ( c1d < lt_5 )
    t2e = ht_5a + 1;
  c2c = (unsigned int)(t2e + c2b);
  if ( c2c < t2e )
    c3f = 1;
  t1g = (unsigned __int16)a[1];
  t2cr = WORD1(a[1]);
  bl_0g = (unsigned __int16)b[2];
  bh_0g = WORD1(b[2]);
  ht_6 = t2cr * bh_0g;
  m_6 = t2cr * bl_0g + t1g * bh_0g;
  if ( m_6 < t2cr * bl_0g )
    ht_6 += 0x10000LL;
  ht_6a = ht_6 + HIWORD(m_6);
  m1_6 = m_6 << 16;
  lt_6 = (unsigned int)(m1_6 + t1g * bl_0g);
  if ( lt_6 < m1_6 )
    ++ht_6a;
  t2f = ht_6a;
  c1e = (unsigned int)(lt_6 + c1d);
  if ( c1e < lt_6 )
    t2f = ht_6a + 1;
  c2d = (unsigned int)(t2f + c2c);
  if ( c2d < t2f )
    ++c3f;
  t1h = (unsigned __int16)a[2];
  t2cs = WORD1(a[2]);
  bl_0h = (unsigned __int16)b[1];
  bh_0h = WORD1(b[1]);
  ht_7 = t2cs * bh_0h;
  m_7 = t2cs * bl_0h + t1h * bh_0h;
  if ( m_7 < t2cs * bl_0h )
    ht_7 += 0x10000LL;
  ht_7a = ht_7 + HIWORD(m_7);
  m1_7 = m_7 << 16;
  lt_7 = (unsigned int)(m1_7 + t1h * bl_0h);
  if ( lt_7 < m1_7 )
    ++ht_7a;
  t2g = ht_7a;
  c1f = (unsigned int)(lt_7 + c1e);
  if ( c1f < lt_7 )
    t2g = ht_7a + 1;
  c2e = (unsigned int)(t2g + c2d);
  if ( c2e < t2g )
    ++c3f;
  t1i = (unsigned __int16)a[3];
  t2ct = WORD1(a[3]);
  bl_0i = (unsigned __int16)*b;
  bh_0i = WORD1(*b);
  ht_8 = t2ct * bh_0i;
  m_8 = t2ct * bl_0i + t1i * bh_0i;
  if ( m_8 < t2ct * bl_0i )
    ht_8 += 0x10000LL;
  ht_8a = ht_8 + HIWORD(m_8);
  m1_8 = m_8 << 16;
  lt_8 = (unsigned int)(m1_8 + t1i * bl_0i);
  if ( lt_8 < m1_8 )
    ++ht_8a;
  t2h = ht_8a;
  c1g = (unsigned int)(lt_8 + c1f);
  if ( c1g < lt_8 )
    t2h = ht_8a + 1;
  c2f = (unsigned int)(t2h + c2e);
  if ( c2f < t2h )
    ++c3f;
  r[3] = c1g;
  c1h = 0;
  t1j = (unsigned __int16)a[4];
  t2cu = WORD1(a[4]);
  bl_0j = (unsigned __int16)*b;
  bh_0j = WORD1(*b);
  ht_9 = t2cu * bh_0j;
  m_9 = t2cu * bl_0j + t1j * bh_0j;
  if ( m_9 < t2cu * bl_0j )
    ht_9 += 0x10000LL;
  ht_9a = ht_9 + HIWORD(m_9);
  m1_9 = m_9 << 16;
  lt_9 = (unsigned int)(m1_9 + t1j * bl_0j);
  if ( lt_9 < m1_9 )
    ++ht_9a;
  t2i = ht_9a;
  c2g = (unsigned int)(lt_9 + c2f);
  if ( c2g < lt_9 )
    t2i = ht_9a + 1;
  c3g = (unsigned int)(t2i + c3f);
  if ( c3g < t2i )
    c1h = 1;
  t1k = (unsigned __int16)a[3];
  t2cv = WORD1(a[3]);
  bl_0k = (unsigned __int16)b[1];
  bh_0k = WORD1(b[1]);
  ht_10 = t2cv * bh_0k;
  m_10 = t2cv * bl_0k + t1k * bh_0k;
  if ( m_10 < t2cv * bl_0k )
    ht_10 += 0x10000LL;
  ht_10a = ht_10 + HIWORD(m_10);
  m1_10 = m_10 << 16;
  lt_10 = (unsigned int)(m1_10 + t1k * bl_0k);
  if ( lt_10 < m1_10 )
    ++ht_10a;
  t2j = ht_10a;
  c2h = (unsigned int)(lt_10 + c2g);
  if ( c2h < lt_10 )
    t2j = ht_10a + 1;
  c3h = (unsigned int)(t2j + c3g);
  if ( c3h < t2j )
    ++c1h;
  t1l = (unsigned __int16)a[2];
  t2cw = WORD1(a[2]);
  bl_0l = (unsigned __int16)b[2];
  bh_0l = WORD1(b[2]);
  ht_11 = t2cw * bh_0l;
  m_11 = t2cw * bl_0l + t1l * bh_0l;
  if ( m_11 < t2cw * bl_0l )
    ht_11 += 0x10000LL;
  ht_11a = ht_11 + HIWORD(m_11);
  m1_11 = m_11 << 16;
  lt_11 = (unsigned int)(m1_11 + t1l * bl_0l);
  if ( lt_11 < m1_11 )
    ++ht_11a;
  t2k = ht_11a;
  c2i = (unsigned int)(lt_11 + c2h);
  if ( c2i < lt_11 )
    t2k = ht_11a + 1;
  c3i = (unsigned int)(t2k + c3h);
  if ( c3i < t2k )
    ++c1h;
  t1m = (unsigned __int16)a[1];
  t2cx = WORD1(a[1]);
  bl_0m = (unsigned __int16)b[3];
  bh_0m = WORD1(b[3]);
  ht_12 = t2cx * bh_0m;
  m_12 = t2cx * bl_0m + t1m * bh_0m;
  if ( m_12 < t2cx * bl_0m )
    ht_12 += 0x10000LL;
  ht_12a = ht_12 + HIWORD(m_12);
  m1_12 = m_12 << 16;
  lt_12 = (unsigned int)(m1_12 + t1m * bl_0m);
  if ( lt_12 < m1_12 )
    ++ht_12a;
  t2l = ht_12a;
  c2j = (unsigned int)(lt_12 + c2i);
  if ( c2j < lt_12 )
    t2l = ht_12a + 1;
  c3j = (unsigned int)(t2l + c3i);
  if ( c3j < t2l )
    ++c1h;
  t1n = (unsigned __int16)*a;
  t2cy = WORD1(*a);
  bl_0n = (unsigned __int16)b[4];
  bh_0n = WORD1(b[4]);
  ht_13 = t2cy * bh_0n;
  m_13 = t2cy * bl_0n + t1n * bh_0n;
  if ( m_13 < t2cy * bl_0n )
    ht_13 += 0x10000LL;
  ht_13a = ht_13 + HIWORD(m_13);
  m1_13 = m_13 << 16;
  lt_13 = (unsigned int)(m1_13 + t1n * bl_0n);
  if ( lt_13 < m1_13 )
    ++ht_13a;
  t2m = ht_13a;
  c2k = (unsigned int)(lt_13 + c2j);
  if ( c2k < lt_13 )
    t2m = ht_13a + 1;
  c3k = (unsigned int)(t2m + c3j);
  if ( c3k < t2m )
    ++c1h;
  r[4] = c2k;
  c2l = 0;
  t1o = (unsigned __int16)*a;
  t2cz = WORD1(*a);
  bl_0o = (unsigned __int16)b[5];
  bh_0o = WORD1(b[5]);
  ht_14 = t2cz * bh_0o;
  m_14 = t2cz * bl_0o + t1o * bh_0o;
  if ( m_14 < t2cz * bl_0o )
    ht_14 += 0x10000LL;
  ht_14a = ht_14 + HIWORD(m_14);
  m1_14 = m_14 << 16;
  lt_14 = (unsigned int)(m1_14 + t1o * bl_0o);
  if ( lt_14 < m1_14 )
    ++ht_14a;
  t2n = ht_14a;
  c3l = (unsigned int)(lt_14 + c3k);
  if ( c3l < lt_14 )
    t2n = ht_14a + 1;
  c1i = (unsigned int)(t2n + c1h);
  if ( c1i < t2n )
    c2l = 1;
  t1p = (unsigned __int16)a[1];
  t2da = WORD1(a[1]);
  bl_0p = (unsigned __int16)b[4];
  bh_0p = WORD1(b[4]);
  ht_15 = t2da * bh_0p;
  m_15 = t2da * bl_0p + t1p * bh_0p;
  if ( m_15 < t2da * bl_0p )
    ht_15 += 0x10000LL;
  ht_15a = ht_15 + HIWORD(m_15);
  m1_15 = m_15 << 16;
  lt_15 = (unsigned int)(m1_15 + t1p * bl_0p);
  if ( lt_15 < m1_15 )
    ++ht_15a;
  t2o = ht_15a;
  c3m = (unsigned int)(lt_15 + c3l);
  if ( c3m < lt_15 )
    t2o = ht_15a + 1;
  c1j = (unsigned int)(t2o + c1i);
  if ( c1j < t2o )
    ++c2l;
  t1q = (unsigned __int16)a[2];
  t2db = WORD1(a[2]);
  bl_0q = (unsigned __int16)b[3];
  bh_0q = WORD1(b[3]);
  ht_16 = t2db * bh_0q;
  m_16 = t2db * bl_0q + t1q * bh_0q;
  if ( m_16 < t2db * bl_0q )
    ht_16 += 0x10000LL;
  ht_16a = ht_16 + HIWORD(m_16);
  m1_16 = m_16 << 16;
  lt_16 = (unsigned int)(m1_16 + t1q * bl_0q);
  if ( lt_16 < m1_16 )
    ++ht_16a;
  t2p = ht_16a;
  c3n = (unsigned int)(lt_16 + c3m);
  if ( c3n < lt_16 )
    t2p = ht_16a + 1;
  c1k = (unsigned int)(t2p + c1j);
  if ( c1k < t2p )
    ++c2l;
  t1r = (unsigned __int16)a[3];
  t2dc = WORD1(a[3]);
  bl_0r = (unsigned __int16)b[2];
  bh_0r = WORD1(b[2]);
  ht_17 = t2dc * bh_0r;
  m_17 = t2dc * bl_0r + t1r * bh_0r;
  if ( m_17 < t2dc * bl_0r )
    ht_17 += 0x10000LL;
  ht_17a = ht_17 + HIWORD(m_17);
  m1_17 = m_17 << 16;
  lt_17 = (unsigned int)(m1_17 + t1r * bl_0r);
  if ( lt_17 < m1_17 )
    ++ht_17a;
  t2q = ht_17a;
  c3o = (unsigned int)(lt_17 + c3n);
  if ( c3o < lt_17 )
    t2q = ht_17a + 1;
  c1l = (unsigned int)(t2q + c1k);
  if ( c1l < t2q )
    ++c2l;
  t1s = (unsigned __int16)a[4];
  t2dd = WORD1(a[4]);
  bl_0s = (unsigned __int16)b[1];
  bh_0s = WORD1(b[1]);
  ht_18 = t2dd * bh_0s;
  m_18 = t2dd * bl_0s + t1s * bh_0s;
  if ( m_18 < t2dd * bl_0s )
    ht_18 += 0x10000LL;
  ht_18a = ht_18 + HIWORD(m_18);
  m1_18 = m_18 << 16;
  lt_18 = (unsigned int)(m1_18 + t1s * bl_0s);
  if ( lt_18 < m1_18 )
    ++ht_18a;
  t2r = ht_18a;
  c3p = (unsigned int)(lt_18 + c3o);
  if ( c3p < lt_18 )
    t2r = ht_18a + 1;
  c1m = (unsigned int)(t2r + c1l);
  if ( c1m < t2r )
    ++c2l;
  t1t = (unsigned __int16)a[5];
  t2de = WORD1(a[5]);
  bl_0t = (unsigned __int16)*b;
  bh_0t = WORD1(*b);
  ht_19 = t2de * bh_0t;
  m_19 = t2de * bl_0t + t1t * bh_0t;
  if ( m_19 < t2de * bl_0t )
    ht_19 += 0x10000LL;
  ht_19a = ht_19 + HIWORD(m_19);
  m1_19 = m_19 << 16;
  lt_19 = (unsigned int)(m1_19 + t1t * bl_0t);
  if ( lt_19 < m1_19 )
    ++ht_19a;
  t2s = ht_19a;
  c3q = (unsigned int)(lt_19 + c3p);
  if ( c3q < lt_19 )
    t2s = ht_19a + 1;
  c1n = (unsigned int)(t2s + c1m);
  if ( c1n < t2s )
    ++c2l;
  r[5] = c3q;
  c3r = 0;
  t1u = (unsigned __int16)a[6];
  t2df = WORD1(a[6]);
  bl_0u = (unsigned __int16)*b;
  bh_0u = WORD1(*b);
  ht_20 = t2df * bh_0u;
  m_20 = t2df * bl_0u + t1u * bh_0u;
  if ( m_20 < t2df * bl_0u )
    ht_20 += 0x10000LL;
  ht_20a = ht_20 + HIWORD(m_20);
  m1_20 = m_20 << 16;
  lt_20 = (unsigned int)(m1_20 + t1u * bl_0u);
  if ( lt_20 < m1_20 )
    ++ht_20a;
  t2t = ht_20a;
  c1o = (unsigned int)(lt_20 + c1n);
  if ( c1o < lt_20 )
    t2t = ht_20a + 1;
  c2m = (unsigned int)(t2t + c2l);
  if ( c2m < t2t )
    c3r = 1;
  t1v = (unsigned __int16)a[5];
  t2dg = WORD1(a[5]);
  bl_0v = (unsigned __int16)b[1];
  bh_0v = WORD1(b[1]);
  ht_21 = t2dg * bh_0v;
  m_21 = t2dg * bl_0v + t1v * bh_0v;
  if ( m_21 < t2dg * bl_0v )
    ht_21 += 0x10000LL;
  ht_21a = ht_21 + HIWORD(m_21);
  m1_21 = m_21 << 16;
  lt_21 = (unsigned int)(m1_21 + t1v * bl_0v);
  if ( lt_21 < m1_21 )
    ++ht_21a;
  t2u = ht_21a;
  c1p = (unsigned int)(lt_21 + c1o);
  if ( c1p < lt_21 )
    t2u = ht_21a + 1;
  c2n = (unsigned int)(t2u + c2m);
  if ( c2n < t2u )
    ++c3r;
  t1w = (unsigned __int16)a[4];
  t2dh = WORD1(a[4]);
  bl_0w = (unsigned __int16)b[2];
  bh_0w = WORD1(b[2]);
  ht_22 = t2dh * bh_0w;
  m_22 = t2dh * bl_0w + t1w * bh_0w;
  if ( m_22 < t2dh * bl_0w )
    ht_22 += 0x10000LL;
  ht_22a = ht_22 + HIWORD(m_22);
  m1_22 = m_22 << 16;
  lt_22 = (unsigned int)(m1_22 + t1w * bl_0w);
  if ( lt_22 < m1_22 )
    ++ht_22a;
  t2v = ht_22a;
  c1q = (unsigned int)(lt_22 + c1p);
  if ( c1q < lt_22 )
    t2v = ht_22a + 1;
  c2o = (unsigned int)(t2v + c2n);
  if ( c2o < t2v )
    ++c3r;
  t1x = (unsigned __int16)a[3];
  t2di = WORD1(a[3]);
  bl_0x = (unsigned __int16)b[3];
  bh_0x = WORD1(b[3]);
  ht_23 = t2di * bh_0x;
  m_23 = t2di * bl_0x + t1x * bh_0x;
  if ( m_23 < t2di * bl_0x )
    ht_23 += 0x10000LL;
  ht_23a = ht_23 + HIWORD(m_23);
  m1_23 = m_23 << 16;
  lt_23 = (unsigned int)(m1_23 + t1x * bl_0x);
  if ( lt_23 < m1_23 )
    ++ht_23a;
  t2w = ht_23a;
  c1r = (unsigned int)(lt_23 + c1q);
  if ( c1r < lt_23 )
    t2w = ht_23a + 1;
  c2p = (unsigned int)(t2w + c2o);
  if ( c2p < t2w )
    ++c3r;
  t1y = (unsigned __int16)a[2];
  t2dj = WORD1(a[2]);
  bl_0y = (unsigned __int16)b[4];
  bh_0y = WORD1(b[4]);
  ht_24 = t2dj * bh_0y;
  m_24 = t2dj * bl_0y + t1y * bh_0y;
  if ( m_24 < t2dj * bl_0y )
    ht_24 += 0x10000LL;
  ht_24a = ht_24 + HIWORD(m_24);
  m1_24 = m_24 << 16;
  lt_24 = (unsigned int)(m1_24 + t1y * bl_0y);
  if ( lt_24 < m1_24 )
    ++ht_24a;
  t2x = ht_24a;
  c1s = (unsigned int)(lt_24 + c1r);
  if ( c1s < lt_24 )
    t2x = ht_24a + 1;
  c2q = (unsigned int)(t2x + c2p);
  if ( c2q < t2x )
    ++c3r;
  t1z = (unsigned __int16)a[1];
  t2dk = WORD1(a[1]);
  bl_0z = (unsigned __int16)b[5];
  bh_0z = WORD1(b[5]);
  ht_25 = t2dk * bh_0z;
  m_25 = t2dk * bl_0z + t1z * bh_0z;
  if ( m_25 < t2dk * bl_0z )
    ht_25 += 0x10000LL;
  ht_25a = ht_25 + HIWORD(m_25);
  m1_25 = m_25 << 16;
  lt_25 = (unsigned int)(m1_25 + t1z * bl_0z);
  if ( lt_25 < m1_25 )
    ++ht_25a;
  t2y = ht_25a;
  c1t = (unsigned int)(lt_25 + c1s);
  if ( c1t < lt_25 )
    t2y = ht_25a + 1;
  c2r = (unsigned int)(t2y + c2q);
  if ( c2r < t2y )
    ++c3r;
  t1ba = (unsigned __int16)*a;
  t2dl = WORD1(*a);
  bl_0ba = (unsigned __int16)b[6];
  bh_0ba = WORD1(b[6]);
  ht_26 = t2dl * bh_0ba;
  m_26 = t2dl * bl_0ba + t1ba * bh_0ba;
  if ( m_26 < t2dl * bl_0ba )
    ht_26 += 0x10000LL;
  ht_26a = ht_26 + HIWORD(m_26);
  m1_26 = m_26 << 16;
  lt_26 = (unsigned int)(m1_26 + t1ba * bl_0ba);
  if ( lt_26 < m1_26 )
    ++ht_26a;
  t2z = ht_26a;
  c1u = (unsigned int)(lt_26 + c1t);
  if ( c1u < lt_26 )
    t2z = ht_26a + 1;
  c2s = (unsigned int)(t2z + c2r);
  if ( c2s < t2z )
    ++c3r;
  r[6] = c1u;
  c1v = 0;
  t1bb = (unsigned __int16)*a;
  t2dm = WORD1(*a);
  bl_0bb = (unsigned __int16)b[7];
  bh_0bb = WORD1(b[7]);
  ht_27 = t2dm * bh_0bb;
  m_27 = t2dm * bl_0bb + t1bb * bh_0bb;
  if ( m_27 < t2dm * bl_0bb )
    ht_27 += 0x10000LL;
  ht_27a = ht_27 + HIWORD(m_27);
  m1_27 = m_27 << 16;
  lt_27 = (unsigned int)(m1_27 + t1bb * bl_0bb);
  if ( lt_27 < m1_27 )
    ++ht_27a;
  t2ba = ht_27a;
  c2t = (unsigned int)(lt_27 + c2s);
  if ( c2t < lt_27 )
    t2ba = ht_27a + 1;
  c3s = (unsigned int)(t2ba + c3r);
  if ( c3s < t2ba )
    c1v = 1;
  t1bc = (unsigned __int16)a[1];
  t2dn = WORD1(a[1]);
  bl_0bc = (unsigned __int16)b[6];
  bh_0bc = WORD1(b[6]);
  ht_28 = t2dn * bh_0bc;
  m_28 = t2dn * bl_0bc + t1bc * bh_0bc;
  if ( m_28 < t2dn * bl_0bc )
    ht_28 += 0x10000LL;
  ht_28a = ht_28 + HIWORD(m_28);
  m1_28 = m_28 << 16;
  lt_28 = (unsigned int)(m1_28 + t1bc * bl_0bc);
  if ( lt_28 < m1_28 )
    ++ht_28a;
  t2bb = ht_28a;
  c2u = (unsigned int)(lt_28 + c2t);
  if ( c2u < lt_28 )
    t2bb = ht_28a + 1;
  c3t = (unsigned int)(t2bb + c3s);
  if ( c3t < t2bb )
    ++c1v;
  t1bd = (unsigned __int16)a[2];
  t2do = WORD1(a[2]);
  bl_0bd = (unsigned __int16)b[5];
  bh_0bd = WORD1(b[5]);
  ht_29 = t2do * bh_0bd;
  m_29 = t2do * bl_0bd + t1bd * bh_0bd;
  if ( m_29 < t2do * bl_0bd )
    ht_29 += 0x10000LL;
  ht_29a = ht_29 + HIWORD(m_29);
  m1_29 = m_29 << 16;
  lt_29 = (unsigned int)(m1_29 + t1bd * bl_0bd);
  if ( lt_29 < m1_29 )
    ++ht_29a;
  t2bc = ht_29a;
  c2v = (unsigned int)(lt_29 + c2u);
  if ( c2v < lt_29 )
    t2bc = ht_29a + 1;
  c3u = (unsigned int)(t2bc + c3t);
  if ( c3u < t2bc )
    ++c1v;
  t1be = (unsigned __int16)a[3];
  t2dp = WORD1(a[3]);
  bl_0be = (unsigned __int16)b[4];
  bh_0be = WORD1(b[4]);
  ht_30 = t2dp * bh_0be;
  m_30 = t2dp * bl_0be + t1be * bh_0be;
  if ( m_30 < t2dp * bl_0be )
    ht_30 += 0x10000LL;
  ht_30a = ht_30 + HIWORD(m_30);
  m1_30 = m_30 << 16;
  lt_30 = (unsigned int)(m1_30 + t1be * bl_0be);
  if ( lt_30 < m1_30 )
    ++ht_30a;
  t2bd = ht_30a;
  c2w = (unsigned int)(lt_30 + c2v);
  if ( c2w < lt_30 )
    t2bd = ht_30a + 1;
  c3v = (unsigned int)(t2bd + c3u);
  if ( c3v < t2bd )
    ++c1v;
  t1bf = (unsigned __int16)a[4];
  t2dq = WORD1(a[4]);
  bl_0bf = (unsigned __int16)b[3];
  bh_0bf = WORD1(b[3]);
  ht_31 = t2dq * bh_0bf;
  m_31 = t2dq * bl_0bf + t1bf * bh_0bf;
  if ( m_31 < t2dq * bl_0bf )
    ht_31 += 0x10000LL;
  ht_31a = ht_31 + HIWORD(m_31);
  m1_31 = m_31 << 16;
  lt_31 = (unsigned int)(m1_31 + t1bf * bl_0bf);
  if ( lt_31 < m1_31 )
    ++ht_31a;
  t2be = ht_31a;
  c2x = (unsigned int)(lt_31 + c2w);
  if ( c2x < lt_31 )
    t2be = ht_31a + 1;
  c3w = (unsigned int)(t2be + c3v);
  if ( c3w < t2be )
    ++c1v;
  t1bg = (unsigned __int16)a[5];
  t2dr = WORD1(a[5]);
  bl_0bg = (unsigned __int16)b[2];
  bh_0bg = WORD1(b[2]);
  ht_32 = t2dr * bh_0bg;
  m_32 = t2dr * bl_0bg + t1bg * bh_0bg;
  if ( m_32 < t2dr * bl_0bg )
    ht_32 += 0x10000LL;
  ht_32a = ht_32 + HIWORD(m_32);
  m1_32 = m_32 << 16;
  lt_32 = (unsigned int)(m1_32 + t1bg * bl_0bg);
  if ( lt_32 < m1_32 )
    ++ht_32a;
  t2bf = ht_32a;
  c2y = (unsigned int)(lt_32 + c2x);
  if ( c2y < lt_32 )
    t2bf = ht_32a + 1;
  c3x = (unsigned int)(t2bf + c3w);
  if ( c3x < t2bf )
    ++c1v;
  t1bh = (unsigned __int16)a[6];
  t2ds = WORD1(a[6]);
  bl_0bh = (unsigned __int16)b[1];
  bh_0bh = WORD1(b[1]);
  ht_33 = t2ds * bh_0bh;
  m_33 = t2ds * bl_0bh + t1bh * bh_0bh;
  if ( m_33 < t2ds * bl_0bh )
    ht_33 += 0x10000LL;
  ht_33a = ht_33 + HIWORD(m_33);
  m1_33 = m_33 << 16;
  lt_33 = (unsigned int)(m1_33 + t1bh * bl_0bh);
  if ( lt_33 < m1_33 )
    ++ht_33a;
  t2bg = ht_33a;
  c2z = (unsigned int)(lt_33 + c2y);
  if ( c2z < lt_33 )
    t2bg = ht_33a + 1;
  c3y = (unsigned int)(t2bg + c3x);
  if ( c3y < t2bg )
    ++c1v;
  t1bi = (unsigned __int16)a[7];
  t2dt = WORD1(a[7]);
  bl_0bi = (unsigned __int16)*b;
  bh_0bi = WORD1(*b);
  ht_34 = t2dt * bh_0bi;
  m_34 = t2dt * bl_0bi + t1bi * bh_0bi;
  if ( m_34 < t2dt * bl_0bi )
    ht_34 += 0x10000LL;
  ht_34a = ht_34 + HIWORD(m_34);
  m1_34 = m_34 << 16;
  lt_34 = (unsigned int)(m1_34 + t1bi * bl_0bi);
  if ( lt_34 < m1_34 )
    ++ht_34a;
  t2bh = ht_34a;
  c2ba = (unsigned int)(lt_34 + c2z);
  if ( c2ba < lt_34 )
    t2bh = ht_34a + 1;
  c3z = (unsigned int)(t2bh + c3y);
  if ( c3z < t2bh )
    ++c1v;
  r[7] = c2ba;
  c2bb = 0;
  t1bj = (unsigned __int16)a[7];
  t2du = WORD1(a[7]);
  bl_0bj = (unsigned __int16)b[1];
  bh_0bj = WORD1(b[1]);
  ht_35 = t2du * bh_0bj;
  m_35 = t2du * bl_0bj + t1bj * bh_0bj;
  if ( m_35 < t2du * bl_0bj )
    ht_35 += 0x10000LL;
  ht_35a = ht_35 + HIWORD(m_35);
  m1_35 = m_35 << 16;
  lt_35 = (unsigned int)(m1_35 + t1bj * bl_0bj);
  if ( lt_35 < m1_35 )
    ++ht_35a;
  t2bi = ht_35a;
  c3ba = (unsigned int)(lt_35 + c3z);
  if ( c3ba < lt_35 )
    t2bi = ht_35a + 1;
  c1w = (unsigned int)(t2bi + c1v);
  if ( c1w < t2bi )
    c2bb = 1;
  t1bk = (unsigned __int16)a[6];
  t2dv = WORD1(a[6]);
  bl_0bk = (unsigned __int16)b[2];
  bh_0bk = WORD1(b[2]);
  ht_36 = t2dv * bh_0bk;
  m_36 = t2dv * bl_0bk + t1bk * bh_0bk;
  if ( m_36 < t2dv * bl_0bk )
    ht_36 += 0x10000LL;
  ht_36a = ht_36 + HIWORD(m_36);
  m1_36 = m_36 << 16;
  lt_36 = (unsigned int)(m1_36 + t1bk * bl_0bk);
  if ( lt_36 < m1_36 )
    ++ht_36a;
  t2bj = ht_36a;
  c3bb = (unsigned int)(lt_36 + c3ba);
  if ( c3bb < lt_36 )
    t2bj = ht_36a + 1;
  c1x = (unsigned int)(t2bj + c1w);
  if ( c1x < t2bj )
    ++c2bb;
  t1bl = (unsigned __int16)a[5];
  t2dw = WORD1(a[5]);
  bl_0bl = (unsigned __int16)b[3];
  bh_0bl = WORD1(b[3]);
  ht_37 = t2dw * bh_0bl;
  m_37 = t2dw * bl_0bl + t1bl * bh_0bl;
  if ( m_37 < t2dw * bl_0bl )
    ht_37 += 0x10000LL;
  ht_37a = ht_37 + HIWORD(m_37);
  m1_37 = m_37 << 16;
  lt_37 = (unsigned int)(m1_37 + t1bl * bl_0bl);
  if ( lt_37 < m1_37 )
    ++ht_37a;
  t2bk = ht_37a;
  c3bc = (unsigned int)(lt_37 + c3bb);
  if ( c3bc < lt_37 )
    t2bk = ht_37a + 1;
  c1y = (unsigned int)(t2bk + c1x);
  if ( c1y < t2bk )
    ++c2bb;
  t1bm = (unsigned __int16)a[4];
  t2dx = WORD1(a[4]);
  bl_0bm = (unsigned __int16)b[4];
  bh_0bm = WORD1(b[4]);
  ht_38 = t2dx * bh_0bm;
  m_38 = t2dx * bl_0bm + t1bm * bh_0bm;
  if ( m_38 < t2dx * bl_0bm )
    ht_38 += 0x10000LL;
  ht_38a = ht_38 + HIWORD(m_38);
  m1_38 = m_38 << 16;
  lt_38 = (unsigned int)(m1_38 + t1bm * bl_0bm);
  if ( lt_38 < m1_38 )
    ++ht_38a;
  t2bl = ht_38a;
  c3bd = (unsigned int)(lt_38 + c3bc);
  if ( c3bd < lt_38 )
    t2bl = ht_38a + 1;
  c1z = (unsigned int)(t2bl + c1y);
  if ( c1z < t2bl )
    ++c2bb;
  t1bn = (unsigned __int16)a[3];
  t2dy = WORD1(a[3]);
  bl_0bn = (unsigned __int16)b[5];
  bh_0bn = WORD1(b[5]);
  ht_39 = t2dy * bh_0bn;
  m_39 = t2dy * bl_0bn + t1bn * bh_0bn;
  if ( m_39 < t2dy * bl_0bn )
    ht_39 += 0x10000LL;
  ht_39a = ht_39 + HIWORD(m_39);
  m1_39 = m_39 << 16;
  lt_39 = (unsigned int)(m1_39 + t1bn * bl_0bn);
  if ( lt_39 < m1_39 )
    ++ht_39a;
  t2bm = ht_39a;
  c3be = (unsigned int)(lt_39 + c3bd);
  if ( c3be < lt_39 )
    t2bm = ht_39a + 1;
  c1ba = (unsigned int)(t2bm + c1z);
  if ( c1ba < t2bm )
    ++c2bb;
  t1bo = (unsigned __int16)a[2];
  t2dz = WORD1(a[2]);
  bl_0bo = (unsigned __int16)b[6];
  bh_0bo = WORD1(b[6]);
  ht_40 = t2dz * bh_0bo;
  m_40 = t2dz * bl_0bo + t1bo * bh_0bo;
  if ( m_40 < t2dz * bl_0bo )
    ht_40 += 0x10000LL;
  ht_40a = ht_40 + HIWORD(m_40);
  m1_40 = m_40 << 16;
  lt_40 = (unsigned int)(m1_40 + t1bo * bl_0bo);
  if ( lt_40 < m1_40 )
    ++ht_40a;
  t2bn = ht_40a;
  c3bf = (unsigned int)(lt_40 + c3be);
  if ( c3bf < lt_40 )
    t2bn = ht_40a + 1;
  c1bb = (unsigned int)(t2bn + c1ba);
  if ( c1bb < t2bn )
    ++c2bb;
  t1bp = (unsigned __int16)a[1];
  t2ea = WORD1(a[1]);
  bl_0bp = (unsigned __int16)b[7];
  bh_0bp = WORD1(b[7]);
  ht_41 = t2ea * bh_0bp;
  m_41 = t2ea * bl_0bp + t1bp * bh_0bp;
  if ( m_41 < t2ea * bl_0bp )
    ht_41 += 0x10000LL;
  ht_41a = ht_41 + HIWORD(m_41);
  m1_41 = m_41 << 16;
  lt_41 = (unsigned int)(m1_41 + t1bp * bl_0bp);
  if ( lt_41 < m1_41 )
    ++ht_41a;
  t2bo = ht_41a;
  c3bg = (unsigned int)(lt_41 + c3bf);
  if ( c3bg < lt_41 )
    t2bo = ht_41a + 1;
  c1bc = (unsigned int)(t2bo + c1bb);
  if ( c1bc < t2bo )
    ++c2bb;
  r[8] = c3bg;
  c3bh = 0;
  t1bq = (unsigned __int16)a[2];
  t2eb = WORD1(a[2]);
  bl_0bq = (unsigned __int16)b[7];
  bh_0bq = WORD1(b[7]);
  ht_42 = t2eb * bh_0bq;
  m_42 = t2eb * bl_0bq + t1bq * bh_0bq;
  if ( m_42 < t2eb * bl_0bq )
    ht_42 += 0x10000LL;
  ht_42a = ht_42 + HIWORD(m_42);
  m1_42 = m_42 << 16;
  lt_42 = (unsigned int)(m1_42 + t1bq * bl_0bq);
  if ( lt_42 < m1_42 )
    ++ht_42a;
  t2bp = ht_42a;
  c1bd = (unsigned int)(lt_42 + c1bc);
  if ( c1bd < lt_42 )
    t2bp = ht_42a + 1;
  c2bc = (unsigned int)(t2bp + c2bb);
  if ( c2bc < t2bp )
    c3bh = 1;
  t1br = (unsigned __int16)a[3];
  t2ec = WORD1(a[3]);
  bl_0br = (unsigned __int16)b[6];
  bh_0br = WORD1(b[6]);
  ht_43 = t2ec * bh_0br;
  m_43 = t2ec * bl_0br + t1br * bh_0br;
  if ( m_43 < t2ec * bl_0br )
    ht_43 += 0x10000LL;
  ht_43a = ht_43 + HIWORD(m_43);
  m1_43 = m_43 << 16;
  lt_43 = (unsigned int)(m1_43 + t1br * bl_0br);
  if ( lt_43 < m1_43 )
    ++ht_43a;
  t2bq = ht_43a;
  c1be = (unsigned int)(lt_43 + c1bd);
  if ( c1be < lt_43 )
    t2bq = ht_43a + 1;
  c2bd = (unsigned int)(t2bq + c2bc);
  if ( c2bd < t2bq )
    ++c3bh;
  t1bs = (unsigned __int16)a[4];
  t2ed = WORD1(a[4]);
  bl_0bs = (unsigned __int16)b[5];
  bh_0bs = WORD1(b[5]);
  ht_44 = t2ed * bh_0bs;
  m_44 = t2ed * bl_0bs + t1bs * bh_0bs;
  if ( m_44 < t2ed * bl_0bs )
    ht_44 += 0x10000LL;
  ht_44a = ht_44 + HIWORD(m_44);
  m1_44 = m_44 << 16;
  lt_44 = (unsigned int)(m1_44 + t1bs * bl_0bs);
  if ( lt_44 < m1_44 )
    ++ht_44a;
  t2br = ht_44a;
  c1bf = (unsigned int)(lt_44 + c1be);
  if ( c1bf < lt_44 )
    t2br = ht_44a + 1;
  c2be = (unsigned int)(t2br + c2bd);
  if ( c2be < t2br )
    ++c3bh;
  t1bt = (unsigned __int16)a[5];
  t2ee = WORD1(a[5]);
  bl_0bt = (unsigned __int16)b[4];
  bh_0bt = WORD1(b[4]);
  ht_45 = t2ee * bh_0bt;
  m_45 = t2ee * bl_0bt + t1bt * bh_0bt;
  if ( m_45 < t2ee * bl_0bt )
    ht_45 += 0x10000LL;
  ht_45a = ht_45 + HIWORD(m_45);
  m1_45 = m_45 << 16;
  lt_45 = (unsigned int)(m1_45 + t1bt * bl_0bt);
  if ( lt_45 < m1_45 )
    ++ht_45a;
  t2bs = ht_45a;
  c1bg = (unsigned int)(lt_45 + c1bf);
  if ( c1bg < lt_45 )
    t2bs = ht_45a + 1;
  c2bf = (unsigned int)(t2bs + c2be);
  if ( c2bf < t2bs )
    ++c3bh;
  t1bu = (unsigned __int16)a[6];
  t2ef = WORD1(a[6]);
  bl_0bu = (unsigned __int16)b[3];
  bh_0bu = WORD1(b[3]);
  ht_46 = t2ef * bh_0bu;
  m_46 = t2ef * bl_0bu + t1bu * bh_0bu;
  if ( m_46 < t2ef * bl_0bu )
    ht_46 += 0x10000LL;
  ht_46a = ht_46 + HIWORD(m_46);
  m1_46 = m_46 << 16;
  lt_46 = (unsigned int)(m1_46 + t1bu * bl_0bu);
  if ( lt_46 < m1_46 )
    ++ht_46a;
  t2bt = ht_46a;
  c1bh = (unsigned int)(lt_46 + c1bg);
  if ( c1bh < lt_46 )
    t2bt = ht_46a + 1;
  c2bg = (unsigned int)(t2bt + c2bf);
  if ( c2bg < t2bt )
    ++c3bh;
  t1bv = (unsigned __int16)a[7];
  t2eg = WORD1(a[7]);
  bl_0bv = (unsigned __int16)b[2];
  bh_0bv = WORD1(b[2]);
  ht_47 = t2eg * bh_0bv;
  m_47 = t2eg * bl_0bv + t1bv * bh_0bv;
  if ( m_47 < t2eg * bl_0bv )
    ht_47 += 0x10000LL;
  ht_47a = ht_47 + HIWORD(m_47);
  m1_47 = m_47 << 16;
  lt_47 = (unsigned int)(m1_47 + t1bv * bl_0bv);
  if ( lt_47 < m1_47 )
    ++ht_47a;
  t2bu = ht_47a;
  c1bi = (unsigned int)(lt_47 + c1bh);
  if ( c1bi < lt_47 )
    t2bu = ht_47a + 1;
  c2bh = (unsigned int)(t2bu + c2bg);
  if ( c2bh < t2bu )
    ++c3bh;
  r[9] = c1bi;
  c1bj = 0;
  t1bw = (unsigned __int16)a[7];
  t2eh = WORD1(a[7]);
  bl_0bw = (unsigned __int16)b[3];
  bh_0bw = WORD1(b[3]);
  ht_48 = t2eh * bh_0bw;
  m_48 = t2eh * bl_0bw + t1bw * bh_0bw;
  if ( m_48 < t2eh * bl_0bw )
    ht_48 += 0x10000LL;
  ht_48a = ht_48 + HIWORD(m_48);
  m1_48 = m_48 << 16;
  lt_48 = (unsigned int)(m1_48 + t1bw * bl_0bw);
  if ( lt_48 < m1_48 )
    ++ht_48a;
  t2bv = ht_48a;
  c2bi = (unsigned int)(lt_48 + c2bh);
  if ( c2bi < lt_48 )
    t2bv = ht_48a + 1;
  c3bi = (unsigned int)(t2bv + c3bh);
  if ( c3bi < t2bv )
    c1bj = 1;
  t1bx = (unsigned __int16)a[6];
  t2ei = WORD1(a[6]);
  bl_0bx = (unsigned __int16)b[4];
  bh_0bx = WORD1(b[4]);
  ht_49 = t2ei * bh_0bx;
  m_49 = t2ei * bl_0bx + t1bx * bh_0bx;
  if ( m_49 < t2ei * bl_0bx )
    ht_49 += 0x10000LL;
  ht_49a = ht_49 + HIWORD(m_49);
  m1_49 = m_49 << 16;
  lt_49 = (unsigned int)(m1_49 + t1bx * bl_0bx);
  if ( lt_49 < m1_49 )
    ++ht_49a;
  t2bw = ht_49a;
  c2bj = (unsigned int)(lt_49 + c2bi);
  if ( c2bj < lt_49 )
    t2bw = ht_49a + 1;
  c3bj = (unsigned int)(t2bw + c3bi);
  if ( c3bj < t2bw )
    ++c1bj;
  t1by = (unsigned __int16)a[5];
  t2ej = WORD1(a[5]);
  bl_0by = (unsigned __int16)b[5];
  bh_0by = WORD1(b[5]);
  ht_50 = t2ej * bh_0by;
  m_50 = t2ej * bl_0by + t1by * bh_0by;
  if ( m_50 < t2ej * bl_0by )
    ht_50 += 0x10000LL;
  ht_50a = ht_50 + HIWORD(m_50);
  m1_50 = m_50 << 16;
  lt_50 = (unsigned int)(m1_50 + t1by * bl_0by);
  if ( lt_50 < m1_50 )
    ++ht_50a;
  t2bx = ht_50a;
  c2bk = (unsigned int)(lt_50 + c2bj);
  if ( c2bk < lt_50 )
    t2bx = ht_50a + 1;
  c3bk = (unsigned int)(t2bx + c3bj);
  if ( c3bk < t2bx )
    ++c1bj;
  t1bz = (unsigned __int16)a[4];
  t2ek = WORD1(a[4]);
  bl_0bz = (unsigned __int16)b[6];
  bh_0bz = WORD1(b[6]);
  ht_51 = t2ek * bh_0bz;
  m_51 = t2ek * bl_0bz + t1bz * bh_0bz;
  if ( m_51 < t2ek * bl_0bz )
    ht_51 += 0x10000LL;
  ht_51a = ht_51 + HIWORD(m_51);
  m1_51 = m_51 << 16;
  lt_51 = (unsigned int)(m1_51 + t1bz * bl_0bz);
  if ( lt_51 < m1_51 )
    ++ht_51a;
  t2by = ht_51a;
  c2bl = (unsigned int)(lt_51 + c2bk);
  if ( c2bl < lt_51 )
    t2by = ht_51a + 1;
  c3bl = (unsigned int)(t2by + c3bk);
  if ( c3bl < t2by )
    ++c1bj;
  t1ca = (unsigned __int16)a[3];
  t2el = WORD1(a[3]);
  bl_0ca = (unsigned __int16)b[7];
  bh_0ca = WORD1(b[7]);
  ht_52 = t2el * bh_0ca;
  m_52 = t2el * bl_0ca + t1ca * bh_0ca;
  if ( m_52 < t2el * bl_0ca )
    ht_52 += 0x10000LL;
  ht_52a = ht_52 + HIWORD(m_52);
  m1_52 = m_52 << 16;
  lt_52 = (unsigned int)(m1_52 + t1ca * bl_0ca);
  if ( lt_52 < m1_52 )
    ++ht_52a;
  t2bz = ht_52a;
  c2bm = (unsigned int)(lt_52 + c2bl);
  if ( c2bm < lt_52 )
    t2bz = ht_52a + 1;
  c3bm = (unsigned int)(t2bz + c3bl);
  if ( c3bm < t2bz )
    ++c1bj;
  r[10] = c2bm;
  c2bn = 0;
  t1cb = (unsigned __int16)a[4];
  t2em = WORD1(a[4]);
  bl_0cb = (unsigned __int16)b[7];
  bh_0cb = WORD1(b[7]);
  ht_53 = t2em * bh_0cb;
  m_53 = t2em * bl_0cb + t1cb * bh_0cb;
  if ( m_53 < t2em * bl_0cb )
    ht_53 += 0x10000LL;
  ht_53a = ht_53 + HIWORD(m_53);
  m1_53 = m_53 << 16;
  lt_53 = (unsigned int)(m1_53 + t1cb * bl_0cb);
  if ( lt_53 < m1_53 )
    ++ht_53a;
  t2ca = ht_53a;
  c3bn = (unsigned int)(lt_53 + c3bm);
  if ( c3bn < lt_53 )
    t2ca = ht_53a + 1;
  c1bk = (unsigned int)(t2ca + c1bj);
  if ( c1bk < t2ca )
    c2bn = 1;
  t1cc = (unsigned __int16)a[5];
  t2en = WORD1(a[5]);
  bl_0cc = (unsigned __int16)b[6];
  bh_0cc = WORD1(b[6]);
  ht_54 = t2en * bh_0cc;
  m_54 = t2en * bl_0cc + t1cc * bh_0cc;
  if ( m_54 < t2en * bl_0cc )
    ht_54 += 0x10000LL;
  ht_54a = ht_54 + HIWORD(m_54);
  m1_54 = m_54 << 16;
  lt_54 = (unsigned int)(m1_54 + t1cc * bl_0cc);
  if ( lt_54 < m1_54 )
    ++ht_54a;
  t2cb = ht_54a;
  c3bo = (unsigned int)(lt_54 + c3bn);
  if ( c3bo < lt_54 )
    t2cb = ht_54a + 1;
  c1bl = (unsigned int)(t2cb + c1bk);
  if ( c1bl < t2cb )
    ++c2bn;
  t1cd = (unsigned __int16)a[6];
  t2eo = WORD1(a[6]);
  bl_0cd = (unsigned __int16)b[5];
  bh_0cd = WORD1(b[5]);
  ht_55 = t2eo * bh_0cd;
  m_55 = t2eo * bl_0cd + t1cd * bh_0cd;
  if ( m_55 < t2eo * bl_0cd )
    ht_55 += 0x10000LL;
  ht_55a = ht_55 + HIWORD(m_55);
  m1_55 = m_55 << 16;
  lt_55 = (unsigned int)(m1_55 + t1cd * bl_0cd);
  if ( lt_55 < m1_55 )
    ++ht_55a;
  t2cc = ht_55a;
  c3bp = (unsigned int)(lt_55 + c3bo);
  if ( c3bp < lt_55 )
    t2cc = ht_55a + 1;
  c1bm = (unsigned int)(t2cc + c1bl);
  if ( c1bm < t2cc )
    ++c2bn;
  t1ce = (unsigned __int16)a[7];
  t2ep = WORD1(a[7]);
  bl_0ce = (unsigned __int16)b[4];
  bh_0ce = WORD1(b[4]);
  ht_56 = t2ep * bh_0ce;
  m_56 = t2ep * bl_0ce + t1ce * bh_0ce;
  if ( m_56 < t2ep * bl_0ce )
    ht_56 += 0x10000LL;
  ht_56a = ht_56 + HIWORD(m_56);
  m1_56 = m_56 << 16;
  lt_56 = (unsigned int)(m1_56 + t1ce * bl_0ce);
  if ( lt_56 < m1_56 )
    ++ht_56a;
  t2cd = ht_56a;
  c3bq = (unsigned int)(lt_56 + c3bp);
  if ( c3bq < lt_56 )
    t2cd = ht_56a + 1;
  c1bn = (unsigned int)(t2cd + c1bm);
  if ( c1bn < t2cd )
    ++c2bn;
  r[11] = c3bq;
  c3br = 0;
  t1cf = (unsigned __int16)a[7];
  t2eq = WORD1(a[7]);
  bl_0cf = (unsigned __int16)b[5];
  bh_0cf = WORD1(b[5]);
  ht_57 = t2eq * bh_0cf;
  m_57 = t2eq * bl_0cf + t1cf * bh_0cf;
  if ( m_57 < t2eq * bl_0cf )
    ht_57 += 0x10000LL;
  ht_57a = ht_57 + HIWORD(m_57);
  m1_57 = m_57 << 16;
  lt_57 = (unsigned int)(m1_57 + t1cf * bl_0cf);
  if ( lt_57 < m1_57 )
    ++ht_57a;
  t2ce = ht_57a;
  c1bo = (unsigned int)(lt_57 + c1bn);
  if ( c1bo < lt_57 )
    t2ce = ht_57a + 1;
  c2bo = (unsigned int)(t2ce + c2bn);
  if ( c2bo < t2ce )
    c3br = 1;
  t1cg = (unsigned __int16)a[6];
  t2er = WORD1(a[6]);
  bl_0cg = (unsigned __int16)b[6];
  bh_0cg = WORD1(b[6]);
  ht_58 = t2er * bh_0cg;
  m_58 = t2er * bl_0cg + t1cg * bh_0cg;
  if ( m_58 < t2er * bl_0cg )
    ht_58 += 0x10000LL;
  ht_58a = ht_58 + HIWORD(m_58);
  m1_58 = m_58 << 16;
  lt_58 = (unsigned int)(m1_58 + t1cg * bl_0cg);
  if ( lt_58 < m1_58 )
    ++ht_58a;
  t2cf = ht_58a;
  c1bp = (unsigned int)(lt_58 + c1bo);
  if ( c1bp < lt_58 )
    t2cf = ht_58a + 1;
  c2bp = (unsigned int)(t2cf + c2bo);
  if ( c2bp < t2cf )
    ++c3br;
  t1ch = (unsigned __int16)a[5];
  t2es = WORD1(a[5]);
  bl_0ch = (unsigned __int16)b[7];
  bh_0ch = WORD1(b[7]);
  ht_59 = t2es * bh_0ch;
  m_59 = t2es * bl_0ch + t1ch * bh_0ch;
  if ( m_59 < t2es * bl_0ch )
    ht_59 += 0x10000LL;
  ht_59a = ht_59 + HIWORD(m_59);
  m1_59 = m_59 << 16;
  lt_59 = (unsigned int)(m1_59 + t1ch * bl_0ch);
  if ( lt_59 < m1_59 )
    ++ht_59a;
  t2cg = ht_59a;
  c1bq = (unsigned int)(lt_59 + c1bp);
  if ( c1bq < lt_59 )
    t2cg = ht_59a + 1;
  c2bq = (unsigned int)(t2cg + c2bp);
  if ( c2bq < t2cg )
    ++c3br;
  r[12] = c1bq;
  c1br = 0;
  t1ci = (unsigned __int16)a[6];
  t2et = WORD1(a[6]);
  bl_0ci = (unsigned __int16)b[7];
  bh_0ci = WORD1(b[7]);
  ht_60 = t2et * bh_0ci;
  m_60 = t2et * bl_0ci + t1ci * bh_0ci;
  if ( m_60 < t2et * bl_0ci )
    ht_60 += 0x10000LL;
  ht_60a = ht_60 + HIWORD(m_60);
  m1_60 = m_60 << 16;
  lt_60 = (unsigned int)(m1_60 + t1ci * bl_0ci);
  if ( lt_60 < m1_60 )
    ++ht_60a;
  t2ch = ht_60a;
  c2br = (unsigned int)(lt_60 + c2bq);
  if ( c2br < lt_60 )
    t2ch = ht_60a + 1;
  c3bs = (unsigned int)(t2ch + c3br);
  if ( c3bs < t2ch )
    c1br = 1;
  t1cj = (unsigned __int16)a[7];
  t2eu = WORD1(a[7]);
  bl_0cj = (unsigned __int16)b[6];
  bh_0cj = WORD1(b[6]);
  ht_61 = t2eu * bh_0cj;
  m_61 = t2eu * bl_0cj + t1cj * bh_0cj;
  if ( m_61 < t2eu * bl_0cj )
    ht_61 += 0x10000LL;
  ht_61a = ht_61 + HIWORD(m_61);
  m1_61 = m_61 << 16;
  lt_61 = (unsigned int)(m1_61 + t1cj * bl_0cj);
  if ( lt_61 < m1_61 )
    ++ht_61a;
  t2ci = ht_61a;
  c2bs = (unsigned int)(lt_61 + c2br);
  if ( c2bs < lt_61 )
    t2ci = ht_61a + 1;
  c3bt = (unsigned int)(t2ci + c3bs);
  if ( c3bt < t2ci )
    ++c1br;
  r[13] = c2bs;
  t1ck = (unsigned __int16)a[7];
  t2ev = WORD1(a[7]);
  bl_0ck = (unsigned __int16)b[7];
  bh_0ck = WORD1(b[7]);
  ht_62 = t2ev * bh_0ck;
  m_62 = t2ev * bl_0ck + t1ck * bh_0ck;
  if ( m_62 < t2ev * bl_0ck )
    ht_62 += 0x10000;
  ht_62a = ht_62 + HIWORD(m_62);
  m1_62 = m_62 << 16;
  lt_62 = (unsigned int)(m1_62 + t1ck * bl_0ck);
  if ( lt_62 < m1_62 )
    ++ht_62a;
  t2cj = ht_62a;
  c3bu = (unsigned int)(lt_62 + c3bt);
  if ( c3bu < lt_62 )
    t2cj = ht_62a + 1;
  r[14] = c3bu;
  r[15] = (unsigned int)(t2cj + c1br);
}