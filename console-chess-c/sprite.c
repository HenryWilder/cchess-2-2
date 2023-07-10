#include "sprite.h"

// 0 = Fill
// 1 = Shade
// 2 = Outline
// 3 = Shine

HBRUSH spriteBrushes[2][NUM_TEAM_SPRITE_BRUSHES];

// Pawn /////////////
//                //0
//                //1
//                //2
//      1111      //3
//     100331     //4
//     200331     //5
//     200001     //6
//     210002     //7
//      2131      //8
//     210032     //9
//      2132      //A
//      2032      //B
//      2032      //C
//     210302     //D
//    21000332    //E
//    22222222    //F
/////////////////////
//0123456789ABCDEF//

const SpritePart pawnOutlineParts[] = {
    {.x = { 0x6, 0x9 }, .y = { 0x3, 0xF }, },
    {.x = { 0x5, 0xA }, .y = { 0x4, 0x7 }, },
    {.x = { 0x5, 0xA }, .y = { 0x9, 0x9 }, },
    {.x = { 0x5, 0xA }, .y = { 0xD, 0xD }, },
    {.x = { 0x4, 0xB }, .y = { 0xE, 0xF }, },
};
const SpritePart pawnFillParts[] = {
    {.x = { 0x6, 0x9 }, .y = { 0x4, 0x7 }, },
    {.x = { 0x7, 0x8 }, .y = { 0x9, 0xE }, },
    {.x = { 0x6, 0x9 }, .y = { 0xE, 0xE }, },
};
const SpritePart pawnShadeParts[] = {
    {.x = { 0x6, 0x9 }, .y = { 0x3, 0x3 }, },
    {.x = { 0x6, 0x9 }, .y = { 0x3, 0x3 }, },
    {.x = { 0x5, 0x5 }, .y = { 0x4, 0x4 }, },
    {.x = { 0xA, 0xA }, .y = { 0x4, 0x6 }, },
    {.x = { 0x6, 0x6 }, .y = { 0x7, 0x7 }, },
    {.x = { 0x7, 0x9 }, .y = { 0x8, 0x8 }, },
    {.x = { 0x6, 0x6 }, .y = { 0x9, 0x9 }, },
};
const SpritePart pawnShineParts[] = {
    {.x = { 0x8, 0x9 }, .y = { 0x4, 0x5 }, },
    {.x = { 0x8, 0x8 }, .y = { 0x8, 0x8 }, },
};

const Sprite pawn = {
    .numOutlineParts = _countof(pawnOutlineParts),
    .numFillParts    = _countof(pawnFillParts),
    .numShadeParts   = _countof(pawnShadeParts),
    .numShineParts   = _countof(pawnShineParts),

    pawnOutlineParts,
    pawnFillParts,
    pawnShadeParts,
    pawnShineParts,
};

// Rook /////////////
//                //0
//                //1
//   2212222122   //2
//   2112002132   //3
//   2122002232   //4
//   2100000032   //5
//    21000002    //6
//     211012     //7
//     210032     //8
//     210032     //9
//     210032     //A
//    21100332    //B
//    21003332    //C
//   2111110032   //D
//   2110000332   //E
//   2222222222   //F
/////////////////////
//0123456789ABCDEF//

const SpritePart rookOutlineParts[] = {
    {0}
};
const SpritePart rookFillParts[] = {
    {0}
};
const SpritePart rookShadeParts[] = {
    {0}
};
const SpritePart rookShineParts[] = {
    {0}
};

const Sprite rook = {
    .numOutlineParts = _countof(rookOutlineParts),
    .numFillParts    = _countof(rookFillParts),
    .numShadeParts   = _countof(rookShadeParts),
    .numShineParts   = _countof(rookShineParts),

    rookOutlineParts,
    rookFillParts,
    rookShadeParts,
    rookShineParts,
};

// Knight ///////////
//      22        //0
//     2101       //1
//    2103122222  //2
//   210003311332 //3
//   210000000012 //4
//   210010000002 //5
//    2101000022  //6
//    21001112    //7
//     210331     //8
//      210331    //9
//      2100332   //A
//      2100302   //B
//     21000012   //C
//    21100012    //D
//   2110000331   //E
//   2222222222   //F
/////////////////////
//0123456789ABCDEF//

const SpritePart knightOutlineParts[] = {
    {0}
};
const SpritePart knightFillParts[] = {
    {0}
};
const SpritePart knightShadeParts[] = {
    {0}
};
const SpritePart knightShineParts[] = {
    {0}
};

const Sprite knight = {
    .numOutlineParts = _countof(knightOutlineParts),
    .numFillParts    = _countof(knightFillParts),
    .numShadeParts   = _countof(knightShadeParts),
    .numShineParts   = _countof(knightShineParts),

    knightOutlineParts,
    knightFillParts,
    knightShadeParts,
    knightShineParts,
};

// Bishop ///////////
//       22       //0
//      2032      //1
//     211021     //2
//    2100021     //3
//    21002032    //4
//    21000032    //5
//     210002     //6
//      2112      //7
//     210032     //8
//      2132      //9
//      2032      //A
//     210032     //B
//     210032     //C
//    21100332    //D
//   2110000332   //E
//   2222222222   //F
/////////////////////
//0123456789ABCDEF//

const SpritePart bishopOutlineParts[] = {
    {0}
};
const SpritePart bishopFillParts[] = {
    {0}
};
const SpritePart bishopShadeParts[] = {
    {0}
};
const SpritePart bishopShineParts[] = {
    {0}
};

const Sprite bishop = {
    .numOutlineParts = _countof(bishopOutlineParts),
    .numFillParts    = _countof(bishopFillParts),
    .numShadeParts   = _countof(bishopShadeParts),
    .numShineParts   = _countof(bishopShineParts),

    bishopOutlineParts,
    bishopFillParts,
    bishopShadeParts,
    bishopShineParts,
};

// Queen ////////////
//       22       //0
//   2212032122   //1
//   2022212202   //2
//   2100000102   //3
//    21110102    //4
//     210002     //5
//     210012     //6
//      2112      //7
//     210032     //8
//      2132      //9
//      2032      //A
//     210032     //B
//     210032     //C
//    21110332    //D
//   2110000332   //E
//   2222222222   //F
/////////////////////
//0123456789ABCDEF//

const SpritePart queenOutlineParts[] = {
    {0}
};
const SpritePart queenFillParts[] = {
    {0}
};
const SpritePart queenShadeParts[] = {
    {0}
};
const SpritePart queenShineParts[] = {
    {0}
};

const Sprite queen = {
    .numOutlineParts = _countof(queenOutlineParts),
    .numFillParts    = _countof(queenFillParts),
    .numShadeParts   = _countof(queenShadeParts),
    .numShineParts   = _countof(queenShineParts),

    queenOutlineParts,
    queenFillParts,
    queenShadeParts,
    queenShineParts,
};

// King /////////////
//       22       //0
//      1221      //1
//    12200221    //2
//    21003332    //3
//    21000012    //4
//     210002     //5
//     210012     //6
//      2112      //7
//     210032     //8
//      2132      //9
//      2032      //A
//     210032     //B
//     210032     //C
//    21110332    //D
//   2110000332   //E
//   2222222222   //F
/////////////////////
//0123456789ABCDEF//

const SpritePart kingOutlineParts[] = {
    {0}
};
const SpritePart kingFillParts[] = {
    {0}
};
const SpritePart kingShadeParts[] = {
    {0}
};
const SpritePart kingShineParts[] = {
    {0}
};

const Sprite king = {
    .numOutlineParts = _countof(kingOutlineParts),
    .numFillParts    = _countof(kingFillParts),
    .numShadeParts   = _countof(kingShadeParts),
    .numShineParts   = _countof(kingShineParts),

    kingOutlineParts,
    kingFillParts,
    kingShadeParts,
    kingShineParts,
};

const Sprite* unitSprites[] = { NULL, &pawn, &rook, &knight, &bishop, &queen, &king, };

// ArrowL ///////////
//       22       //0
//      202       //1
//     2002       //2
//    20002       //3
//   200002       //4
//  2000002       //5
// 20000002       //6
//200000002       //7
//200000002       //8
// 20000002       //9
//  2000002       //A
//   200002       //B
//    20002       //C
//     2002       //D
//      202       //E
//       22       //F
/////////////////////
//0123456789ABCDEF//

const SpritePart arrowLOutlineParts[] = {
    {0}
};
const SpritePart arrowLFillParts[] = {
    {0}
};
const SpritePart arrowLShadeParts[] = {
    {0}
};
const SpritePart arrowLShineParts[] = {
    {0}
};

const Sprite arrowL = {
    .numOutlineParts = _countof(arrowLOutlineParts),
    .numFillParts    = _countof(arrowLFillParts),
    .numShadeParts   = _countof(arrowLShadeParts),
    .numShineParts   = _countof(arrowLShineParts),

    arrowLOutlineParts,
    arrowLFillParts,
    arrowLShadeParts,
    arrowLShineParts,
};

// ArrowR ///////////
//       22       //0
//       202      //1
//       2002     //2
//       20002    //3
//       200002   //4
//       2000002  //5
//       20000002 //6
//       200000002//7
//       200000002//8
//       20000002 //9
//       2000002  //A
//       200002   //B
//       20002    //C
//       2002     //D
//       202      //E
//       22       //F
/////////////////////
//0123456789ABCDEF//

const SpritePart arrowROutlineParts[] = {
    {0}
};
const SpritePart arrowRFillParts[] = {
    {0}
};
const SpritePart arrowRShadeParts[] = {
    {0}
};
const SpritePart arrowRShineParts[] = {
    {0}
};

const Sprite arrowR = {
    .numOutlineParts = _countof(arrowROutlineParts),
    .numFillParts    = _countof(arrowRFillParts),
    .numShadeParts   = _countof(arrowRShadeParts),
    .numShineParts   = _countof(arrowRShineParts),

    arrowROutlineParts,
    arrowRFillParts,
    arrowRShadeParts,
    arrowRShineParts,
};

const Sprite* arrowSprites[] = { &arrowL, &arrowR, };