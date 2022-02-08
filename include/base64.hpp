#pragma once

#include <string>

namespace base64
{
    static constexpr std::string_view base64Chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

    template <class T>
    constexpr std::string encode(T data)
    {
        constexpr auto size = sizeof(data);
        const char *s_data = reinterpret_cast<const char *>(data);

        std::string encoded;
        encoded.reserve(size * 2);

        for (size_t i = 0; i < size; ++i)
        {
            const char a = s_data[i++];
            const char b = i < size ? s_data[i++] : 64;
            const char c = i < size ? s_data[i++] : 64;

            encoded.push_back(a >> 2);
            encoded.push_back((a & 3) << 4 | b >> 4);
            encoded.push_back((b & 15) << 4 | c >> 6);
            encoded.push_back(c & 63);
        }

        return encoded;
    }

    template <class T>
    constexpr T decode(std::string_view data)
    {
    }
};