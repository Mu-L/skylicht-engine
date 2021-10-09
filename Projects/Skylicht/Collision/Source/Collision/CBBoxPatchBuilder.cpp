/*
!@
MIT License

Copyright (c) 2021 Skylicht Technology CO., LTD

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
#include "CBBoxPatchBuilder.h"

namespace Skylicht
{
	CBBoxPatchBuilder::CBBoxPatchBuilder()
	{

	}

	CBBoxPatchBuilder::~CBBoxPatchBuilder()
	{
		clear();
	}

	void CBBoxPatchBuilder::clear()
	{
		CCollisionBuilder::clear();
	}

	void CBBoxPatchBuilder::build()
	{
		const u32 start = os::Timer::getRealTime();
		u32 numPoly = 0;

		core::aabbox3df size;

		// step 1: caculator the box size
		for (u32 i = 0, n = m_nodes.size(); i < n; i++)
		{
			if (i == 0)
				size = m_nodes[i]->getTransformBBox();
			else
				size.addInternalBox(m_nodes[i]->getTransformBBox());
		}

		c8 tmp[256];
		sprintf(tmp, "Needed %ums to CBBoxPatchBuilder::build", os::Timer::getRealTime() - start);
		os::Printer::log(tmp, ELL_INFORMATION);
	}
}