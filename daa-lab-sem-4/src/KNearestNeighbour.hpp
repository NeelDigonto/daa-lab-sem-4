#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <variant>
#include <limits>
#include <exception>
#include <stdexcept>
#include <iterator>

// 1, 2, 3, 4, 5, 6, 7, 8, 9, 
// 3, 5, 8, 9, 2, 1, 7, 4, 6, 
// 4 5 6
// 
// 1. Find neighbors of the median element in an array using partitioning strategy of Quick-Sorting method.*/


class KNearestNeighbour {
public:
	template<typename CType, typename Pred>
	static int partition(typename CType& arr, int l, int r, Pred _comp)
	{
		typename CType::value_type x = arr[r];
		int i = l;

		for (int j = l; j <= r - 1; ++j)
		{
			if (_comp(arr[j], x))
			{
				std::swap(arr[i], arr[j]);
				i++;
			}
		}
		std::swap(arr[i], arr[r]);
		return i;
	}

	template<typename CType, typename Pred>
	static void nth_element(CType& arr, int l, int r, unsigned int k, Pred _comp)
	{
		if (k > r - l + 1)
			throw std::invalid_argument("Invalid Arguments");

		int index = partition(arr, l, r, _comp);

		if (index - l == k - 1)
			return;

		if (index - l > k - 1)
			nth_element(arr, l, index - 1, k, _comp);
		else
			nth_element(arr, index + 1, r, k - index + l - 1, _comp);
	}

	static double handleMedian(std::vector<int>& _container) {

		auto begin = _container.begin();
		auto end = _container.end();
		const auto sample_size = std::distance(begin, end);

		if (sample_size % 2 != 0) {
			auto iter = begin + sample_size / 2;
			nth_element(_container, 0, _container.size() - 1, sample_size / 2, std::less<int>{});
			auto val = *iter;
			_container.erase(iter);
			return val;
		}
		else {
			//auto mid_m1 = begin + sample_size / 2;
			//auto mid_p1 = begin + (sample_size - 1) / 2;
			auto mid_m1 = sample_size / 2;
			auto mid_p1 = (sample_size - 1) / 2;
			nth_element(_container, 0, _container.size() - 1, sample_size / 2, std::less<int>{});
			nth_element(_container, 0, _container.size() - 1, (sample_size - 1) / 2, std::less<int>{});

			return static_cast<double>(_container[mid_m1] + _container[mid_p1]) / 2;
		}

	}

	template<typename CType, typename BckIt>
	static void kNearestNeighbour(CType _container, BckIt _back_inserter, const size_t _k) {

		double median = handleMedian(_container);

		std::vector<std::pair<double, int>> table;

		for (auto iter{ _container.begin() }; iter != _container.end(); ++iter) {
			table.emplace_back(std::pair{ std::abs(median - *iter), *iter });
		}


		nth_element(table, 0, table.size() - 1, _k,
			[](std::pair<double, int> lhs, std::pair<double, int> rhs) {
				return lhs.first < rhs.first;
			});

		for (auto iter = table.begin(); iter != table.begin() + _k * 2; ++iter) {
			*(_back_inserter++) = iter->second;
		}

	}

	static void test() {
		std::vector<int> arr{ 3, 5, 8, 9, 2, 1, 7, 4, 6 };

		std::vector<int> res;

		kNearestNeighbour(arr, std::back_inserter(res), 2);

		for (auto it : res)
			std::cout << it << ", ";

	}
};

/*
template<typename CType>
static auto handleMedian(CType _container) -> typename CType::value_type {

	auto begin = _container.begin();
	auto end = _container.end();
	const auto sample_size = std::distance(begin, end);

	if (sample_size % 2 != 0) {
		auto iter = begin + sample_size / 2;
		std::nth_element(begin, begin + sample_size / 2, end);
		auto val = *iter;
		_container.erase(iter);
		return *iter;
	}
	else {
		auto mid_m1 = begin + sample_size / 2;
		auto mid_p1 = begin + (sample_size - 1) / 2;
		std::nth_element(begin, mid_m1, end);
		std::nth_element(begin, mid_p1, end);

		return (*mid_m1 + *mid_p1) / 2;
	}

}

template<typename CType, typename InsertIterator>
static void kNearestNeighbour(CType _container, InsertIterator _back_inserter, const size_t _k) {

	auto begin = _container.begin();
	auto end = _container.end();

	if (std::distance(begin, end) < _k * 2)
		throw std::invalid_argument("K is out range");

	using value_t = typename CType::value_type;
	using pair_t = std::pair<value_t, value_t>;
	std::vector<pair_t> table;
	table.reserve(std::distance(begin, end));

	const auto& median = handleMedian(_container);

	// create template specalization for bigger elements

	for (auto iter{ begin }; iter != end; ++iter) {
		table.emplace_back(std::pair{ std::abs(median - *iter), *iter });
	}

	std::nth_element(table.begin(), table.begin() + _k * 2, table.end(),
		[](const pair_t& _lhs, const pair_t& _rhs) {
			return _lhs.first < _rhs.first;
		});

	for (auto iter = table.begin() + 1; iter != table.begin() + _k * 2; ++iter) {
		*(_back_inserter++) = iter->second;
	}

}


void testKNearestNeighbour() {
	using value_t = int;
	std::vector<value_t> sample{ 3, 5, 8, 9, 2, 1, 7, 4, 6 };
	std::vector<value_t> result;

	kNearestNeighbour(sample, std::back_inserter(result), 1);

	for (auto& element : result) {
		std::cout << element << " ";
	}

	std::cout << std::endl;
}

*/


/*
	-> typename std::pair<typename std::pair<typename Iter::value_type, typename Iter::value_type>::iterator,
	typename std::pair<typename Iter::value_type, typename Iter::value_type>::iterator>
*/
/*
template <class _RanIt, class _Pr>
void partition(_RanIt _begin, _RanIt _nth, _RanIt _end, _Pr _Pred) {
	if (_start == _end) return;

	auto pivot = _end - 1, i = _begin;

	for (auto j = _begin; j <= r - 1; ++j)
	{
		if (*j <= *pivot)
		{
			std::iter_swap(i, j);
			i++;
		}
	}
	std::iter_swap(i, r);
	return i;
}

template <class _RanIt, class _Pr>
void nth_element(_RanIt _begin, _RanIt _nth, _RanIt _end, _Pr _Pred) {
	if (_start == _end) return;

	auto pivot = _end - 1, i = _begin;

	for (auto j = _begin; j <= r - 1; ++j)
	{
		if (*j <= *pivot)
		{
			std::iter_swap(i, j);
			i++;
		}
	}
	std::iter_swap(i, r);
	return i;
}*/