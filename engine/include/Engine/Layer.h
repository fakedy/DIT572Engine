#pragma once


// this is an abstract base class for layers



namespace Engine {

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void start() = 0;

		virtual void update() = 0;

	};
}