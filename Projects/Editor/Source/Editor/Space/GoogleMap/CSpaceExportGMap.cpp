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

#include "pch.h"
#include "GUI/CGUIContext.h"
#include "CSpaceExportGMap.h"
#include "DownloadMap.h"
#include "AssetManager/CAssetManager.h"

namespace Skylicht
{
	namespace Editor
	{
		CSpaceExportGMap::CSpaceExportGMap(GUI::CWindow* window, CEditor* editor) :
			CSpace(window, editor),
			m_progressBar(NULL),
			m_statusText(NULL),
			m_image(NULL),
			m_state(None),
			m_x1(0),
			m_y1(0),
			m_x2(0),
			m_y2(0),
			m_x(0),
			m_y(0),
			m_z(0),
			m_type(0),
			m_gridSize(0)
		{
			m_progressBar = new GUI::CProgressBar(window);
			m_progressBar->dock(GUI::EPosition::Top);
			m_progressBar->setMargin(GUI::SMargin(14.0f, 14.0, 14.0, 0.0f));

			m_statusText = new GUI::CLabel(window);
			m_statusText->dock(GUI::EPosition::Fill);
			m_statusText->setMargin(GUI::SMargin(14.0f, 5.0, 14.0, 0.0f));
			m_statusText->setWrapMultiline(true);
			m_statusText->setString(L"Exporting...");
		}

		CSpaceExportGMap::~CSpaceExportGMap()
		{
		}

		void CSpaceExportGMap::update()
		{
			if (m_state == Init)
			{
				u32 imageWidth = (m_x2 - m_x1) * m_gridSize;
				u32 imageHeight = (m_y2 - m_y1) * m_gridSize;
				m_image = getVideoDriver()->createImage(video::ECF_R8G8B8, core::dimension2du(imageWidth, imageHeight));
				m_state = Draw;
			}
			else if (m_state == Draw)
			{
				long total = (m_x2 - m_x1) * (m_y2 - m_y1);
				float f = m_drawElement / (float)total;
				m_progressBar->setPercent(f);

				// write image
				std::string localPath = getMapTileLocalCache((EImageMapType)m_type, m_x, m_y, m_z);

				IImage* tile = getVideoDriver()->createImageFromFile(localPath.c_str());
				if (tile != NULL)
				{
					tile->copyTo(m_image, core::vector2di((m_x - m_x1) * m_gridSize, (m_y - m_y1) * m_gridSize));
					tile->drop();
				}
				else
				{
					// need download
				}

				// next element
				m_x++;
				if (m_x >= m_x2)
				{
					m_x = m_x1;
					m_y++;
				}

				if (++m_drawElement == total)
					m_state = Write;
			}
			else if (m_state == Write)
			{
				m_progressBar->setPercent(1.0f);
				getVideoDriver()->writeImageToFile(m_image, m_path.c_str());
				m_image->drop();
				m_image = NULL;
				m_state = Finish;
			}
			else if (m_state == Finish)
			{
				// done!
			}
			CSpace::update();
		}

		void CSpaceExportGMap::onDestroy(GUI::CBase* base)
		{
			CSpace::onDestroy(base);
		}

		bool CSpaceExportGMap::isFinish()
		{
			return m_state == Finish;
		}

		void CSpaceExportGMap::exportMap(const char* path, long x1, long y1, long x2, long y2, int zoom, int type, int gridSize)
		{
			m_path = path;
			m_x1 = x1;
			m_y1 = y1;
			m_x2 = x2;
			m_y2 = y2;

			m_x = x1;
			m_y = y1;
			m_z = zoom;

			m_type = type;

			m_drawElement = 0;
			m_gridSize = gridSize;
			m_progressBar->setPercent(0.0f);
			m_state = Init;
		}
	}
}