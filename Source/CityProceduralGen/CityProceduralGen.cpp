#include "CityProceduralGen.h"
#include "RoadGen.h"
#include "Building.h"

#include <vector>
#include <string>
#include <iostream>


#include <Core/Engine.h>

using namespace std;
RoadGen* roadgen;
std::vector<Building*> buildings;
int buildingsCount = 0;

/*You can move around the city by holding down the right mouse button
and by using the WASD keys, and the Q and E buttons for moving on the
vertical axis.*/

int height = 25, width = 25, maxTunnels = 125, maxLength = 13;
/*parameters used by Roadgen in order to proceduraly generate the Roads*/

const string textureLoc = "Source/CityProceduralGen/Textures/";

CityProceduralGen::CityProceduralGen()
{
}

CityProceduralGen::~CityProceduralGen()
{
}

void CityProceduralGen::Init()
{
	// Create a simple square
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
			glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
			glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple triangle prism
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0, -0.5, 0.5),
			glm::vec3(0, 0.5, 0.5),
			glm::vec3(-0.5, -0.5, -0.5),
			glm::vec3(0.5, -0.5, -0.5),
			glm::vec3(-0.5, 0.5, -0.5),
			glm::vec3(0.5, 0.5, -0.5),
			glm::vec3(0.5, -0.5, -0.5),
			glm::vec3(0.5, 0.5, -0.5),
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(0, 1, 0),
			glm::vec3(1, 1, 1),
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 1, 1),
			glm::vec3(0, 0, 1)
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
		};

		vector<unsigned short> indices =
		{
			0, 2, 3,		1, 4, 5,
			0, 3, 5,		5, 1, 0,
			1, 2, 0,		1, 2, 4,
			7, 2, 4,		7, 2, 6,
		};

		Mesh* mesh = new Mesh("tri");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple triangle
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0, 0, 0.5),
			glm::vec3(-0.5, 0, -0.5),
			glm::vec3(0.5, 0, -0.5),
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2
		};

		Mesh* mesh = new Mesh("triangle");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple hexagonal prism
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0, -0.5, 0.5),
			glm::vec3(0.5, -0.5, 0.25),
			glm::vec3(0.5, -0.5, -0.25),
			glm::vec3(0, -0.5, -0.5),
			glm::vec3(-0.5, -0.5, -0.25),
			glm::vec3(-0.5, -0.5, 0.25),
			glm::vec3(0, 0.5, 0.5),
			glm::vec3(0.5, 0.5, 0.25),
			glm::vec3(0.5, 0.5, -0.25),
			glm::vec3(0, 0.5, -0.5),
			glm::vec3(-0.5, 0.5, -0.25),
			glm::vec3(-0.5, 0.5, 0.25),
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(0, 1, 0),
			glm::vec3(1, 1, 1),
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 1, 1),
			glm::vec3(0, 1, 0),
			glm::vec3(1, 1, 1),
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 0, 1)
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.25f, 0.0f),
			glm::vec2(0.75f, 0.0f),
			glm::vec2(0.25f, 0.0f),
			glm::vec2(0.75f, 0.0f),
			glm::vec2(0.25f, 0.0f),
			glm::vec2(0.75f, 0.0f),
			glm::vec2(0.25f, 1.0f),
			glm::vec2(0.75f, 1.0f),
			glm::vec2(0.25f, 1.0f),
			glm::vec2(0.75f, 1.0f),
			glm::vec2(0.25f, 1.0f),
			glm::vec2(0.75f, 1.0f),
		};

		vector<unsigned short> indices =
		{
			0, 7, 1,		0, 7, 6,
			1, 8, 7,		1, 8, 2,
			2, 9, 8,		2, 9, 3,
			3, 10, 9,		3, 10, 4,
			4, 11, 10,		4, 11, 5,
			5, 6, 11,		5, 6, 0,
			0, 1, 2,		0, 2, 3,
			0, 3, 4,		0, 4, 5,
			6, 7, 8,		6, 8, 9,
			6, 9, 10,		6, 10, 11,
		};

		Mesh* mesh = new Mesh("hexa");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple hexagon
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0, 0, 0.5),
			glm::vec3(0.5, 0, 0.25),
			glm::vec3(0.5, 0, -0.25),
			glm::vec3(0, 0, -0.5),
			glm::vec3(-0.5, 0, -0.25),
			glm::vec3(-0.5, 0, 0.25),
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 0.0f),
			glm::vec2(1.0f, 0.33f),
			glm::vec2(1.0f, 0.66f),
			glm::vec2(0.5f, 1.0f),
			glm::vec2(0.0f, 0.66f),
			glm::vec2(0.0f, 0.33f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	0, 2, 3,
			0, 3, 4,	0, 4, 5,
		};

		Mesh* mesh = new Mesh("hexagon");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}



	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "road.jpg").c_str(), GL_REPEAT);
		mapTextures["road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "lawn.jpg").c_str(), GL_REPEAT);
		mapTextures["lawn"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "intersection.jpg").c_str(), GL_REPEAT);
		mapTextures["intersection"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_complex.jpg").c_str(), GL_REPEAT);
		mapTextures["building"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_complex_blue.jpg").c_str(), GL_REPEAT);
		mapTextures["building_blue"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_complex_yellow.jpg").c_str(), GL_REPEAT);
		mapTextures["building_yellow"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_complex_green.jpg").c_str(), GL_REPEAT);
		mapTextures["building_green"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_triangle.jpg").c_str(), GL_REPEAT);
		mapTextures["building_triangle"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_hexa_complex.jpg").c_str(), GL_REPEAT);
		mapTextures["building_hexa"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_hexa_complex_green.jpg").c_str(), GL_REPEAT);
		mapTextures["building_hexa_green"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_hexa_complex_yellow.jpg").c_str(), GL_REPEAT);
		mapTextures["building_hexa_yellow"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "facade_hexa_complex_blue.jpg").c_str(), GL_REPEAT);
		mapTextures["building_hexa_blue"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "black.jpg").c_str(), GL_REPEAT);
		mapTextures["black"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "top.jpg").c_str(), GL_REPEAT);
		mapTextures["top"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "helipad.jpg").c_str(), GL_REPEAT);
		mapTextures["helipad"] = texture;
	}


	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "moon.jpg").c_str(), GL_REPEAT);
		mapTextures["moon"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "Street_Lamp_SM.png").c_str(), GL_REPEAT);
		mapTextures["streetlamp"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
		mapTextures["bamboo"] = texture;
	}

	// Load meshes
	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("quad");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("lamppost");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "StreetLamp.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	//Create Shaders
	{
		Shader *shader = new Shader("Shader");
		shader->AddShader("Source/CityProceduralGen/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/CityProceduralGen/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}


	{
		Shader *shader = new Shader("SpotShader");
		shader->AddShader("Source/CityProceduralGen/Shaders/SpotVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/CityProceduralGen/Shaders/SpotFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 1, 1);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 60;
		materialKd = 0.5;
		materialKs = 0.5;
	}


	/*Procedurally generate the Road matrix
	roadgen->road[i][j] == 0 if a road will be placed at i+0,5, j+0,5*/
	roadgen = new RoadGen(height, width, maxTunnels, maxLength);
	for (int i = 0; i < roadgen->height; i++) {
		for (int j = 0; j < roadgen->width; j++) {
			cout << roadgen->road[i][j] << " ";
			if (roadgen->road[i][j] == 1) {
				buildingsCount++;
			}
		}
		cout << endl;
	}

	int one = buildingsCount;
	float floors[3][2];
	Building *dummy = new Building(2, floors, -1, -1, "dummy", "dummy", "dummy");

	/*Randomize the number of floors and the type of floor(triangle prism, hexagonal prism, cube)
	for each buildings*/
	for (int i = 0; i < roadgen->height; i++) {
		for (int j = 0; j < roadgen->width; j++) {
			if (roadgen->road[i][j] == 1) {
				one--;
				buildings.push_back(dummy->RandomizeBuilding(i - height / 2, j - height / 2, one));
			}
		}
	}
}

void CityProceduralGen::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 4.0f / 254, 25.0f / 254, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void CityProceduralGen::Update(float deltaTimeSeconds)
{
	for (int i = 0; i < roadgen->height; i++) {
		for (int j = 0; j < roadgen->width; j++) {
			if (roadgen->road[i][j] == 0) {
				glm::mat4 modelMatrix = glm::mat4(1);
				glm::mat4 modelMatrixLamp1 = glm::mat4(1);
				glm::mat4 modelMatrixLamp2 = glm::mat4(1);
				//The lamps that will be placed by the side of the road

				modelMatrix = glm::translate(modelMatrix, glm::vec3(i - height / 2, 0.0f, j - width / 2));
				if (roadgen->direct[i][j] == 1 || roadgen->direct[i][j] == 2) {

					/*Rotate the road texture depending on his direction and Place the lamps depending
					on the direction of the road*/
					modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(0, 1, 0));
					modelMatrixLamp1 = glm::translate(modelMatrixLamp1, glm::vec3(i - height / 2, 0.0f, j - width / 2 - 0.5f));
					modelMatrixLamp1 = glm::scale(modelMatrixLamp1, glm::vec3(0.003));
					modelMatrixLamp1 = glm::rotate(modelMatrixLamp1, (float)-M_PI / 2, glm::vec3(0, 1, 0));

					modelMatrixLamp2 = glm::translate(modelMatrixLamp2, glm::vec3(i - height / 2, 0.0f, j - width / 2 + 0.5f));
					modelMatrixLamp2 = glm::scale(modelMatrixLamp2, glm::vec3(0.003));
					modelMatrixLamp2 = glm::rotate(modelMatrixLamp2, (float)M_PI / 2, glm::vec3(0, 1, 0));

				}
				else {

					/*Place the lamps depending on the direction of the road*/
					modelMatrixLamp1 = glm::translate(modelMatrixLamp1, glm::vec3(i - height / 2 - 0.5f, 0.0f, j - width / 2));
					modelMatrixLamp1 = glm::scale(modelMatrixLamp1, glm::vec3(0.003));

					modelMatrixLamp2 = glm::translate(modelMatrixLamp2, glm::vec3(i - height / 2 + 0.5f, 0.0f, j - width / 2));
					modelMatrixLamp2 = glm::scale(modelMatrixLamp2, glm::vec3(0.003));
					modelMatrixLamp2 = glm::rotate(modelMatrixLamp2, (float)M_PI, glm::vec3(0, 1, 0));

				}



				modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(1, 0, 0));
				int sem = 0;
				if (i > 0) {
					if (roadgen->road[i - 1][j] == 0) {
						if (j > 0) {
							if (roadgen->road[i][j - 1] == 0 && roadgen->road[i - 1][j - 1] != 0) {
								sem++;
							}
						}

						if (j < roadgen->width - 1) {
							if (roadgen->road[i][j + 1] == 0 && roadgen->road[i - 1][j + 1] != 0) {
								sem++;
							}
						}
					}
				}
				if (i < roadgen->height - 1) {
					if (roadgen->road[i + 1][j] == 0) {
						if (j > 0) {
							if (roadgen->road[i][j - 1] == 0 && roadgen->road[i + 1][j - 1] != 0) {
								sem++;
							}
						}

						if (j < roadgen->width - 1) {
							if (roadgen->road[i][j + 1] == 0 && roadgen->road[i + 1][j + 1] != 0) {
								sem++;
							}
						}
					}
				}
				if (sem == 0) {

					{
						int s1 = 0, s2 = 0;
						if (roadgen->direct[i][j] == 1 || roadgen->direct[i][j] == 2) {
								if (j > 0) {
									if (roadgen->road[i][j - 1] != 0) {
										s1 = 1;
									}
								}
								if (j < width - 1) {
									if (roadgen->road[i][j + 1] != 0) {
										s2 = 1;
									}
								}
						}

						if (roadgen->direct[i][j] == -1 || roadgen->direct[i][j] == -2) {
							if (i > 0) {
								if (roadgen->road[i - 1][j] != 0) {
									s1 = 1;
								}
							}
							if (i < height - 1) {
								if (roadgen->road[i + 1][j] != 0) {
									s2 = 1;
								}
							}
						}



						if (s1 == 1) {
							RenderSimpleMesh(meshes["lamppost"], shaders["Shader"], modelMatrixLamp1, mapTextures["streetlamp"]);
						}
						if (s2 == 1) {
							RenderSimpleMesh(meshes["lamppost"], shaders["Shader"], modelMatrixLamp2, mapTextures["streetlamp"]);
						}
					}
					RenderSimpleMesh(meshes["square"], shaders["Shader"], modelMatrix, mapTextures["road"]);
				}
				else {
					RenderSimpleMesh(meshes["square"], shaders["Shader"], modelMatrix, mapTextures["intersection"]);
				}
			}
		}
	}

	
	//Render the Moon
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(width, 20, -height * 3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(7));
		RenderSimpleMesh(meshes["sphere"], shaders["Shader"], modelMatrix, mapTextures["moon"]);
	}


	//Render the buildings
	for (int z = 0; z < buildingsCount; z++) {

		int i = buildings[z]->i, j = buildings[z]->j;
		string primitive = buildings[z]->primitive, texture = buildings[z]->texture,
			primitive1 = buildings[z]->primitive1, texture1 = buildings[z]->texture1,
			primitive2 = buildings[z]->primitive2, texture2 = buildings[z]->texture2;


		//Render the lawn on top of which the building will be placed
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0, j));
		modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(1, 0, 0));
		RenderSimpleMesh(meshes["square"], shaders["Shader"], modelMatrix, mapTextures["lawn"]);

		
		//Render the first floor of the building
		float h = buildings[z]->floor[0][0], w = buildings[z]->floor[0][1];
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h / 2, j));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(w, h, w));
		RenderSimpleMesh(meshes[primitive], shaders["Shader"], modelMatrix, mapTextures[texture]);

		//Render the second floor of the building
		float h1 = buildings[z]->floor[1][0], w1 = buildings[z]->floor[1][1];
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h1 / 2, j));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(w1, h1, w1));
		RenderSimpleMesh(meshes[primitive1], shaders["Shader"], modelMatrix, mapTextures[texture1]);

		//Render the third floor of the building if it exists
		if (buildings[z]->floors == 3) {
			float h2 = buildings[z]->floor[2][0], w2 = buildings[z]->floor[2][1];
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h1 + h2 / 2, j));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(w2, h2, w2));
			lightPosition = glm::vec3(i, h + h1 + h2 / 2 + 2, j);
			RenderSimpleMesh(meshes[primitive2], shaders["Shader"], modelMatrix, mapTextures[texture2]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h1 + h2 / 2 + 1, j));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));
		}

		//Place some other decorations in the scene(bamboo)
		if (primitive.compare("tri") == 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.2, 0, j + 0.33));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.255, 0, j + 0.21));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.31, 0, j + 0.09));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.007f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.365, 0, j - 0.03));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.420, 0, j - 0.15));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - 0.2, 0, j + 0.33));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - 0.255, 0, j + 0.21));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - 0.31, 0, j + 0.09));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.007f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - 0.365, 0, j - 0.03));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - 0.420, 0, j - 0.15));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005f));
			RenderSimpleMesh(meshes["bamboo"], shaders["Shader"], modelMatrix, mapTextures["bamboo"]);

		}

		if (primitive.compare("box") == 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + 0.001, j));
			modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(1, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(w, w, 0));
			RenderSimpleMesh(meshes["square"], shaders["Shader"], modelMatrix, mapTextures["black"]);
		}

		if (primitive1.compare("box") == 0) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h1 + 0.001, j));
			modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(1, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(w1, w1, 0));
			RenderSimpleMesh(meshes["square"], shaders["Shader"], modelMatrix, mapTextures["black"]);
		}


		//Place a helipad on the cube buildings that have three floors
		if (primitive2.compare("box") == 0) {
			if (buildings[z]->floors == 3) {
				float h2 = buildings[z]->floor[2][0], w2 = buildings[z]->floor[2][1];
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h1 + h2 + 0.002, j));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(w2, 0.001, w2));
				lightPosition = glm::vec3(i, h + h1 + h2 + 0.3, j);
				RenderSimpleMesh(meshes["box"], shaders["SpotShader"], modelMatrix, mapTextures["helipad"]);
			}
		}

		string prim;
		if (buildings[z]->floors == 2) {
			prim = primitive1;
		}
		else {
			prim = primitive2;
		}

		int fl = buildings[z]->floors - 1;
			if (prim.compare("box") == 0) {
				float h2 = buildings[z]->floor[fl][0], w2 = buildings[z]->floor[fl][1];
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h2 + 0.002, j));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(w2, 0.001, w2));
				lightPosition = glm::vec3(i, h + h1 + (h2 - h1) + 0.3, j);
				RenderSimpleMesh(meshes["box"], shaders["SpotShader"], modelMatrix, mapTextures["top"]);
			}

			if (prim.compare("hexa") == 0) {
				float h2 = buildings[z]->floor[fl][0], w2 = buildings[z]->floor[fl][1];
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h2 + 0.002, j));
				if (fl == 2) {
					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, h1, 0));
				}
				modelMatrix = glm::scale(modelMatrix, glm::vec3(w2, 0.001, w2));
				lightPosition = glm::vec3(i, h + h1 + (h2 - h1) + 0.3, j);
				if (fl == 2) {
					lightPosition = glm::vec3(i, h + h1 + h2 + 0.3, j);
				}
				RenderSimpleMesh(meshes["hexagon"], shaders["SpotShader"], modelMatrix, mapTextures["top"]);
			}

			if (prim.compare("tri") == 0) {
				float h2 = buildings[z]->floor[fl][0], w2 = buildings[z]->floor[fl][1];
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, h + h2 + 0.002, j));
				if (fl == 2) {
					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, h1, 0));
				}
				modelMatrix = glm::scale(modelMatrix, glm::vec3(w2, 0.001, w2));
				lightPosition = glm::vec3(i, h + h1 + (h2 - h1) + 0.3, j);
				if (fl == 2) {
					lightPosition = glm::vec3(i, h + h1 + h2 + 0.3, j);
				}
				RenderSimpleMesh(meshes["triangle"], shaders["SpotShader"], modelMatrix, mapTextures["top"]);
			}
	}
}


void CityProceduralGen::FrameEnd()
{
	//DrawCoordinatSystem();
}

void CityProceduralGen::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	int light_position = glGetUniformLocation(shader->program, "light_pos");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	float time = Engine::GetElapsedTime();
	int location = glGetUniformLocation(shader->program, "Time");
	glUniform1f(location, time);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
		//TODO : activate texture location 0
		//TODO : Bind the texture1 ID
		//TODO : Send texture uniform value
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
		//TODO : activate texture location 1
		//TODO : Bind the texture2 ID
		//TODO : Send texture uniform value
	}
	else {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Mesh* CityProceduralGen::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

Texture2D* CityProceduralGen::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	for (int i = 0; i < size; i++)
	{
		data[i] = rand() % 256;
	}
	// TODO: generate random texture data
	glGenTextures(1, &textureID);

	// Generate and bind the new texture ID
	glBindTexture(GL_TEXTURE_2D, textureID);

	// TODO: Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// TODO: Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// TODO: Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void CityProceduralGen::OnInputUpdate(float deltaTime, int mods)
{

}

void CityProceduralGen::OnKeyPress(int key, int mods)
{
	// add key press event
}

void CityProceduralGen::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void CityProceduralGen::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void CityProceduralGen::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void CityProceduralGen::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void CityProceduralGen::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void CityProceduralGen::OnWindowResize(int width, int height)
{
}
