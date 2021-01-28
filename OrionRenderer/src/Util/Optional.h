#pragma once

namespace Orion {
	template<typename T>
	class Optional {
	public:
		Optional() = default;

		bool has_value() { return hasValue; }
		T value() { return Value; }

		Optional<T>& operator=(T& rhs) {
			this->Value = rhs;
			return *this;
		}
	private:
		bool hasValue = false;
		T Value{};
	};
}