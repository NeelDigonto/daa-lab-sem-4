#pragma once
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <optional>
#include <iostream>


class TwoSum {
private:
	template<typename FwdIt, typename Ty>
	static std::optional<std::pair<FwdIt, FwdIt>> find(FwdIt _first, FwdIt _last, Ty _sum) {
		using value_type = typename FwdIt::value_type;
		std::unordered_map<value_type, FwdIt> hash;

		for (auto iter = _first; iter != _last; ++iter)
			hash.insert({ *iter, iter });

		for (auto iter = _first; iter != _last; ++iter) {
			Ty complement = _sum - *iter;

			auto found = hash.find(complement);
			if (found != hash.end())
				return std::pair{ iter, found->second };
		}

		return {};
	}

public:
	static void test() {
		std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		auto found = find(vec.begin(), vec.end(), 9);

		if (found.has_value())
		std::cout << *found->first << ", " << *found->second << std::endl;
	}

};