#pragma once
#include "Common.h"

namespace ya
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			return mInstance;
		}

		void Inititalize(WindowData& data);
		void Tick(); //update

		WindowData GetWindowData() { return mWindowData; }
		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor color) { return mBrushs[(UINT)color]; }

	private:
		Application();
		~Application();

		void initializeWindow(WindowData& data);

	private:
		static Application mInstance;
		WindowData mWindowData;

		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushs[(UINT)eBrushColor::End];
	};
}
