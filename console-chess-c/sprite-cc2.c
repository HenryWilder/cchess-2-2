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

// # = Outline
// + = Shade
// - = Fill
// . = Shine

HBRUSH spriteBrushes[2][NUM_TEAM_SPRITE_BRUSHES];

// Pawn /////////////  |  // Outline //////////  // Fill /////////////  // Shade ////////////  // Shine ////////////
//                //0  |  //                //0  //                //0  //                //0  //                //0
//                //1  |  //                //1  //                //1  //                //1  //                //1
//                //2  |  //                //2  //                //2  //                //2  //                //2
//      ++++      //3  |  //      ####      //3  //                //3  //      ++++      //3  //                //3
//     +--..+     //4  |  //     ######     //4  //      ----      //4  //     +    +     //4  //        ..      //4
//     #--..+     //5  |  //     ######     //5  //      ----      //5  //          +     //5  //        ..      //5
//     #----+     //6  |  //     ######     //6  //      ----      //6  //          +     //6  //                //6
//     #+---#     //7  |  //     ######     //7  //      ----      //7  //      +         //7  //                //7
//      #+.+      //8  |  //      ####      //8  //       --       //8  //       + +      //8  //        .       //8
//     #+--.#     //9  |  //     ######     //9  //      ----      //9  //      +         //9  //         .      //9
//      #+.#      //A  |  //      ####      //A  //       --       //A  //       +        //A  //        .       //A
//      #-.#      //B  |  //      ####      //B  //       --       //B  //                //B  //        .       //B
//      #-.#      //C  |  //      ####      //C  //       --       //C  //                //C  //        .       //C
//     #+-.-#     //D  |  //     ######     //D  //      ----      //D  //      +         //D  //        .       //D
//    #+---..#    //E  |  //    ########    //E  //     ------     //E  //     +          //E  //         ..     //E
//    ########    //F  |  //    ########    //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

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

// Rook /////////////  |  // Outline //////////  // Fill /////////////  // Shade ////////////  // Shine ////////////
//                //0  |  //                //0  //                //0  //                //0  //                //0
//                //1  |  //                //1  //                //1  //                //1  //                //1
//   ##+####+##   //2  |  //   ##########   //2  //     -    -     //2  //     +    +     //2  //                //2
//   #++#--#+.#   //3  |  //   ##########   //3  //    -- -- --    //3  //    ++    +     //3  //           .    //3
//   #+##--##.#   //4  |  //   ##########   //4  //    -  --  -    //4  //    +           //4  //           .    //4
//   #+------.#   //5  |  //   ##########   //5  //    --------    //5  //    +           //5  //           .    //5
//    #+-----#    //6  |  //    ########    //6  //     ------     //6  //     +          //6  //                //6
//     #++-+#     //7  |  //     ######     //7  //      ----      //7  //      ++ +      //7  //                //7
//     #+--.#     //8  |  //     ######     //8  //      ----      //8  //      +         //8  //         .      //8
//     #+--.#     //9  |  //     ######     //9  //      ----      //9  //      +         //9  //         .      //9
//     #+--.#     //A  |  //     ######     //A  //      ----      //A  //      +         //A  //         .      //A
//    #++--..#    //B  |  //    ########    //B  //      ----      //B  //     ++         //B  //         ..     //B
//    #+--...#    //C  |  //    ########    //C  //     ------     //C  //     +          //C  //        ...     //C
//   #+++++--.#   //D  |  //   ##########   //D  //    --------    //D  //    +++++       //D  //           .    //D
//   #++----..#   //E  |  //   ##########   //E  //    --------    //E  //    ++          //E  //          ..    //E
//   ##########   //F  |  //   ##########   //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

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
    {.x = S(5),   .y = P(2,3), },
    {.x = S(A),   .y = P(2,3), },
    {.x = S(4),   .y = P(3,5), },
    {.x = S(5),   .y = S(6),   },
    {.x = S(6),   .y = P(7,B), },
    {.x = S(5),   .y = P(B,E), },
    {.x = P(6,8), .y = S(D),   },
    {.x = S(4),   .y = P(D,E), },
    {.x = S(4),   .y = P(D,E), },
    {.x = S(9),   .y = S(7),   },
};
const SpritePart rookShineParts[] = {
    {.x = S(B),   .y = P(3,5), },
    {.x = S(9),   .y = P(8,C), },
    {.x = S(A),   .y = P(B,C), },
    {.x = S(8),   .y = S(C),   },
    {.x = S(B),   .y = P(D,E), },
    {.x = S(A),   .y = S(E),   },
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

// Knight ///////////  |  // Outline //////////  // Fill /////////////  // Shade ////////////  // Shine ////////////
//      ##        //0  |  //      ##        //0  //                //0  //                //0  //                //0
//     #+-+       //1  |  //     ####       //1  //      ---       //1  //      + +       //1  //                //1
//    #+-.+#####  //2  |  //    ##########  //2  //     ----       //2  //     +  +       //2  //       .        //2
//   #+---..++..# //3  |  //   ############ //3  //    ----------  //3  //    +     ++    //3  //        ..  ..  //3
//   #+--------+# //4  |  //   ############ //4  //    ----------  //4  //    +        +  //4  //                //4
//   #+--+------# //5  |  //   ############ //5  //    ----------  //5  //    +  +        //5  //                //5
//    #+-+----##  //6  |  //    ##########  //6  //     -------    //6  //     + +        //6  //                //6
//    #+--+++#    //7  |  //    ########    //7  //     ------     //7  //     +  +++     //7  //                //7
//     #+-..+     //8  |  //     ######     //8  //      -----     //8  //      +   +     //8  //        ..      //8
//      #+-..+    //9  |  //      ######    //9  //       -----    //9  //       +   +    //9  //         ..     //9
//      #+--..#   //A  |  //      #######   //A  //       -----    //A  //       +        //A  //          ..    //A
//      #+--.-#   //B  |  //      #######   //B  //       -----    //B  //       +        //B  //          .     //B
//     #+----+#   //C  |  //     ########   //C  //      ------    //C  //      +    +    //C  //                //C
//    #++---+#    //D  |  //    ########    //D  //     ------     //D  //     ++   +     //D  //                //D
//   #++----..+   //E  |  //   ##########   //E  //    ---------   //E  //    ++      +   //E  //          ..    //E
//   ##########   //F  |  //   ##########   //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

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
    {.x = P(6,8), .y = S(1),   },
    {.x = P(5,8), .y = S(2),   },
    {.x = P(4,D), .y = P(3,5), },
    {.x = P(5,B), .y = S(6),   },
    {.x = P(5,A), .y = S(7),   },
    {.x = P(6,A), .y = S(8),   },
    {.x = P(7,B), .y = P(9,B), },
    {.x = P(6,B), .y = S(C),   },
    {.x = P(5,A), .y = S(D),   },
    {.x = P(4,C), .y = S(E),   },
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

// Bishop ///////////  |  // Outline //////////  // Fill ////////////  // Shade /////////////  // Shine ////////////
//       ##       //0  |  //       ##       //0  //                //0  //                //0  //                //0
//      #-.#      //1  |  //      ####      //1  //       --       //1  //                //1  //        .       //1
//     #++-#+     //2  |  //     ######     //2  //      --- -     //2  //      ++  +     //2  //                //2
//    #+---#+     //3  |  //    #######     //3  //     ---- -     //3  //     +    +     //3  //                //3
//    #+--#-.#    //4  |  //    ########    //4  //     --- --     //4  //     +          //4  //          .     //4
//    #+----.#    //5  |  //    ########    //5  //     ------     //5  //     +          //5  //          .     //5
//     #+---#     //6  |  //     ######     //6  //      ----      //6  //      +         //6  //                //6
//      #++#      //7  |  //      ####      //7  //       --       //7  //       ++       //7  //                //7
//     #+--.#     //8  |  //     ######     //8  //      ----      //8  //      +         //8  //         .      //8
//      #+.#      //9  |  //      ####      //9  //       --       //9  //       +        //9  //        .       //9
//      #-.#      //A  |  //      ####      //A  //       --       //A  //                //A  //        .       //A
//     #+--.#     //B  |  //     ######     //B  //      ----      //B  //      +         //B  //         .      //B
//     #+--.#     //C  |  //     ######     //C  //      ----      //C  //      +         //C  //         .      //C
//    #++--..#    //D  |  //    ########    //D  //     ------     //D  //     ++         //D  //         ..     //D
//   #++----..#   //E  |  //   ##########   //E  //    --------    //E  //    ++          //E  //          ..    //E
//   ##########   //F  |  //   ##########   //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

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
    {.x = P(7,8), .y = S(1),   },
    {.x = P(6,8), .y = S(2),   },
    {.x = S(A),   .y = P(2,4), },
    {.x = S(9),   .y = S(4),   },
    {.x = P(5,8), .y = S(3),   },
    {.x = P(5,7), .y = S(4),   },
    {.x = P(5,A), .y = S(5),   },
    {.x = P(6,9), .y = S(6),   },
    {.x = P(7,8), .y = P(7,A), },
    {.x = P(6,9), .y = S(8),   },
    {.x = P(6,9), .y = P(B,C), },
    {.x = P(5,A), .y = S(D),   },
    {.x = P(4,B), .y = S(E),   },
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

// Queen ////////////  |  // Outline //////////  // Fill /////////////  // Shade ////////////  // Shine ////////////
//       ##       //0  |  //       ##       //0  //                //0  //                //0  //                //0
//   ##+#-.#+##   //1  |  //   ##########   //1  //     - -- -     //1  //     +    +     //1  //        .       //1
//   #-###+##-#   //2  |  //   ##########   //2  //    -   -  -    //2  //        +       //2  //                //2
//   #+-----+-#   //3  |  //   ##########   //3  //    --------    //3  //    +     +     //3  //                //3
//    #+++-+-#    //4  |  //    ########    //4  //     ------     //4  //     +++ +      //4  //                //4
//     #+---#     //5  |  //     ######     //5  //      ----      //5  //      +         //5  //                //5
//     #+--+#     //6  |  //     ######     //6  //      ----      //6  //      +  +      //6  //                //6
//      #++#      //7  |  //      ####      //7  //       --       //7  //       ++       //7  //                //7
//     #+--.#     //8  |  //     ######     //8  //      ----      //8  //      +         //8  //         .      //8
//      #+.#      //9  |  //      ####      //9  //       --       //9  //       +        //9  //        .       //9
//      #-.#      //A  |  //      ####      //A  //       --       //A  //                //A  //        .       //A
//     #+--.#     //B  |  //     ######     //B  //      ----      //B  //      +         //B  //         .      //B
//     #+--.#     //C  |  //     ######     //C  //      ----      //C  //      +         //C  //         .      //C
//    #+++-..#    //D  |  //    ########    //D  //     ------     //D  //     +++        //D  //         ..     //D
//   #++----..#   //E  |  //   ##########   //E  //    --------    //E  //    ++          //E  //          ..    //E
//   ##########   //F  |  //   ##########   //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

const SpritePart queenOutlineParts[] = {
    {.x = P(7,8), .y = S(0),   },
    {.x = P(3,C), .y = P(1,3), },
    {.x = P(4,B), .y = S(4),   },
    {.x = P(5,A), .y = P(5,6), },
    {.x = P(5,A), .y = S(8),   },
    {.x = P(6,9), .y = P(7,A), },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
};
const SpritePart queenFillParts[] = {
    {.x = S(5),   .y = S(1),   },
    {.x = P(7,8), .y = S(1),   },
    {.x = S(A),   .y = S(1),   },
    {.x = S(4),   .y = P(2,3), },
    {.x = S(8),   .y = S(2),   },
    {.x = S(B),   .y = P(2,3), },
    {.x = P(5,A), .y = P(3,4), },
    {.x = P(6,9), .y = P(5,6), },
    {.x = P(7,8), .y = P(7,A), },
    {.x = P(6,9), .y = S(8),   },
    {.x = P(6,9), .y = P(B,C), },
    {.x = P(5,A), .y = S(D),   },
    {.x = P(4,B), .y = S(E),   },
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

// King /////////////  |  // Outline //////////  // Fill /////////////  // Shade ////////////  // Shine ////////////
//       ##       //0  |  //       ##       //0  //                //0  //                //0  //                //0
//      +##+      //1  |  //       ##       //1  //      -  -      //1  //      +  +      //1  //                //1
//    +##--##+    //2  |  //    ########    //2  //    -  --  -    //2  //    +      +    //2  //                //2
//    #+--...#    //3  |  //    ########    //3  //     ------     //3  //     +          //3  //        ...     //3
//    #+----+#    //4  |  //    ########    //4  //     ------     //4  //     +    +     //4  //                //4
//     #+---#     //5  |  //     ######     //5  //      ----      //5  //      +         //5  //                //5
//     #+--+#     //6  |  //     ######     //6  //      ----      //6  //      +  +      //6  //                //6
//      #++#      //7  |  //      ####      //7  //       --       //7  //       ++       //7  //                //7
//     #+--.#     //8  |  //     ######     //8  //      ----      //8  //      +         //8  //         .      //8
//      #+.#      //9  |  //      ####      //9  //       --       //9  //       +        //9  //        .       //9
//      #-.#      //A  |  //      ####      //A  //       --       //A  //                //A  //        .       //A
//     #+--.#     //B  |  //     ######     //B  //      ----      //B  //      +         //B  //         .      //B
//     #+--.#     //C  |  //     ######     //C  //      ----      //C  //      +         //C  //         .      //C
//    #+++-..#    //D  |  //    ########    //D  //     ------     //D  //     +++        //D  //         ..     //D
//   #++----..#   //E  |  //   ##########   //E  //    --------    //E  //    ++          //E  //          ..    //E
//   ##########   //F  |  //   ##########   //F  //                //F  //                //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//   //0123456789ABCDEF//

const SpritePart kingOutlineParts[] = {
    {.x = P(7,8), .y = P(0,1), },
    {.x = P(4,B), .y = P(2,4), },
    {.x = P(5,A), .y = P(5,6), },
    {.x = P(6,9), .y = P(7,A), },
    {.x = P(5,A), .y = S(8),   },
    {.x = P(5,A), .y = P(B,C), },
    {.x = P(4,B), .y = S(D),   },
    {.x = P(3,C), .y = P(E,F), },
};
const SpritePart kingFillParts[] = {
    {.x = S(6),   .y = S(1),   },
    {.x = S(9),   .y = S(1),   },
    {.x = S(4),   .y = S(2),   },
    {.x = P(7,8), .y = S(2),   },
    {.x = S(B),   .y = S(2),   },
    {.x = P(5,A), .y = P(3,4), },
    {.x = P(6,9), .y = P(5,6), },
    {.x = P(7,8), .y = P(7,A), },
    {.x = P(6,9), .y = S(8),   },
    {.x = P(6,9), .y = P(B,C), },
    {.x = P(5,A), .y = S(D),   },
    {.x = P(4,B), .y = S(E),   },
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

// ArrowL ///////////  |  // Outline //////////  // Fill /////////////
//       ##       //0  |  //       ##       //0  //                //0
//      #-#       //1  |  //      ###       //1  //       -        //1
//     #--#       //2  |  //     ####       //2  //      --        //2
//    #---#       //3  |  //    #####       //3  //     ---        //3
//   #----#       //4  |  //   ######       //4  //    ----        //4
//  #-----#       //5  |  //  #######       //5  //   -----        //5
// #------#       //6  |  // ########       //6  //  ------        //6
//#-------#       //7  |  //#########       //7  // -------        //7
//#-------#       //8  |  //#########       //8  // -------        //8
// #------#       //9  |  // ########       //9  //  ------        //9
//  #-----#       //A  |  //  #######       //A  //   -----        //A
//   #----#       //B  |  //   ######       //B  //    ----        //B
//    #---#       //C  |  //    #####       //C  //     ---        //C
//     #--#       //D  |  //     ####       //D  //      --        //D
//      #-#       //E  |  //      ###       //E  //       -        //E
//       ##       //F  |  //       ##       //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//

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

// ArrowR ///////////  |  // Outline //////////  // Fill /////////////
//       ##       //0  |  //       ##       //0  //                //0
//       #-#      //1  |  //       ###      //1  //        -       //1
//       #--#     //2  |  //       ####     //2  //        --      //2
//       #---#    //3  |  //       #####    //3  //        ---     //3
//       #----#   //4  |  //       ######   //4  //        ----    //4
//       #-----#  //5  |  //       #######  //5  //        -----   //5
//       #------# //6  |  //       ######## //6  //        ------  //6
//       #-------#//7  |  //       #########//7  //        ------- //7
//       #-------#//8  |  //       #########//8  //        ------- //8
//       #------# //9  |  //       ######## //9  //        ------  //9
//       #-----#  //A  |  //       #######  //A  //        -----   //A
//       #----#   //B  |  //       ######   //B  //        ----    //B
//       #---#    //C  |  //       #####    //C  //        ---     //C
//       #--#     //D  |  //       ####     //D  //        --      //D
//       #-#      //E  |  //       ###      //E  //        -       //E
//       ##       //F  |  //       ##       //F  //                //F
/////////////////////  |  /////////////////////  /////////////////////
//0123456789ABCDEF//   |  //0123456789ABCDEF//   //0123456789ABCDEF//

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