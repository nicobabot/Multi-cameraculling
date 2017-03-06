#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"

#include "j1Gui.h"



#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
	
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("zelda_map.tmx");
	link=App->tex->Load("textures/Link_Sprites copia.png");
	p2 = App->tex->Load("textures/Link_Sprites2.png");
	p2_pos.x = 100;
	p2_pos.y = 50;
	link_pos.x = 200;
	link_pos.y = 100;
	
	
	
	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{	
	App->map->Draw();

	

	if (App->input->GetKey(SDL_SCANCODE_W)==KEY_REPEAT) {
		link_pos.y--;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		link_pos.y++;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		link_pos.x++;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		link_pos.x--;
	}


	uint x, y;
	App->win->GetWindowSize(x, y);
	
	int movementx = -link_pos.x * App->win->GetScale() + x/2-8 ;
	int movementy = -link_pos.y * App->win->GetScale() + (y/2)/ 2-8;

	App->render->camera.x = movementx;
	App->render->camera.y = movementy;


	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		p2_pos.y--;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		p2_pos.y++;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		p2_pos.x++;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		p2_pos.x--;
	}


	movementx = -p2_pos.x * App->win->GetScale() + x / 2 - 8;
	movementy = -p2_pos.y * App->win->GetScale() + (y / 2) / 2 - 8;

	App->render->camera_two.x = movementx;
	App->render->camera_two.y = movementy;


	
	App->render->Blit(p2, p2_pos.x, p2_pos.y);
	App->render->Blit(link, link_pos.x, link_pos.y);
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	
	
	return true;
}
