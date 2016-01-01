#ifndef _AQUILA_MAIN_H
#define _AQUILA_MAIN_H

#include "Common.h"
#include "Raytracer.h"
#include "Camera.h"
#include "Sampler.h"
#include "Image.h"

class Main
{
public:
	static Main Instance;
	int Execute();

private:
	Main();
	~Main();

	bool OnInit();
	bool SetupRaytracer();
	void OnEvent(const SDL_Event& e);
	void OnUpdate();
	void OnRender();

private:
	bool mRunning;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	Sampler mSampler;
	std::unique_ptr<Camera> mCamera;
	Raytracer mRaytracer;
	Scene mScene;
	std::unique_ptr<Image> mImage;
};

#endif