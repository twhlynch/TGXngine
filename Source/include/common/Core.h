#pragma once

#include <any>
#include <array>
#include <cstdlib>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

namespace TGX
{
template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

using String = std::string;

template <typename K, typename V>
using Map = std::unordered_map<K, V>;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using List = std::list<T>;

template <typename T>
using Set = std::set<T>;

template <typename T, size_t N>
using Array = std::array<T, N>;

template <typename T>
using Queue = std::queue<T>;

template <typename X, typename Y>
using Pair = std::pair<X, Y>;

template <typename X, typename Y, typename Z>
using Tuple = std::tuple<X, Y, Z>;

template <typename T>
using Function = std::function<T>;

template <typename T>
using Optional = std::optional<T>;

using Any = std::any;

template <typename K, typename V, typename H>
using HashableMap = std::unordered_map<K, V, H>;
} // namespace TGX
