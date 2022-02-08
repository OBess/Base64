#pragma once

#include <string>

namespace base64
{
    static constexpr std::string_view base64Chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

    template <class T>
    constexpr std::string encode(T const &data)
    {

        return {};
    }

    template <class T>
    constexpr T decode(std::string_view data)
    {
    }
};