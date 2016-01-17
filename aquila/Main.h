#ifndef _AQUILA_MAIN_H
#define _AQUILA_MAIN_H

#include "Common.h"
#include "Raytracer.h"
#include "Pathtracer.h"
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
	bool SetupSDL();
	void OnEvent(const SDL_Event& e);
	void OnUpdate();
	void OnRender();

private:
	bool mRunning;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::unique_ptr<Sampler> mSampler;
	Sample mSample;
	Ray mEyeRay;
	std::unique_ptr<Camera> mCamera;
	Raytracer mRaytracer;
	Pathtracer mPathtracer;
	Scene mScene;
	Color mPixelColor;
	std::unique_ptr<Image> mImage;

	int mUpdateCycle;
};

#endif