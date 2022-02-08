#include <iostream>

#include "base64.hpp"
#include "fmt.hpp"

int main()
{
    std::string_view data{"demon"};
    auto result = base64::encode(data);

    fmt::println("\"{}\" in base64 is \"{}\"", data, result);

    /* Do not write code */
    return EXIT_SUCCESS;
}