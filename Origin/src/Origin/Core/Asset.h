#pragma once

#include <memory>

namespace Origin {

	template<typename T>
	using ScopedReference = std::unique_ptr<T>;

	template<typename T>
	using Reference = std::shared_ptr<T>;

}