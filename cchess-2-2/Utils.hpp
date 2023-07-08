#pragma once
#include <concepts>

template<typename Func, typename T>
concept evalable = requires(Func fn, T px)
{
    { fn(px) };
};

void SleepForMS(int ms = 1);

void SleepForMS(double ms = 1.0);

template<std::integral iT>
bool IsOdd(iT a)
{
    return !!(a & (iT)1);
}

template<std::integral iT>
bool IsEven(iT a)
{
    return !(a & (iT)1);
}

template<std::integral iT1, std::integral iT2>
iT1 Snap(iT1 value, iT2 gridsize) {
    using TBig = std::conditional_t<sizeof(iT1) >= sizeof(iT2), iT1, iT2>;
    value = (iT1)((TBig)value / (TBig)gridsize);
    value = (iT1)((TBig)value * (TBig)gridsize);
    return value;
}
