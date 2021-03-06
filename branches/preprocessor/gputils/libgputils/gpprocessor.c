/* GNU PIC processor definitions
   Copyright (C) 2001, 2002, 2003, 2004, 2005
   Craig Franklin

This file is part of gputils.

gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "stdhdr.h"
#include "libgputils.h"

/* XXXPRO: Need to add a line here for any extra processors.  Please
   keep this list sorted primarily by number, secondarily sorting
   alphabetically. */

static struct px pics[] = {
  { PROC_CLASS_PIC12    , "__10F200"      , { "pic10f200"      , "p10f200"        , "10f200"          }, 0xF200,  1,    1, 0x0000FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f200_g.lkr"       },
  { PROC_CLASS_PIC12    , "__10F202"      , { "pic10f202"      , "p10f202"        , "10f202"          }, 0xF202,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f202_g.lkr"       },
  { PROC_CLASS_PIC12    , "__10F204"      , { "pic10f204"      , "p10f204"        , "10f204"          }, 0xF204,  1,    1, 0x0000FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f204_g.lkr"       },
  { PROC_CLASS_PIC12    , "__10F206"      , { "pic10f206"      , "p10f206"        , "10f206"          }, 0xF206,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f206_g.lkr"       },
  { PROC_CLASS_PIC12    , "__10F220"      , { "pic10f220"      , "p10f220"        , "10f220"          }, 0xF220,  1,    1, 0x0000FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f220_g.lkr"       },
  { PROC_CLASS_PIC12    , "__10F222"      , { "pic10f222"      , "p10f222"        , "10f222"          }, 0xF222,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "10f222_g.lkr"       },
  { PROC_CLASS_PIC14    , "__10F320"      , { "pic10f320"      , "p10f320"        , "10f320"          }, 0xF320,  1,    1, 0x0000FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "10f320_g.lkr"       },
  { PROC_CLASS_PIC14    , "__10F322"      , { "pic10f322"      , "p10f322"        , "10f322"          }, 0xF322,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "10f322_g.lkr"       },
  { PROC_CLASS_PIC14    , "__10LF320"     , { "pic10lf320"     , "p10lf320"       , "10lf320"         }, 0xA320,  1,    1, 0x0000FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "10lf320_g.lkr"      },
  { PROC_CLASS_PIC14    , "__10LF322"     , { "pic10lf322"     , "p10lf322"       , "10lf322"         }, 0xA322,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "10lf322_g.lkr"      },
  { PROC_CLASS_PIC12    , "__12C508"      , { "pic12c508"      , "p12c508"        , "12c508"          }, 0x2508,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12c508_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12C508A"     , { "pic12c508a"     , "p12c508a"       , "12c508a"         }, 0x508A,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12c508a_g.lkr"      },
  { PROC_CLASS_PIC12    , "__12C509"      , { "pic12c509"      , "p12c509"        , "12c509"          }, 0x2509,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12c509_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12C509A"     , { "pic12c509a"     , "p12c509a"       , "12c509a"         }, 0x509A,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12c509a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12C671"      , { "pic12c671"      , "p12c671"        , "12c671"          }, 0x2671,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12c671_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12C672"      , { "pic12c672"      , "p12c672"        , "12c672"          }, 0x2672,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12c672_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12CE518"     , { "pic12ce518"     , "p12ce518"       , "12ce518"         }, 0x2518,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12ce518_g.lkr"      },
  { PROC_CLASS_PIC12    , "__12CE519"     , { "pic12ce519"     , "p12ce519"       , "12ce519"         }, 0x2519,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12ce519_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12CE673"     , { "pic12ce673"     , "p12ce673"       , "12ce673"         }, 0x2673,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12ce673_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12CE674"     , { "pic12ce674"     , "p12ce674"       , "12ce674"         }, 0x2674,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12ce674_g.lkr"      },
  { PROC_CLASS_PIC12    , "__12CR509A"    , { "pic12cr509a"    , "p12cr509a"      , "12cr509a"        }, 0xD09A,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12cr509a_g.lkr"     },
  { PROC_CLASS_PIC12    , "__12F508"      , { "pic12f508"      , "p12f508"        , "12f508"          }, 0xF508,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f508_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12F509"      , { "pic12f509"      , "p12f509"        , "12f509"          }, 0xF509,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f509_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12F510"      , { "pic12f510"      , "p12f510"        , "12f510"          }, 0xF510,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f510_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12F519"      , { "pic12f519"      , "p12f519"        , "12f519"          }, 0xF519,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f519_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12F520"      , { "pic12f520"      , "p12f520"        , "12f520"          }, 0xF520,  3,    8, 0x0005FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f520_g.lkr"       },
  { PROC_CLASS_PIC12    , "__12F529T39A"  , { "pic12f529t39a"  , "p12f529t39a"    , "12f529t39a"      }, 0xE529,  3,    8, 0x0005FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f529t39a_g.lkr"   },
  { PROC_CLASS_PIC12    , "__12F529T48A"  , { "pic12f529t48a"  , "p12f529t48a"    , "12f529t48a"      }, 0xD529,  3,    8, 0x0005FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "12f529t48a_g.lkr"   },
  { PROC_CLASS_PIC14    , "__12F609"      , { "pic12f609"      , "p12f609"        , "12f609"          }, 0xF609,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12f609_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F615"      , { "pic12f615"      , "p12f615"        , "12f615"          }, 0xF615,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12f615_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F617"      , { "pic12f617"      , "p12f617"        , "12f617"          }, 0xF617,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12f617_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F629"      , { "pic12f629"      , "p12f629"        , "12f629"          }, 0x2629,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "12f629_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F635"      , { "pic12f635"      , "p12f635"        , "12f635"          }, 0xF635,  1,    4, 0x00217F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "12f635_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F675"      , { "pic12f675"      , "p12f675"        , "12f675"          }, 0x2675,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "12f675_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F683"      , { "pic12f683"      , "p12f683"        , "12f683"          }, 0xF683,  1,    2, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "12f683_g.lkr"       },
  { PROC_CLASS_PIC14    , "__12F752"      , { "pic12f752"      , "p12f752"        , "12f752"          }, 0xF752,  1,    4, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12f752_g.lkr"       },
  { PROC_CLASS_PIC14E   , "__12F1501"     , { "pic12f1501"     , "p12f1501"       , "12f1501"         }, 0x1501,  1,   32, 0x0003FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "12f1501_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__12F1822"     , { "pic12f1822"     , "p12f1822"       , "12f1822"         }, 0x1822,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "12f1822_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__12F1840"     , { "pic12f1840"     , "p12f1840"       , "12f1840"         }, 0x1840,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "12f1840_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12HV609"     , { "pic12hv609"     , "p12hv609"       , "12hv609"         }, 0x6609,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12hv609_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12HV615"     , { "pic12hv615"     , "p12hv615"       , "12hv615"         }, 0x6615,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12hv615_g.lkr"      },
  { PROC_CLASS_PIC14    , "__12HV752"     , { "pic12hv752"     , "p12hv752"       , "12hv752"         }, 0x6652,  1,    4, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "12hv752_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__12LF1501"    , { "pic12lf1501"    , "p12lf1501"      , "12lf1501"        }, 0xA501,  1,   32, 0x0003FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "12lf1501_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__12LF1552"    , { "pic12lf1552"    , "p12lf1552"      , "12lf1552"        }, 0xA552,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "12lf1552_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__12LF1822"    , { "pic12lf1822"    , "p12lf1822"      , "12lf1822"        }, 0xA822,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "12lf1822_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__12LF1840"    , { "pic12lf1840"    , "p12lf1840"      , "12lf1840"        }, 0xA840,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "12lf1840_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__12LF1840T39A", { "pic12lf1840t39a", "p12lf1840t39a"  , "12lf1840t39a"    }, 0xC840,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "12lf1840t39a_g.lkr" },
  { PROC_CLASS_PIC14E   , "__12LF1840T48A", { "pic12lf1840t48a", "p12lf1840t48a"  , "12lf1840t48a"    }, 0xB840,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "12lf1840t48a_g.lkr" },
  { PROC_CLASS_PIC12    , "__16C5X"       , { "pic16c5x"       , "p16c5x"         , "16c5x"           }, 0x658A,  4,    4,       -1, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_PIC12    , "__16C52"       , { "pic16c52"       , "p16c52"         , "16c52"           }, 0x6C52,  1,    1, 0x00017F, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c52_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16C54"       , { "pic16c54"       , "p16c54"         , "16c54"           }, 0x6C54,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c54_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16C54A"      , { "pic16c54a"      , "p16c54a"        , "16c54a"          }, 0x654A,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c54a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C54B"      , { "pic16c54b"      , "p16c54b"        , "16c54b"          }, 0x654B,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c54b_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C54C"      , { "pic16c54c"      , "p16c54c"        , "16c54c"          }, 0x654C,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c54c_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C55"       , { "pic16c55"       , "p16c55"         , "16c55"           }, 0x6C55,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c55_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16C55A"      , { "pic16c55a"      , "p16c55a"        , "16c55a"          }, 0x655A,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c55a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C56"       , { "pic16c56"       , "p16c56"         , "16c56"           }, 0x6C56,  2,    1, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c56_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16C56A"      , { "pic16c56a"      , "p16c56a"        , "16c56a"          }, 0x656A,  2,    1, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c56a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C57"       , { "pic16c57"       , "p16c57"         , "16c57"           }, 0x6C57,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c57_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16C57C"      , { "pic16c57c"      , "p16c57c"        , "16c57c"          }, 0x657C,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c57c_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C58A"      , { "pic16c58a"      , "p16c58a"        , "16c58a"          }, 0x658A,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c58a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C58B"      , { "pic16c58b"      , "p16c58b"        , "16c58b"          }, 0x658B,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c58b_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C61"       , { "pic16c61"       , "p16c61"         , "16c61"           }, 0x6C61,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c61_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C62"       , { "pic16c62"       , "p16c62"         , "16c62"           }, 0x6C62,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c62_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C62A"      , { "pic16c62a"      , "p16c62a"        , "16c62a"          }, 0x662A,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c62a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C62B"      , { "pic16c62b"      , "p16c62b"        , "16c62b"          }, 0x662B,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c62b_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C63"       , { "pic16c63"       , "p16c63"         , "16c63"           }, 0x6C63,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c63_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C63A"      , { "pic16c63a"      , "p16c63a"        , "16c63a"          }, 0x663A,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c63a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C64"       , { "pic16c64"       , "p16c64"         , "16c64"           }, 0x6C64,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c64_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C64A"      , { "pic16c64a"      , "p16c64a"        , "16c64a"          }, 0x664A,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c64a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C65"       , { "pic16c65"       , "p16c65"         , "16c65"           }, 0x6C65,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c65_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C65A"      , { "pic16c65a"      , "p16c65a"        , "16c65a"          }, 0x665A,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c65a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C65B"      , { "pic16c65b"      , "p16c65b"        , "16c65b"          }, 0x665B,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c65b_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C66"       , { "pic16c66"       , "p16c66"         , "16c66"           }, 0x6C66,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c66_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C67"       , { "pic16c67"       , "p16c67"         , "16c67"           }, 0x6C67,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c67_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C71"       , { "pic16c71"       , "p16c71"         , "16c71"           }, 0x6C71,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c71_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C72"       , { "pic16c72"       , "p16c72"         , "16c72"           }, 0x6C72,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c72_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C72A"      , { "pic16c72a"      , "p16c72a"        , "16c72a"          }, 0x672A,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c72a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C73"       , { "pic16c73"       , "p16c73"         , "16c73"           }, 0x6C73,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c73_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C73A"      , { "pic16c73a"      , "p16c73a"        , "16c73a"          }, 0x673A,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c73a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C73B"      , { "pic16c73b"      , "p16c73b"        , "16c73b"          }, 0x673B,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c73b_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C74"       , { "pic16c74"       , "p16c74"         , "16c74"           }, 0x6C74,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c74_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C74A"      , { "pic16c74a"      , "p16c74a"        , "16c74a"          }, 0x674A,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c74a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C74B"      , { "pic16c74b"      , "p16c74b"        , "16c74b"          }, 0x674B,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c74b_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C76"       , { "pic16c76"       , "p16c76"         , "16c76"           }, 0x6C76,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c76_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C77"       , { "pic16c77"       , "p16c77"         , "16c77"           }, 0x6C77,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c77_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C84"       , { "pic16c84"       , "p16c84"         , "16c84"           }, 0x6C84,  1,    2, 0x00213F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16c84_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16C432"      , { "pic16c432"      , "p16c432"        , "16c432"          }, 0x6432,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c432_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C433"      , { "pic16c433"      , "p16c433"        , "16c433"          }, 0x6433,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c433_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16C505"      , { "pic16c505"      , "p16c505"        , "16c505"          }, 0x2505,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16c505_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C554"      , { "pic16c554"      , "p16c554"        , "16c554"          }, 0x6554,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c554_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C557"      , { "pic16c557"      , "p16c557"        , "16c557"          }, 0x6557,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c557_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C558"      , { "pic16c558"      , "p16c558"        , "16c558"          }, 0x6558,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c558_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C620"      , { "pic16c620"      , "p16c620"        , "16c620"          }, 0x6620,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c620_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C620A"     , { "pic16c620a"     , "p16c620a"       , "16c620a"         }, 0x620A,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c620a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16C621"      , { "pic16c621"      , "p16c621"        , "16c621"          }, 0x6621,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c621_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C621A"     , { "pic16c621a"     , "p16c621a"       , "16c621a"         }, 0x621A,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c621a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16C622"      , { "pic16c622"      , "p16c622"        , "16c622"          }, 0x6622,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c622_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C622A"     , { "pic16c622a"     , "p16c622a"       , "16c622a"         }, 0x622A,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c622a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16C642"      , { "pic16c642"      , "p16c642"        , "16c642"          }, 0x6642,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c642_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C662"      , { "pic16c662"      , "p16c662"        , "16c662"          }, 0x6662,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c662_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C710"      , { "pic16c710"      , "p16c710"        , "16c710"          }, 0x6710,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c710_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C711"      , { "pic16c711"      , "p16c711"        , "16c711"          }, 0x6711,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c711_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C712"      , { "pic16c712"      , "p16c712"        , "16c712"          }, 0x6712,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c712_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C715"      , { "pic16c715"      , "p16c715"        , "16c715"          }, 0x6715,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c715_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C716"      , { "pic16c716"      , "p16c716"        , "16c716"          }, 0x6716,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c716_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C717"      , { "pic16c717"      , "p16c717"        , "16c717"          }, 0x6717,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c717_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C745"      , { "pic16c745"      , "p16c745"        , "16c745"          }, 0x6745,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c745_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C765"      , { "pic16c765"      , "p16c765"        , "16c765"          }, 0x6765,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c765_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C770"      , { "pic16c770"      , "p16c770"        , "16c770"          }, 0x6770,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c770_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C771"      , { "pic16c771"      , "p16c771"        , "16c771"          }, 0x6771,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c771_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C773"      , { "pic16c773"      , "p16c773"        , "16c773"          }, 0x6773,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c773_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C774"      , { "pic16c774"      , "p16c774"        , "16c774"          }, 0x6774,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c774_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C781"      , { "pic16c781"      , "p16c781"        , "16c781"          }, 0x6781,  1,    4, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c781_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C782"      , { "pic16c782"      , "p16c782"        , "16c782"          }, 0x6782,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c782_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C923"      , { "pic16c923"      , "p16c923"        , "16c923"          }, 0x6923,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c923_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C924"      , { "pic16c924"      , "p16c924"        , "16c924"          }, 0x6924,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c924_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C925"      , { "pic16c925"      , "p16c925"        , "16c925"          }, 0x6925,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c925_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16C926"      , { "pic16c926"      , "p16c926"        , "16c926"          }, 0x6926,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16c926_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CE623"     , { "pic16ce623"     , "p16ce623"       , "16ce623"         }, 0x6623,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16ce623_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16CE624"     , { "pic16ce624"     , "p16ce624"       , "16ce624"         }, 0x6624,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16ce624_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16CE625"     , { "pic16ce625"     , "p16ce625"       , "16ce625"         }, 0x6625,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16ce625_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR54"      , { "pic16cr54"      , "p16cr54"        , "16cr54"          }, 0xDC54,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr54_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16CR54A"     , { "pic16cr54a"     , "p16cr54a"       , "16cr54a"         }, 0xD54A,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr54a_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR54B"     , { "pic16cr54b"     , "p16cr54b"       , "16cr54b"         }, 0xD54B,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr54b_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR54C"     , { "pic16cr54c"     , "p16cr54c"       , "16cr54c"         }, 0xD54C,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr54c_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR56A"     , { "pic16cr56a"     , "p16cr56a"       , "16cr56a"         }, 0xD56A,  2,    1, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr56a_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR57A"     , { "pic16cr57a"     , "p16cr57a"       , "16cr57a"         }, 0xD57A,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr57a_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR57B"     , { "pic16cr57b"     , "p16cr57b"       , "16cr57b"         }, 0xD57B,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr57b_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR57C"     , { "pic16cr57c"     , "p16cr57c"       , "16cr57c"         }, 0xD57C,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr57c_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR58A"     , { "pic16cr58a"     , "p16cr58a"       , "16cr58a"         }, 0xD58A,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr58a_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16CR58B"     , { "pic16cr58b"     , "p16cr58b"       , "16cr58b"         }, 0xD58B,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16cr58b_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16CR62"      , { "pic16cr62"      , "p16cr62"        , "16cr62"          }, 0xDC62,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr62_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR63"      , { "pic16cr63"      , "p16cr63"        , "16cr63"          }, 0x6D63,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr63_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR64"      , { "pic16cr64"      , "p16cr64"        , "16cr64"          }, 0xDC64,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr64_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR65"      , { "pic16cr65"      , "p16cr65"        , "16cr65"          }, 0x6D65,  2,    2, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr65_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR72"      , { "pic16cr72"      , "p16cr72"        , "16cr72"          }, 0x6D72,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr72_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR83"      , { "pic16cr83"      , "p16cr83"        , "16cr83"          }, 0xDC83,  1,    2, 0x00213F, { 0x000200, 0x0020FF }, { 0x002007, 0x002007 }, "16cr83_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR84"      , { "pic16cr84"      , "p16cr84"        , "16cr84"          }, 0xDC84,  1,    2, 0x00213F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16cr84_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16CR620A"    , { "pic16cr620a"    , "p16cr620a"      , "16cr620a"        }, 0xD20A,  1,    2, 0x0001FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16cr620a_g.lkr"     },
  { PROC_CLASS_PIC14    , "__16CXX"       , { "pic16cxx"       , "p16cxx"         , "16cxx"           }, 0x6C77,  4,    4,       -1, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_PIC12    , "__16F54"       , { "pic16f54"       , "p16f54"         , "16f54"           }, 0x6F54,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f54_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16F57"       , { "pic16f57"       , "p16f57"         , "16f57"           }, 0x6F57,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f57_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16F59"       , { "pic16f59"       , "p16f59"         , "16f59"           }, 0x6F59,  4,    8, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f59_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F72"       , { "pic16f72"       , "p16f72"         , "16f72"           }, 0x672F,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f72_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F73"       , { "pic16f73"       , "p16f73"         , "16f73"           }, 0x673F,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f73_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F74"       , { "pic16f74"       , "p16f74"         , "16f74"           }, 0x674F,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f74_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F76"       , { "pic16f76"       , "p16f76"         , "16f76"           }, 0x676F,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f76_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F77"       , { "pic16f77"       , "p16f77"         , "16f77"           }, 0x677F,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f77_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F83"       , { "pic16f83"       , "p16f83"         , "16f83"           }, 0x6C83,  1,    2, 0x00213F, { 0x000200, 0x0020FF }, { 0x002007, 0x002007 }, "16f83_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F84"       , { "pic16f84"       , "p16f84"         , "16f84"           }, 0x684A,  1,    2, 0x00213F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f84_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F84A"      , { "pic16f84a"      , "p16f84a"        , "16f84a"          }, 0x6F84,  1,    2, 0x00213F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f84a_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F87"       , { "pic16f87"       , "p16f87"         , "16f87"           }, 0x687F,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002008 }, "16f87_g.lkr"        },
  { PROC_CLASS_PIC14    , "__16F88"       , { "pic16f88"       , "p16f88"         , "16f88"           }, 0x688F,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002008 }, "16f88_g.lkr"        },
  { PROC_CLASS_PIC12    , "__16F505"      , { "pic16f505"      , "p16f505"        , "16f505"          }, 0xF505,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f505_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16F506"      , { "pic16f506"      , "p16f506"        , "16f506"          }, 0xF506,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f506_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16F526"      , { "pic16f526"      , "p16f526"        , "16f526"          }, 0xF526,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f526_g.lkr"       },
  { PROC_CLASS_PIC12    , "__16F527"      , { "pic16f527"      , "p16f527"        , "16f527"          }, 0xF527,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16f527_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F610"      , { "pic16f610"      , "p16f610"        , "16f610"          }, 0xF610,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f610_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F616"      , { "pic16f616"      , "p16f616"        , "16f616"          }, 0xF616,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f616_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F627"      , { "pic16f627"      , "p16f627"        , "16f627"          }, 0x6627,  1,    4, 0x00217F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f627_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F627A"     , { "pic16f627a"     , "p16f627a"       , "16f627a"         }, 0x627A,  1,    4, 0x00217F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f627a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F628"      , { "pic16f628"      , "p16f628"        , "16f628"          }, 0x6628,  1,    4, 0x00217F, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f628_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F628A"     , { "pic16f628a"     , "p16f628a"       , "16f628a"         }, 0x628A,  1,    4, 0x00217F, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f628a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F630"      , { "pic16f630"      , "p16f630"        , "16f630"          }, 0x6630,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "16f630_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F631"      , { "pic16f631"      , "p16f631"        , "16f631"          }, 0x6631,  1,    4, 0x00217F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f631_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F636"      , { "pic16f636"      , "p16f636"        , "16f636"          }, 0xF636,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f636_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F639"      , { "pic16f639"      , "p16f639"        , "16f639"          }, 0xF639,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f639_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F648A"     , { "pic16f648a"     , "p16f648a"       , "16f648a"         }, 0x648A,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f648a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F676"      , { "pic16f676"      , "p16f676"        , "16f676"          }, 0x6676,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "16f676_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F677"      , { "pic16f677"      , "p16f677"        , "16f677"          }, 0x6677,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f677_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F684"      , { "pic16f684"      , "p16f684"        , "16f684"          }, 0x6684,  1,    2, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f684_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F685"      , { "pic16f685"      , "p16f685"        , "16f685"          }, 0x6685,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f685_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F687"      , { "pic16f687"      , "p16f687"        , "16f687"          }, 0x6687,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f687_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F688"      , { "pic16f688"      , "p16f688"        , "16f688"          }, 0x6688,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f688_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F689"      , { "pic16f689"      , "p16f689"        , "16f689"          }, 0x6689,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f689_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F690"      , { "pic16f690"      , "p16f690"        , "16f690"          }, 0x6690,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f690_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F707"      , { "pic16f707"      , "p16f707"        , "16f707"          }, 0xF707,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f707_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F716"      , { "pic16f716"      , "p16f716"        , "16f716"          }, 0xF716,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16f716_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F720"      , { "pic16f720"      , "p16f720"        , "16f720"          }, 0xF720,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f720_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F721"      , { "pic16f721"      , "p16f721"        , "16f721"          }, 0xF721,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f721_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F722"      , { "pic16f722"      , "p16f722"        , "16f722"          }, 0xF722,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f722_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F722A"     , { "pic16f722a"     , "p16f722a"       , "16f722a"         }, 0xA722,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f722a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F723"      , { "pic16f723"      , "p16f723"        , "16f723"          }, 0xF723,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f723_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F723A"     , { "pic16f723a"     , "p16f723a"       , "16f723a"         }, 0xA723,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f723a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F724"      , { "pic16f724"      , "p16f724"        , "16f724"          }, 0xF724,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f724_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F726"      , { "pic16f726"      , "p16f726"        , "16f726"          }, 0xF726,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f726_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F727"      , { "pic16f727"      , "p16f727"        , "16f727"          }, 0xF727,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f727_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F737"      , { "pic16f737"      , "p16f737"        , "16f737"          }, 0x6737,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f737_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F747"      , { "pic16f747"      , "p16f747"        , "16f747"          }, 0x6747,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f747_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F767"      , { "pic16f767"      , "p16f767"        , "16f767"          }, 0x6767,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f767_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F777"      , { "pic16f777"      , "p16f777"        , "16f777"          }, 0x6777,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16f777_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F785"      , { "pic16f785"      , "p16f785"        , "16f785"          }, 0xF785,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f785_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F818"      , { "pic16f818"      , "p16f818"        , "16f818"          }, 0x818F,  1,    4, 0x00217F, { 0x000400, 0x0020FF }, { 0x002007, 0x002007 }, "16f818_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F819"      , { "pic16f819"      , "p16f819"        , "16f819"          }, 0x819F,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f819_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F870"      , { "pic16f870"      , "p16f870"        , "16f870"          }, 0x870F,  1,    4, 0x00213F, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f870_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F871"      , { "pic16f871"      , "p16f871"        , "16f871"          }, 0x871F,  1,    4, 0x00213F, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f871_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F872"      , { "pic16f872"      , "p16f872"        , "16f872"          }, 0x872F,  1,    4, 0x00213F, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16f872_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F873"      , { "pic16f873"      , "p16f873"        , "16f873"          }, 0x873F,  2,    4, 0x00217F, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f873_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F873A"     , { "pic16f873a"     , "p16f873a"       , "16f873a"         }, 0x873A,  2,    4, 0x00217F, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f873a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F874"      , { "pic16f874"      , "p16f874"        , "16f874"          }, 0x874F,  2,    4, 0x00217F, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f874_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F874A"     , { "pic16f874a"     , "p16f874a"       , "16f874a"         }, 0x874A,  2,    4, 0x00217F, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f874a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F876"      , { "pic16f876"      , "p16f876"        , "16f876"          }, 0x876F,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f876_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F876A"     , { "pic16f876a"     , "p16f876a"       , "16f876a"         }, 0x876A,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f876a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F877"      , { "pic16f877"      , "p16f877"        , "16f877"          }, 0x877F,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f877_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F877A"     , { "pic16f877a"     , "p16f877a"       , "16f877a"         }, 0x877A,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f877a_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16F882"      , { "pic16f882"      , "p16f882"        , "16f882"          }, 0x882F,  1,    4, 0x00217F, { 0x000800, 0x0020FF }, { 0x002007, 0x002008 }, "16f882_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F883"      , { "pic16f883"      , "p16f883"        , "16f883"          }, 0x883F,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002008 }, "16f883_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F884"      , { "pic16f884"      , "p16f884"        , "16f884"          }, 0x884F,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002008 }, "16f884_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F886"      , { "pic16f886"      , "p16f886"        , "16f886"          }, 0x886F,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002008 }, "16f886_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F887"      , { "pic16f887"      , "p16f887"        , "16f887"          }, 0x887F,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002008 }, "16f887_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F913"      , { "pic16f913"      , "p16f913"        , "16f913"          }, 0xF913,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f913_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F914"      , { "pic16f914"      , "p16f914"        , "16f914"          }, 0xF914,  2,    4, 0x0021FF, { 0x001000, 0x0020FF }, { 0x002007, 0x002007 }, "16f914_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F916"      , { "pic16f916"      , "p16f916"        , "16f916"          }, 0xF916,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f916_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F917"      , { "pic16f917"      , "p16f917"        , "16f917"          }, 0xF917,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f917_g.lkr"       },
  { PROC_CLASS_PIC14    , "__16F946"      , { "pic16f946"      , "p16f946"        , "16f946"          }, 0xF946,  4,    4, 0x0021FF, { 0x002000, 0x0020FF }, { 0x002007, 0x002007 }, "16f946_g.lkr"       },
  { PROC_CLASS_PIC14E   , "__16F1454"     , { "pic16f1454"     , "p16f1454"       , "16f1454"         }, 0x1454,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1454_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1455"     , { "pic16f1455"     , "p16f1455"       , "16f1455"         }, 0x1455,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1455_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1458"     , { "pic16f1458"     , "p16f1458"       , "16f1458"         }, 0x1458,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1458_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1459"     , { "pic16f1459"     , "p16f1459"       , "16f1459"         }, 0x1459,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1459_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1503"     , { "pic16f1503"     , "p16f1503"       , "16f1503"         }, 0x1503,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1503_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1507"     , { "pic16f1507"     , "p16f1507"       , "16f1507"         }, 0x1507,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1507_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1508"     , { "pic16f1508"     , "p16f1508"       , "16f1508"         }, 0x1508,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1508_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1509"     , { "pic16f1509"     , "p16f1509"       , "16f1509"         }, 0x1509,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1509_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1512"     , { "pic16f1512"     , "p16f1512"       , "16f1512"         }, 0x1512,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1512_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1513"     , { "pic16f1513"     , "p16f1513"       , "16f1513"         }, 0x1513,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1513_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1516"     , { "pic16f1516"     , "p16f1516"       , "16f1516"         }, 0x1516,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1516_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1517"     , { "pic16f1517"     , "p16f1517"       , "16f1517"         }, 0x1517,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1517_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1518"     , { "pic16f1518"     , "p16f1518"       , "16f1518"         }, 0x1518,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1518_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1519"     , { "pic16f1519"     , "p16f1519"       , "16f1519"         }, 0x1519,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1519_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1526"     , { "pic16f1526"     , "p16f1526"       , "16f1526"         }, 0x1526,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1526_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1527"     , { "pic16f1527"     , "p16f1527"       , "16f1527"         }, 0x1527,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1527_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1782"     , { "pic16f1782"     , "p16f1782"       , "16f1782"         }, 0x1782,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1782_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1783"     , { "pic16f1783"     , "p16f1783"       , "16f1783"         }, 0x1783,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1783_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1784"     , { "pic16f1784"     , "p16f1784"       , "16f1784"         }, 0x1784,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1784_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1786"     , { "pic16f1786"     , "p16f1786"       , "16f1786"         }, 0x1786,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1786_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1787"     , { "pic16f1787"     , "p16f1787"       , "16f1787"         }, 0x1787,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1787_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1823"     , { "pic16f1823"     , "p16f1823"       , "16f1823"         }, 0x1823,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1823_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1824"     , { "pic16f1824"     , "p16f1824"       , "16f1824"         }, 0x1824,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1824_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1825"     , { "pic16f1825"     , "p16f1825"       , "16f1825"         }, 0x1825,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1825_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1826"     , { "pic16f1826"     , "p16f1826"       , "16f1826"         }, 0x1826,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1826_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1827"     , { "pic16f1827"     , "p16f1827"       , "16f1827"         }, 0x1827,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1827_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1828"     , { "pic16f1828"     , "p16f1828"       , "16f1828"         }, 0x1828,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1828_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1829"     , { "pic16f1829"     , "p16f1829"       , "16f1829"         }, 0x1829,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1829_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1847"     , { "pic16f1847"     , "p16f1847"       , "16f1847"         }, 0x1847,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1847_g.lkr"      },
  /*{ PROC_CLASS_PIC14E   , "__16F1902"     , { "pic16f1902"     , "p16f1902"       , "16f1902"         }, 0x1902,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1902_g.lkr"      },*/
  /*{ PROC_CLASS_PIC14E   , "__16F1903"     , { "pic16f1903"     , "p16f1903"       , "16f1903"         }, 0x1903,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1903_g.lkr"      },*/
  /*{ PROC_CLASS_PIC14E   , "__16F1904"     , { "pic16f1904"     , "p16f1904"       , "16f1904"         }, 0x1904,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1904_g.lkr"      },*/
  /*{ PROC_CLASS_PIC14E   , "__16F1906"     , { "pic16f1906"     , "p16f1906"       , "16f1906"         }, 0x1906,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1906_g.lkr"      },*/
  /*{ PROC_CLASS_PIC14E   , "__16F1907"     , { "pic16f1907"     , "p16f1907"       , "16f1907"         }, 0x1907,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16f1907_g.lkr"      },*/
  { PROC_CLASS_PIC14E   , "__16F1933"     , { "pic16f1933"     , "p16f1933"       , "16f1933"         }, 0x1933,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1933_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1934"     , { "pic16f1934"     , "p16f1934"       , "16f1934"         }, 0x1934,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1934_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1936"     , { "pic16f1936"     , "p16f1936"       , "16f1936"         }, 0x1936,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1936_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1937"     , { "pic16f1937"     , "p16f1937"       , "16f1937"         }, 0x1937,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1937_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1938"     , { "pic16f1938"     , "p16f1938"       , "16f1938"         }, 0x1938,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1938_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1939"     , { "pic16f1939"     , "p16f1939"       , "16f1939"         }, 0x1939,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1939_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1946"     , { "pic16f1946"     , "p16f1946"       , "16f1946"         }, 0x1946,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1946_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16F1947"     , { "pic16f1947"     , "p16f1947"       , "16f1947"         }, 0x1947,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16f1947_g.lkr"      },
  { PROC_CLASS_PIC12    , "__16HV540"     , { "pic16hv540"     , "p16hv540"       , "16hv540"         }, 0x6540,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "16hv540_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16HV610"     , { "pic16hv610"     , "p16hv610"       , "16hv610"         }, 0x6610,  1,    2, 0x0003FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16hv610_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16HV616"     , { "pic16hv616"     , "p16hv616"       , "16hv616"         }, 0x6616,  1,    2, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002007 }, "16hv616_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16HV785"     , { "pic16hv785"     , "p16hv785"       , "16hv785"         }, 0x6785,  1,    4, 0x0021FF, { 0x000800, 0x0020FF }, { 0x002007, 0x002007 }, "16hv785_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF707"     , { "pic16lf707"     , "p16lf707"       , "16lf707"         }, 0xD707,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf707_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF720"     , { "pic16lf720"     , "p16lf720"       , "16lf720"         }, 0xD720,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf720_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF721"     , { "pic16lf721"     , "p16lf721"       , "16lf721"         }, 0xD721,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf721_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF722"     , { "pic16lf722"     , "p16lf722"       , "16lf722"         }, 0xD722,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf722_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF722A"    , { "pic16lf722a"    , "p16lf722a"      , "16lf722a"        }, 0xB722,  1,    4, 0x0007FF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf722a_g.lkr"     },
  { PROC_CLASS_PIC14    , "__16LF723"     , { "pic16lf723"     , "p16lf723"       , "16lf723"         }, 0xD723,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf723_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF723A"    , { "pic16lf723a"    , "p16lf723a"      , "16lf723a"        }, 0xB723,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf723a_g.lkr"     },
  { PROC_CLASS_PIC14    , "__16LF724"     , { "pic16lf724"     , "p16lf724"       , "16lf724"         }, 0xD724,  2,    4, 0x000FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf724_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF726"     , { "pic16lf726"     , "p16lf726"       , "16lf726"         }, 0xD726,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf726_g.lkr"      },
  { PROC_CLASS_PIC14    , "__16LF727"     , { "pic16lf727"     , "p16lf727"       , "16lf727"         }, 0xD727,  4,    4, 0x001FFF, {       -1,       -1 }, { 0x002007, 0x002008 }, "16lf727_g.lkr"      },
  { PROC_CLASS_PIC14E   , "__16LF1454"    , { "pic16lf1454"    , "p16lf1454"      , "16lf1454"        }, 0xA454,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1454_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1455"    , { "pic16lf1455"    , "p16lf1455"      , "16lf1455"        }, 0xA455,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1455_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1458"    , { "pic16lf1458"    , "p16lf1458"      , "16lf1458"        }, 0xA458,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1458_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1459"    , { "pic16lf1459"    , "p16lf1459"      , "16lf1459"        }, 0xA459,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1459_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1503"    , { "pic16lf1503"    , "p16lf1503"      , "16lf1503"        }, 0xA503,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1503_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1507"    , { "pic16lf1507"    , "p16lf1507"      , "16lf1507"        }, 0xA507,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1507_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1508"    , { "pic16lf1508"    , "p16lf1508"      , "16lf1508"        }, 0xA508,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1508_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1509"    , { "pic16lf1509"    , "p16lf1509"      , "16lf1509"        }, 0xA509,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1509_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1512"    , { "pic16lf1512"    , "p16lf1512"      , "16lf1512"        }, 0xA512,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1512_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1513"    , { "pic16lf1513"    , "p16lf1513"      , "16lf1513"        }, 0xA513,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1513_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1516"    , { "pic16lf1516"    , "p16lf1516"      , "16lf1516"        }, 0xA516,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1516_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1517"    , { "pic16lf1517"    , "p16lf1517"      , "16lf1517"        }, 0xA517,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1517_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1518"    , { "pic16lf1518"    , "p16lf1518"      , "16lf1518"        }, 0xA518,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1518_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1519"    , { "pic16lf1519"    , "p16lf1519"      , "16lf1519"        }, 0xA519,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1519_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1526"    , { "pic16lf1526"    , "p16lf1526"      , "16lf1526"        }, 0xA526,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1526_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1527"    , { "pic16lf1527"    , "p16lf1527"      , "16lf1527"        }, 0xA527,  8,   32, 0x003FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1527_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1782"    , { "pic16lf1782"    , "p16lf1782"      , "16lf1782"        }, 0xA782,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1782_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1783"    , { "pic16lf1783"    , "p16lf1783"      , "16lf1783"        }, 0xA783,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1783_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1784"    , { "pic16lf1784"    , "p16lf1784"      , "16lf1784"        }, 0xA784,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1784_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1786"    , { "pic16lf1786"    , "p16lf1786"      , "16lf1786"        }, 0xA786,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1786_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1787"    , { "pic16lf1787"    , "p16lf1787"      , "16lf1787"        }, 0xA787,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1787_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1823"    , { "pic16lf1823"    , "p16lf1823"      , "16lf1823"        }, 0xA823,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1823_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1824"    , { "pic16lf1824"    , "p16lf1824"      , "16lf1824"        }, 0xA824,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1824_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1825"    , { "pic16lf1825"    , "p16lf1825"      , "16lf1825"        }, 0xA825,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1825_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1826"    , { "pic16lf1826"    , "p16lf1826"      , "16lf1826"        }, 0xA826,  1,   32, 0x00F0FF, { 0x000800, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1826_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1827"    , { "pic16lf1827"    , "p16lf1827"      , "16lf1827"        }, 0xA827,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1827_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1828"    , { "pic16lf1828"    , "p16lf1828"      , "16lf1828"        }, 0xA828,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1828_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1829"    , { "pic16lf1829"    , "p16lf1829"      , "16lf1829"        }, 0xA829,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1829_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1847"    , { "pic16lf1847"    , "p16lf1847"      , "16lf1847"        }, 0xA847,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1847_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1902"    , { "pic16lf1902"    , "p16lf1902"      , "16lf1902"        }, 0xA902,  1,   32, 0x0007FF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1902_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1903"    , { "pic16lf1903"    , "p16lf1903"      , "16lf1903"        }, 0xA903,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1903_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1904"    , { "pic16lf1904"    , "p16lf1904"      , "16lf1904"        }, 0xA904,  2,   32, 0x000FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1904_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1906"    , { "pic16lf1906"    , "p16lf1906"      , "16lf1906"        }, 0xA906,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1906_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1907"    , { "pic16lf1907"    , "p16lf1907"      , "16lf1907"        }, 0xA907,  4,   32, 0x001FFF, {       -1,       -1 }, { 0x008007, 0x008008 }, "16lf1907_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1933"    , { "pic16lf1933"    , "p16lf1933"      , "16lf1933"        }, 0xA933,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1933_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1934"    , { "pic16lf1934"    , "p16lf1934"      , "16lf1934"        }, 0xA934,  2,   32, 0x00F0FF, { 0x001000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1934_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1936"    , { "pic16lf1936"    , "p16lf1936"      , "16lf1936"        }, 0xA936,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1936_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1937"    , { "pic16lf1937"    , "p16lf1937"      , "16lf1937"        }, 0xA937,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1937_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1938"    , { "pic16lf1938"    , "p16lf1938"      , "16lf1938"        }, 0xA938,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1938_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1939"    , { "pic16lf1939"    , "p16lf1939"      , "16lf1939"        }, 0xA939,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1939_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1946"    , { "pic16lf1946"    , "p16lf1946"      , "16lf1946"        }, 0xA946,  4,   32, 0x00F0FF, { 0x002000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1946_g.lkr"     },
  { PROC_CLASS_PIC14E   , "__16LF1947"    , { "pic16lf1947"    , "p16lf1947"      , "16lf1947"        }, 0xA947,  8,   32, 0x00F0FF, { 0x004000, 0x00EFFF }, { 0x008007, 0x008008 }, "16lf1947_g.lkr"     },
  { PROC_CLASS_PIC16    , "__17C42"       , { "pic17c42"       , "p17c42"         , "17c42"           }, 0x7C42,  0,    0, 0x0007FF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c42_g.lkr"        },
  { PROC_CLASS_PIC16    , "__17C42A"      , { "pic17c42a"      , "p17c42a"        , "17c42a"          }, 0x742A,  0,    0, 0x0007FF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c42a_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17C43"       , { "pic17c43"       , "p17c43"         , "17c43"           }, 0x7C43,  0,    0, 0x000FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c43_g.lkr"        },
  { PROC_CLASS_PIC16    , "__17C44"       , { "pic17c44"       , "p17c44"         , "17c44"           }, 0x7C44,  0,    0, 0x001FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c44_g.lkr"        },
  { PROC_CLASS_PIC16    , "__17C752"      , { "pic17c752"      , "p17c752"        , "17c752"          }, 0x7752,  0,    0, 0x001FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c752_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17C756"      , { "pic17c756"      , "p17c756"        , "17c756"          }, 0x7756,  0,    0, 0x003FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c756_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17C756A"     , { "pic17c756a"     , "p17c756a"       , "17c756a"         }, 0x756A,  0,    0, 0x003FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c756a_g.lkr"      },
  { PROC_CLASS_PIC16    , "__17C762"      , { "pic17c762"      , "p17c762"        , "17c762"          }, 0x7762,  0,    0, 0x001FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c762_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17C766"      , { "pic17c766"      , "p17c766"        , "17c766"          }, 0x7766,  0,    0, 0x003FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17c766_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17CR42"      , { "pic17cr42"      , "p17cr42"        , "17cr42"          }, 0xE42A,  0,    0, 0x0007FF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17cr42_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17CR43"      , { "pic17cr43"      , "p17cr43"        , "17cr43"          }, 0xEC43,  0,    0, 0x000FFF, {       -1,       -1 }, { 0x00FE00, 0x00FE0F }, "17cr43_g.lkr"       },
  { PROC_CLASS_PIC16    , "__17CXX"       , { "pic17cxx"       , "p17cxx"         , "17cxx"           }, 0x7756,  0,    0,       -1, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_PIC16E   , "__18C242"      , { "pic18c242"      , "p18c242"        , "18c242"          }, 0x8242,  0, 0x80, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c242_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C252"      , { "pic18c252"      , "p18c252"        , "18c252"          }, 0x8252,  0, 0x80, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c252_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C442"      , { "pic18c442"      , "p18c442"        , "18c442"          }, 0x8442,  0, 0x80, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c442_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C452"      , { "pic18c452"      , "p18c452"        , "18c452"          }, 0x8452,  0, 0x80, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c452_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C601"      , { "pic18c601"      , "p18c601"        , "18c601"          }, 0x8601,  0, 0x80, 0x03FFFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c601_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C658"      , { "pic18c658"      , "p18c658"        , "18c658"          }, 0x8658,  0, 0x60, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c658_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C801"      , { "pic18c801"      , "p18c801"        , "18c801"          }, 0x8801,  0, 0x80, 0x1FFFFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c801_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18C858"      , { "pic18c858"      , "p18c858"        , "18c858"          }, 0x8858,  0, 0x60, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x300007 }, "18c858_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18CXX"       , { "pic18cxx"       , "p18cxx"         , "18cxx"           }, 0x8452,  0, 0x80,       -1, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_PIC16E   , "__18F13K22"    , { "pic18f13k22"    , "p18f13k22"      , "18f13k22"        }, 0xB132,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f13k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F13K50"    , { "pic18f13k50"    , "p18f13k50"      , "18f13k50"        }, 0xA135,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f13k50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F14K22"    , { "pic18f14k22"    , "p18f14k22"      , "18f14k22"        }, 0xB142,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f14k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F14K22LIN" , { "pic18f14k22lin" , "p18f14k22lin"   , "18f14k22lin"     }, 0xC142,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f14k22lin_g.lkr"  },
  { PROC_CLASS_PIC16E   , "__18F14K50"    , { "pic18f14k50"    , "p18f14k50"      , "18f14k50"        }, 0xA145,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f14k50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F23K20"    , { "pic18f23k20"    , "p18f23k20"      , "18f23k20"        }, 0xD320,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f23k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F23K22"    , { "pic18f23k22"    , "p18f23k22"      , "18f23k22"        }, 0xD322,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f23k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24J10"    , { "pic18f24j10"    , "p18f24j10"      , "18f24j10"        }, 0xD410,  0, 0x80, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f24j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24J11"    , { "pic18f24j11"    , "p18f24j11"      , "18f24j11"        }, 0xD411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18f24j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24J50"    , { "pic18f24j50"    , "p18f24j50"      , "18f24j50"        }, 0xD450,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18f24j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24K20"    , { "pic18f24k20"    , "p18f24k20"      , "18f24k20"        }, 0xD420,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f24k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24K22"    , { "pic18f24k22"    , "p18f24k22"      , "18f24k22"        }, 0xD422,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f24k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F24K50"    , { "pic18f24k50"    , "p18f24k50"      , "18f24k50"        }, 0xD451,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f24k50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25J10"    , { "pic18f25j10"    , "p18f25j10"      , "18f25j10"        }, 0xD510,  0, 0x80, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f25j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25J11"    , { "pic18f25j11"    , "p18f25j11"      , "18f25j11"        }, 0xD511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18f25j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25J50"    , { "pic18f25j50"    , "p18f25j50"      , "18f25j50"        }, 0xD550,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18f25j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25K20"    , { "pic18f25k20"    , "p18f25k20"      , "18f25k20"        }, 0xD520,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f25k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25K22"    , { "pic18f25k22"    , "p18f25k22"      , "18f25k22"        }, 0xD522,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f25k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25K50"    , { "pic18f25k50"    , "p18f25k50"      , "18f25k50"        }, 0xD551,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f25k50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F25K80"    , { "pic18f25k80"    , "p18f25k80"      , "18f25k80"        }, 0xA580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f25k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26J11"    , { "pic18f26j11"    , "p18f26j11"      , "18f26j11"        }, 0xD611,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f26j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26J13"    , { "pic18f26j13"    , "p18f26j13"      , "18f26j13"        }, 0xD616,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f26j13_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26J50"    , { "pic18f26j50"    , "p18f26j50"      , "18f26j50"        }, 0xD650,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f26j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26J53"    , { "pic18f26j53"    , "p18f26j53"      , "18f26j53"        }, 0xD655,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f26j53_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26K20"    , { "pic18f26k20"    , "p18f26k20"      , "18f26k20"        }, 0xD620,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f26k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26K22"    , { "pic18f26k22"    , "p18f26k22"      , "18f26k22"        }, 0xD622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f26k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F26K80"    , { "pic18f26k80"    , "p18f26k80"      , "18f26k80"        }, 0xA680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f26k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F27J13"    , { "pic18f27j13"    , "p18f27j13"      , "18f27j13"        }, 0xD711,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f27j13_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F27J53"    , { "pic18f27j53"    , "p18f27j53"      , "18f27j53"        }, 0xD750,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f27j53_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F43K20"    , { "pic18f43k20"    , "p18f43k20"      , "18f43k20"        }, 0xE320,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f43k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F43K22"    , { "pic18f43k22"    , "p18f43k22"      , "18f43k22"        }, 0xE322,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f43k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F44J10"    , { "pic18f44j10"    , "p18f44j10"      , "18f44j10"        }, 0xE410,  0, 0x80, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f44j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F44J11"    , { "pic18f44j11"    , "p18f44j11"      , "18f44j11"        }, 0xE411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18f44j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F44J50"    , { "pic18f44j50"    , "p18f44j50"      , "18f44j50"        }, 0xE450,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18f44j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F44K20"    , { "pic18f44k20"    , "p18f44k20"      , "18f44k20"        }, 0xE420,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f44k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F44K22"    , { "pic18f44k22"    , "p18f44k22"      , "18f44k22"        }, 0xE422,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f44k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45J10"    , { "pic18f45j10"    , "p18f45j10"      , "18f45j10"        }, 0xE510,  0, 0x80, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f45j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45J11"    , { "pic18f45j11"    , "p18f45j11"      , "18f45j11"        }, 0xE511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18f45j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45J50"    , { "pic18f45j50"    , "p18f45j50"      , "18f45j50"        }, 0xE550,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18f45j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45K20"    , { "pic18f45k20"    , "p18f45k20"      , "18f45k20"        }, 0xE520,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f45k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45K22"    , { "pic18f45k22"    , "p18f45k22"      , "18f45k22"        }, 0xE522,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f45k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45K50"    , { "pic18f45k50"    , "p18f45k50"      , "18f45k50"        }, 0xE551,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f45k50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F45K80"    , { "pic18f45k80"    , "p18f45k80"      , "18f45k80"        }, 0xB580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f45k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46J11"    , { "pic18f46j11"    , "p18f46j11"      , "18f46j11"        }, 0xE611,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f46j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46J13"    , { "pic18f46j13"    , "p18f46j13"      , "18f46j13"        }, 0xE616,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f46j13_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46J50"    , { "pic18f46j50"    , "p18f46j50"      , "18f46j50"        }, 0xE650,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f46j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46J53"    , { "pic18f46j53"    , "p18f46j53"      , "18f46j53"        }, 0xE655,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f46j53_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46K20"    , { "pic18f46k20"    , "p18f46k20"      , "18f46k20"        }, 0xE620,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f46k20_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46K22"    , { "pic18f46k22"    , "p18f46k22"      , "18f46k22"        }, 0xE622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f46k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F46K80"    , { "pic18f46k80"    , "p18f46k80"      , "18f46k80"        }, 0xB680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f46k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F47J13"    , { "pic18f47j13"    , "p18f47j13"      , "18f47j13"        }, 0xE711,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f47j13_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F47J53"    , { "pic18f47j53"    , "p18f47j53"      , "18f47j53"        }, 0xE750,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f47j53_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F63J11"    , { "pic18f63j11"    , "p18f63j11"      , "18f63j11"        }, 0x6311,  0, 0x60, 0x001FF7, {       -1,       -1 }, { 0x001FF8, 0x001FFD }, "18f63j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F63J90"    , { "pic18f63j90"    , "p18f63j90"      , "18f63j90"        }, 0xB390,  0, 0x60, 0x001FF7, {       -1,       -1 }, { 0x001FF8, 0x001FFD }, "18f63j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F64J11"    , { "pic18f64j11"    , "p18f64j11"      , "18f64j11"        }, 0x6411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f64j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F64J15"    , { "pic18f64j15"    , "p18f64j15"      , "18f64j15"        }, 0xB415,  0, 0x60,       -1, {       -1,       -1 }, {       -1,       -1 }, "18f64j15.lkr"       }, /* not documented by Microchip, added in svn rev. #378, see http://osdir.com/ml/hardware.microcontrollers.gnupic/2008-05/msg00013.html */
  { PROC_CLASS_PIC16E   , "__18F64J90"    , { "pic18f64j90"    , "p18f64j90"      , "18f64j90"        }, 0xB490,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f64j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J10"    , { "pic18f65j10"    , "p18f65j10"      , "18f65j10"        }, 0xB510,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f65j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J11"    , { "pic18f65j11"    , "p18f65j11"      , "18f65j11"        }, 0x6511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f65j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J15"    , { "pic18f65j15"    , "p18f65j15"      , "18f65j15"        }, 0xB515,  0, 0x60, 0x00BFF7, {       -1,       -1 }, { 0x00BFF8, 0x00BFFD }, "18f65j15_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J50"    , { "pic18f65j50"    , "p18f65j50"      , "18f65j50"        }, 0xB550,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f65j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J90"    , { "pic18f65j90"    , "p18f65j90"      , "18f65j90"        }, 0xB590,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f65j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65J94"    , { "pic18f65j94"    , "p18f65j94"      , "18f65j94"        }, 0x6594,  0, 0x60, 0x007FEF, {       -1,       -1 }, { 0x007FF0, 0x007FFF }, "18f65j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65K22"    , { "pic18f65k22"    , "p18f65k22"      , "18f65k22"        }, 0x6522,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f65k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65K80"    , { "pic18f65k80"    , "p18f65k80"      , "18f65k80"        }, 0xC580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f65k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F65K90"    , { "pic18f65k90"    , "p18f65k90"      , "18f65k90"        }, 0xB591,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f65k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J10"    , { "pic18f66j10"    , "p18f66j10"      , "18f66j10"        }, 0xB610,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f66j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J11"    , { "pic18f66j11"    , "p18f66j11"      , "18f66j11"        }, 0xB611,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f66j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J15"    , { "pic18f66j15"    , "p18f66j15"      , "18f66j15"        }, 0xB615,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f66j15_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J16"    , { "pic18f66j16"    , "p18f66j16"      , "18f66j16"        }, 0xB616,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f66j16_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J50"    , { "pic18f66j50"    , "p18f66j50"      , "18f66j50"        }, 0xB650,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f66j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J55"    , { "pic18f66j55"    , "p18f66j55"      , "18f66j55"        }, 0xB655,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f66j55_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J60"    , { "pic18f66j60"    , "p18f66j60"      , "18f66j60"        }, 0xB660,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f66j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J65"    , { "pic18f66j65"    , "p18f66j65"      , "18f66j65"        }, 0xB665,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f66j65_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J90"    , { "pic18f66j90"    , "p18f66j90"      , "18f66j90"        }, 0xB690,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f66j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J93"    , { "pic18f66j93"    , "p18f66j93"      , "18f66j93"        }, 0x6693,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f66j93_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J94"    , { "pic18f66j94"    , "p18f66j94"      , "18f66j94"        }, 0x6694,  0, 0x60, 0x00FFEF, {       -1,       -1 }, { 0x00FFF0, 0x00FFFF }, "18f66j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66J99"    , { "pic18f66j99"    , "p18f66j99"      , "18f66j99"        }, 0x6699,  0, 0x60, 0x017FEF, {       -1,       -1 }, { 0x017FF0, 0x017FFF }, "18f66j99_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66K22"    , { "pic18f66k22"    , "p18f66k22"      , "18f66k22"        }, 0xB622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f66k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66K80"    , { "pic18f66k80"    , "p18f66k80"      , "18f66k80"        }, 0xC680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f66k80_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F66K90"    , { "pic18f66k90"    , "p18f66k90"      , "18f66k90"        }, 0xB691,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f66k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J10"    , { "pic18f67j10"    , "p18f67j10"      , "18f67j10"        }, 0xB710,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f67j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J11"    , { "pic18f67j11"    , "p18f67j11"      , "18f67j11"        }, 0xB711,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f67j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J50"    , { "pic18f67j50"    , "p18f67j50"      , "18f67j50"        }, 0xB750,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f67j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J60"    , { "pic18f67j60"    , "p18f67j60"      , "18f67j60"        }, 0xB760,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f67j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J90"    , { "pic18f67j90"    , "p18f67j90"      , "18f67j90"        }, 0x6790,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f67j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J93"    , { "pic18f67j93"    , "p18f67j93"      , "18f67j93"        }, 0x6793,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f67j93_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67J94"    , { "pic18f67j94"    , "p18f67j94"      , "18f67j94"        }, 0x6794,  0, 0x60, 0x01FFEF, {       -1,       -1 }, { 0x01FFF0, 0x01FFFF }, "18f67j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67K22"    , { "pic18f67k22"    , "p18f67k22"      , "18f67k22"        }, 0x6722,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f67k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F67K90"    , { "pic18f67k90"    , "p18f67k90"      , "18f67k90"        }, 0xB790,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f67k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F83J11"    , { "pic18f83j11"    , "p18f83j11"      , "18f83j11"        }, 0x8311,  0, 0x60, 0x001FF7, {       -1,       -1 }, { 0x001FF8, 0x001FFD }, "18f83j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F83J90"    , { "pic18f83j90"    , "p18f83j90"      , "18f83j90"        }, 0xC390,  0, 0x60, 0x001FF7, {       -1,       -1 }, { 0x001FF8, 0x001FFD }, "18f83j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F84J11"    , { "pic18f84j11"    , "p18f84j11"      , "18f84j11"        }, 0x8411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f84j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F84J15"    , { "pic18f84j15"    , "p18f84j15"      , "18f84j15"        }, 0xC415,  0, 0x60,       -1, {       -1,       -1 }, {       -1,       -1 }, "18f84j15.lkr"       }, /* not documented by Microchip, added in svn rev. #378, see http://osdir.com/ml/hardware.microcontrollers.gnupic/2008-05/msg00013.html */
  { PROC_CLASS_PIC16E   , "__18F84J90"    , { "pic18f84j90"    , "p18f84j90"      , "18f84j90"        }, 0xC490,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18f84j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J10"    , { "pic18f85j10"    , "p18f85j10"      , "18f85j10"        }, 0xC510,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f85j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J11"    , { "pic18f85j11"    , "p18f85j11"      , "18f85j11"        }, 0x8511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f85j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J15"    , { "pic18f85j15"    , "p18f85j15"      , "18f85j15"        }, 0xC515,  0, 0x60, 0x00BFF7, {       -1,       -1 }, { 0x00BFF8, 0x00BFFD }, "18f85j15_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J50"    , { "pic18f85j50"    , "p18f85j50"      , "18f85j50"        }, 0xC550,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f85j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J90"    , { "pic18f85j90"    , "p18f85j90"      , "18f85j90"        }, 0xC590,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18f85j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85J94"    , { "pic18f85j94"    , "p18f85j94"      , "18f85j94"        }, 0x8594,  0, 0x60, 0x007FEF, {       -1,       -1 }, { 0x007FF0, 0x007FFF }, "18f85j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85K22"    , { "pic18f85k22"    , "p18f85k22"      , "18f85k22"        }, 0x8522,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f85k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F85K90"    , { "pic18f85k90"    , "p18f85k90"      , "18f85k90"        }, 0xC591,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f85k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J10"    , { "pic18f86j10"    , "p18f86j10"      , "18f86j10"        }, 0xC610,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f86j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J11"    , { "pic18f86j11"    , "p18f86j11"      , "18f86j11"        }, 0xC611,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f86j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J15"    , { "pic18f86j15"    , "p18f86j15"      , "18f86j15"        }, 0xC615,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f86j15_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J16"    , { "pic18f86j16"    , "p18f86j16"      , "18f86j16"        }, 0xC616,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f86j16_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J50"    , { "pic18f86j50"    , "p18f86j50"      , "18f86j50"        }, 0xC650,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f86j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J55"    , { "pic18f86j55"    , "p18f86j55"      , "18f86j55"        }, 0xC655,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f86j55_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J60"    , { "pic18f86j60"    , "p18f86j60"      , "18f86j60"        }, 0xC660,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f86j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J65"    , { "pic18f86j65"    , "p18f86j65"      , "18f86j65"        }, 0xC665,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f86j65_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J72"    , { "pic18f86j72"    , "p18f86j72"      , "18f86j72"        }, 0x8672,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f86j72_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J90"    , { "pic18f86j90"    , "p18f86j90"      , "18f86j90"        }, 0x8690,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f86j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J93"    , { "pic18f86j93"    , "p18f86j93"      , "18f86j93"        }, 0x8693,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18f86j93_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J94"    , { "pic18f86j94"    , "p18f86j94"      , "18f86j94"        }, 0x8694,  0, 0x60, 0x00FFEF, {       -1,       -1 }, { 0x00FFF0, 0x00FFFF }, "18f86j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86J99"    , { "pic18f86j99"    , "p18f86j99"      , "18f86j99"        }, 0x8699,  0, 0x60, 0x017FEF, {       -1,       -1 }, { 0x017FF0, 0x017FFF }, "18f86j99_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86K22"    , { "pic18f86k22"    , "p18f86k22"      , "18f86k22"        }, 0xC622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f86k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F86K90"    , { "pic18f86k90"    , "p18f86k90"      , "18f86k90"        }, 0xC690,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f86k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J10"    , { "pic18f87j10"    , "p18f87j10"      , "18f87j10"        }, 0xC710,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f87j10_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J11"    , { "pic18f87j11"    , "p18f87j11"      , "18f87j11"        }, 0xC711,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f87j11_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J50"    , { "pic18f87j50"    , "p18f87j50"      , "18f87j50"        }, 0xC750,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f87j50_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J60"    , { "pic18f87j60"    , "p18f87j60"      , "18f87j60"        }, 0xC760,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f87j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J72"    , { "pic18f87j72"    , "p18f87j72"      , "18f87j72"        }, 0x8772,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f87j72_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J90"    , { "pic18f87j90"    , "p18f87j90"      , "18f87j90"        }, 0x8790,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f87j90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J93"    , { "pic18f87j93"    , "p18f87j93"      , "18f87j93"        }, 0x8793,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18f87j93_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87J94"    , { "pic18f87j94"    , "p18f87j94"      , "18f87j94"        }, 0x8794,  0, 0x60, 0x01FFEF, {       -1,       -1 }, { 0x01FFF0, 0x01FFFF }, "18f87j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87K22"    , { "pic18f87k22"    , "p18f87k22"      , "18f87k22"        }, 0x8722,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f87k22_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F87K90"    , { "pic18f87k90"    , "p18f87k90"      , "18f87k90"        }, 0xC790,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f87k90_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F95J94"    , { "pic18f95j94"    , "p18f95j94"      , "18f95j94"        }, 0x9594,  0, 0x60, 0x007FEF, {       -1,       -1 }, { 0x007FF0, 0x007FFF }, "18f95j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F96J60"    , { "pic18f96j60"    , "p18f96j60"      , "18f96j60"        }, 0xD660,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFD }, "18f96j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F96J65"    , { "pic18f96j65"    , "p18f96j65"      , "18f96j65"        }, 0xD665,  0, 0x60, 0x017FF7, {       -1,       -1 }, { 0x017FF8, 0x017FFD }, "18f96j65_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F96J94"    , { "pic18f96j94"    , "p18f96j94"      , "18f96j94"        }, 0x9694,  0, 0x60, 0x00FFEF, {       -1,       -1 }, { 0x00FFF0, 0x00FFFF }, "18f96j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F96J99"    , { "pic18f96j99"    , "p18f96j99"      , "18f96j99"        }, 0x9699,  0, 0x60, 0x017FEF, {       -1,       -1 }, { 0x017FF0, 0x017FFF }, "18f96j99_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F97J60"    , { "pic18f97j60"    , "p18f97j60"      , "18f97j60"        }, 0xD760,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFD }, "18f97j60_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F97J94"    , { "pic18f97j94"    , "p18f97j94"      , "18f97j94"        }, 0x9794,  0, 0x60, 0x01FFEF, {       -1,       -1 }, { 0x01FFF0, 0x01FFFF }, "18f97j94_g.lkr"     },
  { PROC_CLASS_PIC16E   , "__18F242"      , { "pic18f242"      , "p18f242"        , "18f242"          }, 0x242F,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f242_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F248"      , { "pic18f248"      , "p18f248"        , "18f248"          }, 0x8248,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f248_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F252"      , { "pic18f252"      , "p18f252"        , "18f252"          }, 0x252F,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f252_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F258"      , { "pic18f258"      , "p18f258"        , "18f258"          }, 0x8258,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f258_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F442"      , { "pic18f442"      , "p18f442"        , "18f442"          }, 0x442F,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f442_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F448"      , { "pic18f448"      , "p18f448"        , "18f448"          }, 0x8448,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f448_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F452"      , { "pic18f452"      , "p18f452"        , "18f452"          }, 0x452F,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f452_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F458"      , { "pic18f458"      , "p18f458"        , "18f458"          }, 0x8458,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f458_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__18F1220"     , { "pic18f1220"     , "p18f1220"       , "18f1220"         }, 0xA122,  0, 0x80, 0xF000FF, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f1220_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F1230"     , { "pic18f1230"     , "p18f1230"       , "18f1230"         }, 0x1230,  0, 0x80, 0xF0007F, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f1230_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F1320"     , { "pic18f1320"     , "p18f1320"       , "18f1320"         }, 0xA132,  0, 0x80, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f1320_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F1330"     , { "pic18f1330"     , "p18f1330"       , "18f1330"         }, 0x1330,  0, 0x80, 0xF0007F, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f1330_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2220"     , { "pic18f2220"     , "p18f2220"       , "18f2220"         }, 0xA222,  0, 0x80, 0xF000FF, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2220_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2221"     , { "pic18f2221"     , "p18f2221"       , "18f2221"         }, 0x2221,  0, 0x80, 0xF000FF, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2221_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2320"     , { "pic18f2320"     , "p18f2320"       , "18f2320"         }, 0xA232,  0, 0x80, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2320_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2321"     , { "pic18f2321"     , "p18f2321"       , "18f2321"         }, 0x2321,  0, 0x80, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2321_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2331"     , { "pic18f2331"     , "p18f2331"       , "18f2331"         }, 0x2331,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2331_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2410"     , { "pic18f2410"     , "p18f2410"       , "18f2410"         }, 0x2410,  0, 0x80, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f2410_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2420"     , { "pic18f2420"     , "p18f2420"       , "18f2420"         }, 0x2420,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2420_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2423"     , { "pic18f2423"     , "p18f2423"       , "18f2423"         }, 0x2423,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2423_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2431"     , { "pic18f2431"     , "p18f2431"       , "18f2431"         }, 0x2431,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2431_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2439"     , { "pic18f2439"     , "p18f2439"       , "18f2439"         }, 0x2439,  0, 0x80, 0xF000FF, { 0x003000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2439_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2450"     , { "pic18f2450"     , "p18f2450"       , "18f2450"         }, 0x2450,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f2450_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2455"     , { "pic18f2455"     , "p18f2455"       , "18f2455"         }, 0x2455,  0, 0x60, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2455_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2458"     , { "pic18f2458"     , "p18f2458"       , "18f2458"         }, 0x2458,  0, 0x60, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2458_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2480"     , { "pic18f2480"     , "p18f2480"       , "18f2480"         }, 0x2480,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2480_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2510"     , { "pic18f2510"     , "p18f2510"       , "18f2510"         }, 0x2510,  0, 0x80, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f2510_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2515"     , { "pic18f2515"     , "p18f2515"       , "18f2515"         }, 0x2515,  0, 0x80, 0x00BFFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f2515_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2520"     , { "pic18f2520"     , "p18f2520"       , "18f2520"         }, 0x2520,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2520_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2523"     , { "pic18f2523"     , "p18f2523"       , "18f2523"         }, 0x2523,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2523_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2525"     , { "pic18f2525"     , "p18f2525"       , "18f2525"         }, 0x2525,  0, 0x80, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2525_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2539"     , { "pic18f2539"     , "p18f2539"       , "18f2539"         }, 0x2539,  0, 0x80, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2539_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2550"     , { "pic18f2550"     , "p18f2550"       , "18f2550"         }, 0x2550,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2550_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2553"     , { "pic18f2553"     , "p18f2553"       , "18f2553"         }, 0x2553,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2553_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2580"     , { "pic18f2580"     , "p18f2580"       , "18f2580"         }, 0x2580,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2580_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2585"     , { "pic18f2585"     , "p18f2585"       , "18f2585"         }, 0x2585,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2585_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2610"     , { "pic18f2610"     , "p18f2610"       , "18f2610"         }, 0x2610,  0, 0x80, 0x00FFFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f2610_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2620"     , { "pic18f2620"     , "p18f2620"       , "18f2620"         }, 0x2620,  0, 0x80, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2620_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2680"     , { "pic18f2680"     , "p18f2680"       , "18f2680"         }, 0x2680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2680_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2681"     , { "pic18f2681"     , "p18f2681"       , "18f2681"         }, 0x2681,  0, 0x60,       -1, {       -1,       -1 }, {       -1,       -1 }, "18f2681.lkr"        }, /* not documented by Microchip, added in svn rev. #317, see http://osdir.com/ml/hardware.microcontrollers.gnupic/2008-05/msg00013.html */
  { PROC_CLASS_PIC16E   , "__18F2682"     , { "pic18f2682"     , "p18f2682"       , "18f2682"         }, 0x2682,  0, 0x60, 0xF003FF, { 0x014000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2682_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F2685"     , { "pic18f2685"     , "p18f2685"       , "18f2685"         }, 0x2685,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f2685_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4220"     , { "pic18f4220"     , "p18f4220"       , "18f4220"         }, 0xA422,  0, 0x80, 0xF000FF, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4220_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4221"     , { "pic18f4221"     , "p18f4221"       , "18f4221"         }, 0x4221,  0, 0x80, 0xF000FF, { 0x001000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4221_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4320"     , { "pic18f4320"     , "p18f4320"       , "18f4320"         }, 0xA432,  0, 0x80, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4320_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4321"     , { "pic18f4321"     , "p18f4321"       , "18f4321"         }, 0x4321,  0, 0x80, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4321_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4331"     , { "pic18f4331"     , "p18f4331"       , "18f4331"         }, 0x4331,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4331_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4410"     , { "pic18f4410"     , "p18f4410"       , "18f4410"         }, 0x4410,  0, 0x80, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f4410_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4420"     , { "pic18f4420"     , "p18f4420"       , "18f4420"         }, 0x4420,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4420_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4423"     , { "pic18f4423"     , "p18f4423"       , "18f4423"         }, 0x4423,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4423_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4431"     , { "pic18f4431"     , "p18f4431"       , "18f4431"         }, 0x4431,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4431_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4439"     , { "pic18f4439"     , "p18f4439"       , "18f4439"         }, 0x4439,  0, 0x80, 0xF000FF, { 0x003000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4439_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4450"     , { "pic18f4450"     , "p18f4450"       , "18f4450"         }, 0x4450,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f4450_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4455"     , { "pic18f4455"     , "p18f4455"       , "18f4455"         }, 0x4455,  0, 0x60, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4455_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4458"     , { "pic18f4458"     , "p18f4458"       , "18f4458"         }, 0x4458,  0, 0x60, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4458_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4480"     , { "pic18f4480"     , "p18f4480"       , "18f4480"         }, 0x4480,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4480_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4510"     , { "pic18f4510"     , "p18f4510"       , "18f4510"         }, 0x4510,  0, 0x80, 0x007FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f4510_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4515"     , { "pic18f4515"     , "p18f4515"       , "18f4515"         }, 0x4515,  0, 0x80, 0x00BFFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f4515_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4520"     , { "pic18f4520"     , "p18f4520"       , "18f4520"         }, 0x4520,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4520_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4523"     , { "pic18f4523"     , "p18f4523"       , "18f4523"         }, 0x4523,  0, 0x80, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4523_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4525"     , { "pic18f4525"     , "p18f4525"       , "18f4525"         }, 0x4525,  0, 0x80, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4525_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4539"     , { "pic18f4539"     , "p18f4539"       , "18f4539"         }, 0x4539,  0, 0x80, 0xF000FF, { 0x006000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4539_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4550"     , { "pic18f4550"     , "p18f4550"       , "18f4550"         }, 0x4550,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4550_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4553"     , { "pic18f4553"     , "p18f4553"       , "18f4553"         }, 0x4553,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4553_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4580"     , { "pic18f4580"     , "p18f4580"       , "18f4580"         }, 0x4580,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4580_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4585"     , { "pic18f4585"     , "p18f4585"       , "18f4585"         }, 0x4585,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4585_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4610"     , { "pic18f4610"     , "p18f4610"       , "18f4610"         }, 0x4610,  0, 0x80, 0x00FFFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f4610_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4620"     , { "pic18f4620"     , "p18f4620"       , "18f4620"         }, 0x4620,  0, 0x80, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4620_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4680"     , { "pic18f4680"     , "p18f4680"       , "18f4680"         }, 0x4680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4680_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4681"     , { "pic18f4681"     , "p18f4681"       , "18f4681"         }, 0x4681,  0, 0x60,       -1, {       -1,       -1 }, {       -1,       -1 }, "18f4681.lkr"        }, /* not documented by Microchip, added in svn rev. #317, see http://osdir.com/ml/hardware.microcontrollers.gnupic/2008-05/msg00013.html */
  { PROC_CLASS_PIC16E   , "__18F4682"     , { "pic18f4682"     , "p18f4682"       , "18f4682"         }, 0x4682,  0, 0x60, 0xF003FF, { 0x014000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4682_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F4685"     , { "pic18f4685"     , "p18f4685"       , "18f4685"         }, 0x4685,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f4685_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6310"     , { "pic18f6310"     , "p18f6310"       , "18f6310"         }, 0x6310,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6310_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6390"     , { "pic18f6390"     , "p18f6390"       , "18f6390"         }, 0x6390,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6390_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6393"     , { "pic18f6393"     , "p18f6393"       , "18f6393"         }, 0x6393,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6393_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6410"     , { "pic18f6410"     , "p18f6410"       , "18f6410"         }, 0x6410,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6410_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6490"     , { "pic18f6490"     , "p18f6490"       , "18f6490"         }, 0x6490,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6490_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6493"     , { "pic18f6493"     , "p18f6493"       , "18f6493"         }, 0x6493,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f6493_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6520"     , { "pic18f6520"     , "p18f6520"       , "18f6520"         }, 0xA652,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6520_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6525"     , { "pic18f6525"     , "p18f6525"       , "18f6525"         }, 0x6525,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6525_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6527"     , { "pic18f6527"     , "p18f6527"       , "18f6527"         }, 0x6527,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6527_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6585"     , { "pic18f6585"     , "p18f6585"       , "18f6585"         }, 0x6585,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6585_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6620"     , { "pic18f6620"     , "p18f6620"       , "18f6620"         }, 0xA662,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6620_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6621"     , { "pic18f6621"     , "p18f6621"       , "18f6621"         }, 0xA621,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6621_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6622"     , { "pic18f6622"     , "p18f6622"       , "18f6622"         }, 0xF622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6622_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6627"     , { "pic18f6627"     , "p18f6627"       , "18f6627"         }, 0xF625,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6627_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6628"     , { "pic18f6628"     , "p18f6628"       , "18f6628"         }, 0xA628,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6628_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6680"     , { "pic18f6680"     , "p18f6680"       , "18f6680"         }, 0x6680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6680_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6720"     , { "pic18f6720"     , "p18f6720"       , "18f6720"         }, 0xA672,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6720_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6722"     , { "pic18f6722"     , "p18f6722"       , "18f6722"         }, 0x6721,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6722_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F6723"     , { "pic18f6723"     , "p18f6723"       , "18f6723"         }, 0x6723,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f6723_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8310"     , { "pic18f8310"     , "p18f8310"       , "18f8310"         }, 0x8310,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8310_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8390"     , { "pic18f8390"     , "p18f8390"       , "18f8390"         }, 0x8390,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8390_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8393"     , { "pic18f8393"     , "p18f8393"       , "18f8393"         }, 0x8393,  0, 0x60, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8393_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8410"     , { "pic18f8410"     , "p18f8410"       , "18f8410"         }, 0x8410,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8410_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8490"     , { "pic18f8490"     , "p18f8490"       , "18f8490"         }, 0x8490,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8490_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8493"     , { "pic18f8493"     , "p18f8493"       , "18f8493"         }, 0x8493,  0, 0x60, 0x003FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "18f8493_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8520"     , { "pic18f8520"     , "p18f8520"       , "18f8520"         }, 0xA852,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8520_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8525"     , { "pic18f8525"     , "p18f8525"       , "18f8525"         }, 0x8525,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8525_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8527"     , { "pic18f8527"     , "p18f8527"       , "18f8527"         }, 0x8527,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8527_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8585"     , { "pic18f8585"     , "p18f8585"       , "18f8585"         }, 0x8585,  0, 0x60, 0xF003FF, { 0x00C000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8585_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8620"     , { "pic18f8620"     , "p18f8620"       , "18f8620"         }, 0xA862,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8620_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8621"     , { "pic18f8621"     , "p18f8621"       , "18f8621"         }, 0x8621,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8621_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8622"     , { "pic18f8622"     , "p18f8622"       , "18f8622"         }, 0x8622,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8622_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8627"     , { "pic18f8627"     , "p18f8627"       , "18f8627"         }, 0x8625,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8627_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8628"     , { "pic18f8628"     , "p18f8628"       , "18f8628"         }, 0x8628,  0, 0x60, 0xF003FF, { 0x018000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8628_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8680"     , { "pic18f8680"     , "p18f8680"       , "18f8680"         }, 0x8680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8680_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8720"     , { "pic18f8720"     , "p18f8720"       , "18f8720"         }, 0xA872,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8720_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8722"     , { "pic18f8722"     , "p18f8722"       , "18f8722"         }, 0x8721,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8722_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18F8723"     , { "pic18f8723"     , "p18f8723"       , "18f8723"         }, 0x8723,  0, 0x60, 0xF003FF, { 0x020000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18f8723_g.lkr"      },
  { PROC_CLASS_PIC16E   , "__18LF13K22"   , { "pic18lf13k22"   , "p18lf13k22"     , "18lf13k22"       }, 0xA133,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf13k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF13K50"   , { "pic18lf13k50"   , "p18lf13k50"     , "18lf13k50"       }, 0xD135,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf13k50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF14K22"   , { "pic18lf14k22"   , "p18lf14k22"     , "18lf14k22"       }, 0xA142,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf14k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF14K50"   , { "pic18lf14k50"   , "p18lf14k50"     , "18lf14k50"       }, 0xD145,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf14k50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF23K22"   , { "pic18lf23k22"   , "p18lf23k22"     , "18lf23k22"       }, 0xB322,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf23k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF24J10"   , { "pic18lf24j10"   , "p18lf24j10"     , "18lf24j10"       }, 0xA241,  0, 0x80, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18lf24j10_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF24J11"   , { "pic18lf24j11"   , "p18lf24j11"     , "18lf24j11"       }, 0xB411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18lf24j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF24J50"   , { "pic18lf24j50"   , "p18lf24j50"     , "18lf24j50"       }, 0xB450,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18lf24j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF24K22"   , { "pic18lf24k22"   , "p18lf24k22"     , "18lf24k22"       }, 0xB422,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf24k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF24K50"   , { "pic18lf24k50"   , "p18lf24k50"     , "18lf24k50"       }, 0xD452,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf24k50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25J10"   , { "pic18lf25j10"   , "p18lf25j10"     , "18lf25j10"       }, 0xA251,  0, 0x80, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18lf25j10_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25J11"   , { "pic18lf25j11"   , "p18lf25j11"     , "18lf25j11"       }, 0xB511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18lf25j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25J50"   , { "pic18lf25j50"   , "p18lf25j50"     , "18lf25j50"       }, 0xB551,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18lf25j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25K22"   , { "pic18lf25k22"   , "p18lf25k22"     , "18lf25k22"       }, 0xB522,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf25k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25K50"   , { "pic18lf25k50"   , "p18lf25k50"     , "18lf25k50"       }, 0xD552,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf25k50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF25K80"   , { "pic18lf25k80"   , "p18lf25k80"     , "18lf25k80"       }, 0xD580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf25k80_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26J11"   , { "pic18lf26j11"   , "p18lf26j11"     , "18lf26j11"       }, 0xB612,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf26j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26J13"   , { "pic18lf26j13"   , "p18lf26j13"     , "18lf26j13"       }, 0xB617,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf26j13_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26J50"   , { "pic18lf26j50"   , "p18lf26j50"     , "18lf26j50"       }, 0xB651,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf26j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26J53"   , { "pic18lf26j53"   , "p18lf26j53"     , "18lf26j53"       }, 0xB656,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf26j53_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26K22"   , { "pic18lf26k22"   , "p18lf26k22"     , "18lf26k22"       }, 0xB623,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf26k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF26K80"   , { "pic18lf26k80"   , "p18lf26k80"     , "18lf26k80"       }, 0xD680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf26k80_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF27J13"   , { "pic18lf27j13"   , "p18lf27j13"     , "18lf27j13"       }, 0xB712,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18lf27j13_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF27J53"   , { "pic18lf27j53"   , "p18lf27j53"     , "18lf27j53"       }, 0xC753,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18lf27j53_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF43K22"   , { "pic18lf43k22"   , "p18lf43k22"     , "18lf43k22"       }, 0xC322,  0, 0x60, 0xF000FF, { 0x002000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf43k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF44J10"   , { "pic18lf44j10"   , "p18lf44j10"     , "18lf44j10"       }, 0xA441,  0, 0x80, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFD }, "18lf44j10_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF44J11"   , { "pic18lf44j11"   , "p18lf44j11"     , "18lf44j11"       }, 0xC411,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18lf44j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF44J50"   , { "pic18lf44j50"   , "p18lf44j50"     , "18lf44j50"       }, 0xC450,  0, 0x60, 0x003FF7, {       -1,       -1 }, { 0x003FF8, 0x003FFF }, "18lf44j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF44K22"   , { "pic18lf44k22"   , "p18lf44k22"     , "18lf44k22"       }, 0xC422,  0, 0x60, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf44k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45J10"   , { "pic18lf45j10"   , "p18lf45j10"     , "18lf45j10"       }, 0xA451,  0, 0x80, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFD }, "18lf45j10_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45J11"   , { "pic18lf45j11"   , "p18lf45j11"     , "18lf45j11"       }, 0xC511,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18lf45j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45J50"   , { "pic18lf45j50"   , "p18lf45j50"     , "18lf45j50"       }, 0xC551,  0, 0x60, 0x007FF7, {       -1,       -1 }, { 0x007FF8, 0x007FFF }, "18lf45j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45K22"   , { "pic18lf45k22"   , "p18lf45k22"     , "18lf45k22"       }, 0xC522,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf45k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45K50"   , { "pic18lf45k50"   , "p18lf45k50"     , "18lf45k50"       }, 0xE552,  0, 0x60, 0xF000FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf45k50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF45K80"   , { "pic18lf45k80"   , "p18lf45k80"     , "18lf45k80"       }, 0xE580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf45k80_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46J11"   , { "pic18lf46j11"   , "p18lf46j11"     , "18lf46j11"       }, 0xC612,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf46j11_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46J13"   , { "pic18lf46j13"   , "p18lf46j13"     , "18lf46j13"       }, 0xC617,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf46j13_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46J50"   , { "pic18lf46j50"   , "p18lf46j50"     , "18lf46j50"       }, 0xC651,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf46j50_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46J53"   , { "pic18lf46j53"   , "p18lf46j53"     , "18lf46j53"       }, 0xC656,  0, 0x60, 0x00FFF7, {       -1,       -1 }, { 0x00FFF8, 0x00FFFF }, "18lf46j53_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46K22"   , { "pic18lf46k22"   , "p18lf46k22"     , "18lf46k22"       }, 0xC623,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf46k22_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF46K80"   , { "pic18lf46k80"   , "p18lf46k80"     , "18lf46k80"       }, 0xE680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf46k80_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF47J13"   , { "pic18lf47j13"   , "p18lf47j13"     , "18lf47j13"       }, 0xC712,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18lf47j13_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF47J53"   , { "pic18lf47j53"   , "p18lf47j53"     , "18lf47j53"       }, 0xC751,  0, 0x60, 0x01FFF7, {       -1,       -1 }, { 0x01FFF8, 0x01FFFF }, "18lf47j53_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF65K80"   , { "pic18lf65k80"   , "p18lf65k80"     , "18lf65k80"       }, 0xF580,  0, 0x60, 0xF003FF, { 0x008000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf65k80_g.lkr"    },
  { PROC_CLASS_PIC16E   , "__18LF66K80"   , { "pic18lf66k80"   , "p18lf66k80"     , "18lf66k80"       }, 0xF680,  0, 0x60, 0xF003FF, { 0x010000, 0xEFFFFF }, { 0x300000, 0x30000D }, "18lf66k80_g.lkr"    },
  { PROC_CLASS_PIC14    , "__14000"       , { "pic14000"       , "p14000"         , "14000"           }, 0x4000,  2,    2, 0x000FBF, {       -1,       -1 }, { 0x002007, 0x002007 }, "14000_g.lkr"        },
  { PROC_CLASS_EEPROM8  , "__EEPROM8"     , { "eeprom8"        , "eeprom8"        , "eeprom8"         }, 0x1FFF,  0,    0, 0x0000FF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_EEPROM16 , "__EEPROM16"    , { "eeprom16"       , "eeprom16"       , "eeprom16"        }, 0x1FFF,  0,    0, 0x00007F, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_GENERIC  , "__GEN"         , { "generic"        , "gen"            , "unknown"         }, 0x0000,  0,    0,       -1, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_PIC12    , "__HCS1365"     , { "hcs1365"        , "hcs1365"        , "hcs1365"         }, 0xF365,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x0007FF, 0x0007FF }, "hcs1365_g.lkr"      },
  { PROC_CLASS_PIC12    , "__HCS1370"     , { "hcs1370"        , "hcs1370"        , "hcs1370"         }, 0xF370,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x0007FF, 0x0007FF }, "hcs1370_g.lkr"      },
  { PROC_CLASS_PIC12    , "__MCV08A"      , { "mcv08a"         , "mcv08a"         , "mcv08a"          }, 0xA510,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "mcv08a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__MCV14A"      , { "mcv14a"         , "mcv14a"         , "mcv14a"          }, 0xC526,  2,    4, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "mcv14a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__MCV18A"      , { "mcv18a"         , "mcv18a"         , "mcv18a"          }, 0xCF54,  1,    1, 0x0001FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "mcv18a_g.lkr"       },
  { PROC_CLASS_PIC12    , "__MCV28A"      , { "mcv28a"         , "mcv28a"         , "mcv28a"          }, 0xCF57,  4,    4, 0x0007FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "mcv28a_g.lkr"       },
  { PROC_CLASS_PIC16E   , "__PS500"       , { "ps500"          , "ps500"          , "ps500"           }, 0x0500,  0, 0x80, 0xF000FF, { 0x004000, 0xEFFFFF }, { 0x300000, 0x30000D }, "ps500_g.lkr"        },
  { PROC_CLASS_PIC16E   , "__PS810"       , { "ps810"          , "ps810"          , "ps810"           }, 0x0810,  0, 0x80, 0x001FFF, {       -1,       -1 }, { 0x300000, 0x30000D }, "ps810_g.lkr"        },
  { PROC_CLASS_PIC12    , "__RF509AF"     , { "rf509af"        , "rf509af"        , "rf509af"         }, 0x6509,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "rf509af_g.lkr"      },
  { PROC_CLASS_PIC12    , "__RF509AG"     , { "rf509ag"        , "rf509ag"        , "rf509ag"         }, 0x7509,  2,    2, 0x0003FF, {       -1,       -1 }, { 0x000FFF, 0x000FFF }, "rf509ag_g.lkr"      },
  { PROC_CLASS_PIC14    , "__RF675F"      , { "rf675f"         , "rf675f"         , "rf675f"          }, 0x3675,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "rf675f_g.lkr"       },
  { PROC_CLASS_PIC14    , "__RF675H"      , { "rf675h"         , "rf675h"         , "rf675h"          }, 0x4675,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "rf675h_g.lkr"       },
  { PROC_CLASS_PIC14    , "__RF675K"      , { "rf675k"         , "rf675k"         , "rf675k"          }, 0x5675,  1,    2, 0x00217F, { 0x0003FF, 0x0020FF }, { 0x002007, 0x002007 }, "rf675k_g.lkr"       },
  { PROC_CLASS_SX       , "__SX18"        , { "sx18ac"         , "sx18"           , "sx18"            }, 0x0018,  0,    0, 0x0007FF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_SX       , "__SX20"        , { "sx20ac"         , "sx20"           , "sx20"            }, 0x0020,  0,    0, 0x0007FF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_SX       , "__SX28"        , { "sx28ac"         , "sx28"           , "sx28"            }, 0x0028,  0,    0, 0x0007FF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_SX       , "__SX48"        , { "sx48bd"         , "sx48"           , "sx48"            }, 0x0048,  0,    0, 0x000FFF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
  { PROC_CLASS_SX       , "__SX52"        , { "sx52bd"         , "sx52"           , "sx52"            }, 0x0052,  0,    0, 0x000FFF, {       -1,       -1 }, {       -1,       -1 }, NULL                 },
};

#define NUM_PICS        (sizeof(pics) / sizeof(pics[0]))

/*
 * Display a list of the processor names
 */
void gp_dump_processor_list(gp_boolean list_all, proc_class_t class)
{
#define COLUMNS  6
#define SPACE_BETWEEN 2   /* number of chars between columns */
#define FAVORITE 1        /* there are 3 names to choose from */

  int i;
  int j;
  int length;
  int num = 0;
  int longest = 0;

  for(i = 0; i < NUM_PICS; i++) {
    length = strlen(pics[i].names[FAVORITE]);
    if (length > longest)
      longest = length;
  }

  for(i = 0; i < NUM_PICS; i++) {
    if (list_all || (pics[i].class == class)) {
      num++;
      printf("%s", pics[i].names[FAVORITE]);
      length = longest + SPACE_BETWEEN - strlen(pics[i].names[FAVORITE]);
      for(j = 0; j < length; j++) {
        putchar(' ');
      }
      if ((num % COLUMNS) == 0) {
        putchar('\n');
      }
    }
  }

  if ((num % COLUMNS) != 0) {
    putchar('\n');
  }

}

const struct px *
gp_find_processor(const char *name)
{
  int i, j;

  for (i = 0; i < NUM_PICS; i++) {
    for (j = 0; (j < MAX_NAMES) && (pics[i].names[j] != NULL); j++) {
      if (strcasecmp(name, pics[i].names[j]) == 0) {
        return &pics[i];
      }
    }
  }

  return NULL;
}

proc_class_t
gp_processor_class(pic_processor_t processor)
{
  if (processor)
    return processor->class;
  return PROC_CLASS_UNKNOWN;
}

/* 18xx bsr boundary location */

int
gp_processor_bsr_boundary(pic_processor_t processor)
{
  if (processor && processor->class == PROC_CLASS_PIC16E)
    return processor->num_banks;
  return 0;
}

unsigned long
gp_processor_coff_type(pic_processor_t processor)
{
  if (processor)
    return processor->coff_type;
  return 0;
}

int
gp_processor_num_pages(pic_processor_t processor)
{
  if (processor)
    return processor->num_pages;
  return 0;
}

int
gp_processor_num_banks(pic_processor_t processor)
{
  if (processor && processor->class != PROC_CLASS_PIC16E)
    return processor->num_banks;
  return 0;
}

pic_processor_t
gp_processor_coff_proc(unsigned long coff_type)
{
  int i;
  pic_processor_t processor = NULL;

  for (i = 0; i < NUM_PICS; i++) {
    if (pics[i].coff_type == coff_type) {
      processor = &pics[i];
      break;
    }
  }

  return processor;
}

const char *
gp_processor_name(pic_processor_t processor, unsigned int choice)
{
  assert(!(choice > MAX_NAMES - 1));

  if (processor)
    return processor->names[choice];

  return NULL;
}

const char *
gp_processor_coff_name(unsigned long coff_type, unsigned int choice)
{
  int i;

  if (coff_type == 0)
    return NULL;

  assert(!(choice > MAX_NAMES - 1));

  for (i = 0; i < NUM_PICS; i++) {
    if (pics[i].coff_type == coff_type) {
      return pics[i].names[choice];
    }
  }

  return NULL;
}

const char *
gp_processor_script(pic_processor_t processor)
{
  if (processor)
    return processor->script;
  return NULL;
}

unsigned int
gp_processor_id_location(pic_processor_t processor)
{
  if (processor->class->id_location)
    return processor->class->id_location(processor);
  return 0;
}

int
gp_processor_rom_width(proc_class_t class)
{
  assert(class->rom_width > 0);
  return class->rom_width;
}

/* Set the page bits, return the number of instructions required. */

int
gp_processor_set_page(proc_class_t class,
                      int num_pages,
                      int page,
                      MemBlock *m,
                      unsigned int address,
                      int use_wreg)
{
  return class->set_page(num_pages, page, m, address, use_wreg);
}

/* Set the bank bits, return the number of instructions required. */

int
gp_processor_set_bank(proc_class_t class,
                      int num_banks,
                      int bank,
                      MemBlock *m,
                      unsigned int address)
{
  return class->set_bank(num_banks, bank, m, address);
}

/* determine the value for retlw */

int
gp_processor_retlw(proc_class_t class)
{
  assert(class->retlw >= 0);
  return class->retlw;
}

int
gp_processor_org_to_byte(proc_class_t class, int org)
{
  /* FIXME: In some places we use this value before we know what the
     processor is. Rather than fix those now, I'll just return some
     value. */
  if (!class)
    return org;

  return org << class->org_to_byte_shift;
}

int
gp_processor_byte_to_org(proc_class_t class, int byte)
{
  /* FIXME: In some places we use this value before we know what the
     processor is. Rather than fix those now, I'll just return some
     value. */
  if (!class)
    return byte;

  return byte >> class->org_to_byte_shift;
}

int
gp_org_to_byte(unsigned shift, int org)
{
  return org << shift;
}

int
gp_byte_to_org(unsigned shift, int byte)
{
  return byte >> shift;
}

/* determine which page of program memory the byte address is located */
int
gp_processor_check_page(proc_class_t class, unsigned int org)
{
  return class->check_page(org);
}

/* determine which bank of data memory the address is located */
int
gp_processor_check_bank(proc_class_t class, unsigned int address)
{
  return class->check_bank(address);
}

/* When unsupported on the class */
static int
gp_processor_check_page_unsupported(unsigned int org)
{
  assert(0);
  return 0;
}

static int
gp_processor_check_bank_unsupported(unsigned int address)
{
  assert(0);
  return 0;
}

static int
gp_processor_set_page_unsupported(int num_pages,
                                  int page,
                                  MemBlock *m,
                                  unsigned int address,
                                  int use_wreg)
{
    assert(0);
    return 0;
}

static int
gp_processor_set_bank_unsupported(int num_banks,
                                  int bank,
                                  MemBlock *m,
                                  unsigned int address)
{
  assert(0);
  return 0;
}

static int reloc_unsupported(unsigned int address)
{
  assert(0);
  return 0;
}
static int
reloc_bra_unsupported(gp_section_type *section, unsigned value, unsigned int byte_org)
{
  assert(0);
  return 0;
}

/* Common to most */

static const struct insn *
find_insn_generic(proc_class_t cls, long int opcode)
{
  const struct insn *base = cls->instructions;
  int count = base == NULL ? 0 : *cls->num_instructions;
  int i;
  for(i = 0; i < count; i++) {
    if((base[i].mask & opcode) == base[i].opcode) {
      return &base[i];
    }
  }
  return NULL;
}

/* Common to PIC12 and PIC14 */

static int
gp_processor_set_page_pic12_14(int num_pages,
                               int page,
                               MemBlock *m,
                               unsigned int address,
                               int use_wreg,
                               int bcf_insn,
                               int bsf_insn,
                               int movlw_insn,
                               int movwf_insn,
                               int location,
                               int page0,
                               int page1)
{
  unsigned int data;
  int count = 4;
  if (num_pages == 1) {
    return 0;
  }

  if (use_wreg) {
    data = movlw_insn | page;
    i_memory_put_le(m, address, data);
    data = movwf_insn | location;
    i_memory_put_le(m, address + 2, data);
  }
  else {
    /* page low bit */
    data = (page & 1 ? bsf_insn : bcf_insn) | page0 | location;
    i_memory_put_le(m, address, data);

    /* page high bit */
    if (num_pages == 4) {
      data = (page & 2 ? bsf_insn : bcf_insn) | page1 | location;
      i_memory_put_le(m, address + 2, data);
    }

    if (num_pages == 2) {
      count = 2;
    } else {
      count = 4;
    }
  }
  return count;
}

static int
gp_processor_set_bank_pic12_14(int num_banks,
                               int bank,
                               MemBlock *m,
                               unsigned int address,
                               int bcf_insn,
                               int bsf_insn,
                               int location,
                               int bank0,
                               int bank1)
{
  unsigned int data;
  int count;
  if (num_banks == 1) {
    return 0;
  }

  switch(bank) {
  case 0:
    /* bcf location, bank0 */
    data = bcf_insn | bank0 | location;
    i_memory_put_le(m, address, data);
    if (num_banks == 4) {
      /* bcf location, bank1 */
      data = bcf_insn | bank1 | location;
      i_memory_put_le(m, address + 2, data);
    }
    break;
  case 1:
    /* bsf location, bank0 */
    data = bsf_insn | bank0 | location;
    i_memory_put_le(m, address, data);
    if (num_banks == 4) {
      /* bcf location, bank1 */
      data = bcf_insn | bank1 | location;
      i_memory_put_le(m, address + 2, data);
    }
    break;
  case 2:
    /* bcf location, bank0 */
    data = bcf_insn | bank0 | location;
    i_memory_put_le(m, address, data);
    if (num_banks == 4) {
      /* bsf location, bank1 */
      data = bsf_insn | bank1 | location;
      i_memory_put_le(m, address + 2, data);
    }
    break;
  case 3:
    /* bsf location, bank0 */
    data = bsf_insn | bank0 | location;
    i_memory_put_le(m, address, data);
    if (num_banks == 4) {
      /* bsf location, bank1 */
      data = bsf_insn | bank1 | location;
      i_memory_put_le(m, address + 2, data);
    }
    break;
  default:
    assert(0);
    break;
  }

  if (num_banks == 2) {
    count = 2;
  } else {
    count = 4;
  }

  return count;
}

/* PIC12 */

static unsigned int
id_location_pic12(const struct px *processor)
{
  if (processor->maxrom > 0) {
    /* Sometimes the last hex digit is e due to some calibration
       instruction or something. Therefore we look for the next
       multiple of 16. */
    /* We carry org in the struct px, but return byte address. */
    return ((processor->maxrom + 0xf) & ~0xf) << 1;
  }
  return 0;
}

static int
gp_processor_check_page_pic12(unsigned int org)
{
  return (org >> 9) & 0x3;
}

static int
gp_processor_check_bank_pic12(unsigned int address)
{
  return (address >> 5) & 0x3;
}

static int
gp_processor_set_page_pic12(int num_pages,
                            int page,
                            MemBlock *m,
                            unsigned int address,
                            int use_wreg)

{
  return gp_processor_set_page_pic12_14(num_pages,
                                        page,
                                        m,
                                        address,
                                        use_wreg,
                                        0x400,
                                        0x500,
                                        0xc00,
                                        0x020,
                                        0x3,
                                        5 << 5,
                                        6 << 5);
}

static int
gp_processor_set_bank_pic12(int num_banks,
                            int bank,
                            MemBlock *m,
                            unsigned int address)
{
  return gp_processor_set_bank_pic12_14(num_banks, bank, m, address,
                                        0x400,
                                        0x500,
                                        0x4,
                                        5 << 5,
                                        6 << 5);
}

static int reloc_call_pic12(unsigned int org)
{
  return org & 0xff;
}
static int reloc_goto_pic12(unsigned int org)
{
  return org & 0x1ff;
}
static int reloc_f_pic12(unsigned int address)
{
  return address & 0x1f;
}
static int reloc_tris_pic12(unsigned int address)
{
  /* TODO This is not accurate, for example PIC12F510/16F506 only has
     three bits and allowed values of 6 and 7. MPASM 5.34 has
     Error[126]  : Argument out of range (0000 not between 0005 and 0009)
  */
  return address & 0x1f;
}

/* PIC14 */

static unsigned int
id_location_pic14(const struct px *processor)
{
  if (processor->config_addrs[0] > 0)
    /* I only know of 0x2007 to 0x2000 and 0x8007 to 0x8000 and this
       returns correct for both. */
    /* We carry org in the struct px, but return byte address. */
    return (processor->config_addrs[0] & ~0xFFF) << 1;
  return 0;
}

static int
gp_processor_check_page_pic14(unsigned int org)
{
  return (org >> 11) & 0x3;
}

static int
gp_processor_check_bank_pic14(unsigned int address)
{
  return (address >> 7) & 0x3;
}

static int
gp_processor_set_page_pic14(int num_pages,
                            int page,
                            MemBlock *m,
                            unsigned int address,
                            int use_wreg)
{
  return gp_processor_set_page_pic12_14(num_pages,
                                        page,
                                        m,
                                        address,
                                        use_wreg,
                                        0x1000,
                                        0x1400,
                                        0x3000,
                                        0x0080,
                                        0xa,
                                        3 << 7,
                                        4 << 7);
}

static int
gp_processor_set_bank_pic14(int num_banks,
                            int bank,
                            MemBlock *m,
                            unsigned int address)
{
  return gp_processor_set_bank_pic12_14(num_banks, bank, m, address,
                                        0x1000,
                                        0x1400,
                                        0x3,
                                        5 << 7,
                                        6 << 7);
}

static int reloc_call_pic14(unsigned int org)
{
  return org & 0x7ff;
}
static int reloc_goto_pic14(unsigned int org)
{
  return org & 0x7ff;
}
static int reloc_ibanksel_pic14(unsigned int address)
{
  if (address < 0x100) {
    /* bcf 0x3, 0x7 */
    return 0x1383;
  } else {
    /* bsf 0x3, 0x7 */
    return 0x1783;
  }
}
static int reloc_f_pic14(unsigned int address)
{
  return address & 0x7f;
}
static int reloc_tris_pic14(unsigned int address)
{
  return address & 0x7f;
}

static void patch_strict_pic14(void)
{
  int i, j = 0;
  for (i = 0; i < num_op_16cxx && j < num_op_16cxx_strict_mask; ++i) {
    if (!strcasecmp(op_16cxx[i].name, op_16cxx_strict_mask[j].name)) {
      op_16cxx[i].mask = op_16cxx_strict_mask[j].mask;
      ++j;
    }
  }
}

/* PIC14E */

static int
gp_processor_check_page_pic14e(unsigned int org)
{
  return (org >> 8) & 0x7f;
}

static int
gp_processor_check_bank_pic14e(unsigned int address)
{
  return (address >> 7) & 0x1f;
}

static int
gp_processor_set_page_pic14e(int num_pages,
                             int page,
                             MemBlock *m,
                             unsigned int address,
                             int use_wreg)
{
  unsigned int data;
  if (num_pages == 1) {
    return 0;
  }

  if (use_wreg) {
    /* page is in bits 3:6 of PCLATH */
    data = 0x3000 | (page & 0x74); /* movlw */
    i_memory_put_le(m, address, data);
    data = 0x0080 | 0xa; /* movwf 0xa*/
    i_memory_put_le(m, address + 2, data);
    return 4;
  }
  else {
    data = 0x3180 | (page & 0x7f); /* movlp */
    i_memory_put_le(m, address, data);
    return 2;
  }
}

static int
gp_processor_set_bank_pic14e(int num_banks,
                             int bank,
                             MemBlock *m,
                             unsigned int address)
{
  unsigned int data;
  data = 0x0020 | (bank & 0x1f);
  i_memory_put_le(m, address, data);
  return 2;
}

static int reloc_movlb_pic14e(unsigned int address)
{
  return (address >> 7) & 0xff;
}
static int
reloc_bra_pic14e(gp_section_type *section, unsigned value, unsigned int byte_org)
{
  int offset = value - byte_org/2 - 1;
  if (offset > 0xff || offset < -0x100) {
    gp_warning("relative branch out of range in at %#x of section \"%s\"",
               byte_org << 1,
               section->name);
  }
  return offset & 0x1ff;
}

static const struct insn *
find_insn_pic14e(proc_class_t cls, long int opcode)
{
  int i;
  /* might be from the enganced instruction set */
  for(i = 0; i < num_op_16cxx_enh; i++) {
    if((op_16cxx_enh[i].mask & opcode) == op_16cxx_enh[i].opcode) {
      return &op_16cxx_enh[i];
    }
  }
  for(i = 0; i < num_op_16cxx; i++) {
    if((op_16cxx[i].mask & opcode) == op_16cxx[i].opcode) {
      return &op_16cxx[i];
    }
  }
  return NULL;
}

/* PIC16 */

static int
gp_processor_check_page_pic16(unsigned int org)
{
  return (org >> 8) & 0xff;
}


static int
gp_processor_check_bank_pic16(unsigned int address)
{
  if ((address & 0xFF) < 0x20)
    return (address >> 8) & 0xff;
  else
    /* 0x200 turns MOVLB to MOVLR for setting GPR RAM bank in
       set_bank */
    return 0x200 + ((address >> 8) & 0xff);
}


static int
gp_processor_set_page_pic16(int num_pages,
                            int page,
                            MemBlock *m,
                            unsigned int address,
                            int use_wreg)
{
  unsigned int data;
  /* movlw <page> */
  data = 0xb000 | (page & 0xff);
  i_memory_put_le(m, address, data);
  /* movwf 0x3 */
  data = 0x0100 | 0x3;
  i_memory_put_le(m, address + 2, data);
  return 4;
}

static int
gp_processor_set_bank_pic16(int num_banks,
                            int bank,
                            MemBlock *m,
                            unsigned int address)
{
  /* movlb bank */
  i_memory_put_le(m, address,
                  0xb800 | bank);
  return 2;
}

static int reloc_call_pic16(unsigned int org)
{
  return org & 0x1fff;
}
static int reloc_goto_pic16(unsigned int org)
{
  return org & 0x1fff;
}
static int reloc_ibanksel_pic16(unsigned int address)
{
  return 0xb800 | gp_processor_check_bank_pic16(address);
}
static int reloc_f_pic16(unsigned int address)
{
  return address & 0xff;
}

/* PIC16E */

static unsigned int
id_location_pic16e(const struct px *processor)
{
  return IDLOC0;
}

static int
gp_processor_set_bank_pic16e(int num_banks,
                             int bank,
                             MemBlock *m,
                             unsigned int address)
{
  /* movlb bank */
  i_memory_put_le(m, address,
                  0x0100 | (bank & 0xff));
  return 2;
}

static int reloc_call_pic16e(unsigned int org)
{
  return (org >> 1) & 0xff;
}
static int reloc_goto_pic16e(unsigned int org)
{
  return (org >> 1) & 0xff;
}
static int reloc_movlb_pic16e(unsigned int address)
{
  /* The upper byte of the symbol is used for the BSR.  This is inconsistent
     with the datasheet and the assembler, but is done to maintain
     compatibility with mplink. */
  return (address >> 8) & 0xff;
}
static int
reloc_bra_pic16e(gp_section_type *section, unsigned value, unsigned int byte_org)
{
  int offset = ((int)(value - byte_org - 2)) >> 1;
  if (offset > 0x3ff || offset < -0x400) {
    gp_warning("relative branch out of range in at %#x of section \"%s\"",
               byte_org,
               section->name);
  }
  return offset & 0x7ff;
}

static const struct insn *
find_insn_pic16e(proc_class_t cls, long int opcode)
{
  int i;
  if (gp_decode_mnemonics) {
    for(i = 0; i < num_op_18cxx_sp; i++) {
      if((op_18cxx_sp[i].mask & opcode) == op_18cxx_sp[i].opcode) {
        return &op_18cxx_sp[i];
      }
    }
  }
  for(i = 0; i < num_op_18cxx; i++) {
    if((op_18cxx[i].mask & opcode) == op_18cxx[i].opcode) {
      return &op_18cxx[i];
    }
  }
  if (gp_decode_extended) {
    /* might be from the extended instruction set */
    for(i = 0; i < num_op_18cxx_ext; i++) {
      if((op_18cxx_ext[i].mask & opcode) == op_18cxx_ext[i].opcode) {
        return &op_18cxx_ext[i];
      }
    }
  }
  return NULL;
}

const struct proc_class proc_class_eeprom8 = {
  -1,                                   /* retlw */
  8,                                    /* rom_width */
  0,                                    /* org_to_byte_shift */
  0,                                    /* bank_mask */
  (1<<8)-1,                             /* core_size */
  0,                                    /* id_location */
  gp_processor_check_bank_unsupported,
  gp_processor_set_bank_unsupported,
  gp_processor_check_page_unsupported,
  gp_processor_set_page_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_bra_unsupported,
  NULL, NULL,
  NULL,
  i_memory_get_le, i_memory_put_le,
  NULL,
};

const struct proc_class proc_class_eeprom16 = {
  -1,                                   /* retlw */
  16,                                   /* rom_width */
  0,                                    /* org_to_byte_shift */
  0,                                    /* bank_mask */
  (1<<16)-1,                            /* core_size */
  0,                                    /* id_location */
  gp_processor_check_bank_unsupported,
  gp_processor_set_bank_unsupported,
  gp_processor_check_page_unsupported,
  gp_processor_set_page_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_bra_unsupported,
  NULL, NULL,
  NULL,
  i_memory_get_be, i_memory_put_be,
  NULL,
};

const struct proc_class proc_class_generic = {
  -1,                                   /* retlw */
  12,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  ~0x1fu,                               /* bank_mask */
  (1<<12)-1,                            /* core_size */
  id_location_pic12,                    /* id_location */
  gp_processor_check_bank_pic12,
  gp_processor_set_bank_pic12,
  gp_processor_check_page_pic12,
  gp_processor_set_page_pic12,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_unsupported,
  reloc_bra_unsupported,
  NULL, NULL,
  NULL,
  i_memory_get_le, i_memory_put_le,
  NULL,
};

const struct proc_class proc_class_pic12 = {
  0x800,                                /* retlw */
  12,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  ~0x1fu,                               /* bank_mask */
  (1<<12)-1,                            /* core_size */
  id_location_pic12,                    /* id_location */
  gp_processor_check_bank_pic12,
  gp_processor_set_bank_pic12,
  gp_processor_check_page_pic12,
  gp_processor_set_page_pic12,
  reloc_call_pic12,
  reloc_goto_pic12,
  reloc_unsupported,
  reloc_f_pic12,
  reloc_tris_pic12,
  reloc_unsupported,
  reloc_bra_unsupported,
  op_12c5xx, &num_op_12c5xx,
  find_insn_generic,
  i_memory_get_le, i_memory_put_le,
  NULL,
};

const struct proc_class proc_class_sx = {
  0x800,                                /* retlw */
  12,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  ~0x1fu,                               /* bank_mask */
  (1<<12)-1,                            /* core_size */
  id_location_pic12,                    /* id_location */
  gp_processor_check_bank_pic12,
  gp_processor_set_bank_pic12,
  gp_processor_check_page_pic12,
  gp_processor_set_page_pic12,
  reloc_call_pic12,
  reloc_goto_pic12,
  reloc_unsupported,
  reloc_f_pic12,
  reloc_tris_pic12,
  reloc_unsupported,
  reloc_bra_unsupported,
  op_sx, &num_op_sx,
  find_insn_generic,
  i_memory_get_le, i_memory_put_le,
  NULL,
};

const struct proc_class proc_class_pic14 = {
  0x3400,                               /* retlw */
  14,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  ~0x7fu,                               /* bank_mask */
  (1<<14)-1,                            /* core_size */
  id_location_pic14,                    /* id_location */
  gp_processor_check_bank_pic14,
  gp_processor_set_bank_pic14,
  gp_processor_check_page_pic14,
  gp_processor_set_page_pic14,
  reloc_call_pic14,
  reloc_goto_pic14,
  reloc_ibanksel_pic14,
  reloc_f_pic14,
  reloc_tris_pic14,
  reloc_unsupported,
  reloc_bra_unsupported,
  op_16cxx, &num_op_16cxx,
  find_insn_generic,
  i_memory_get_le, i_memory_put_le,
  patch_strict_pic14,
};

const struct proc_class proc_class_pic14e = {
  0x3400,                               /* retlw */
  14,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  0,                                    /* bank_mask */
  (1<<14)-1,                            /* core_size */
  id_location_pic14,                    /* id_location */
  gp_processor_check_bank_pic14e,
  gp_processor_set_bank_pic14e,
  gp_processor_check_page_pic14e,
  gp_processor_set_page_pic14e,
  reloc_call_pic14,
  reloc_goto_pic14,
  reloc_ibanksel_pic14,
  reloc_f_pic14,
  reloc_tris_pic14,
  reloc_movlb_pic14e,
  reloc_bra_pic14e,
  op_16cxx, &num_op_16cxx,
  find_insn_pic14e,
  i_memory_get_le, i_memory_put_le,
  patch_strict_pic14,
};

const struct proc_class proc_class_pic16 = {
  0xb600,                               /* retlw */
  16,                                   /* rom_width */
  1,                                    /* org_to_byte_shift */
  ~0xffu,                               /* bank_mask */
  (1<<16)-1,                            /* core_size */
  0,                                    /* id_location */
  gp_processor_check_bank_pic16,
  gp_processor_set_bank_pic16,
  gp_processor_check_page_pic16,
  gp_processor_set_page_pic16,
  reloc_call_pic16,
  reloc_goto_pic16,
  reloc_ibanksel_pic16,
  reloc_f_pic16,
  reloc_unsupported,
  reloc_unsupported,
  reloc_bra_unsupported,
  op_17cxx, &num_op_17cxx,
  find_insn_generic,
  i_memory_get_le, i_memory_put_le,
  NULL,
};

const struct proc_class proc_class_pic16e = {
  0x0c00,                               /* retlw */
  8,                                    /* rom_width */
  0,                                    /* org_to_byte_shift */
  0,                                    /* bank_mask */
  (1<<16)-1,                            /* core_size */
  id_location_pic16e,                   /* id_location */
  gp_processor_check_bank_pic16,        /* Same as for pic16 */
  gp_processor_set_bank_pic16e,
  gp_processor_check_page_unsupported,
  gp_processor_set_page_unsupported,
  reloc_call_pic16e,
  reloc_goto_pic16e,
  reloc_unsupported,
  reloc_f_pic16,        /* Same as for pic16 */
  reloc_unsupported,
  reloc_movlb_pic16e,
  reloc_bra_pic16e,
  op_18cxx, &num_op_18cxx,
  find_insn_pic16e,
  i_memory_get_le, i_memory_put_le,
  NULL,
};
