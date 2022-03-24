#pragma once

#include <memory>



namespace Origin {
	
	template<typename T>
	using ScopedReference = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr ScopedReference<T>MakeScopedReference(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Reference = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Reference<T>MakeReference(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}