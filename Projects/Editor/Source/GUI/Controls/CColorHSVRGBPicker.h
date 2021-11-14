/*
!@
MIT License

Copyright (c) 2020 Skylicht Technology CO., LTD

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
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

#include "CBase.h"
#include "CButton.h"
#include "CTextBox.h"
#include "CRawImage.h"
#include "CLabel.h"
#include "CSlider.h"

#include "CColorHuePicker.h"
#include "CColorSVPicker.h"

namespace Skylicht
{
	namespace Editor
	{
		namespace GUI
		{
			class CColorHSVRGBPicker : public CBase
			{
			protected:
				CGUIImage* m_hsvImage;
				CGUIImage* m_hueImage;
				CGUIImage* m_colorBGImage;

				CColorSVPicker* m_sv;
				CColorHuePicker* m_hue;

				CButton* m_buttonOK;
				CButton* m_buttonCancel;

				CTextBox* m_textboxHex;
				CTextBox* m_textboxColor;

				CSlider* m_red;
				CSlider* m_green;
				CSlider* m_blue;
				CSlider* m_alpha;

				CSlider* m_s;
				CSlider* m_v;

				SGUIColor m_color;
				SGUIColor m_oldColor;

				SRect m_previewBounds;
			public:
				CColorHSVRGBPicker(CBase* parent);

				virtual ~CColorHSVRGBPicker();

				virtual void renderUnder();

				const SGUIColor& getColor()
				{
					return m_color;
				}

				inline void setOldColor(const SGUIColor& c)
				{
					m_oldColor = c;
				}

				void setColor(const SGUIColor& c);

				void changeHue(int hue);

				void changeSV(int s, int v);

				void refreshColor();

			protected:

				void onRGBAChange(CBase* base);

				void onSVChange(CBase* base);

				void updateColorText();

				void setupHSVBitmap(unsigned char h, unsigned char s, unsigned char v);

				void setupHUEBitmap();

				void setupColorBGBitmap();
			};
		}
	}
}