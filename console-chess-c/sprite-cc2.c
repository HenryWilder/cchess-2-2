#include "sprite.h"

#define V(x,...) { 0x0##x, ((0x1##__VA_ARGS__ == 0x1) ? 0x0##x : 0x0##__VA_ARGS__) }

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
    {.x = V(6,9), .y = V(3,F), },
    {.x = V(5,A), .y = V(4,7), },
    {.x = V(5,A), .y = V( 9 ), },
    {.x = V(5,A), .y = V( D ), },
    {.x = V(4,B), .y = V(E,F), },
};
const SpritePart pawnFillParts[] = {
    {.x = V(6,9), .y = V(4,7), },
    {.x = V(7,8), .y = V(8,E), },
    {.x = V(6,9), .y = V( 9 ), },
    {.x = V(6,9), .y = V( D ), },
    {.x = V(5,A), .y = V( E ), },
};
const SpritePart pawnShadeParts[] = {
    {.x = V(6,9), .y = V( 3 ), },
    {.x = V( 5 ), .y = V( 4 ), },
    {.x = V( A ), .y = V(4,6), },
    {.x = V( 6 ), .y = V( 7 ), },
    {.x = V( 7 ), .y = V( 8 ), },
    {.x = V( 6 ), .y = V( 9 ), },
    {.x = V( 7 ), .y = V( A ), },
    {.x = V( 6 ), .y = V( D ), },
    {.x = V( 5 ), .y = V( E ), },
};
const SpritePart pawnShineParts[] = {
    {.x = V(8,9), .y = V(4,5), },
    {.x = V( 8 ), .y = V( 8 ), },
    {.x = V( 9 ), .y = V( 9 ), },
    {.x = V( 8 ), .y = V(A,D), },
    {.x = V(9,A), .y = V( E ), },
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
    {.x = V(3,C), .y = V(2,5), },
    {.x = V(4,B), .y = V( 6 ), },
    {.x = V(5,A), .y = V(7,A), },
    {.x = V(4,B), .y = V(B,C), },
    {.x = V(3,C), .y = V(D,F), },
};
const SpritePart rookFillParts[] = {
    {.x = V( 4 ), .y = V(3,4), },
    {.x = V(7,8), .y = V(3,4), },
    {.x = V( B ), .y = V(3,4), },
    {.x = V(4,B), .y = V( 5 ), },
    {.x = V(5,A), .y = V( 6 ), },
    {.x = V(6,9), .y = V(7,A), },
    {.x = V(5,A), .y = V(B,C), },
    {.x = V(4,B), .y = V(D,E), },
};
const SpritePart rookShadeParts[] = {
    {.x = V( 5 ), .y = V(2,3), },
    {.x = V( A ), .y = V(2,3), },
    {.x = V( 4 ), .y = V(3,5), },
    {.x = V( 5 ), .y = V( 6 ), },
    {.x = V( 6 ), .y = V(7,B), },
    {.x = V( 5 ), .y = V(B,E), },
    {.x = V(6,8), .y = V( D ), },
    {.x = V( 4 ), .y = V(D,E), },
    {.x = V( 4 ), .y = V(D,E), },
    {.x = V( 9 ), .y = V( 7 ), },
};
const SpritePart rookShineParts[] = {
    {.x = V( B ), .y = V(3,5), },
    {.x = V( 9 ), .y = V(8,C), },
    {.x = V( A ), .y = V(B,C), },
    {.x = V( 8 ), .y = V( C ), },
    {.x = V( B ), .y = V(D,E), },
    {.x = V( A ), .y = V( E ), },
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
    {.x = V(6,7), .y = V( 0 ), },
    {.x = V(5,8), .y = V( 1 ), },
    {.x = V(4,D), .y = V( 2 ), },
    {.x = V(3,E), .y = V(3,5), },
    {.x = V(4,D), .y = V( 6 ), },
    {.x = V(4,B), .y = V( 7 ), },
    {.x = V(5,A), .y = V( 8 ), },
    {.x = V(6,B), .y = V( 9 ), },
    {.x = V(6,C), .y = V(A,B), },
    {.x = V(5,C), .y = V( C ), },
    {.x = V(4,B), .y = V( D ), },
    {.x = V(3,C), .y = V(E,F), },
};
const SpritePart knightFillParts[] = {
    {.x = V(6,8), .y = V( 1 ), },
    {.x = V(5,8), .y = V( 2 ), },
    {.x = V(4,D), .y = V(3,5), },
    {.x = V(5,B), .y = V( 6 ), },
    {.x = V(5,A), .y = V( 7 ), },
    {.x = V(6,A), .y = V( 8 ), },
    {.x = V(7,B), .y = V(9,B), },
    {.x = V(6,B), .y = V( C ), },
    {.x = V(5,A), .y = V( D ), },
    {.x = V(4,C), .y = V( E ), },
};
const SpritePart knightShadeParts[] = {
    {.x = V( 6 ), .y = V( 1 ), },
    {.x = V( 8 ), .y = V(1,2), },
    {.x = V( 5 ), .y = V( 2 ), },
    {.x = V( 4 ), .y = V(3,5), },
    {.x = V(A,B), .y = V( 3 ), },
    {.x = V( D ), .y = V( 4 ), },
    {.x = V( 7 ), .y = V(5,6), },
    {.x = V( 5 ), .y = V(6,7), },
    {.x = V(8,A), .y = V( 7 ), },
    {.x = V( A ), .y = V( 8 ), },
    {.x = V( 7 ), .y = V(9,B), },
    {.x = V( 6 ), .y = V(C,D), },
    {.x = V( 5 ), .y = V(D,E), },
    {.x = V( 4 ), .y = V( E ), },
    {.x = V( B ), .y = V( 9 ), },
    {.x = V( B ), .y = V( C ), },
    {.x = V( A ), .y = V( D ), },
    {.x = V( C ), .y = V( E ), },
};
const SpritePart knightShineParts[] = {
    {.x = V( 7 ), .y = V( 2 ), },
    {.x = V(8,9), .y = V( 3 ), },
    {.x = V(C,D), .y = V( 3 ), },
    {.x = V(8,9), .y = V( 8 ), },
    {.x = V(9,A), .y = V( 9 ), },
    {.x = V(A,B), .y = V( A ), },
    {.x = V( A ), .y = V( B ), },
    {.x = V(A,B), .y = V( E ), },
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
    {.x = V(7,8), .y = V( 0 ), },
    {.x = V(6,9), .y = V(1,A), },
    {.x = V(5,A), .y = V(2,6), },
    {.x = V( 4 ), .y = V(3,5), },
    {.x = V( B ), .y = V(4,5), },
    {.x = V(5,A), .y = V( 8 ), },
    {.x = V(5,A), .y = V(B,C), },
    {.x = V(4,B), .y = V( D ), },
    {.x = V(3,C), .y = V(E,F), },
};
const SpritePart bishopFillParts[] = {
    {.x = V(7,8), .y = V( 1 ), },
    {.x = V(6,8), .y = V( 2 ), },
    {.x = V( A ), .y = V(2,4), },
    {.x = V( 9 ), .y = V( 4 ), },
    {.x = V(5,8), .y = V( 3 ), },
    {.x = V(5,7), .y = V( 4 ), },
    {.x = V(5,A), .y = V( 5 ), },
    {.x = V(6,9), .y = V( 6 ), },
    {.x = V(7,8), .y = V(7,A), },
    {.x = V(6,9), .y = V( 8 ), },
    {.x = V(6,9), .y = V(B,C), },
    {.x = V(5,A), .y = V( D ), },
    {.x = V(4,B), .y = V( E ), },
};
const SpritePart bishopShadeParts[] = {
    {.x = V(6,7), .y = V( 2 ), },
    {.x = V( A ), .y = V(2,3), },
    {.x = V( 5 ), .y = V(3,5), },
    {.x = V( 6 ), .y = V( 6 ), },
    {.x = V(7,8), .y = V( 7 ), },
    {.x = V( 6 ), .y = V( 8 ), },
    {.x = V( 7 ), .y = V( 9 ), },
    {.x = V( 6 ), .y = V(B,D), },
    {.x = V( 5 ), .y = V(D,E), },
    {.x = V( 4 ), .y = V( E ), },
};
const SpritePart bishopShineParts[] = {
    {.x = V( 8 ), .y = V( 1 ), },
    {.x = V( A ), .y = V(4,5), },
    {.x = V( 9 ), .y = V( 8 ), },
    {.x = V( 8 ), .y = V(9,A), },
    {.x = V( 9 ), .y = V(B,D), },
    {.x = V( A ), .y = V(D,E), },
    {.x = V( B ), .y = V( E ), },
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
    {.x = V(7,8), .y = V( 0 ), },
    {.x = V(3,C), .y = V(1,3), },
    {.x = V(4,B), .y = V( 4 ), },
    {.x = V(5,A), .y = V(5,6), },
    {.x = V(5,A), .y = V( 8 ), },
    {.x = V(6,9), .y = V(7,A), },
    {.x = V(5,A), .y = V(B,C), },
    {.x = V(4,B), .y = V( D ), },
    {.x = V(3,C), .y = V(E,F), },
};
const SpritePart queenFillParts[] = {
    {.x = V( 5 ), .y = V( 1 ), },
    {.x = V(7,8), .y = V( 1 ), },
    {.x = V( A ), .y = V( 1 ), },
    {.x = V( 4 ), .y = V(2,3), },
    {.x = V( 8 ), .y = V( 2 ), },
    {.x = V( B ), .y = V(2,3), },
    {.x = V(5,A), .y = V(3,4), },
    {.x = V(6,9), .y = V(5,6), },
    {.x = V(7,8), .y = V(7,A), },
    {.x = V(6,9), .y = V( 8 ), },
    {.x = V(6,9), .y = V(B,C), },
    {.x = V(5,A), .y = V( D ), },
    {.x = V(4,B), .y = V( E ), },
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
    {.x = V(7,8), .y = V(0,1), },
    {.x = V(4,B), .y = V(2,4), },
    {.x = V(5,A), .y = V(5,6), },
    {.x = V(6,9), .y = V(7,A), },
    {.x = V(5,A), .y = V( 8 ), },
    {.x = V(5,A), .y = V(B,C), },
    {.x = V(4,B), .y = V( D ), },
    {.x = V(3,C), .y = V(E,F), },
};
const SpritePart kingFillParts[] = {
    {.x = V( 6 ), .y = V( 1 ), },
    {.x = V( 9 ), .y = V( 1 ), },
    {.x = V( 4 ), .y = V( 2 ), },
    {.x = V(7,8), .y = V( 2 ), },
    {.x = V( B ), .y = V( 2 ), },
    {.x = V(5,A), .y = V(3,4), },
    {.x = V(6,9), .y = V(5,6), },
    {.x = V(7,8), .y = V(7,A), },
    {.x = V(6,9), .y = V( 8 ), },
    {.x = V(6,9), .y = V(B,C), },
    {.x = V(5,A), .y = V( D ), },
    {.x = V(4,B), .y = V( E ), },
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