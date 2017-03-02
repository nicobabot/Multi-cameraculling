#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	p2List_item<UI*> *temp = UI_Elements.start;
	for (temp; temp != nullptr; temp = temp->next) {
		delete temp;
	}
	UI_Elements.clear();
	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

UI * j1Gui::create(TYPE type)
{
	UI *detector=nullptr;
	switch (type) {
	case UI_DETECTOR:
		detector = new UI_Detector();
		break;
	case UI_IMAGE:
		detector = new UI_Image();
		break;
	case UI_BUTTONS:
		detector = new UI_Buttons();
		break;
	case UI_NON_STATIC_LETTERS:
		detector = new UI_Letters_NonStatic();
		break;
	case UI_STATIC_LETTERS:
		detector = new UI_Letters_Static();
		break;
	}
	UI_Elements.add(detector);
	return detector;
}

bool j1Gui::UIdelete(UI * node)
{
	bool ret = false;
	if (UI_Elements.find(node) != -1) {
		p2List_item<UI*> *temp = UI_Elements.start;
		for (temp; temp != nullptr; temp = temp->next) {
			if (temp->data == node) {
				ret=UI_Elements.del(temp);
				return ret;
			}
		}
	}
	return ret;
}

p2List<UI*>j1Gui::Getlist() {
	return UI_Elements;
}

// class Gui ---------------------------------------------------

UI::UI()
{
}

UI::UI(TYPE type, SDL_Rect rect): UI_type(type), UI_Rect(rect){
}

UI::~UI()
{
}

void UI::update()
{
}

void UI::draw()
{
}

void UI::handleinput()
{
}

UI_Detector::UI_Detector()
{
}

UI_Detector::~UI_Detector()
{
}

bool UI_Detector::oncollision(iPoint, UI*)
{
	return false;
}

void UI_Detector::draw()
{
}

void UI_Image::draw()
{
	p2List<UI*>list = Getlist();
	p2List_item<UI*>* temp = list.start;

}

UI_Buttons::UI_Buttons()
{
}

UI_Buttons::~UI_Buttons()
{
}

void UI_Buttons::draw(BUTTON_TYPE)
{
}

UI_Letters_NonStatic::UI_Letters_NonStatic()
{
}

UI_Letters_NonStatic::~UI_Letters_NonStatic()
{
}

void UI_Letters_NonStatic::draw()
{
}

void UI_Letters_NonStatic::handleinput()
{
}

UI_Letters_Static::UI_Letters_Static()
{
}

UI_Letters_Static::~UI_Letters_Static()
{
}

void UI_Letters_Static::draw()
{
}
