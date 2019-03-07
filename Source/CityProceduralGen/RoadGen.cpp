#include "RoadGen.h"

#include <Core/Engine.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;

RoadGen::RoadGen(int height, int width, int maxTunnels, int maxLength) {
	this->height = height;
	this->width = width;
	this->maxTunnels = maxTunnels;
	this->maxLength = maxLength;
	road = new int*[height];
	for (int i = 0; i < height; i++)
		road[i] = new int[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			road[i][j] = 1;

	/*Initialize the direct matrix with 0.*/
	direct = new int*[height];
	for (int i = 0; i < height; i++)
		direct[i] = new int[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			direct[i][j] = 0;

	Roads();
}


/*The algorithm for procedurally generating the Direct matrix which will 
determine where the roads and buildings will be.*/
void RoadGen::Roads()
{
	pair <int, int> point;
	point.first = rand() % this->height;
	point.second = rand() % this->width;
	cout << point.first << " " << point.second << endl;

	int tunnels = 0, tunnel_length_max = 0;
	while (tunnels < maxTunnels / 2) {
		tunnels = rand() % maxTunnels;
	}

	while (tunnel_length_max < maxLength / 2) {
		tunnel_length_max = rand() % maxLength;
	}

	int direction = chooseDirection(0);
	int tunnel_length = -1;

	while (checkMove(direction, point, tunnel_length) == false) {
		direction = chooseDirection(0);
	}

	while (tunnels > 0) {
		int i = point.first, j = point.second;
		road[i][j] = 0;
		direct[i][j] = direction;
		tunnel_length++;

		int old_direction = direction;
		while (checkMove(direction, point, tunnel_length) == false || tunnel_length == tunnel_length_max - 1) {
			direction = chooseDirection(old_direction);
			if (checkMove(direction, point, tunnel_length) == true) {
				while (tunnel_length_max < maxLength / 2) {
					tunnel_length_max = rand() % maxLength;
				}
				tunnel_length = 0;
				tunnels--;
			}
		}
		point = move(direction, point);
	}

}

int RoadGen::chooseDirection(int oldDirection)
{
	//Directions: 1 -> UP, 2 -> DOWN, -1 -> LEFT, -2 -> RIGHT 
	if (oldDirection == 0) {
		int newDirection = rand() % 4;
		if (newDirection == 0) {
			newDirection = -2;
		}
		if (newDirection == 3) {
			newDirection = -1;
		}
		return newDirection;

	} else 
	{
		int newDirection = 0;
		while (newDirection == 0) {
			newDirection = rand() % 4;
			if (newDirection == 0) {
				newDirection = -2;
			}
			if (newDirection == 3) {
				newDirection = -1;
			}

			if (abs(newDirection - oldDirection) == 1 || newDirection == oldDirection) {
				newDirection = 0;
			}
		}

		return newDirection;
	}
}

bool RoadGen::checkMove(int direction, pair<int, int> point, int tunnel_length)
{
	//Directions: 1 -> UP, 2 -> DOWN, -1 -> LEFT, -2 -> RIGHT 
	int i = point.first, j = point.second;
	if (direction == 1) {
		if (i == 0) {
			return false;
		}
	}
	if (direction == 2) {
		if (i == height - 1) {
			return false;
		}
	}
	if (direction == -1) {
		if (j == 0) {
			return false;
		}
	}
	if (direction == -2) {
		if (j == width - 1) {
			return false;
		}
	}
	return true;
}

pair<int, int> RoadGen::move(int direction, pair<int, int> point)
{
	//Directions: 1 -> UP, 2 -> DOWN, -1 -> LEFT, -2 -> RIGHT 

	int i = point.first, j = point.second;
	pair <int, int> new_point;
	if (direction == 1) {
		new_point.first = i - 1;
		new_point.second = j;
	}

	if (direction == 2) {
		new_point.first = i + 1;
		new_point.second = j;
	}

	if (direction == -1) {
		new_point.first = i;
		new_point.second = j - 1;
	}

	if (direction == -2) {
		new_point.first = i;
		new_point.second = j + 1;
	}

	return new_point;
}
