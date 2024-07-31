#if !defined CONVERTER_CLASS_HPP
#define CONVERTER_CLASS_HPP
#include <concepts>
#include <string>

template<typename T, typename To>
concept ConverterClass = requires(T a, const std::string& str) {
    { a(str) } -> std::convertible_to<To>;
};
#endif
