/*  Fillings Coordinates
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonSV_FillingsCoordinates_H
#define PokemonAutomation_PokemonSV_FillingsCoordinates_H

#include "CommonFramework/ImageTools/ImageBoxes.h"
#include <vector>
#include <map>

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

class FillingsCoordinates {
    struct FillingInfo {
        uint8_t piecesPerServing;
        uint8_t servingsPerBowl;
        std::map<int, std::vector<ImageFloatBox>> placementCoordinates;
    };

    //Easy to place fillings. Three pieces per serving. Cucumber, Pickle, etc. Works with Lettuce, Onion, others as well.
    const std::map<int, std::vector<ImageFloatBox>> flatCircleFilling{ //Number of servings, Coordinates for each piece
        {1, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }}, //One serving, three pieces
        {2, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }}, //Two servings, six pieces
        {3, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }}, //Three servings, etc.
        {4, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }},
        {5, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }},
        {6, { {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055},
            {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }},
    };

    //Hamburger, potato salad, etc. Intended for recipe use. If you do 1 serving each of mutliple big items they'll end up stacking in the center.
    const std::map<int, std::vector<ImageFloatBox>> bigSingleFilling{
        {1, { {0.470, 0.507, 0.060, 0.055} }}, //One serving, one piece. If only one place in the center
        {2, { {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }}, //Two pieces, left and right
        {3, { {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055} }}, //Three pieces, left right then center
        {4, { {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }}, //l r l r
        {5, { {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.470, 0.507, 0.060, 0.055} }}, //l r l r c
        {6, { {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055}, {0.386, 0.507, 0.060, 0.055}, {0.554, 0.507, 0.060, 0.055} }},
    };

    //This is for basil as it has four pieces per serving
    const std::map<int, std::vector<ImageFloatBox>> fourPiecesFilling{
        {1, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }}, //left, center left, center right, right
        {2, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }},
        {3, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }},
        {4, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }},
        {5, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }},
        {6, { {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072},
                {0.344, 0.498, 0.064, 0.052} , {0.424, 0.498, 0.064, 0.053}, {0.504, 0.498, 0.061, 0.055}, {0.573, 0.475, 0.076, 0.072} }},
    };

    const std::map<std::string, FillingInfo> SandwichFillingsData{
        {"baguette",            {0, 0, flatCircleFilling}},
        {"lettuce",             {3, 2, flatCircleFilling}},
        {"tomato",              {3, 2, flatCircleFilling}},
        {"cherry-tomatoes",     {3, 3, flatCircleFilling}}, //Will most likely need custom coordinates because of placement issues
        {"cucumber",            {3, 2, flatCircleFilling}},
        {"pickle",              {3, 2, flatCircleFilling}},
        {"onion",               {3, 2, flatCircleFilling}},
        {"red-onion",           {3, 2, flatCircleFilling}},
        {"green-bell-pepper",   {3, 2, flatCircleFilling}},
        {"red-bell-pepper",     {3, 2, flatCircleFilling}},
        {"yellow-bell-pepper",  {3, 2, flatCircleFilling}},
        {"avocado",             {3, 2, flatCircleFilling}},
        {"bacon",               {3, 2, flatCircleFilling}},
        {"ham",                 {3, 2, flatCircleFilling}},
        {"prosciutto",          {3, 2, flatCircleFilling}},
        {"chorizo",             {3, 2, flatCircleFilling}},
        {"herbed-sausage",      {3, 2, flatCircleFilling}},
        {"hamburger",           {1, 1, bigSingleFilling}},
        {"klawf-stick",         {3, 1, flatCircleFilling}},
        {"smoked-fillet",       {3, 1, flatCircleFilling}},
        {"fried-fillet",        {1, 1, bigSingleFilling}},
        {"egg",                 {3, 1, flatCircleFilling}},
        {"potato-tortilla",     {1, 1, bigSingleFilling}},
        {"tofu",                {3, 1, flatCircleFilling}}, //Tofu needs to be spaced further apart
        {"rice",                {1, 1, bigSingleFilling}},
        {"noodles",             {1, 1, bigSingleFilling}},
        {"potato-salad",        {1, 1, bigSingleFilling}},
        {"cheese",              {3, 2, flatCircleFilling}},
        {"banana",              {3, 2, flatCircleFilling}},
        {"strawberry",          {3, 2, flatCircleFilling}},
        {"apple",               {3, 2, flatCircleFilling}},
        {"kiwi",                {3, 2, flatCircleFilling}},
        {"pineapple",           {3, 2, flatCircleFilling}},
        {"jalape\xc3\xb1o",         {3, 2, flatCircleFilling}},
        {"watercress",          {3, 2, flatCircleFilling}},
        {"basil",               {4, 1, fourPiecesFilling}},
    };

public:
    FillingInfo get_filling_information(std::string filling) {
        auto iter = SandwichFillingsData.find(filling);
        return iter->second;
    }


};
}
}
}
#endif
