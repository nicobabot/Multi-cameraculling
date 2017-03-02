#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2
enum TYPE {
	UI_DETECTOR,
	UI_IMAGE,
	UI_BUTTONS,
	UI_NON_STATIC_LETTERS,
	UI_STATIC_LETTERS
};

enum BUTTON_TYPE {
	BUTTON_TRIGGERED,
	BUTTON_NONTRIGGERED
};

class UI;
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	
	// Gui creation functions

	const SDL_Texture* GetAtlas() const;

	p2List<UI*>Getlist();
private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<UI*> UI_Elements;
	UI* create(TYPE type);
	bool UIdelete(UI* node);
	
};

class UI : public j1Gui {
public:
	UI();
	UI(TYPE, SDL_Rect);
	~UI();
private:
	TYPE UI_type;
	SDL_Rect UI_Rect;
	virtual void update();
	virtual void draw();
	virtual void handleinput();
};

class UI_Detector : public UI {
public:
	UI_Detector();
	~UI_Detector();
private:
	bool oncollision(iPoint, UI*);
	void draw();
};

class UI_Image : public UI {
public:

private:
	void draw();
};

class UI_Buttons : public UI {
public:
	UI_Buttons();
	~UI_Buttons();
private:
	bool trigered;
	BUTTON_TYPE button_state;
	void draw(BUTTON_TYPE);
};

class UI_Letters : public UI {
public:
	p2SString TextureOrder;
private:

};

class UI_Letters_NonStatic: public UI_Letters {
public:
	UI_Letters_NonStatic();
	~UI_Letters_NonStatic();
private:
	p2SString string;
	void draw();
	void handleinput();
};

class UI_Letters_Static : public UI_Letters {
public:
	UI_Letters_Static();
	~UI_Letters_Static();
private:
	static p2SString string;
	void draw();
};

#endif // __j1GUI_H__