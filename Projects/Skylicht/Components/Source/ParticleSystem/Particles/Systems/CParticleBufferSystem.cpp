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
#include "CParticleBufferSystem.h"

#include "ParticleSystem/Particles/CParticle.h"
#include "ParticleSystem/Particles/CGroup.h"

namespace Skylicht
{
	namespace Particle
	{
		CParticleBufferSystem::CParticleBufferSystem()
		{

		}

		CParticleBufferSystem::~CParticleBufferSystem()
		{

		}

		void CParticleBufferSystem::update(CParticle *particles, int num, CGroup *group, float dt)
		{
			CVertexBuffer<SParticleInstance>* buffer = group->getIntancing()->getInstanceBuffer();

			buffer->set_used(num);

			SParticleInstance *vtx = (SParticleInstance*)buffer->getVertices();
			for (int i = 0; i < num; i++)
			{
				CParticle &p = particles[i];	
				vtx->Pos = p.Position;
				vtx->Color = p.Color;
				vtx->SizeRotation.X = 1.0f;
				vtx->SizeRotation.Y = 0.0f;
				vtx->UVScale.set(1.0f, 1.0f);
				vtx->UVOffset.set(0.0f, 0.0f);
			}

			buffer->setDirty();
		}
	}
}