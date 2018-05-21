#ifndef UTIL_HPP
#define UTIL_HPP

#include <array>

template <typename T, std::size_t W, std::size_t H>
using Array2D = std::array<std::array<T, H>, W>;

template <typename T, std::size_t W>
using Array = std::array<T, W>;

#endif // UTIL_HPP
