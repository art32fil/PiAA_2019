// lr4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
int* build_LSP_table(std::string pattern) {
	int *lsp = new int[pattern.length()];
	for (int i = 0; i < pattern.length(); i++) lsp[i] = 0;
	lsp[0] = 0;
	int pos = 1;
	int j = 0;
	while (pos < pattern.length()) {
		while (j > 0 && pattern.at(pos) != pattern.at(j)) j = lsp[j - 1];
		if (pattern.at(pos) == pattern.at(j)) {
			j++;
		}
		lsp[pos] = j;
		pos++;
	}
	return lsp;
}
std::vector<int> KMP(std::string text, std::string pattern, int* lsp) {
	std::vector<int> result_set;
	int i = 0;
	int j = 0;
	while (i < text.length()) {
		if (pattern.at(j) == text.at(i)) {
			j++;
			i++;
		}
		if (j == pattern.length()) {
			result_set.push_back(i - j);
			j = lsp[j - 1];

		}
		else if (i < text.length() && pattern.at(j) != text.at(i)) {
			if (j != 0)
				j = lsp[j - 1];
			else
				i++;
		}
	}
	return result_set;
}
int main()
{
	std::string text = "abab";
	std::string pattern = "ab";
	std::getline(std::cin, pattern);
	std::getline(std::cin, text);

	int *lsp = build_LSP_table(pattern);
	std::vector<int> result = KMP(text, pattern, lsp);
	if (result.size() > 0) {
		for (int i = 0; i < result.size(); i++) {
			if (i != result.size() - 1)std::cout << result[i] << ",";
			else std::cout << result[i];
		}
		std::cout << std::endl;
	}
	else std::cout << -1 << std::endl;
	getchar();
	return 0;
}

