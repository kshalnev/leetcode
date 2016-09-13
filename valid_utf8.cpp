#include "std.hpp"

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        const size_t n = data.size();
        for (size_t i = 0; i < n;) {
            const uint8_t b = static_cast<uint8_t>(data[i] & 0xff);
            size_t r = 0; // remained part
            if ((b & 0b10000000) == 0b00000000) {
                r = 0; // one byte
            } else if ((b & 0b11100000) == 0b11000000) {
                r = 1; // two bytes
            } else if ((b & 0b11110000) == 0b11100000) {
                r = 2; // three bytes
            } else if ((b & 0b11111000) == 0b11110000) {
                r = 3; // four bytes
            } else {
                return false; // invalid format
            }
            if ((i + r) >= n) return false; // eof
            for (size_t j = 1; j <= r; ++j) {
                const uint8_t nb = static_cast<uint8_t>(data[i + j] & 0xff);
                if ((nb & 0b11000000) != 0b10000000)
                    return false; // invalid format
            }
            i += r + 1;
        }
        return true;
    }
};
