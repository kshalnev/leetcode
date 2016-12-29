#include "std.hpp"

// https://leetcode.com/problems/heaters/

class Solution {
public:
    static inline int distance(int a, int b) {
        return (a >= b) ? (a - b) : (b - a);
    }
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if (heaters.empty() || houses.empty()) return 0;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int res = 0;
        auto heater_begin = heaters.begin();
        for (size_t i = 0; i < houses.size(); ++i) {
            const int house = houses[i];
            // find the heater in house or on after house
            const auto hi = lower_bound(heater_begin, heaters.end(), house);
            int heater; // heater for the house
            if (hi == heaters.end()) {
                // heaters end before house, only last heater can be used by the house
                heater = heaters.back();
                heater_begin = heaters.end();
            } else {
                if (*hi == house) {
                    // heater is in the house
                    heater = *hi;
                } else {
                    // found heater is after the house, but also possible heater before
                    // the house, need to take the closest
                    if (hi == heaters.begin()) {
                        // no heater before take hi
                        heater = *hi;
                    } else {
                        int ha = *hi; // heater after position
                        int hb = *(hi - 1); // heater before position
                        if ((ha - house) > (house - hb)) {
                            heater = hb;
                            heater_begin = hi - 1;
                        } else {
                            heater = ha;
                            heater_begin = hi;
                        }
                    }
                }
            }
            res = max(res, distance(house, heater));
        }
        return res;
    }
};

