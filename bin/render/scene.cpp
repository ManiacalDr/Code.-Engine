// Standard Libraries
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

#include "renderer.h"
#include "jsoncons/json.hpp"
#include "scene.h"
#include "object.hpp"
#include "sprite.h"
#include "stb_image.h"
#include <box2d/box2d.h>


Scene::Scene()
{
	world = new b2World(b2Vec2(0.0, -5.81));
	void worldStep();
	contactListener = new MyContactListener();
	world->SetContactListener(contactListener);
}

void Scene::worldStep()
{
	world->Step(1.0 / 60, 8, 3);
}

Scene::~Scene()
{
	
}

//Save the Sprites vector
void Scene::saveSprites(const std::string file)
{
	//Open file specifed in arguments
	std::ofstream output;
	output.open(file, std::ios_base::out);

	output << playerStart.x << std::endl << playerStart.y << std::endl << playerStart.z << std::endl;

	//String vector to save unique names and flag if name has been found
	std::vector<std::string> uniques;
	int uniFlag = 0, val = 0;

	//Run through the sprites list to collect unique names only at the top
	for (auto i = sprites.begin(); i != sprites.end(); i++)
	{
		Sprite* temp = dynamic_cast<Sprite*>(*i);
		//Compare list of uniques with current sprite
		if (temp != nullptr) {
			for (auto j = uniques.begin(); j != uniques.end(); j++)
			{
				//If any match, it's not unique
				if (temp->name == *j)
				{
					uniFlag = 1;
					val++;
				}
			}
			//If no match, it's unique
			if (uniFlag == 0)
			{
				//Add to vector, add to file, output to console
				uniques.push_back(temp->name);
				output << temp->name << std::endl;
				std::cout << temp->name << " ";
			}
			//Next string, reset flag
			uniFlag = 0;
		}
	}
	//End console line and reset temp head and uniques
	//Maybe add a "end of names" line, so reading is easier
	output << "endofnames" << std::endl;
	//std::cout << std::endl;

	//Run through sprites list to collect rest of variables
	for (int i = 0; i < sprites.size(); i++)
	{
		Sprite* temp = dynamic_cast<Sprite*>(sprites[i]);
		
		

			//Save each variable, each variable separated by a new line
			//Comment out whatever isn't needed, I'm sure some of this stuff can be initialized when reading file
		output << std::endl << temp->name << std::endl;
			output << temp->position.x << std::endl << temp->position.y << std::endl << temp->position.z << std::endl;
			output << temp->rotation << std::endl;
			output << temp->scaleValue.x << std::endl << temp->scaleValue.y << std::endl << temp->scaleValue.z << std::endl;
			output << temp->ID << std::endl;
			//whatever defaultUV is
			output << temp->color.x << std::endl << temp->color.y << std::endl << temp->color.z << std::endl << temp->color.w << std::endl;
			//Animation
			//if (!temp->animating)
				//output << -1 << std::endl;
			//else
				//output << temp->animating << std::endl;
			//output << temp->frame;
			//no clue about texture, collider, or scene
			if (temp->collider != nullptr) {
				if (temp->collider->GetType() == b2_dynamicBody)
					output << std::to_string(1);
				else
					output << std::to_string(2);
			}
			else
				output << std::to_string(-1);

		
	}

	output.close();
}

//Read sprites from file
void Scene::readSprites(const std::string file)
{
	//Input variable, open file from argument
	std::ifstream input;
	input.open(file, std::ios_base::in);

	//Create a temp from the root object
	//Maybe make a new sprite completely to add stuff to? not entirely sure
	Sprite* temp;

	//Input string, along with a section flag to determine if on names or other vars
	std::string inpStr;
	int secFlag = 0;
	std::vector<GLint> tempvec;
	std::vector<std::string> temppath;

	input >> inpStr;
	playerStart.x = std::stoi(inpStr);
	input >> inpStr;
	playerStart.y = std::stoi(inpStr);
	input >> inpStr;
	playerStart.z = std::stoi(inpStr);

	//While reading input
	while (input >> inpStr)
	{
		std::cout << inpStr << std::endl;
		//While in the first part & input isn't reading end of names
		if (secFlag == 0 && inpStr != "endofnames") //part 1
		{
			//add name to temp, add temp to sprites vector
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			int width, height, nrChannels;

			unsigned char* data = stbi_load(inpStr.c_str(), &width, &height, &nrChannels, 4);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture" << std::endl;
			}
			stbi_image_free(data);
			tempvec.push_back(texture);
			temppath.push_back(inpStr);
		}
		//If end of names, change it to part 2
		else if (secFlag == 0)
		{
			secFlag = 1;
			//Reset temp to first variable, although I'm positive this is messed up
			//Because in the previous step, we change the name

			//temp = dynamic_cast<Sprite*>(root);
		}
		//Starting at the first sprite, add all the other variables to them
		else //part 2
		{
			temp = new Sprite();
			temp->name = inpStr;
			//I think this should work
			//Comment out whatever isn't needed, I'm sure some of this stuff can be initialized when reading file
			input >> inpStr;
			temp->position.x = std::stof(inpStr);
			input >> inpStr; 
			temp->position.y = std::stof(inpStr);
			input >> inpStr; 
			temp->position.z = std::stof(inpStr);
			input >> inpStr;
			temp->rotation = std::stof(inpStr);
			input >> inpStr; 
			temp->scaleValue.x = std::stof(inpStr);
			input >> inpStr; 
			temp->scaleValue.y = std::stof(inpStr);
			input >> inpStr; 
			temp->scaleValue.z = std::stof(inpStr);
			input >> temp->ID;
			input >> inpStr;
			temp->color.x = std::stof(inpStr);
			input >> inpStr;
			temp->color.y = std::stof(inpStr);
			input >> inpStr;
			temp->color.z = std::stof(inpStr); 
			input >> inpStr;
			temp->color.w = std::stof(inpStr);
			//same thing with UV and curFrame, I have no clue how these are set upper_bound
			
			//input >> inpStr;
			//if (std::stoi(inpStr) == -1)
				//temp->animating = 0;
			//else
				//temp->animating = std::stoi(inpStr);
			//input >> inpStr;
			//temp->frame = 0;
			input >> inpStr;
			//std::cout << inpStr;
			int ifCollision = std::stoi(inpStr);
			if (ifCollision != -1) {
				if (ifCollision == 1)
					temp->addCollider(true, this);
				else if(ifCollision == 2)
					temp->addCollider(false, this);
			}

			if (temp->ID == "PlayerSprite") {
				temp->makePlayer(this);
				temp->setUV(glm::vec2(0, 0), glm::vec2(318, 424), 12, glm::vec2(106, 106));
				int* tmpFrames = new int[3]{ 0,1,2 };
				temp->setAnimation("downWalk", tmpFrames, 3);
				tmpFrames = new int[3]{ 3,4,5 };
				temp->setAnimation("leftWalk", tmpFrames, 3);
				tmpFrames = new int[3]{ 6,7,8 };
				temp->setAnimation("rightWalk", tmpFrames, 3);
				tmpFrames = new int[3]{ 9,10,11 };
				temp->setAnimation("upWalk", tmpFrames, 3);
				temp->animating = true;
			}
			else {
				temp->curFrame = glm::mat4x2(temp->defaultUV);
				temp->UV = new glm::mat4x2(temp->defaultUV);
			}
			
			int place = 0;
			for (auto i = temppath.begin(); i != temppath.end(); i++) {
				if (temp->name == *i)
					temp->texture = tempvec[place];
				place++;
			}

			temp->print();
			sprites.emplace_back(temp);
		}
	}
	//Tuck the file into bed
	input.close();
}