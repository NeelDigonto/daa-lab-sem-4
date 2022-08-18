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

class Knapsack{
private:
	template<typename CVType, typename CWType, typename Ty>
	static auto calcRec(const CVType& _values, const CWType& _weights, std::size_t _index, const Ty& _max_weight) -> typename CVType::value_type {
		using value_type = typename CVType::value_type;
		if (_index == 0 && _weights[0] <= _max_weight)
			return _weights[0];

		value_type take = std::numeric_limits<value_type>::min();
		value_type nottake = calcRec(_values, _weights, _index - 1, _max_weight);

		if(_weights[_index] < _max_weight)
			take = calcRec(_values, _weights, _index - 1, _max_weight - _weights[_index]);

		return std::max(take, nottake);

	}

	template<typename CVType, typename CWType, typename Ty>
	static auto KnapsackRec(const CVType& _values, const CWType& _weights, const Ty& _max_weight) -> typename CVType::value_type {
		return calcRec(_values, _weights, _values.size() - 1, _max_weight);

	}

public:
	static void test() {
		std::vector<unsigned int> value{ 60, 100, 120 };
		std::vector<unsigned int> weight{ 10, 20, 30 };;
		unsigned int max_weight = 50;

		auto ans = KnapsackRec(value, weight, max_weight);

		std::cout << ans << std::endl;
	}

};

//220