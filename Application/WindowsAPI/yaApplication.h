#pragma once
#include "Common.h"

namespace ya
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			static Application mInstance;
			return mInstance;
		}

		void Inititalize(WindowData& data);
		void Tick(); //update

		WindowData GetWindowData() { return mWindowData; }
		HDC GetHdc() { return mWindowData.hdc; }
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
