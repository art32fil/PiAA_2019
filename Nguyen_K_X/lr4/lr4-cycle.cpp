// lr4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include <string>
//#include <iostream>
//#include <vector>
//int* build_LSP_table(std::string pattern) {
//	int *lsp = new int[pattern.length()];
//	for (int i = 0; i < pattern.length(); i++) lsp[i] = 0;
//	lsp[0] = 0;
//	int pos = 1;
//	int j = 0;
//	while (pos < pattern.length()) {
//		while (j > 0 && pattern.at(pos) != pattern.at(j)) j = lsp[j - 1];
//		if (pattern.at(pos) == pattern.at(j)) {
//			j++;
//		}
//		lsp[pos] = j;
//		pos++;
//	}
//	return lsp;
//}
//int KMP(std::string text, std::string pattern, int* lsp) {
//	int i = 0;
//	int j = 0;
//	bool isFirstRound = true;
//	while (i < text.length()) {
//		if (pattern.at(j) == text.at(i)) {
//			j++;
//			i++;
//			if (i >= text.length() && isFirstRound)
//			{
//				i -= text.length();
//				isFirstRound = false;
//			}
//		}
//		if (j == pattern.length()) {
//			return i;
//		}
//		else{
//			if (i < text.length() && pattern.at(j) != text.at(i)) {
//				if (j != 0)
//					j = lsp[j - 1];  // j!=0 -> mismatch in middle of pattern 
//				else {
//					i++;			// j==0 -> mismatch first character -> increase i
//					if (i >= text.length() && isFirstRound)
//					{
//						i -= text.length();
//						isFirstRound = false;
//					}
//				}
//			}
//		}
//
//	}
//	return -1;
//}
//int main()
//{
//	std::string A = "abcdefghi";
//	std::string B = "defghiabc";
//	std::getline(std::cin, A);
//	std::getline(std::cin, B);
//	if (A.length() != B.length()) {
//		std::cout << -1 << std::endl;
//		return 0;
//	}
//	int *lsp = build_LSP_table(B);
//	int result = KMP(A, B, lsp);
//	std::cout << result << std::endl;
//	getchar();
//	getchar();
//	getchar();
//	return 0;
//}
//
