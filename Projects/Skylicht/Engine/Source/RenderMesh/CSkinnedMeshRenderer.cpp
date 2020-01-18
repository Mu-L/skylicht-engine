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
#include "CSkinnedMeshRenderer.h"

#include "Culling/CCullingData.h"
#include "Material/Shader/CShaderManager.h"

namespace Skylicht
{
	CSkinnedMeshRenderer::CSkinnedMeshRenderer()
	{
		m_pipelineType = IRenderPipeline::Mix;
	}

	CSkinnedMeshRenderer::~CSkinnedMeshRenderer()
	{

	}

	void CSkinnedMeshRenderer::beginQuery()
	{
		m_meshs.set_used(0);
		m_transforms.set_used(0);
	}

	void CSkinnedMeshRenderer::onQuery(CEntityManager *entityManager, CEntity *entity)
	{
		CRenderMeshData *meshData = entity->getData<CRenderMeshData>();
		if (meshData != NULL)
		{
			if (meshData->isSkinnedMesh() == true && meshData->isSoftwareSkinning() == false)
			{
				bool cullingVisible = true;

				// get culling result from CCullingSystem
				CCullingData *cullingData = entity->getData<CCullingData>();
				if (cullingData != NULL)
					cullingVisible = cullingData->Visible;

				// only render visible culling mesh
				if (cullingVisible == true)
				{
					CWorldTransformData *transform = entity->getData<CWorldTransformData>();
					if (transform != NULL)
					{
						m_meshs.push_back(meshData);
						m_transforms.push_back(transform);
					}
				}
			}
		}
	}

	void CSkinnedMeshRenderer::init(CEntityManager *entityManager)
	{

	}

	void CSkinnedMeshRenderer::update(CEntityManager *entityManager)
	{

	}

	void CSkinnedMeshRenderer::render(CEntityManager *entityManager)
	{
		IVideoDriver *driver = getVideoDriver();

		CRenderMeshData** meshs = m_meshs.pointer();
		CWorldTransformData** transforms = m_transforms.pointer();

		CShaderManager *shaderManager = CShaderManager::getInstance();

		for (u32 i = 0, n = m_meshs.size(); i < n; i++)
		{
			CSkinnedMesh *mesh = (CSkinnedMesh*)m_meshs[i]->getMesh();

			// set bone matrix to shader callback
			shaderManager->BoneMatrix = mesh->SkinningMatrix;

			// set transform
			driver->setTransform(video::ETS_WORLD, transforms[i]->World);

			// render mesh
			for (u32 j = 0, m = mesh->getMeshBufferCount(); j < m; j++)
			{
				IMeshBuffer* meshBuffer = mesh->getMeshBuffer(j);

				driver->setMaterial(meshBuffer->getMaterial());
				driver->drawMeshBuffer(meshBuffer);
			}
		}
	}
}