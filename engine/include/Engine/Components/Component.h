#pragma once

namespace Engine {

	class GameObject;

	class Component {
	public:

		virtual ~Component() = default;


		virtual void onAdd() = 0;


		GameObject* owner{ nullptr };


	};

}