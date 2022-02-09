#pragma once

#include <string>

namespace base64
{
    static constexpr size_t base64Size = 65;
    static constexpr char base64Chars[base64Size] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                                     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '='};

    static constexpr inline size_t index(char c)
    {
        for (size_t i = 0; i < base64Size; ++i)
        {
            if (c == base64Chars[i])
                return i;
        }

        return -1;
    }

    // ENCODING
    std::string encode(const char *data, const size_t size)
    {
        std::string encoded;
        encoded.reserve(size);

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

        return std::move(encoded);
    }

    std::string encode(std::string_view data)
    {
        return std::move(encode(data.data(), data.size()));
    }
    // ~ENCODING

    // DECODING
    std::string decode(std::string_view data)
    {
        std::string decoded;
        decoded.reserve(data.size());

        for (size_t i = 0; i < data.size(); i += 4)
        {
            if (data[i] == '=')
                break;

            const char a = static_cast<char>(index(data[i]));
            const char b = static_cast<char>(index(data[i + 1]));
            const char c = static_cast<char>(index(data[i + 2]));
            const char d = static_cast<char>(index(data[i + 3]));

            decoded.push_back((a << 2) | (b >> 4));

            if (c == 64)
                break;

            decoded.push_back((b << 4) | (c >> 2));

            if (d == 64)
                break;

            decoded.push_back((c << 6) | d);
        }

        return decoded;
    }
    // ~DECODING
};