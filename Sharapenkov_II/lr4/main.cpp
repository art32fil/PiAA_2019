#include <iostream>
#include <vector>

std::vector<int> prefix(std::string s) {
    size_t n = s.length();
    std::vector<int> p(n);

    for (int i = 1; i < n; i++) {
        int j = p[i - 1];

        while ((j > 0) && (s[i] != s[j]))
            j = p[j - 1];

        if (s[i] == s[j])
            ++j;

        p[i] = j;
    }

    return p;
}


std::vector<int> KMPA(std::string &text, std::string &pattern) {
    std::string concat;
    std::vector<int> result;
    concat = pattern + "@" + text;
    size_t pattern_len = pattern.length();

    std::vector<int> p = prefix(concat);

    for (unsigned i = 0; i < p.size(); i++)
        if (p[i] == pattern_len)
            result.push_back(i - 2 * int(pattern_len));
    return result;
}


int isCicleShift(std::string &text_a, std::string &text_b) {
    std::string concat;
    concat = text_a + "@" + text_b;

    std::vector<int> p = prefix(concat);

    int index = p[p.size() - 1];
    for (int i = index; i < text_a.size(); i++)
        if (text_a[i] != text_b[i - index]) return -1;

    return index;
}


int main() {
    std::string text_a, text_b;

    std::cin >> text_a >> text_b;

    if(text_a.length() != text_b.length()) {
        std::cout << -1;
        return 0;
    }

    if(text_a == text_b){
        std::cout << 0;
        return 0;
    }

    int index;
    if ((index = isCicleShift(text_a, text_b)) != -1) {
        std::cout << index;
    } else {
        std::cout << "-1";
    }

    return 0;
}