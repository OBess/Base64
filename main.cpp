#include <iostream>
#include <cassert>

#include "base64.hpp"
#include "fmt.hpp"

inline void testing(std::string_view data)
{
    const auto encoded = base64::encode(data);
    const auto decoded = base64::decode(encoded);

    fmt::println("Test: {}\nencoded: {}\ndecoded: {}", data, encoded, decoded);
    assert(data == decoded);
}

int main()
{
    testing("demo");
    testing("demon");
    testing("demo");
    testing("demo");
    testing("demo");

    /* Do not write code */
    return EXIT_SUCCESS;
}