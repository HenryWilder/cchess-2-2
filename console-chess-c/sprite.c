#include "sprite.h"

#if 1
// Single
#define S(x)   { 0x##x, 0x##x }
// Pair
#define P(x,y) { 0x##x, 0x##y }
#else
#define A 0xA
#define B 0xB
#define C 0xC
#define D 0xD
#define E 0xE
#define F 0xF
// Single
#define S(x)   { x, x }
// Pair
#define P(x,y) { x, y }
#endif

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
    {.x = P(6,9), .y = P(3,F), },
    {.x = P(5,A), .y = P(4,7), },
    {.x = P(5,A), .y = S(9),   },
    {.x = P(5,A), .y = S(D),   },
    {.x = P(4,B), .y = P(E,F), },
};
const SpritePart pawnFillParts[] = {
    {.x = P(6,9), .y = P(4,7), },
    {.x = P(7,8), .y = P(8,E), },
    {.x = P(6,9), .y = S(9),   },
    {.x = P(6,9), .y = S(D),   },
    {.x = P(5,A), .y = S(E),   },
};
const SpritePart pawnShadeParts[] = {
    {.x = P(6,9), .y = S(3),   },
    {.x = S(5),   .y = S(4),   },
    {.x = S(A),   .y = P(4,6), },
    {.x = S(6),   .y = S(7),   },
    {.x = S(7),   .y = S(8),   },
    {.x = S(6),   .y = S(9),   },
    {.x = S(7),   .y = S(A),   },
    {.x = S(6),   .y = S(D),   },
    {.x = S(5),   .y = S(E),   },
};
const SpritePart pawnShineParts[] = {
    {.x = P(8,9), .y = P(4,5), },
    {.x = S(8),   .y = S(8),   },
    {.x = S(9),   .y = S(9),   },
    {.x = S(8),   .y = P(A,D), },
    {.x = P(9,A), .y = S(E),   },
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
    {.x = P(3,C), .y = P(2,5), },
    {.x = P(4,B), .y = S(6),   },
    {.x = P(5,A), .y = P(7,A), },
    {.x = P(4,B), .y = P(B,C), },
    {.x = P(3,C), .y = P(D,F), },
};
const SpritePart rookFillParts[] = {
    {.x = S(4),   .y = P(3,4), },
    {.x = P(7,8), .y = P(3,4), },
    {.x = S(B),   .y = P(3,4), },
    {.x = P(4,B), .y = S(5),   },
    {.x = P(5,A), .y = S(6),   },
    {.x = P(6,9), .y = P(7,A), },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = P(D,E), },
};
const SpritePart rookShadeParts[] = {
    {.x = S(5), .y = P(2,3), },
    {.x = S(A), .y = P(2,3), },
    {.x = S(4), .y = P(3,5), },
};
const SpritePart rookShineParts[] = {
    {.x = S(5), .y = P(2,3), },
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
    {.x = P(6,7), .y = S(0),   },
    {.x = P(5,8), .y = S(1),   },
    {.x = P(4,D), .y = S(2),   },
    {.x = P(3,E), .y = P(3,5), },
    {.x = P(4,D), .y = S(6),   },
    {.x = P(4,B), .y = S(7),   },
    {.x = P(5,A), .y = S(8),   },
    {.x = P(6,B), .y = S(9),   },
    {.x = P(6,C), .y = P(A,B), },
    {.x = P(5,C), .y = S(C),   },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
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
    {.x = P(7,8), .y = S(0),   },
    {.x = P(6,9), .y = P(1,A), },
    {.x = P(5,A), .y = P(2,6), },
    {.x = S(4),   .y = P(3,5), },
    {.x = S(B),   .y = P(4,5), },
    {.x = P(5,A), .y = S(8),   },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
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
    {.x = P(7,8), .y = S(0),   },
    {.x = P(3,C), .y = P(1,3), },
    {.x = P(4,B), .y = S(4),   },
    {.x = P(5,A), .y = P(5,6), },
    {.x = P(6,9), .y = P(7,A), },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
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
    {.x = P(7,8), .y = S(0),   },
    {.x = P(6,9), .y = S(1),   },
    {.x = P(4,B), .y = P(2,4), },
    {.x = P(5,A), .y = P(5,6), },
    {.x = P(6,9), .y = P(7,A), },
    {.x = P(5,A), .y = S(8),   },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
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