#include <iostream>
#include <type_traits>

template <int Number, int Divisor>
struct IsPrimeRecursion :
    std::conditional_t<(Number % Divisor != 0), IsPrimeRecursion<Number, Divisor - 1>,
    std::integral_constant<bool, false>> {};

template <int Number>
struct IsPrimeRecursion<Number, 1> : std::integral_constant<bool, true> {};

template <int Number>
struct IsPrime : IsPrimeRecursion<Number, Number - 1> {};

template <int Current, int Counter>
struct NthPrimeRecursion :
    std::conditional_t<IsPrime<Current>::value,
    std::conditional_t<(Counter == 1), std::integral_constant<int, Current>,
    NthPrimeRecursion<Current + 1, Counter - 1>>,
    NthPrimeRecursion<Current + 1, Counter>> {};

template <int Counter>
struct NthPrime : NthPrimeRecursion<2, Counter> {};

template <>
struct NthPrime<1> : std::integral_constant<int, 2> {};

int main() {
    std::cout << "The " << 11 << "th prime number is: " << NthPrime<11>::value << std::endl;
    std::cout << "The " << 12 << "th prime number is: " << NthPrime<12>::value << std::endl;
    std::cout << "The " << 13 << "th prime number is: " << NthPrime<13>::value << std::endl;
    std::cout << "The " << 14 << "th prime number is: " << NthPrime<14>::value << std::endl;
    std::cout << "The " << 15 << "th prime number is: " << NthPrime<15>::value << std::endl;
    std::cout << "The " << 16 << "th prime number is: " << NthPrime<16>::value << std::endl;
    return 0;
}
