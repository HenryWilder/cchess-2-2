#include "Sprite.hpp"

namespace sprite
{
    namespace unit
    {
        const Sprite null
        {
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "                "
            "               "
        };

        const Sprite pawn
        {
            "                "
            "                "
            "                "
            "      2222      "
            "     211442     "
            "     311442     "
            "     311112     "
            "     321113     "
            "      3242      "
            "     321143     "
            "      3243      "
            "      3143      "
            "      3143      "
            "     321413     "
            "    32111443    "
            "    33333333   "
        };

        const Sprite rook
        {
            "                "
            "                "
            "   3323333233   "
            "   3223113243   "
            "   3233113343   "
            "   3211111143   "
            "    32111113    "
            "     322123     "
            "     321143     "
            "     321143     "
            "     321143     "
            "    32211443    "
            "    32114443    "
            "   3222221143   "
            "   3221111443   "
            "   3333333333  "
        };

        const Sprite knight
        {
            "      33        "
            "     3212       "
            "    3214233333  "
            "   321114422443 "
            "   321111111123 "
            "   321121111113 "
            "    3212111133  "
            "    32112223    "
            "     321442     "
            "      321442    "
            "      3211443   "
            "      3211413   "
            "     32111123   "
            "    32211123    "
            "   3221111442   "
            "   3333333333  "
        };

        const Sprite bishop
        {
            "       33       "
            "      3143      "
            "     322132     "
            "    3211132     "
            "    32113143    "
            "    32111143    "
            "     321113     "
            "      3223      "
            "     321143     "
            "      3243      "
            "      3143      "
            "     321143     "
            "     321143     "
            "    32211443    "
            "   3221111443   "
            "   3333333333  "
        };

        const Sprite queen
        {
            "       33       "
            "   3323143233   "
            "   3133323313   "
            "   3211111213   "
            "    32221213    "
            "     321113     "
            "     321123     "
            "      3223      "
            "     321143     "
            "      3243      "
            "      3143      "
            "     321143     "
            "     321143     "
            "    32221443    "
            "   3221111443   "
            "   3333333333  "
        };

        const Sprite king
        {
            "       33       "
            "      2332      "
            "    23311332    "
            "    32114443    "
            "    32111123    "
            "     321113     "
            "     321123     "
            "      3223      "
            "     321143     "
            "      3243      "
            "      3143      "
            "     321143     "
            "     321143     "
            "    32221443    "
            "   3221111443   "
            "   3333333333  "
        };

        const Sprite* all[7]
        {
            &null,
            &pawn,
            &rook,
            &knight,
            &bishop,
            &queen,
            &king,
        };
    }

    namespace symbol
    {
        const Sprite arrowL
        {
            "       33       "
            "      313       "
            "     3113       "
            "    31113       "
            "   311113       "
            "  3111113       "
            " 31111113       "
            "311111113       "
            "311111113       "
            " 31111113       "
            "  3111113       "
            "   311113       "
            "    31113       "
            "     3113       "
            "      313       "
            "       33      "
        };

        const Sprite arrowR
        {
            "       33       "
            "       313      "
            "       3113     "
            "       31113    "
            "       311113   "
            "       3111113  "
            "       31111113 "
            "       311111113"
            "       311111113"
            "       31111113 "
            "       3111113  "
            "       311113   "
            "       31113    "
            "       3113     "
            "       313      "
            "       33      "
        };

        const Sprite* arrows[2]
        {
            &arrowL,
            &arrowR,
        };
    }
}
