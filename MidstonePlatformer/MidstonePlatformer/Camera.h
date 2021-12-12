#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "Point.h"
#include "Math.h"
#include "Vector.h"

class Camera {
public:

	void Update(float dt);
	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2f GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }
	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

private:
	Camera() {m_ViewBox = { 0, 0, 1280, 720 }; }
	Point* m_Target;
	Vector2f m_Position;
	SDL_Rect m_ViewBox;
	static Camera* s_Instance;

};

#endif // CAMERA_H