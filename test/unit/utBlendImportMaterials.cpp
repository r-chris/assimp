/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2016, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

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
---------------------------------------------------------------------------
*/
#include "UnitTestPCH.h"

#include <assimp/cexport.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class BlendImportMaterials : public ::testing::Test {
public:

    virtual void SetUp()
    {
        im = new Assimp::Importer();
    }

    virtual void TearDown()
    {
        delete im;
    }

protected:

    Assimp::Importer* im;
};

// ------------------------------------------------------------------------------------------------
TEST_F(BlendImportMaterials, testImportMaterial)
{
    const aiScene* pTest = im->ReadFile(ASSIMP_TEST_MODELS_DIR "/BLEND/BlenderMaterial_269.blend", 0);
    ASSERT_TRUE(pTest != NULL);
    ASSERT_TRUE(pTest->HasMaterials());

    ASSERT_EQ(1, pTest->mNumMaterials);

    auto alpha = pTest->mMaterials[0];

    #define ASSERT_PROPERTY_EQ(expected, key, var) \
        auto var = expected; \
        ASSERT_EQ(aiReturn_SUCCESS, alpha->Get("$mat.blend." key, 0, 0, var)); \
        ASSERT_EQ(expected, var);

    #define ASSERT_PROPERTY_FLOAT_EQ(expected, key, var) \
        auto var = expected; \
        ASSERT_EQ(aiReturn_SUCCESS, alpha->Get("$mat.blend." key, 0, 0, var)); \
        ASSERT_FLOAT_EQ(expected, var);

    ASSERT_PROPERTY_EQ(aiColor3D(0.1, 0.2, 0.3), "diffuse.color", diffuseColor);
    ASSERT_PROPERTY_EQ(0.4, "diffuse.intensity", diffuseIntensity);
    ASSERT_PROPERTY_EQ(1, "diffuse.shader", diffuseShader);
    ASSERT_PROPERTY_EQ(0, "diffuse.ramp", diffuseRamp);

    ASSERT_PROPERTY_EQ(aiColor3D(0.5, 0.6, 0.7), "specular.color", specularColor);
    ASSERT_PROPERTY_EQ(0.8, "specular.intensity", specularIntensity);
    ASSERT_PROPERTY_EQ(1, "specular.shader", specularShader);
    ASSERT_PROPERTY_EQ(0, "specular.ramp", specularRamp);
    ASSERT_PROPERTY_EQ(9, "specular.hardness", specularHardness);

    ASSERT_PROPERTY_EQ(1, "transparency.use", transparencyUse);
    ASSERT_PROPERTY_EQ(2, "transparency.method", transparencyMethod);
    ASSERT_PROPERTY_EQ(0.01, "transparency.alpha", transparencyAlpha);
    ASSERT_PROPERTY_EQ(0.02, "transparency.specular", transparencySpecular);
    ASSERT_PROPERTY_EQ(0.03, "transparency.fresnel", transparencyFresnel);
    ASSERT_PROPERTY_EQ(3.14, "transparency.blend", transparencyBlend);
    ASSERT_PROPERTY_EQ(0.85, "transparency.ior", transparencyIor);
    ASSERT_PROPERTY_FLOAT_EQ(0.128, "transparency.filter", transparencyFilter);
    ASSERT_PROPERTY_FLOAT_EQ(1.298, "transparency.falloff", transparencyFalloff);
    ASSERT_PROPERTY_FLOAT_EQ(0.2376, "transparency.limit", transparencyLimit);
    ASSERT_PROPERTY_EQ(7, "transparency.depth", transparencyDepth);
    ASSERT_PROPERTY_FLOAT_EQ(0.678, "transparency.glossAmount", transparencyGlossAmount);
    ASSERT_PROPERTY_FLOAT_EQ(0.208, "transparency.glossThreshold", transparencyGlossThreshold);
    ASSERT_PROPERTY_EQ(17, "transparency.glossSamples", transparencyGlossSamples);

    ASSERT_PROPERTY_EQ(1, "mirror.use", mirrorUse);
    ASSERT_PROPERTY_FLOAT_EQ(0.28, "mirror.reflectivity", mirrorReflectivity);
    ASSERT_PROPERTY_EQ(aiColor3D(0.25, 0.5, 0.128), "mirror.color", mirrorColor);
    ASSERT_PROPERTY_FLOAT_EQ(0.256, "mirror.fresnel", mirrorFresnel);
    ASSERT_PROPERTY_FLOAT_EQ(1.61, "mirror.blend", mirrorBlend);
    ASSERT_PROPERTY_EQ(12, "mirror.depth", mirrorDepth);
    ASSERT_PROPERTY_FLOAT_EQ(0.4, "mirror.maxDist", mirrorMaxDist);
    ASSERT_PROPERTY_EQ(1, "mirror.fadeTo", mirrorFadeTo);
    ASSERT_PROPERTY_FLOAT_EQ(0.512, "mirror.glossAmount", mirrorGlossAmount);
    ASSERT_PROPERTY_FLOAT_EQ(0.18, "mirror.glossThreshold", mirrorGlossThreshold);
    ASSERT_PROPERTY_EQ(61, "mirror.glossSamples", mirrorGlossSamples);
    ASSERT_PROPERTY_FLOAT_EQ(0.87, "mirror.glossAnisotropic", mirrorGlossAnisotropic);
}
