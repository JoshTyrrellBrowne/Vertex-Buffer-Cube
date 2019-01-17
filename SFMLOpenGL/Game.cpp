#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vert;

Vert vertex[36];
Vert displacementVerts[36];
Vert resultVerts[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	for (int i = 0; i < 36; i++)
	{
		displacementVerts[i].coordinate[0] = 0.1;
		displacementVerts[i].coordinate[1] = 0.1;
		displacementVerts[i].coordinate[2] = 0.1;
	}

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = -0.5f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = -0.5f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = -0.5f;

	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = -0.5f;

	vertex[4].coordinate[0] = 0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = -0.5f;

	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = -0.5f;

	vertex[6].coordinate[0] = -0.5f;
	vertex[6].coordinate[1] = -0.5f;
	vertex[6].coordinate[2] = 0.5f;

	vertex[7].coordinate[0] = -0.5f;
	vertex[7].coordinate[1] = 0.5f;
	vertex[7].coordinate[2] = 0.5f;

	vertex[8].coordinate[0] = 0.5f;
	vertex[8].coordinate[1] = 0.5f;
	vertex[8].coordinate[2] = 0.5f;

	vertex[9].coordinate[0] = 0.5f;
	vertex[9].coordinate[1] = 0.5f;
	vertex[9].coordinate[2] = 0.5f;

	vertex[10].coordinate[0] = 0.5f;
	vertex[10].coordinate[1] = -0.5f;
	vertex[10].coordinate[2] = 0.5f;

	vertex[11].coordinate[0] = -0.5f;
	vertex[11].coordinate[1] = -0.5f;
	vertex[11].coordinate[2] = 0.5f;
	//=====================================================
	vertex[12].coordinate[0] = -0.5f;
	vertex[12].coordinate[1] = -0.5f;
	vertex[12].coordinate[2] = -0.5f;

	vertex[13].coordinate[0] = -0.5f;
	vertex[13].coordinate[1] = 0.5f;		// left wall
	vertex[13].coordinate[2] = -0.5f;

	vertex[14].coordinate[0] = -0.5f;
	vertex[14].coordinate[1] = 0.5f;
	vertex[14].coordinate[2] = 0.5f;

	vertex[15].coordinate[0] = -0.5f;
	vertex[15].coordinate[1] = 0.5f;
	vertex[15].coordinate[2] = 0.5f;

	vertex[16].coordinate[0] = -0.5f;
	vertex[16].coordinate[1] = -0.5f;
	vertex[16].coordinate[2] = 0.5f;

	vertex[17].coordinate[0] = -0.5f;
	vertex[17].coordinate[1] = -0.5f;
	vertex[17].coordinate[2] = -0.5f;

	vertex[18].coordinate[0] = 0.5f;
	vertex[18].coordinate[1] = -0.5f;
	vertex[18].coordinate[2] = 0.5f;

	vertex[19].coordinate[0] = 0.5f;
	vertex[19].coordinate[1] = 0.5f;
	vertex[19].coordinate[2] = 0.5f;

	vertex[20].coordinate[0] = 0.5f;
	vertex[20].coordinate[1] = 0.5f;
	vertex[20].coordinate[2] = -0.5f;

	vertex[21].coordinate[0] = 0.5f;
	vertex[21].coordinate[1] = 0.5f;
	vertex[21].coordinate[2] = -0.5f;

	vertex[22].coordinate[0] = 0.5f;
	vertex[22].coordinate[1] = -0.5f;
	vertex[22].coordinate[2] = -0.5f;

	vertex[23].coordinate[0] = 0.5f;
	vertex[23].coordinate[1] = -0.5f;
	vertex[23].coordinate[2] = 0.5f;
	//============================================
	vertex[24].coordinate[0] = -0.5f;
	vertex[24].coordinate[1] = -0.5f;
	vertex[24].coordinate[2] = -0.5f;

	vertex[25].coordinate[0] = 0.5f;
	vertex[25].coordinate[1] = -0.5f;		// left wall
	vertex[25].coordinate[2] = -0.5f;

	vertex[26].coordinate[0] = 0.5f;
	vertex[26].coordinate[1] = -0.5f;
	vertex[26].coordinate[2] = 0.5f;

	vertex[27].coordinate[0] = 0.5f;
	vertex[27].coordinate[1] = -0.5f;
	vertex[27].coordinate[2] = 0.5f;

	vertex[28].coordinate[0] = -0.5f;
	vertex[28].coordinate[1] = -0.5f;
	vertex[28].coordinate[2] = 0.5f;

	vertex[29].coordinate[0] = -0.5f;
	vertex[29].coordinate[1] = -0.5f;
	vertex[29].coordinate[2] = -0.5f;
	//
	vertex[30].coordinate[0] = -0.5f;
	vertex[30].coordinate[1] = 0.5f;
	vertex[30].coordinate[2] = 0.5f;

	vertex[31].coordinate[0] = 0.5f;
	vertex[31].coordinate[1] = 0.5f;
	vertex[31].coordinate[2] = 0.5f;

	vertex[32].coordinate[0] = 0.5f;
	vertex[32].coordinate[1] = 0.5f;
	vertex[32].coordinate[2] = -0.5f;

	vertex[33].coordinate[0] = 0.5f;
	vertex[33].coordinate[1] = 0.5f;
	vertex[33].coordinate[2] = -0.5f;

	vertex[34].coordinate[0] = -0.5f;
	vertex[34].coordinate[1] = 0.5f;
	vertex[34].coordinate[2] = -0.5f;

	vertex[35].coordinate[0] = -0.5f;
	vertex[35].coordinate[1] = 0.5f;
	vertex[35].coordinate[2] = 0.5f;

	/*COLOURS*/
	vertex[0].color[0] = 0.0f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.5f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.5f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;
	//
	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 0.0f;
	vertex[7].color[2] = 1.0f;

	vertex[8].color[0] = 0.0f;
	vertex[8].color[1] = 0.0f;
	vertex[8].color[2] = 1.0f;

	vertex[9].color[0] = 0.5f;
	vertex[9].color[1] = 0.0f;
	vertex[9].color[2] = 1.0f;

	vertex[10].color[0] = 0.5f;
	vertex[10].color[1] = 0.0f;
	vertex[10].color[2] = 1.0f;

	vertex[11].color[0] = 0.5f;
	vertex[11].color[1] = 0.0f;
	vertex[11].color[2] = 1.0f;

	vertex[12].color[0] = 0.0f;
	vertex[12].color[1] = 1.0f;
	vertex[12].color[2] = 0.0f;

	vertex[13].color[0] = 0.0f;
	vertex[13].color[1] = 1.0f;
	vertex[13].color[2] = 0.0f;

	vertex[14].color[0] = 0.0f;
	vertex[14].color[1] = 1.0f;
	vertex[14].color[2] = 0.0f;

	vertex[15].color[0] = 0.5f;
	vertex[15].color[1] = 1.0f;
	vertex[15].color[2] = 0.0f;

	vertex[16].color[0] = 0.5f;
	vertex[16].color[1] = 1.0f;
	vertex[16].color[2] = 0.0f;

	vertex[17].color[0] = 0.5f;
	vertex[17].color[1] = 1.0f;
	vertex[17].color[2] = 0.0f;
	//
	vertex[18].color[0] = 1.0f;
	vertex[18].color[1] = 0.0f;
	vertex[18].color[2] = 1.0f;

	vertex[19].color[0] = 1.0f;
	vertex[19].color[1] = 0.0f;
	vertex[19].color[2] = 1.0f;

	vertex[20].color[0] = 1.0f;
	vertex[20].color[1] = 0.0f;
	vertex[20].color[2] = 1.0f;

	vertex[21].color[0] = 0.0f;
	vertex[21].color[1] = 1.0f;
	vertex[21].color[2] = 1.0f;

	vertex[22].color[0] = 0.0f;
	vertex[22].color[1] = 1.0f;
	vertex[22].color[2] = 1.0f;

	vertex[23].color[0] = 0.0f;
	vertex[23].color[1] = 1.0f;
	vertex[23].color[2] = 1.0f;

	vertex[24].color[0] = 2.0f;
	vertex[24].color[1] = 1.0f;
	vertex[24].color[2] = 0.0f;

	vertex[25].color[0] = 2.0f;
	vertex[25].color[1] = 1.0f;
	vertex[25].color[2] = 0.0f;

	vertex[26].color[0] = 2.0f;
	vertex[26].color[1] = 1.0f;
	vertex[26].color[2] = 0.0f;

	vertex[27].color[0] = 1.0f;
	vertex[27].color[1] = 0.0f;
	vertex[27].color[2] = 2.0f;

	vertex[28].color[0] = 1.0f;
	vertex[28].color[1] = 0.0f;
	vertex[28].color[2] = 2.0f;

	vertex[29].color[0] = 1.0f;
	vertex[29].color[1] = 0.0f;
	vertex[29].color[2] = 2.0f;

	vertex[30].color[0] = 3.0f;
	vertex[30].color[1] = 0.0f;
	vertex[30].color[2] = 1.0f;

	vertex[31].color[0] = 3.0f;
	vertex[31].color[1] = 0.0f;
	vertex[31].color[2] = 1.0f;

	vertex[32].color[0] = 3.0f;
	vertex[32].color[1] = 0.0f;
	vertex[32].color[2] = 1.0f;

	vertex[33].color[0] = 0.0f;
	vertex[33].color[1] = 3.0f;
	vertex[33].color[2] = 1.0f;

	vertex[34].color[0] = 0.0f;
	vertex[34].color[1] = 3.0f;
	vertex[34].color[2] = 1.0f;

	vertex[35].color[0] = 0.0f;
	vertex[35].color[1] = 3.0f;
	vertex[35].color[2] = 1.0f;

	for (int i = 0; i < sizeof(triangles); i++)
	{
		triangles[i] = i;
	}

	/*triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;*/

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, resultVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	//Change vertex data
	//vertex[0].coordinate[0] += -0.0001f;
	//vertex[0].coordinate[1] += -0.0001f;
	//vertex[0].coordinate[2] += -0.0001f;
	checkKeyInput();
	updateResultVerts();

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, resultVerts, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

void Game::checkKeyInput()
{
	// rotations...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationX(0.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationX(-0.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationZ(0.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationZ(-0.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	// SCALE...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::scale(0.99) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::scale(1.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	// TRANSLATION...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 36; i++)
		{
			// vector addition way..
			/*displacementVectors[i] = displacementVectors[i] + MyVector3(0,0.01,0);*/

			// Matrix Translation way..
			if (displacementVerts[i].coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, 0.01, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, -0.01, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts[i].coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, -0.01, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, 0.01, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts[i].coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0.01, 0, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(-0.01, 0, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts[i].coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(-0.01, 0, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts[i].coordinate[0];
				tempVector.y = displacementVerts[i].coordinate[1];
				tempVector.z = displacementVerts[i].coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0.01, 0, 0)) * tempVector;

				displacementVerts[i].coordinate[0] = tempVector.x;
				displacementVerts[i].coordinate[1] = tempVector.y;
				displacementVerts[i].coordinate[2] = tempVector.z;
			}
		}
	}
}

void Game::updateResultVerts()
{
	for (int i = 0; i < 36; i++)
	{
		resultVerts[i] = vertex[i];

		resultVerts[i].coordinate[0] = vertex[i].coordinate[0] + displacementVerts[i].coordinate[0];
		resultVerts[i].coordinate[1] = vertex[i].coordinate[1] + displacementVerts[i].coordinate[1];
		resultVerts[i].coordinate[2] = vertex[i].coordinate[2] + displacementVerts[i].coordinate[2];
	}
}

