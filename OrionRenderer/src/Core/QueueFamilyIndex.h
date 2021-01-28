#pragma once
#include <cstdint>
#include "../Util/Optional.h"
#include "GraphicsAdapter.h"
#include "Surface.h"
namespace Orion {
	class QueueFamilyIndices {
	public:
		QueueFamilyIndices() = default;
		Optional<uint32_t> Graphics{};
		Optional<uint32_t> Present{};

		static QueueFamilyIndices FindQueueFamilies(GraphicsAdapter* graphicsAdapter, Surface& surface);

		bool IsComplete() {
			return Graphics.has_value() && Present.has_value();
		}
	};
}