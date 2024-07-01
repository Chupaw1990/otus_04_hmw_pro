#pragma once
#include <list>
#include <type_traits>
#include <vector>
#include <tuple>

/**
 * @brief print integral typename ip address
 *
 * @tparam T
 * @param value
 * @return std::enable_if_t<std::is_integral_v<T>, void>
 */
template <typename T>
std::enable_if_t<std::is_integral_v<T>> print_ip(T value) {
    for (size_t i = sizeof(T); i--;) {
        std::cout << (value >> (i << 3) & 0xFF);
        if (i > 0) std::cout << ".";
    }
    std::cout << std::endl;
}

/**
 * @brief print string typename ip address
 *
 * @tparam T
 * @param value
 */
template <typename T>
std::enable_if_t<
    std::is_same<T, std::basic_string<typename T::value_type>>::value, void>
print_ip(T value) {
    std::cout << value << std::endl;
}

/**
 * @brief class to identify vector or list
 *
 * @tparam T
 */
template <typename>
struct is_vector_or_list : std::false_type {};

template <typename T, typename... Args>
struct is_vector_or_list<std::vector<T, Args...>> : std::true_type {};

template <typename T, typename... Args>
struct is_vector_or_list<std::list<T, Args...>> : std::true_type {};

/**
 * @brief print vector or list typename ip address
 *
 * @tparam T
 * @param container
 * @return std::enable_if_t<is_vector_or_list<T>::value, void>
 */
template <typename T>
void print_ip(
    std::enable_if_t<is_vector_or_list<T>::value, const T> lst_or_vec) {
    for (auto item : lst_or_vec) {
        std::cout << item << '.';
    }
    std::cout << "\b \b\n";
}

/**
 * @brief Recursive helper class for printing tuple elements
 *
 * @tparam T
 * @tparam idx parameter pack size
 */
template <size_t idx, typename... T>
struct PrintTuple {
    static void print(const std::tuple<T...>& t) {
        PrintTuple<idx - 1, T...>::print(t);
        std::cout << '.';
        std::cout << std::get<idx>(t);
    }
};

/**
 * @brief Partial specialization to complete recursion
 *
 * @tparam T
 */
template <typename... T>
struct PrintTuple<0, T...> {
    static void print(const std::tuple<T...>& t) {
        std::cout << std::get<0>(t);
    }
};

/**
 * @brief Function for printing std::tuple
 *
 * @tparam T
 */
template <typename... T>
void print_ip(const std::tuple<T...>& t) {
    PrintTuple<std::tuple_size<std::tuple<T...>>::value - 1, T...>::print(t);
    std::cout << std::endl;
}