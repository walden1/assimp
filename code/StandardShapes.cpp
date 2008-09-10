/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file Implementation of the StandardShapes class
 */
#include "../include/aiTypes.h"
#include "../include/DefaultLogger.h"
#include "../include/aiAssert.h"

#include "StandardShapes.h"

namespace Assimp	{

#define ADD_TRIANGLE(n0,n1,n2) \
	positions.push_back(n0); \
	positions.push_back(n1); \
	positions.push_back(n2);

// ------------------------------------------------------------------------------------------------
void Subdivide(std::vector<aiVector3D>& positions)
{
	// assume this to be constant - input must be a Platonic primitive!
	const float fl1 = positions[0].Length();

	unsigned int origSize = (unsigned int)positions.size();
	for (unsigned int i = 0 ; i < origSize ; i+=3)
	{
		aiVector3D& tv0 = positions[i];
		aiVector3D& tv1 = positions[i+1];
		aiVector3D& tv2 = positions[i+2];

		aiVector3D a = tv0, b = tv1, c = tv2;
		aiVector3D v1 = aiVector3D(a.x+b.x, a.y+b.y, a.z+b.z).Normalize()*fl1;
		aiVector3D v2 = aiVector3D(a.x+c.x, a.y+c.y, a.z+c.z).Normalize()*fl1;
		aiVector3D v3 = aiVector3D(b.x+c.x, b.y+c.y, b.z+c.z).Normalize()*fl1;

		tv0 = v1; tv1 = v3; tv2 = v2; // overwrite the original
		ADD_TRIANGLE(a, v1, v2);
		ADD_TRIANGLE(c, v2, v3);
		ADD_TRIANGLE(b, v3, v1);
	}
}


// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeIcosahedron(aiVector3D& center,float length,
	std::vector<aiVector3D>& positions)
{
	positions.reserve(positions.size()+60);

	const float t = (1.f + 2.236067977f)/2.f;
	const float s = sqrt(1.f + t*t) / length;
	
	aiVector3D v0  = aiVector3D(t,1.f, 0.f)/s;
	aiVector3D v1  = aiVector3D(-t,1.f, 0.f)/s;
	aiVector3D v2  = aiVector3D(t,-1.f, 0.f)/s;
	aiVector3D v3  = aiVector3D(-t,-1.f, 0.f)/s;
	aiVector3D v4  = aiVector3D(1.f, 0.f, t)/s;
	aiVector3D v5  = aiVector3D(1.f, 0.f,-t)/s;
	aiVector3D v6  = aiVector3D(-1.f, 0.f,t)/s;
	aiVector3D v7  = aiVector3D(-1.f, 0.f,-t)/s;
	aiVector3D v8  = aiVector3D(0.f, t, 1.f)/s;
	aiVector3D v9  = aiVector3D(0.f,-t, 1.f)/s;
	aiVector3D v10 = aiVector3D(0.f, t,-1.f)/s;
	aiVector3D v11 = aiVector3D(0.f,-t,-1.f)/s;

	ADD_TRIANGLE(v0,v8,v4);
	ADD_TRIANGLE(v0,v5,v10);
	ADD_TRIANGLE(v2,v4,v9);
	ADD_TRIANGLE(v2,v11,v5);

	ADD_TRIANGLE(v1,v6,v8);
	ADD_TRIANGLE(v1,v10,v7);
	ADD_TRIANGLE(v3,v9,v6);
	ADD_TRIANGLE(v3,v7,v11);

	ADD_TRIANGLE(v0,v10,v8);
	ADD_TRIANGLE(v1,v8,v10);
	ADD_TRIANGLE(v2,v9,v11);
	ADD_TRIANGLE(v3,v11,v9);

	ADD_TRIANGLE(v4,v2,v0);
	ADD_TRIANGLE(v5,v0,v2);
	ADD_TRIANGLE(v6,v1,v3);
	ADD_TRIANGLE(v7,v3,v1);

	ADD_TRIANGLE(v8,v6,v4);
	ADD_TRIANGLE(v9,v4,v6);
	ADD_TRIANGLE(v10,v5,v7);
	ADD_TRIANGLE(v11,v7,v5);
}

// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeDodecahedron(aiVector3D& center,float length,
	std::vector<aiVector3D>& positions)
{
	positions.reserve(positions.size()+60);

}

// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeOctahedron(aiVector3D& center,float length,
	std::vector<aiVector3D>& positions)
{
	positions.reserve(positions.size()+24);

	aiVector3D v0  = aiVector3D(length, 0.f, 0.f) ;
	aiVector3D v1  = aiVector3D(-length, 0.f, 0.f);
	aiVector3D v2  = aiVector3D(0.f, length, 0.f);
	aiVector3D v3  = aiVector3D(0.f, -length, 0.f);
	aiVector3D v4  = aiVector3D(0.f, 0.f, length);
	aiVector3D v5  = aiVector3D(0.f, 0.f, -length);

	ADD_TRIANGLE(v4,v0,v2);
	ADD_TRIANGLE(v4,v2,v1);
	ADD_TRIANGLE(v4,v1,v3);
	ADD_TRIANGLE(v4,v3,v0);

	ADD_TRIANGLE(v5,v2,v0);
	ADD_TRIANGLE(v5,v1,v2);
	ADD_TRIANGLE(v5,v3,v1);
	ADD_TRIANGLE(v5,v0,v3);
}

#undef ADD_TRIANGLE

// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeSphere(
	aiVector3D&		center,
	float			radius,
	unsigned int	tess,
	std::vector<aiVector3D>& positions)
{
	MakeIcosahedron(center,radius,positions);

	for (unsigned int i = 0; i<tess;++i)
		Subdivide(positions);
}

// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeCone(
	aiVector3D&		center1,
	float			radius1,
	aiVector3D&		center2,
	float			radius2,
	unsigned int	tess, 
	std::vector<aiVector3D>& positions, 
	bool bOpened /*= false*/)
{
}

// ------------------------------------------------------------------------------------------------
void StandardShapes::MakeCircle(
	aiVector3D&		center, 
	aiVector3D&		normal, 
	float			radius,
	unsigned int	tess,
	std::vector<aiVector3D>& positions)
{
}

} // ! Assimp