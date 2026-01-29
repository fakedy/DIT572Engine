#pragma once


// this is an abstract base class for scenes



namespace Engine {

	class Scene {
	public:
		virtual ~Scene() = default;

		virtual void start() = 0;

		virtual void update() = 0;

	};
}