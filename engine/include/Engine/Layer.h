#pragma once


namespace Engine {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void start() = 0;

		virtual void update() = 0;

	};
}