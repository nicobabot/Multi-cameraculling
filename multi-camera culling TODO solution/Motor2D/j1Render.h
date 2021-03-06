#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include<vector>;


//TODO 1
//Create Class Camera
//We will need a viewport where the camera will be shown
//and the position of the camera
//This camera  will be used for navegate through the map
class Camera {
public:
	Camera(iPoint position, SDL_Rect viewport) :camera_move(position), viewport_camera(viewport){}
	iPoint camera_move;
	SDL_Rect  viewport_camera;
	
};


class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y, Camera *camera) const;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, Camera* cam = nullptr, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer;
	

	

	SDL_Rect		viewport;
	SDL_Color		background;
	//TODO 2
	//Add a list or array of cameras? Wich is better?
	//In this list/array we will store all the cameras 
	//that we will use on the game
	//Add also a function to create cameras
	std::vector<Camera*> Mycameras;
	Camera* CreateCamera(iPoint position, SDL_Rect viewport);
	void PrintingTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = nullptr, Camera* camera =nullptr, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
};

#endif // __j1RENDER_H__