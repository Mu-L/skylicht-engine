/*
!@
MIT License

Copyright (c) 2020 Skylicht Technology CO., LTD

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including without limitation the Rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This file is part of the "Skylicht Engine".
https://github.com/skylicht-lab/skylicht-engine
!#
*/

#pragma once

#include "SkylichtEngine.h"
#include "Editor/Space/CSpace.h"

namespace Skylicht
{
	namespace Editor
	{
		class CSpaceGUIDesign : public CSpace
		{
		protected:
			GUI::CToolbar* m_toolBar;
			GUI::CRulerBar* m_topRuler;
			GUI::CRulerBar* m_leftRuler;
			GUI::CBase* m_view;

			GUI::CLabel* m_textZoom;

			float m_guiWidth;
			float m_guiHeight;
			float m_guiScale;

			float m_pressX;
			float m_pressY;
			float m_viewX;
			float m_viewY;

			bool m_middleDrag;

			CScene* m_scene;
			CCamera* m_guiCamera;

		public:
			CSpaceGUIDesign(GUI::CWindow* window, CEditor* editor);

			virtual ~CSpaceGUIDesign();

			void openGUI(const char* path);

		protected:

			void onMiddleMouseClick(GUI::CBase* view, float x, float y, bool down);

			void onMouseMoved(GUI::CBase* view, float x, float y, float deltaX, float deltaY);

			void onMouseWheel(GUI::CBase* view, int delta);

			void onZoomIn(GUI::CBase* base);

			void onZoomOut(GUI::CBase* base);

			void onRender(GUI::CBase* base);
		};
	}
}