#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include"j1Map.h"
#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
j1Render::~j1Render()
{}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
	
		
		
	}

	return ret;
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	
	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool j1Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);

	return true;
}


void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	for (std::vector<Camera*>::const_iterator item = Mycameras.begin(); item != Mycameras.cend(); ++item) {
		SDL_Rect reset_viewport = { 0,0,0,0 };
		(*item)->viewport_camera = reset_viewport;
	}
}

iPoint j1Render::ScreenToWorld(int x, int y, Camera *camera) const
{
	iPoint ret;
	int scale = App->win->GetScale();
	
	uint i = 0;
	
		ret.x = (x - camera->camera_move.x / scale);
		ret.y = (y - camera->camera_move.y / scale);

	return ret;
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, Camera* cam, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	int scale = App->win->GetScale();
	uint i = 0;

	//TODO 5 
	//Adapt blit to print on each camera 
	//Make that only the textures inside the camera are printed
	if (cam == nullptr) {
		for (std::vector<Camera*>::const_iterator item = Mycameras.begin(); i != Mycameras.size(); i++) {
			if (x >= -item[i]->camera_move.x / scale && x <= (-item[i]->camera_move.x / scale + item[i]->viewport_camera.w / scale)) {
				if (y >= -item[i]->camera_move.y / scale && y <= (-item[i]->camera_move.y / scale + item[i]->viewport_camera.h / scale) ) {
					App->render->SetViewPort(item[i]->viewport_camera);
					App->render->PrintingTexture(texture, x, y, section, item[i], speed, angle, pivot_x, pivot_y);
					SDL_RenderSetViewport(renderer, NULL);
				}
			}
		}
	}
	else {
		i = 0;
		if (x >= -cam->camera_move.x / scale && x <= (-cam->camera_move.x / scale + cam->viewport_camera.w / scale)) {
			if (y >= -cam->camera_move.y / scale && y <= (-cam->camera_move.y / scale + cam->viewport_camera.h / scale)) {
				App->render->SetViewPort(cam->viewport_camera);
				App->render->PrintingTexture(texture, x, y, section, cam, speed, angle, pivot_x, pivot_y);
				SDL_RenderSetViewport(renderer, NULL);
			}
		}
	
	}
	return ret;
}

void j1Render::PrintingTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section , Camera* camera, float speed, double angle, int pivot_x, int pivot_y) {

	int scale = App->win->GetScale();
	SDL_Rect rect;
	rect.x = (int)(camera->camera_move.x * speed) + x * scale;
	rect.y = (int)(camera->camera_move.y * speed) + y * scale;
	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;

	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		//LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
	}
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint i = 0;
	
		
		uint scale = App->win->GetScale();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);

		SDL_Rect rec(rect);
		if(use_camera)
		{
			for (std::vector<Camera*>::const_iterator item = Mycameras.begin(); i != Mycameras.size(); i++) {
				rec.x = (int)(item[i]->camera_move.x + rect.x * scale);
				rec.y = (int)(item[i]->camera_move.y + rect.y * scale);
				rec.w *= scale;
				rec.h *= scale;
			}
		}

		int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

		if(result != 0)
		{
			LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
			ret = false;
		}
		
	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

Camera* j1Render::CreateCamera(iPoint position, SDL_Rect viewport) {

	Camera* cam = new Camera(position, viewport);
	Mycameras.push_back(cam);

	return cam;
}