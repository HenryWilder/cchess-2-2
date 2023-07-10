#include "sprite.h"

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

const SpritePart pawnParts[] = {
    { .brushIndex = 0, .x0 = 0x6, 0x9, .y0 = 0x3, 0xF, },
    { .brushIndex = 0, .x0 = 0x5, 0xA, .y0 = 0x4, 0x7, },
    { .brushIndex = 0, .x0 = 0x5, 0xA, .y0 = 0x9, 0x9, },
    { .brushIndex = 0, .x0 = 0x5, 0xA, .y0 = 0xD, 0xD, },
    { .brushIndex = 0, .x0 = 0x4, 0xB, .y0 = 0xE, 0xF, },
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

const SpritePart rookParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
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

const SpritePart knightParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
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

const SpritePart bishopParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
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

const SpritePart queenParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
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

const SpritePart kingParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
};

const Sprite null   = {                     0,         NULL };
const Sprite pawn   = { _countof(  pawnParts),   &pawnParts };
const Sprite rook   = { _countof(  rookParts),   &rookParts };
const Sprite knight = { _countof(knightParts), &knightParts };
const Sprite bishop = { _countof(bishopParts), &bishopParts };
const Sprite queen  = { _countof( queenParts),  &queenParts };
const Sprite king   = { _countof(  kingParts),   &kingParts };

const Sprite* unitSprites[] = { &null, &pawn, &rook, &knight, &bishop, &queen, &king, };

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

const SpritePart arrowLParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
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

const SpritePart arrowRParts[] = {
    { .brushIndex = 0, .x0 = 0x0, .x1 = 0x0, .y0 = 0x0, .y1 = 0x0, },
};

const Sprite arrowL = { _countof(arrowLParts), &arrowLParts };
const Sprite arrowR = { _countof(arrowRParts), &arrowRParts };

const Sprite* arrowSprites[] = { &arrowL, &arrowR, };