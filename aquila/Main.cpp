#include "Main.h"

Main Main::Instance;

Main::Main()
{
	mRunning = true;
	mRenderer = nullptr;
	mWindow = nullptr;
}

Main::~Main()
{
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit();
}

int Main::Execute()
{
	if (!OnInit())
	{
		return -1;
	}

	SDL_Event e;

	while (mRunning && mSampler->GetSample(&mSample))
	{
		while (SDL_PollEvent(&e))
		{
			OnEvent(e);
		}

		OnUpdate();
		OnRender();
	}

	mImage->Save("image.bmp");

	return 0;
}

bool Main::SetupSDL()
{
	//Initialize SDL system
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initiation error", SDL_GetError(), NULL);
		return false;
	}

#if _DEBUG
	//Enable console output
	freopen("CON", "w", stdout); // redirects stdout
	freopen("CON", "w", stderr); // redirects stderr
#endif

	//Create window
	mWindow = SDL_CreateWindow(CONSTANT::WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScene.Properties.ImageWidth, mScene.Properties.ImageHeight, SDL_WINDOW_SHOWN);
	if (mWindow == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window creation error", SDL_GetError(), NULL);
		return false;
	}

	//Setup renderer
	if ((mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE)) == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer creation error", SDL_GetError(), NULL);
		return false;
	}
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	return true;
}

bool Main::OnInit()
{
	mScene.InitScene("scene1.json");

	if (!SetupSDL())
		return false;

	mSampler = std::make_unique<Sampler>(mScene.Properties.ImageWidth, mScene.Properties.ImageHeight);
	mCamera = std::make_unique<Camera>(mScene.Properties.CameraPos, mScene.Properties.CameraDir, mScene.Properties.CameraUp, 45.0, mScene.Properties.ImageWidth, mScene.Properties.ImageHeight);
	mRaytracer.SetScene(&mScene);
	mImage = std::make_unique<Image>(mRenderer, mScene.Properties.ImageWidth, mScene.Properties.ImageHeight);

	return true;
}

void Main::OnEvent(const SDL_Event& e)
{
	if (e.type == SDL_QUIT)	mRunning = false;
}

void Main::OnUpdate()
{
	mPixelColor = COLOR::BLACK;
	Color TempColor;
	aq_float Offset = 1.0 / (mScene.Properties.PrimarySample + 1.0);
	for (int i = 1; i <= mScene.Properties.PrimarySample; i++)
	{
		for (int j = 1; j <= mScene.Properties.PrimarySample; j++)
		{
			double offX = i * Offset - 0.5;
			double offY = j * Offset - 0.5;

			mCamera->GetRay(mSample, &mEyeRay, offX, offY);
			mRaytracer.Trace(mEyeRay, &TempColor);
			mPixelColor += TempColor;
		}
	}
	mPixelColor /= mScene.Properties.PrimarySample * mScene.Properties.PrimarySample;
	mImage->Commit(mSample, mPixelColor, mScene.Properties.Exposure);
}

void Main::OnRender()
{
	SDL_RenderPresent(mRenderer);
}

#include <Windows.h>

int main(int argc, char** argv)
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	return Main::Instance.Execute();
}