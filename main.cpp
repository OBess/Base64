#include <iostream>
#include <cassert>
#include <chrono>

#include "base64.hpp"
#include "fmt.hpp"

inline void testing(std::string_view data, [[maybe_unused]] std::string_view expected)
{
    const auto encodedTimeStart = std::chrono::high_resolution_clock::now();
    const auto encoded = base64::encode(data);
    const auto encodedTimeStop = std::chrono::high_resolution_clock::now();
    const auto encodedTimeDuration = std::chrono::duration_cast<std::chrono::microseconds>(encodedTimeStop - encodedTimeStart);

    auto decodedTimeStart = std::chrono::high_resolution_clock::now();
    const auto decoded = base64::decode(encoded);
    const auto decodedTimeStop = std::chrono::high_resolution_clock::now();
    const auto decodedTimeDuration = std::chrono::duration_cast<std::chrono::microseconds>(decodedTimeStop - decodedTimeStart);

    fmt::println("Test: {}\nencoded: {}\ndecoded: {}\n Encoded time: {};\n Decoded time: {}", data, encoded, decoded, encodedTimeDuration.count(), decodedTimeDuration.count());
    assert(data == decoded);
    assert(encoded == expected);
}

int main()
{
    testing("demo", "ZGVtbw==");
    testing("demon", "ZGVtb24=");
    testing("test", "dGVzdA==");
    testing("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.", "TG9yZW0gSXBzdW0gaXMgc2ltcGx5IGR1bW15IHRleHQgb2YgdGhlIHByaW50aW5nIGFuZCB0eXBlc2V0dGluZyBpbmR1c3RyeS4gTG9yZW0gSXBzdW0gaGFzIGJlZW4gdGhlIGluZHVzdHJ5J3Mgc3RhbmRhcmQgZHVtbXkgdGV4dCBldmVyIHNpbmNlIHRoZSAxNTAwcywgd2hlbiBhbiB1bmtub3duIHByaW50ZXIgdG9vayBhIGdhbGxleSBvZiB0eXBlIGFuZCBzY3JhbWJsZWQgaXQgdG8gbWFrZSBhIHR5cGUgc3BlY2ltZW4gYm9vay4gSXQgaGFzIHN1cnZpdmVkIG5vdCBvbmx5IGZpdmUgY2VudHVyaWVzLCBidXQgYWxzbyB0aGUgbGVhcCBpbnRvIGVsZWN0cm9uaWMgdHlwZXNldHRpbmcsIHJlbWFpbmluZyBlc3NlbnRpYWxseSB1bmNoYW5nZWQuIEl0IHdhcyBwb3B1bGFyaXNlZCBpbiB0aGUgMTk2MHMgd2l0aCB0aGUgcmVsZWFzZSBvZiBMZXRyYXNldCBzaGVldHMgY29udGFpbmluZyBMb3JlbSBJcHN1bSBwYXNzYWdlcywgYW5kIG1vcmUgcmVjZW50bHkgd2l0aCBkZXNrdG9wIHB1Ymxpc2hpbmcgc29mdHdhcmUgbGlrZSBBbGR1cyBQYWdlTWFrZXIgaW5jbHVkaW5nIHZlcnNpb25zIG9mIExvcmVtIElwc3VtLg==");

    /* Do not write code */
    return EXIT_SUCCESS;
}