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

namespace my {
	template<typename FwdIt, typename Ty>
	FwdIt lower_bound(FwdIt _first, FwdIt _last, const Ty& _val) {
		return lower_bound(_first, _last, _val, std::less<>{});
	}

	template<typename FwdIt, typename Ty, typename Pred>
	FwdIt lower_bound(FwdIt _first, FwdIt _last, const Ty& _val, Pred _pred) {
		auto left = _first;
		auto right = _last ;
		auto mid = left;

		while (left <= right) {
			auto mid = left + std::distance(left, right) / 2;

			if (_val < mid)
				right = mid - 1;
			else if (mid < _val)
				mid = left + 1;
			else
				return mid;
		}
	}

	template<typename FwdIt, typename Ty>
	FwdIt upper_bound(FwdIt _first, FwdIt _last, const Ty& _val) {
		return upper_bound(_first, _last, _val, std::less<>{});
	}

	template<typename FwdIt, typename Ty, typename Pred>
	FwdIt upper_bound(FwdIt _first, FwdIt _last, const Ty& _val, Pred _pred) {
		auto left = _first;
		auto right = _last ;
		auto mid = left;

		while (left <= right) {
			auto mid = left + std::distance(left, right) / 2;

			if (mid < _val)
				mid = left + 1;
			else if (_val < mid)
				right = mid - 1;
			else
				return mid;
		}
	}
}

class NOccurences {
private:
	template<typename FwdIt, typename Ty>
	static std::size_t find(FwdIt _begin, FwdIt _end, Ty _element) {
		
		auto lft_it = my::lower_bound(_begin, _end, _element);
		auto rht_it = my::upper_bound(_begin, _end, _element);

		return std::distance(lft_it, rht_it);
	}

public:
	static void test() {
		std::vector<int> vec{ 1, 2, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10 };
		//std::vector<int> vec{ 1, 2, 3, 3, 3, 4, 5 };

		auto occurences = find(vec.begin(), vec.end(), 3);

		std::cout << occurences << std::endl;
	}

};
