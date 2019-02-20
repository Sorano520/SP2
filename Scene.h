#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual bool prev_state() = 0;
	virtual bool next_state() = 0;
};

#endif