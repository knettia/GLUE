#pragma once // UNUSED / WIP

// std
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <cstring>

namespace glue
{
	template <typename _base>
	class polymorphic_vector
	{
	private:
		struct header
		{
			uint16_t offset;
			uint16_t size;
			uint16_t type_id;
		};

		std::vector<header> index;
		std::vector<uint8_t> buffer;
		std::unordered_map<uint16_t, std::function<std::unique_ptr<_base>()>> type_registry;

		template <typename _T>
		void register_type()
		{
			type_registry.insert(
			    {typeid(_T).hash_code(),
			     []() -> std::unique_ptr<_base>
			     {
				     return std::make_unique<_T>();
			     }});
		}

	public:
		std::unique_ptr<_base> get(const unsigned int &i)
		{
			const header &obj_header = index[i];
			if (type_registry.find(obj_header.type_id) != type_registry.end())
			{
				auto return_function = type_registry[obj_header.type_id];
				auto obj = return_function();
				std::memcpy(obj.get(), buffer.data() + obj_header.offset, obj_header.size);
				return obj;
			}

			std::cerr << "internal error." << '\n';
		}

		template <typename _T>
		void push_back(const _T &obj)
		{
			static_assert(std::is_base_of<_base, _T>::value, "type must derive from base");

			uint16_t obj_size = sizeof(obj);
			uint16_t type_id = typeid(_T).hash_code();
			uint16_t offset = buffer.size();
			buffer.resize(offset + obj_size);
			std::memcpy(buffer.data() + offset, static_cast<const void *>(&obj), obj_size);
			if (type_registry.find(type_id) == type_registry.end())
			{
				register_type<_T>();
			}

			index.push_back({offset, obj_size, type_id});
		}
	};
}