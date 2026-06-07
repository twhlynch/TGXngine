#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

struct Payload;

using Complex = std::variant<std::monostate, int, float, bool, std::string, std::vector<Payload>, std::unordered_map<std::string, Payload>>;

template <typename T>
struct is_payload : std::false_type
{
};
template <>
struct is_payload<Payload> : std::true_type
{
};

struct Payload
{
	Complex value;

	Payload() : value(std::monostate{}) {}

	Payload(const Payload &) = default;
	Payload(Payload &&) = default;
	Payload &operator=(const Payload &) = default;
	Payload &operator=(Payload &&) = default;

	template <typename T>
	Payload(T &&v)
		requires(!std::is_same_v<std::decay_t<T>, Payload>)
	{
		using DecayT = std::decay_t<T>;
		if constexpr (std::is_same_v<DecayT, const char *>)
		{
			value = std::string(v);
		}
		else
		{
			value = std::forward<T>(v);
		}
	}

	Payload &operator[](const std::string &key)
	{
		if (auto *pval = std::get_if<std::unordered_map<std::string, Payload>>(&value))
		{
			return (*pval)[key];
		}
		throw std::runtime_error("PAYLOAD is not an object");
	}

	const Payload &operator[](const std::string &key) const
	{
		if (const auto *pval = std::get_if<std::unordered_map<std::string, Payload>>(&value))
		{
			auto it = pval->find(key);
			if (it != pval->end())
			{
				return it->second;
			}
			throw std::runtime_error("Key not found: " + key);
		}
		throw std::runtime_error("PAYLOAD is not an object");
	}

	int AsInt() const
	{
		return std::get<int>(value);
	}
	float AsDouble() const
	{
		return std::get<float>(value);
	}
	bool AsBool() const
	{
		return std::get<bool>(value);
	}
	std::string AsString() const
	{
		return std::get<std::string>(value);
	}
};

template <typename T>
Payload MakePayload(T &&v)
{
	return Payload(std::forward<T>(v));
}

template <typename... Ts>
Payload MakePayloadArray(Ts &&...elems)
{
	std::vector<Payload> arr;
	arr.reserve(sizeof...(elems));
	(arr.push_back(MakeJSON(std::forward<Ts>(elems))), ...);
	return std::move(arr);
}

inline void InsertPairs(std::unordered_map<std::string, Payload> & /*unused*/) {}

template <typename K, typename V, typename... Rest>
void InsertPairs(std::unordered_map<std::string, Payload> &m, K &&key, V &&val, Rest &&...rest)
{
	m[std::string(key)] = MakePayload(std::forward<V>(val));
	InsertPairs(m, std::forward<Rest>(rest)...);
}

template <typename... Ts>
Payload MakePayloadObject(Ts &&...keyvals)
{
	static_assert(sizeof...(Ts) % 2 == 0, "Key-value pairs required (even number of arguments)");

	std::unordered_map<std::string, Payload> m;
	InsertPairs(m, std::forward<Ts>(keyvals)...);
	return std::move(m);
}

inline std::ostream &operator<<(std::ostream &os, const Payload &j)
{
	std::visit([&](auto &&arg) {
		using T = std::decay_t<decltype(arg)>;

		if constexpr (std::is_same_v<T, std::monostate>)
		{
			os << "null";
		}
		else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, float>)
		{
			os << arg;
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			os << (arg ? "true" : "false");
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			os << '"' << arg << '"';
		}
		else if constexpr (std::is_same_v<T, std::vector<Payload>>)
		{
			os << "[";
			bool first = true;
			for (const auto &el : arg)
			{
				if (!first)
				{
					os << ", ";
				}
				os << el;
				first = false;
			}
			os << "]";
		}
		else if constexpr (std::is_same_v<T, std::unordered_map<std::string, Payload>>)
		{
			os << "{";
			bool first = true;
			for (const auto &kv : arg)
			{
				if (!first)
				{
					os << ", ";
				}
				os << '"' << kv.first << "\": " << kv.second;
				first = false;
			}
			os << "}";
		}
	},
			   j.value);
	return os;
}
