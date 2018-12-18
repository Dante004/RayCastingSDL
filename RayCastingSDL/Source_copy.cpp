/*#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
#include "Source.h"
using namespace QuickCG;
#define screenWidth 800
#define screenHeight 600
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define numSprites 20

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

int map[mapWidth][mapHeight] =
{
	{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

struct Sprite
{
	double x;
	double y;
	int texture[8];
};

Sprite sprite[numSprites] =
{
	//green light in front of playerstart
	{20.5, 11.5, {10,10,10,10,10,10,10,10}},
	//green lights in every room
	{18.5,4.5, {10,10,10,10,10,10,10,10}},
	{10.0,4.5, {10,10,10,10,10,10,10,10}},
	{10.0,12.5,{10,10,10,10,10,10,10,10}},
	{3.5, 6.5, {10,10,10,10,10,10,10,10}},
	{3.5, 20.5,{10,10,10,10,10,10,10,10}},
	{3.5, 14.5,{10,10,10,10,10,10,10,10}},
	{14.5,20.5,{10,10,10,10,10,10,10,10}},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, {9,9,9,9,9,9,9,9}},
	{18.5, 11.5, {9,9,9,9,9,9,9,9}},
	{18.5, 12.5, {9,9,9,9,9,9,9,9}},

	//some barrels around the map
	{21.5, 1.5, {8,8,8,8,8,8,8,8}},
	{15.5, 1.5, {8,8,8,8,8,8,8,8}},
	{16.0, 1.8, {8,8,8,8,8,8,8,8}},
	{16.2, 1.2, {8,8,8,8,8,8,8,8}},
	{3.5,  2.5, {8,8,8,8,8,8,8,8}},
	{9.5, 15.5, {8,8,8,8,8,8,8,8}},
	{10.0, 15.1,{8,8,8,8,8,8,8,8}},
	{10.5, 15.8,{8,8,8,8,8,8,8,8}},

	//enemy
	{20.5,11.5,{11,12,13,14,15,16,17,18}}
};

//1D Zbuffer
double ZBuffer[screenWidth];

//arrays used to sort the sprites
int spriteOrder[numSprites];
double spriteDistance[numSprites];

//function used to sort the sprites
void combSort(int* order, double* dist, int amount);

void RayCasting(double dirX, double planeX, double dirY, double planeY, double posX, double posY, std::vector<Uint32>  texture[11]);

int LoadTexture(std::vector<Uint32>  texture[11], bool &retflag);

void DetectWall(int &hit, double &sideDistX, double &sideDistY, double deltaDistX, int &mapX, int stepX, int &side, double deltaDistY, int &mapY, int stepY);

Uint32 buffer[screenHeight][screenWidth];

int main(int /*argc, char *argv[])
{
double posX = 22.0, posY = 11.5;  //x and y start position
double dirX = -1.0, dirY = 0.0; //initial direction vector
double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane

double time = 0; //time of current frame
double oldTime = 0; //time of previous frame

std::vector<Uint32> texture[19];
for (int i = 0; i < 19; ++i) texture[i].resize(texWidth * texHeight);

//load some textures
unsigned long tw, th, error = 0;
error |= loadImage(texture[0], tw, th, "Texture/eagle.png");
error |= loadImage(texture[1], tw, th, "Texture/redbrick.png");
error |= loadImage(texture[2], tw, th, "Texture/purplestone.png");
error |= loadImage(texture[3], tw, th, "Texture/greystone.png");
error |= loadImage(texture[4], tw, th, "Texture/bluestone.png");
error |= loadImage(texture[5], tw, th, "Texture/mossy.png");
error |= loadImage(texture[6], tw, th, "Texture/wood.png");
error |= loadImage(texture[7], tw, th, "Texture/colorstone.png");
error |= loadImage(texture[8], tw, th, "Texture/barrel.png");
error |= loadImage(texture[9], tw, th, "Texture/pillar.png");
error |= loadImage(texture[10], tw, th, "Texture/greenlight.png");
error |= loadImage(texture[11], tw, th, "Texture/enemy1.png");
error |= loadImage(texture[12], tw, th, "Texture/enemy2.png");
error |= loadImage(texture[13], tw, th, "Texture/enemy3.png");
error |= loadImage(texture[14], tw, th, "Texture/enemy4.png");
error |= loadImage(texture[15], tw, th, "Texture/enemy5.png");
error |= loadImage(texture[16], tw, th, "Texture/enemy6.png");
error |= loadImage(texture[17], tw, th, "Texture/enemy7.png");
error |= loadImage(texture[18], tw, th, "Texture/enemy8.png");
if (error) {
	std::cout << "error loading images" << std::endl; return 1;
}

screen(screenWidth, screenHeight, 0, "Raycaster");

//start the main loop
while (!done())
{
	RayCasting(dirX, planeX, dirY, planeY, posX, posY, texture);

	drawBuffer(buffer[0]);
	for (int x = 0; x < w; ++x) for (int y = 0; y < h; ++y) buffer[y][x] = 0; //clear the buffer instead of cls()
	//timing for input and FPS counter
	oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	print(1.0 / frameTime); //FPS counter
	redraw();

	//speed modifiers
	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

	readKeys();
	//move forward if no wall in front of you
	if (keyDown(SDLK_w))
	{
		if (map[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		if (map[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_s))
	{
		if (map[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		if (map[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}

	//rotate to the right
	if (keyDown(SDLK_d))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (keyDown(SDLK_a))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
}
return 0;
}

void RayCasting(double dirX, double planeX, double dirY, double planeY, double posX, double posY, std::vector<Uint32>  texture[11])
{
	for (int x = 0; x < w; ++x)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		//which box of the map we're in
		int mapX = int(posX);
		int mapY = int(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

				  //calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		DetectWall(hit, sideDistX, sideDistY, deltaDistX, mapX, stepX, side, deltaDistY, mapY, stepY);

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h) drawEnd = h - 1;

		//texturing calculations
		int texNum = map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

										  //calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = posY + perpWallDist * rayDirY;
		else           wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = int(wallX * double(texWidth));
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		int y = drawStart;
		while (++y < drawEnd)
		{
			int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
														   // TODO: avoid the division to speed this up
			int texY = ((d * texHeight) / lineHeight) / 256;
			Uint32 color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1) color = (color >> 1) & 8355711;
			buffer[y][x] = color;
		}

		//set the zbuffer for the sprite casting
		ZBuffer[x] = perpWallDist; //perpendicular distance in used

								   //Floor casting
		double floorXWall, floorYWall; //x,y position of the floor texel at the bottom of the wall

									   //4 diffrent wall directions possible
		if (side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if (side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if (side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}
		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows

									  //draw the floor from drawEnd to the bottom of the screen
		for (int y = drawEnd + 1; y < h; ++y)
		{
			currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

			int floorTexX, floorTexY;
			floorTexX = int(currentFloorX * texWidth) % texWidth;
			floorTexY = int(currentFloorY * texHeight) % texHeight;

			//floor
			buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
		}
	}

	//Sprite casting
	//sort sprites from far to close
	for (int i = 0; i < numSprites; ++i)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((posX - sprite[i].x)*(posX - sprite[i].x) + (posY - sprite[i].y)*(posY - sprite[i].y));
	}
	combSort(spriteOrder, spriteDistance, numSprites);
	//after sorting the sprtite do the projection and draw them
	for (int i = 0; i < numSprites; ++i)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - posX;
		double spriteY = sprite[spriteOrder[i]].y - posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs(int(h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
													   //calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + h / 2;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h) drawEndY = h - 1;

		//calculate width of the sprite
		int spriteWidth = abs(int(h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w) drawEndX = w - 1;
		double dx = posX - sprite[spriteOrder[i]].x;
		double dy = posY - sprite[spriteOrder[i]].y;
		int angle = std::abs(round(atan2(dy, dx)));
		//if (angle > 7) angle = 7;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; ++stripe)
		{
			int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; ++y) //for every pixel of the current stripe
				{
					int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					Uint32 color = texture[sprite[spriteOrder[i]].texture[angle]][texWidth * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}

void DetectWall(int &hit, double &sideDistX, double &sideDistY, double deltaDistX, int &mapX, int stepX, int &side, double deltaDistY, int &mapY, int stepY)
{
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (map[mapX][mapY] > 0) hit = 1;
	}
}

//sort algorithm
void combSort(int* order, double* dist, int amount)
{
	int gap = amount;
	bool swapped = false;
	while (gap > 1 || swapped)
	{
		//shrink factor 1.3
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10) gap = 11;
		if (gap < 1) gap = 1;
		swapped = false;
		for (int i = 0; i < amount - gap; i++)
		{
			int j = i + gap;
			if (dist[i] < dist[j])
			{
				std::swap(dist[i], dist[j]);
				std::swap(order[i], order[j]);
				swapped = true;
			}
		}
	}
}
*/