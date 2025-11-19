class Solution {
public:
    vector<vector<int>> palindromePairs(const vector<string> &w) {
        using ull = unsigned long long;
        vector<vector<int>> r;
        unordered_map<ull, int> m;
        constexpr ull p = 31, l = 301;
        ull fh[l]{0}, bh[l]{0}, pp[l]{1};
        bool ss[l]{};
        for (int i = 1; i < l; ++i) pp[i] = p * pp[i - 1];
        for (int i = 0; i < w.size(); ++i) {
            ull h = 0; for (int c : w[i]) h = p * h + c;
            m.emplace(h, i);
            ss[w[i].size()] = true;
        }
        for (int i = 0; i < w.size(); ++i) {
            const auto &s = w[i];
            const int n = s.size();
            for (int j = 0; j < n; ++j) {
                fh[j + 1] = p * fh[j] + s[j];
                bh[j + 1] = p * bh[j] + s[n - 1 - j];
            }
            for (int j = 0, k = n; k >= 0; ++j, --k) if (ss[j]) {
                if (fh[n] - pp[k] * fh[j] == bh[k]) {
                    auto a = m.find(bh[n] - pp[j] * bh[k]);
                    if (a != end(m) && (k != 0 ? i != a->second : i < a->second))
                        r.push_back({ i, a->second });
                }
                if (bh[n] - pp[k] * bh[j] == fh[k]) {
                    auto a = m.find(bh[j]);
                    if (a != end(m) && (k != 0 ? i != a->second : i < a->second))
                        r.push_back({ a->second, i });
                }
            }
        }
        return r;
    }
};