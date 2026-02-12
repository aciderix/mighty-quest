/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 14-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

namespace Pattern
{
    using Range_t = std::pair<size_t, size_t>;
    extern Range_t Textsegment;
    extern Range_t Datasegment;

    size_t _Findpattern(Range_t &Range, std::vector<uint8_t> Pattern, std::vector<uint8_t> Mask);
    std::vector<size_t> Findpatterns(Range_t &Range, std::vector<uint8_t> Pattern, std::vector<uint8_t> Mask);
    std::vector<uint8_t> Stringtopattern(std::string Humanreadable);
    std::vector<uint8_t> Stringtomask(std::string Humanreadable);
}
