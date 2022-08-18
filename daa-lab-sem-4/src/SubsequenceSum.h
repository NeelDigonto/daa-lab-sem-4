#pragma once
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <optional>
#include <iostream>


class SubsequenceSum {
private:
	template<typename FwdIt, typename Ty>
	static bool find(FwdIt _first, FwdIt _last, Ty _sum) {
		using value_type = typename FwdIt::value_type;

		if (_sum == 0)
			return false;
		if (_first == _last) {
			std::cout << *_first << ", " << _sum << "\n";
			return *_first == _sum;
		}


		bool include = false;
		
		if(_sum >= *(_last - 1))
			include = find(_first, _last - 1, _sum - *(_last - 1));

		bool exclude = find(_first, _last - 1, _sum);

		return include || exclude;
	}

public:
	static void test() {
		std::vector<int> vec{ 2, 3, 1, 1 };

		auto found = find(vec.begin(), vec.end(), 8);


		std::cout << std::boolalpha << found << std::endl;
	}

};