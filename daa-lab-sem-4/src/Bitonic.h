#pragma once
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <optional>
#include <iostream>
#include <iterator>

class BitonicSequence {
private:
	template<typename FwdIt>
	static auto find(FwdIt _first, FwdIt _last) -> FwdIt {
		using value_type = typename FwdIt::value_type;

		auto left = _first;
		auto right = _last - 1;
		auto mid = left;

		while (left <= right) {
			auto mid = left + std::distance(left, right) / 2;

			if (*(mid-1) < *mid && *mid > *(mid+1)) {
				return mid;
			}

			if (*mid < *(mid+1))
				left = mid + 1;
			else
				right = mid - 1;
		}

		return mid;
	}

public:
	static void test() {
		std::vector<int> bt_seq{ 1, 2, 3, 4, 5, 6, 7, 8, 3, 2, 1 };

		auto iter = find(bt_seq.begin(), bt_seq.end());

		std::cout << *iter << std::endl;
	}

};
