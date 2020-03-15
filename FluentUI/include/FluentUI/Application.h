#pragma once
#include <list>
#include <GLFW/glfw3.h>

namespace skiaui
{
	class Application
	{
	public:
		static Application& instance()
		{ 
			static Application __instance;
			return __instance; 
		}
		void exec();
	private:
		//Singleton pattern, disable constructors.
		Application()
		{
			initGLFW();
		}
		Application(const Application&);

		void initGLFW();
	};
}

