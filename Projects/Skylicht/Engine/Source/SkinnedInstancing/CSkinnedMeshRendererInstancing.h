/*
!@
MIT License

Copyright (c) 2024 Skylicht Technology CO., LTD

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

#include "RenderMesh/CRenderMeshData.h"
#include "RenderMesh/CMeshRenderSystem.h"
#include "RenderMesh/CMeshRendererInstancing.h"

#include "Transform/CWorldTransformData.h"
#include "IndirectLighting/CIndirectLightingData.h"

#include "CTransformTextureData.h"

namespace Skylicht
{
	class SKYLICHT_API CSkinnedMeshRendererInstancing : public CMeshRenderSystem
	{
	protected:
		core::array<CRenderMeshData*> m_meshs;
		core::array<CTransformTextureData*> m_textures;

		std::map<SMeshInstancingData*, SMeshInstancingGroup*> m_groups;

	public:
		CSkinnedMeshRendererInstancing();

		virtual ~CSkinnedMeshRendererInstancing();

		virtual void beginQuery(CEntityManager* entityManager);

		virtual void onQuery(CEntityManager* entityManager, CEntity** entities, int numEntity);

		virtual void init(CEntityManager* entityManager);

		virtual void update(CEntityManager* entityManager);

		virtual void render(CEntityManager* entityManager);
	};
}