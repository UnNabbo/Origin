#pragma once

#include <memory>

namespace Origin {

	template<typename T>
	using ScopedAssetRef = std::unique_ptr<T>;

	template<typename T>
	using AssetRef = std::shared_ptr<T>;

}