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

#include "pch.h"
#include "CLightmapper.h"

namespace Skylicht
{
	namespace Lightmapper
	{
		CLightmapper::CLightmapper()
		{
			m_singleBaker = new CBaker();
			m_multiBaker = new CMTBaker();
		}

		CLightmapper::~CLightmapper()
		{
			delete m_singleBaker;
			delete m_multiBaker;
		}

		const CSH9& CLightmapper::bakeAtPosition(
			CCamera *camera, IRenderPipeline* rp, CEntityManager *entityMgr,
			const core::vector3df& position,
			const core::vector3df& normal,
			const core::vector3df& tangent,
			const core::vector3df& binormal)
		{
			return m_singleBaker->bake(camera, rp, entityMgr, position, normal, tangent, binormal);
		}

		void CLightmapper::bakeAtPosition(
			CCamera *camera, IRenderPipeline* rp, CEntityManager* entityMgr,
			const core::vector3df *position,
			const core::vector3df *normal,
			const core::vector3df *tangent,
			const core::vector3df *binormal,
			std::vector<CSH9>& out,
			int count)
		{
			out.clear();

			int maxMT = m_multiBaker->getMaxMT();
			int current = 0;

			while (current < count)
			{
				int numMT = count - current;
				numMT = core::min_(numMT, maxMT);

				// bake and get SH result
				m_multiBaker->bake(camera,
					rp,
					entityMgr,
					position + current,
					normal + current,
					tangent + current,
					binormal + current,
					numMT);

				for (int i = 0; i < numMT; i++)
					out.push_back(m_multiBaker->getSH(i));

				current += numMT;
			}
		}

		void CLightmapper::bakeProbes(std::vector<CProbe*>& probes, CCamera *camera, IRenderPipeline* rp, CEntityManager* entityMgr)
		{
			// prepare comput sh
			core::array<core::vector3df> positions;
			core::array<core::vector3df> normals;
			core::array<core::vector3df> tangents;
			core::array<core::vector3df> binormals;
			for (u32 i = 0, n = probes.size(); i < n; i++)
			{
				CProbe* probe = probes[i];

				core::vector3df pos = probe->getGameObject()->getPosition();
				core::vector3df normal = CTransform::s_oy;
				core::vector3df tangent = CTransform::s_ox;
				core::vector3df binormal = normal.crossProduct(tangent);
				binormal.normalize();

				positions.push_back(pos);
				normals.push_back(normal);
				tangents.push_back(tangent);
				binormals.push_back(binormal);
			}

			// bake sh
			std::vector<CSH9> out;
			CLightmapper::getInstance()->bakeAtPosition(
				camera,
				rp,
				entityMgr,
				positions.pointer(),
				normals.pointer(),
				tangents.pointer(),
				binormals.pointer(),
				out,
				(int)probes.size());

			// apply sh
			for (u32 i = 0, n = probes.size(); i < n; i++)
				probes[i]->setSH(out[i]);
		}

		int CLightmapper::bakeMeshBuffer(IMeshBuffer *mb, CCamera *camera, IRenderPipeline* rp, CEntityManager* entityMgr, int begin, int count, core::array<SColor>& out)
		{
			if (mb->getVertexBufferCount() == 0)
			{
				char log[512];
				sprintf(log, "[CLightmapper] bakeMeshBuffer skip bake MeshBuffer");
				os::Printer::log(log);
				return 0;
			}

			if (mb->getVertexType() != EVT_TANGENTS)
			{
				char log[512];
				sprintf(log, "[CLightmapper] bakeMeshBuffer skip non tangent MeshBuffer");
				os::Printer::log(log);
				return 0;
			}

			IVertexBuffer *vb = mb->getVertexBuffer(0);
			u32 vtxCount = vb->getVertexCount();

			int remain = vtxCount - begin;
			if (remain <= 0)
				return 0;

			count = core::min_(count, remain);

			video::S3DVertexTangents *vtx = (video::S3DVertexTangents*)vb->getVertices();

			core::array<core::vector3df> positions;
			core::array<core::vector3df> normals;
			core::array<core::vector3df> tangents;
			core::array<core::vector3df> binormals;

			for (int i = begin; i < begin + count; i++)
			{
				positions.push_back(vtx[i].Pos);
				normals.push_back(vtx[i].Normal);
				tangents.push_back(vtx[i].Tangent);
				binormals.push_back(vtx[i].Binormal);
			}

			std::vector<CSH9> outSH;
			bakeAtPosition(
				camera,
				rp,
				entityMgr,
				positions.pointer(),
				normals.pointer(),
				tangents.pointer(),
				binormals.pointer(),
				outSH,
				count);

			return count;
		}
	}
}