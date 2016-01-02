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

	while (mRunning && mSampler.GetSample(&mSample))
	{
		while (SDL_PollEvent(&e))
		{
			OnEvent(e);
		}

		OnUpdate();
		OnRender();
	}

	return 0;
}

bool Main::OnInit()
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
	mWindow = SDL_CreateWindow(CONSTANT::WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONSTANT::IMAGE_WIDTH, CONSTANT::IMAGE_HEIGHT, SDL_WINDOW_SHOWN);
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
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	return SetupRaytracer();
}

bool Main::SetupRaytracer()
{
	mCamera = std::make_unique<Camera>(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, CONSTANT::IMAGE_WIDTH, CONSTANT::IMAGE_HEIGHT);
	mScene.InitScene();
	mRaytracer.SetScene(&mScene);
	mImage = std::make_unique<Image>(mRenderer, CONSTANT::IMAGE_WIDTH, CONSTANT::IMAGE_HEIGHT);

	return true;
}

void Main::OnEvent(const SDL_Event& e)
{
	if (e.type == SDL_QUIT)	mRunning = false;
}

void Main::OnUpdate()
{
	mCamera->GetRay(mSample, &mEyeRay, 0, 0);
	mRaytracer.Trace(mEyeRay, &mPixelColor);
	mImage->Commit(mSample, mPixelColor);
}

void Main::OnRender()
{
	SDL_RenderPresent(mRenderer);
}

int main(int argc, char** argv)
{
	return Main::Instance.Execute();
}