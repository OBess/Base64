#pragma once

#include <string>

namespace base64
{
    static constexpr std::string_view base64Chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

    // ENCODING
    constexpr std::string encode(const char *data, const size_t size)
    {
        std::string encoded;
        encoded.reserve(size * 2);

        for (size_t i = 0; i < size; i += 3)
        {
            const char a = data[i];
            const char b = i + 1 < size ? data[i + 1] : 0;
            const char c = i + 2 < size ? data[i + 2] : 0;

            encoded.push_back(base64Chars[a >> 2]);
            encoded.push_back(base64Chars[(a & 3) << 4 | b >> 4]);
            encoded.push_back(base64Chars[i + 1 < size ? (b & 15) << 2 | c >> 6 : 64]);
            encoded.push_back(base64Chars[i + 2 < size ? c & 63 : 64]);
        }

        return encoded;
    }

    constexpr std::string encode(std::string_view data)
    {
        return encode(data.data(), data.size());
    }

    constexpr std::string encode(const std::string &data)
    {
        return encode(data.data(), data.size());
    }

    template <class T>
    constexpr std::string encode(T data)
    {
        return encode(reinterpret_cast<char *>(&data), sizeof(data));
    }
    // ~ENCODING

    template <class T>
    constexpr T decode(std::string_view data)
    {
    }
};