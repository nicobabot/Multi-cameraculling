#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Gui.h"
#include "SDL\include\SDL.h"

struct SDL_Texture;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	


	
private:
	SDL_Texture *link;
	SDL_Texture *p2;
	iPoint link_pos,p2_pos;

	Camera* camera_one;
	Camera* camera_two;
//	Camera* camera_3;
};

#endif // __j1SCENE_H__