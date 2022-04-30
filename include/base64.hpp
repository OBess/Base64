#pragma once

#include <string>

namespace ds::base64
{
    /**
     * @brief All characters in base64 format
     *
     */
    static constexpr std::string_view base64Chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};

    /**
     * @brief Convert string to base64 format
     *
     * @param data
     * @param size
     * @return std::string
     */
    static std::string encode(const char *data, size_t size)
    {
        std::string encoded;
        encoded.reserve(size + size);

        const size_t minSize = size % 3;
        size -= minSize;

        {
            size_t i = 0;
            while (i < size)
            {
                const char a = data[i++];
                const char b = data[i++];
                const char c = data[i++];

                encoded.push_back(base64Chars[a >> 2]);
                encoded.push_back(base64Chars[(a & 3) << 4 | b >> 4]);
                encoded.push_back(base64Chars[(b & 15) << 2 | c >> 6]);
                encoded.push_back(base64Chars[c & 63]);
            }

            size += minSize;
            if (i < size)
            {
                const char a = data[i];
                const char b = i + 1 < size ? data[i + 1] : 0;
                const char c = i + 2 < size ? data[i + 2] : 0;

                encoded.push_back(base64Chars[a >> 2]);
                encoded.push_back(base64Chars[(a & 3) << 4 | b >> 4]);
                encoded.push_back(base64Chars[i + 1 < size ? (b & 15) << 2 | c >> 6 : 64]);
                encoded.push_back(base64Chars[i + 2 < size ? c & 63 : 64]);
            }
        }

        return std::move(encoded);
    }

    /**
     * @brief Overloading the base64 string conversion algorithm
     *
     * @param data
     * @return std::string
     */
    static std::string encode(const std::string_view data)
    {
        return std::move(encode(data.data(), data.size()));
    }

    /**
     * @brief Convert string from base64 format
     *
     * @param data
     * @return std::string
     */
    static std::string decode(const std::string_view data)
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

        return std::move(decoded);
    }
};