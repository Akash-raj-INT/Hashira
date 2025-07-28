#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
using BigInt = boost::multiprecision::cpp_int;

const BigInt MOD = static_cast<BigInt>(1e18) + 7;


BigInt decodeValue(const string& val, int base) {
    BigInt result = 0;
    for (char digit : val) {
        int d = isdigit(digit) ? digit - '0' : toupper(digit) - 'A' + 10;
        result = result * base + d;
    }
    return result;
}

BigInt modInverse(BigInt a, BigInt m) {
    BigInt m0 = m, t, q;
    BigInt x0 = 0, x1 = 1;
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

BigInt lagrangeInterpolation(const vector<pair<BigInt, BigInt>>& shares) {
    BigInt secret = 0;
    int k = shares.size();

    for (int i = 0; i < k; ++i) {
        BigInt xi = shares[i].first;
        BigInt yi = shares[i].second;
        BigInt num = 1, denom = 1;

        for (int j = 0; j < k; ++j) {
            if (i != j) {
                BigInt xj = shares[j].first;
                num = (num * (-xj + MOD)) % MOD;
                denom = (denom * (xi - xj + MOD)) % MOD;
            }
        }

        BigInt li = (num * modInverse(denom, MOD)) % MOD;
        secret = (secret + yi * li) % MOD;
    }

    return secret;
}

int main() {
    ifstream file("input.json");
    if (!file.is_open()) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    json j;
    file >> j;
    file.close();

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<pair<BigInt, BigInt>> points;

    for (auto& [key, val] : j.items()) {
        if (key == "keys") continue;

        try {
            BigInt x = BigInt(key);
            int base = stoi(val["base"].get<string>());
            string encoded = val["value"].get<string>();
            BigInt y = decodeValue(encoded, base);
            points.emplace_back(x, y);
        } catch (...) {
            continue;
        }
    }

    if (points.size() < k) {
        cerr << "Not enough valid points.\n";
        return 1;
    }

    vector<pair<BigInt, BigInt>> selected(points.begin(), points.begin() + k);

    BigInt secret = lagrangeInterpolation(selected);
    cout << secret << endl;
    return 0;
}
