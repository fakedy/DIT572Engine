#pragma once




namespace Event {


	class Event {
	public:

		virtual ~Event() = default;

	};


	class ResizeEvent : public Event {
	public:


		int width;
		int height;

		ResizeEvent(int w, int h) : width(w), height(h) {
		}

	};


}