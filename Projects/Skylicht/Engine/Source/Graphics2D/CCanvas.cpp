/*
!@
MIT License

Copyright (c) 2019 Skylicht Technology CO., LTD

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

#include "pch.h"
#include "CCanvas.h"
#include "Graphics2D/CGraphics2D.h"

namespace Skylicht
{
	CCanvas::CCanvas() :
		m_sortDepth(0),
		m_enable3DBillboard(false),
		m_renderCamera(NULL)
	{
		CGraphics2D* g = CGraphics2D::getInstance();
		float w = (float)g->getScreenSize().Width;
		float h = (float)g->getScreenSize().Height;

		// default rect is fullscreen
		m_rect = core::rectf(0.0f, 0.0f, w, h);

		// add root
		m_root = new CGUIElement(this, NULL, m_rect);
		m_root->setDock(CGUIElement::DockFill);

		// add this canvas
		CGraphics2D::getInstance()->addCanvas(this);
	}

	CCanvas::~CCanvas()
	{
		// remove all entity gui
		delete m_root;

		// remove this canvas
		CGraphics2D::getInstance()->removeCanvas(this);
	}

	void CCanvas::initComponent()
	{
	}

	void CCanvas::updateComponent()
	{
	}

	void CCanvas::layout()
	{
		// layout on 2d ui
		if (m_renderCamera->getProjectionType() == CCamera::OrthoUI)
		{
			// get current screen size
			CGraphics2D* g = CGraphics2D::getInstance();
			float w = (float)g->getScreenSize().Width;
			float h = (float)g->getScreenSize().Height;

			m_rect = core::rectf(0.0f, 0.0f, w, h);

			m_root->layout(m_rect);
		}
	}

	void CCanvas::render(CCamera* camera)
	{
		m_renderCamera = camera;

		// render
		std::stack<CGUIElement*> renderEntity;
		renderEntity.push(m_root);

		while (renderEntity.size() > 0)
		{
			CGUIElement* entity = renderEntity.top();
			renderEntity.pop();

			if (entity->isVisible() == false)
				continue;

			entity->update(camera);
			entity->calcAbsoluteTransform();

			// apply mask
			entity->applyCurrentMask(entity->getMask());

			// try set the parrent mask
			CGUIElement* parent = entity->getParent();
			if (parent != NULL)
			{
				CGUIMask* mask = parent->getMask();
				if (mask == NULL)
					mask = parent->getCurrentMask();

				if (mask != NULL)
					entity->applyCurrentMask(mask);
			}

			CGUIMask* mask = entity->getCurrentMask();
			if (mask != NULL)
				mask->beginMaskTest(camera);

			entity->render(camera);

			if (mask != NULL)
				mask->endMaskTest();

			// note
			// we use stack to render parent -> child
			// so we must inverse render position because stack = Last-In First-Out (LIFO)
			for (int i = (int)entity->m_childs.size() - 1; i >= 0; i--)
				renderEntity.push(entity->m_childs[i]);
		}
	}

	/*
	* Element constructor
	*/

	CGUIElement* CCanvas::createElement()
	{
		CGUIElement* element = new CGUIElement(this, m_root, m_rect);
		return element;
	}

	CGUIElement* CCanvas::createElement(const core::rectf& r)
	{
		CGUIElement* element = new CGUIElement(this, m_root, r);
		return element;
	}

	CGUIElement* CCanvas::createElement(CGUIElement* e, const core::rectf& r)
	{
		CGUIElement* element = new CGUIElement(this, e, r);
		return element;
	}

	/*
	* Image constructor
	*/

	CGUIImage* CCanvas::createImage()
	{
		CGUIImage* element = new CGUIImage(this, m_root, m_rect);
		return element;
	}

	CGUIImage* CCanvas::createImage(const core::rectf& r)
	{
		CGUIImage* element = new CGUIImage(this, m_root, r);
		return element;
	}

	CGUIImage* CCanvas::createImage(CGUIElement* e, const core::rectf& r)
	{
		CGUIImage* element = new CGUIImage(this, e, r);
		return element;
	}

	/*
	* Text constructor
	*/

	CGUIText* CCanvas::createText(IFont* font)
	{
		CGUIText* element = new CGUIText(this, m_root, m_rect, font);
		return element;
	}

	CGUIText* CCanvas::createText(const core::rectf& r, IFont* font)
	{
		CGUIText* element = new CGUIText(this, m_root, r, font);
		return element;
	}

	CGUIText* CCanvas::createText(CGUIElement* e, IFont* font)
	{
		CGUIText* element = new CGUIText(this, e, e->getRect(), font);
		return element;
	}

	CGUIText* CCanvas::createText(CGUIElement* e, const core::rectf& r, IFont* font)
	{
		CGUIText* element = new CGUIText(this, e, r, font);
		return element;
	}

	/*
	* Sprite constructor
	*/

	CGUISprite* CCanvas::createSprite(SFrame* frame)
	{
		CGUISprite* element = new CGUISprite(this, m_root, m_rect, frame);
		return element;
	}

	CGUISprite* CCanvas::createSprite(const core::rectf& r, SFrame* frame)
	{
		CGUISprite* element = new CGUISprite(this, m_root, r, frame);
		return element;
	}

	CGUISprite* CCanvas::createSprite(CGUIElement* e, SFrame* frame)
	{
		CGUISprite* element = new CGUISprite(this, e, e->getRect(), frame);
		return element;
	}

	CGUISprite* CCanvas::createSprite(CGUIElement* e, const core::rectf& r, SFrame* frame)
	{
		CGUISprite* element = new CGUISprite(this, e, r, frame);
		return element;
	}

	/*
	* Mask constructor
	*/

	CGUIMask* CCanvas::createMask(const core::rectf& r)
	{
		CGUIMask* element = new CGUIMask(this, m_root, r);
		return element;
	}

	CGUIMask* CCanvas::createMask(CGUIElement* e, const core::rectf& r)
	{
		CGUIMask* element = new CGUIMask(this, e, r);
		return element;
	}

	/*
	* Rect constructor
	*/

	CGUIRect* CCanvas::createRect(const video::SColor& c)
	{
		CGUIRect* element = new CGUIRect(this, m_root, m_rect);
		element->setColor(c);
		return element;
	}

	CGUIRect* CCanvas::createRect(const core::rectf& r, const video::SColor& c)
	{
		CGUIRect* element = new CGUIRect(this, m_root, r);
		element->setColor(c);
		return element;
	}

	CGUIRect* CCanvas::createRect(CGUIElement* e, const core::rectf& r, const video::SColor& c)
	{
		CGUIRect* element = new CGUIRect(this, e, r);
		element->setColor(c);
		return element;
	}


	/*
	* RoundedRect constructor
	*/

	CGUIRoundedRect* CCanvas::createRoundedRect(float radius, const video::SColor& c)
	{
		CGUIRoundedRect* element = new CGUIRoundedRect(this, m_root, m_rect, radius);
		element->setColor(c);
		return element;
	}

	CGUIRoundedRect* CCanvas::createRoundedRect(const core::rectf& r, float radius, const video::SColor& c)
	{
		CGUIRoundedRect* element = new CGUIRoundedRect(this, m_root, r, radius);
		element->setColor(c);
		return element;
	}

	CGUIRoundedRect* CCanvas::createRoundedRect(CGUIElement* e, const core::rectf& r, float radius, const video::SColor& c)
	{
		CGUIRoundedRect* element = new CGUIRoundedRect(this, e, r, radius);
		element->setColor(c);
		return element;
	}
}