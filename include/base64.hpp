#pragma once

#include <string>

namespace base64
{
    static constexpr std::string_view base64Chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

    // ENCODING
    std::string encode(const char *data, const size_t size)
    {
        std::string encoded;
        encoded.reserve(static_cast<size_t>(size + size * 0.25f));

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

    std::string encode(const std::string &data)
    {
        return std::move(encode(data.data(), data.size()));
    }

    template <class T>
    std::string encode(T data)
    {
        return std::move(encode(reinterpret_cast<char *>(&data), sizeof(data)));
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

            const char a = static_cast<char>(base64Chars.find(data[i]));
            const char b = static_cast<char>(base64Chars.find(data[i + 1]));
            const char c = static_cast<char>(base64Chars.find(data[i + 2]));
            const char d = static_cast<char>(base64Chars.find(data[i + 3]));

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

    template <class T>
    T decode(std::string_view data)
    {
        return *reinterpret_cast<T *>(decode(data).data());
    }
    // ~DECODING
};