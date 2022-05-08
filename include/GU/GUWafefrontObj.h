#ifndef _GUWAVEFRONTOBJ_H_
#define _GUWAVEFRONTOBJ_H_

#include <string>
#include <vector>
#include <fstream>

#include "GUMath.h"

namespace GU
{
  /*********************************************************/
  struct Vertex
  {
  	Vector3 pos;
  	Vector2 texCoord;
  	Vector3 normal;
  	Vector3 tangent;
  	Vector3 bitangent;
  };

	typedef unsigned long Index;
	/*********************************************************/


	/*********************************************************/
	struct _Face
	{
		_Face(std::string one, std::string two, std::string three)
		{
			Vert[0] = one;
			Vert[1] = two;
			Vert[2] = three;
		}

		std::string Vert[3];
	};

	struct _ObjMesh
	{
		std::vector<Vector3> Pos;
		std::vector<Vector2> Tex;
		std::vector<Vector3> Nor;
		std::vector<_Face> Fac;
		std::string Material;
		bool hasTexture;
		bool hasNormal;
	};

	struct _Index
	{
		int Pos;
		int Tex;
		int Nor;
	};

	/*********************************************************/


    inline bool LoadObj(const char* filename, std::vector<Vertex>& vertices, std::vector<Index>& indices,
		std::vector<Index>& subsets, std::string& materialFile, std::vector<std::string>& materials,
		bool isRhCoordSystem = true, bool calculateNormals = false)
    {
		// Step 1: Read in the .obj-File
		std::ifstream fileIn;
		fileIn.open(filename);

		std::vector<_ObjMesh> meshes;
		_ObjMesh tempMesh;
		tempMesh.hasTexture = false;
		tempMesh.hasNormal = false;
		bool newMesh = false;

		// Temp data
		float x, y, z;
		std::string tempFace[3];

		if (!fileIn.good())
			return false;

		wchar_t checkChar;

		while (fileIn)
		{
			checkChar = fileIn.get();
			switch (checkChar)
			{
			// Skip comments
			case '#':
				do
				{
					checkChar = fileIn.get();
				} while (checkChar != ('\n'));
				break;
			case 's':
				do
				{
					checkChar = fileIn.get();
				} while (checkChar != '\n');
				break;

			// Vectors
			case 'v':
				checkChar = fileIn.get();
				if (newMesh)
				{
					newMesh = false;
					if (!tempMesh.hasTexture)
						tempMesh.Tex.push_back(Vector2(0.0f, 0.0f));

					if (!tempMesh.hasNormal)
						tempMesh.Nor.push_back(Vector3(0.0f, 0.0f, 0.0f));
					meshes.push_back(tempMesh);
					tempMesh = _ObjMesh();
					tempMesh.hasNormal = false;
					tempMesh.hasTexture = false;
				}
				switch (checkChar)
				{
				case ' ':		// Position
					fileIn >> x >> y >> z;
					if (isRhCoordSystem)
						tempMesh.Pos.push_back(Vector3(x, y, z * -1.0f));
					else
						tempMesh.Pos.push_back(Vector3(x, y, z));
					break;
				case 't':		// Texture
					tempMesh.hasTexture = true;
					fileIn >> x >> y;
					if (isRhCoordSystem)
						tempMesh.Tex.push_back(Vector2(x, 1.0f - y));
					else
						tempMesh.Tex.push_back(Vector2(x, 1.0f - y));
					break;
				case 'n':		// Normal
					tempMesh.hasNormal = true;
					fileIn >> x >> y >> z;
					if (isRhCoordSystem)
						tempMesh.Nor.push_back(Vector3(x, y, z * -1.0f));
					else
						tempMesh.Nor.push_back(Vector3(x, y, z));
					break;
				}
				break;

			// Face
			case 'f':
				newMesh = true;
				fileIn >> tempFace[0] >> tempFace[1] >> tempFace[2];
				tempMesh.Fac.push_back(_Face(tempFace[0], tempFace[1], tempFace[2]));
				break;

			//Store the material libraries file name
			case 'm':
				checkChar = fileIn.get();
				if (checkChar == 't')
				{
					checkChar = fileIn.get();
					if (checkChar == 'l')
					{
						checkChar = fileIn.get();
						if (checkChar == 'l')
						{
							checkChar = fileIn.get();
							if (checkChar == 'i')
							{
								checkChar = fileIn.get();
								if (checkChar == 'b')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										fileIn >> materialFile;
									}
								}
							}
						}
					}
				}
				break;

			//Store the material name
			case 'u':
				checkChar = fileIn.get();
				if (checkChar == 's')
				{
					checkChar = fileIn.get();
					if (checkChar == 'e')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										fileIn >> tempMesh.Material;
									}
								}
							}
						}
					}
				}
				break;
			}

		}


		if (!tempMesh.hasTexture)
			tempMesh.Tex.push_back(Vector2(0.0f, 0.0f));

		if (!tempMesh.hasNormal)
			tempMesh.Nor.push_back(Vector3(0.0f, 0.0f, 0.0f));

		newMesh = false;
		meshes.push_back(tempMesh);
		fileIn.close();

		// Step 2: Convert mesh
		for (auto mesh : meshes)
		{

		}

		return true;
    }



}

#endif
