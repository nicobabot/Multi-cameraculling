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
#include"j1Window.h"
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
	App->map->Load("zelda_map_7.tmx");
	link=App->tex->Load("textures/Link_Sprites copia.png");
	p2 = App->tex->Load("textures/Link_Sprites2.png");
	p2_pos.x = 320;
	p2_pos.y = 200;
	link_pos.x = 300;
	link_pos.y = 200;
	

	
	//TODO 3
	//Create two cameras (using your class and function)
	//One camera will be above the other like in the solution.exe
	App->render->camera = { 0,0,App->win->screen_surface->w,App->win->screen_surface->h };

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
	SDL_Rect Sprite_Rect = { 0,0,20,31 };
	App->render->Blit(p2, p2_pos.x, p2_pos.y, &Sprite_Rect);
	App->render->Blit(link, link_pos.x, link_pos.y,&Sprite_Rect);


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
	SDL_Rect camera_Rect = { 0,App->win->screen_surface->h,App->win->screen_surface->w,10 };
	App->render->DrawQuad(camera_Rect, 0, 0, 255, 255, true, false);

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


	//TODO 4 
	//Make each camera to follow each link 
	
	
	

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
