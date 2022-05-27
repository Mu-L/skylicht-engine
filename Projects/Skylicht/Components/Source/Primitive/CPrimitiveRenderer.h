/*
!@
MIT License

Copyright (c) 2022 Skylicht Technology CO., LTD

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

#include "Entity/IRenderSystem.h"
#include "RenderMesh/CMesh.h"
#include "Material/CMaterial.h"
#include "CPrimiviteData.h"

namespace Skylicht
{
	class CPrimitiveRenderer : public IRenderSystem
	{
	protected:
		CMesh* m_mesh[CPrimiviteData::Count];
		CMaterial* m_materials[CPrimiviteData::Count];

		core::array<CPrimiviteData*> m_primitives[CPrimiviteData::Count];
		core::array<core::matrix4> m_transforms[CPrimiviteData::Count];

	public:
		CPrimitiveRenderer();

		virtual ~CPrimitiveRenderer();

		void initMesh(IMesh* primitiveMesh, CPrimiviteData::EPrimitive primitive);

		virtual void beginQuery(CEntityManager* entityManager);

		virtual void onQuery(CEntityManager* entityManager, CEntity* entity);

		virtual void init(CEntityManager* entityManager);

		virtual void update(CEntityManager* entityManager);

		virtual void render(CEntityManager* entityManager);

		void renderPrimitive(CEntityManager* entityManager,
			core::array<CPrimiviteData*>& primitives,
			core::array<core::matrix4>& transforms,
			CMesh* mesh,
			CMaterial* material
		);
	};
}