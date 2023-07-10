#include "sprite.h"

// Pawn ////////////
//                //
//                //
//                //
//      1111      //
//     100331     //
//     200331     //
//     200001     //
//     210002     //
//      2131      //
//     210032     //
//      2132      //
//      2032      //
//      2032      //
//     210302     //
//    21000332    //
//    22222222    //
////////////////////

const SpritePart pawnParts[] = {
    { .brushIndex = 1, .x = 6, .y = 3, .w = 4, .h = 1, }
};

// Rook ////////////
//                //
//                //
//   2212222122   //
//   2112002132   //
//   2122002232   //
//   2100000032   //
//    21000002    //
//     211012     //
//     210032     //
//     210032     //
//     210032     //
//    21100332    //
//    21003332    //
//   2111110032   //
//   2110000332   //
//   2222222222   //
////////////////////

const SpritePart rookParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

// Knight //////////
//      22        //
//     2101       //
//    2103122222  //
//   210003311332 //
//   210000000012 //
//   210010000002 //
//    2101000022  //
//    21001112    //
//     210331     //
//      210331    //
//      2100332   //
//      2100302   //
//     21000012   //
//    21100012    //
//   2110000331   //
//   2222222222   //
////////////////////

const SpritePart knightParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

// Bishop //////////
//       22       //
//      2032      //
//     211021     //
//    2100021     //
//    21002032    //
//    21000032    //
//     210002     //
//      2112      //
//     210032     //
//      2132      //
//      2032      //
//     210032     //
//     210032     //
//    21100332    //
//   2110000332   //
//   2222222222   //
////////////////////

const SpritePart bishopParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

// Queen ///////////
//       22       //
//   2212032122   //
//   2022212202   //
//   2100000102   //
//    21110102    //
//     210002     //
//     210012     //
//      2112      //
//     210032     //
//      2132      //
//      2032      //
//     210032     //
//     210032     //
//    21110332    //
//   2110000332   //
//   2222222222   //
////////////////////

const SpritePart queenParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

// King ////////////
//       22       //
//      1221      //
//    12200221    //
//    21003332    //
//    21000012    //
//     210002     //
//     210012     //
//      2112      //
//     210032     //
//      2132      //
//      2032      //
//     210032     //
//     210032     //
//    21110332    //
//   2110000332   //
//   2222222222   //
////////////////////

const SpritePart kingParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

const Sprite null   = {                     0,         NULL };
const Sprite pawn   = { _countof(  pawnParts),   &pawnParts };
const Sprite rook   = { _countof(  rookParts),   &rookParts };
const Sprite knight = { _countof(knightParts), &knightParts };
const Sprite bishop = { _countof(bishopParts), &bishopParts };
const Sprite queen  = { _countof( queenParts),  &queenParts };
const Sprite king   = { _countof(  kingParts),   &kingParts };

const Sprite* units[] = { &null, &pawn, &rook, &knight, &bishop, &queen, &king, };

// ArrowL //////////
//       22       //
//      202       //
//     2002       //
//    20002       //
//   200002       //
//  2000002       //
// 20000002       //
//200000002       //
//200000002       //
// 20000002       //
//  2000002       //
//   200002       //
//    20002       //
//     2002       //
//      202       //
//       22       //
////////////////////

const SpritePart arrowLParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

// ArrowR //////////
//       22       //
//       202      //
//       2002     //
//       20002    //
//       200002   //
//       2000002  //
//       20000002 //
//       200000002//
//       200000002//
//       20000002 //
//       2000002  //
//       200002   //
//       20002    //
//       2002     //
//       202      //
//       22       //
////////////////////

const SpritePart arrowRParts[] = {
    { .brushIndex = , .x = , .y = , .w = , .h = , }
};

const Sprite arrowL = { _countof(arrowLParts), &arrowLParts };
const Sprite arrowR = { _countof(arrowRParts), &arrowRParts };

const Sprite* arrows[] = { &arrowL, &arrowR, };