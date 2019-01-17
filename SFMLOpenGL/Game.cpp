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
GLubyte triangles[6];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

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

	vertex[3].color[0] = 1.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 1.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 1.0f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 0.0f;
	vertex[7].color[2] = 1.0f;

	vertex[8].color[0] = 0.0f;
	vertex[8].color[1] = 0.0f;
	vertex[8].color[2] = 1.0f;

	vertex[9].color[0] = 0.0f;
	vertex[9].color[1] = 0.0f;
	vertex[9].color[2] = 1.0f;

	vertex[10].color[0] = 0.0f;
	vertex[10].color[1] = 0.0f;
	vertex[10].color[2] = 1.0f;

	vertex[11].color[0] = 0.0f;
	vertex[11].color[1] = 0.0f;
	vertex[11].color[2] = 1.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, vertex, GL_STATIC_DRAW);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, vertex, GL_STATIC_DRAW);

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
		for (int i = 0; i < 12; i++)
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

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cubeCorners[i] = (MyMatrix3::rotationX(-0.01) * cubeCorners[i]);
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cubeCorners[i] = (MyMatrix3::rotationZ(0.01) * cubeCorners[i]);
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cubeCorners[i] = (MyMatrix3::rotationZ(-0.01) * cubeCorners[i]);
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//{
	//	glLoadIdentity();
	//}
	//// SCALE...
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cubeCorners[i] = (MyMatrix3::scale(0.99) * cubeCorners[i]);
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cubeCorners[i] = (MyMatrix3::scale(1.01) * cubeCorners[i]);
	//	}
	//}
	//// TRANSLATION...
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		// vector addition way..
	//		/*displacementVectors[i] = displacementVectors[i] + MyVector3(0,0.01,0);*/

	//		// Matrix Translation way..
	//		if (displacementVectors[i].z >= 0)// if z < 0 the translation will be opposite
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0, 0.01, 0)) * displacementVectors[i];
	//		}
	//		else
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0, -0.01, 0)) * displacementVectors[i];
	//		}
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		// vector addition way..
	//		/*displacementVectors[i] = displacementVectors[i] + MyVector3(0, -0.01, 0);*/

	//		// Matrix Translation way..
	//		if (displacementVectors[i].z >= 0)// if z < 0 the translation will be opposite
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0, -0.01, 0)) * displacementVectors[i];
	//		}
	//		else
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0, 0.01, 0)) * displacementVectors[i];
	//		}
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		// vector addition way..
	//		/*displacementVectors[i] = displacementVectors[i] + MyVector3(0.01, 0, 0);*/

	//		// Matrix Translation way..
	//		if (displacementVectors[i].z >= 0)// if z < 0 the translation will be opposite
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0.01, 0, 0)) * displacementVectors[i];
	//		}
	//		else
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(-0.01, 0, 0)) * displacementVectors[i];
	//		}
	//	}
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		// vector addition way..
	//		/*displacementVectors[i] = displacementVectors[i] + MyVector3(-0.01, 0, 0);*/

	//		// Matrix Translation way..
	//		if (displacementVectors[i].z >= 0)	// if z < 0 the translation will be opposite
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(-0.01, 0, 0)) * displacementVectors[i];
	//		}
	//		else
	//		{
	//			displacementVectors[i] = MyMatrix3::translation(MyVector3(0.01, 0, 0)) * displacementVectors[i];
	//		}
	//	}
	//}

}

