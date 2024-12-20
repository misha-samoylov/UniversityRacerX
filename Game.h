#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>

#include <SDL.h>

#include "BaseApp.h"
#include "Scene.h"
#include "Gui.h"
#include "Physics.h"
#include "ShadowVolumes.h"

#define UNUSED_SHADER_ATTR -1
#define WALK_SPEED 0.01f
#define STATICS_SCALE 0.05f
#define INTRO_TIME_MS 2000


class Game : public BaseApp
{
public:
	Game();
	~Game();
	void onInit(SDL_Window *window);
	void onWindowRedraw(const GameTime & gameTime);
	void onWindowResized(int w, int h);
		
    void drawLines(std::vector<PhysicsDebugDraw::LINE> & lines); // vykresli usecky

	void handleActiveKeys(const GameTime & gameTime);		
	void onKeyDown(SDL_Keycode key, Uint16 mod);
	void onMouseMove(unsigned x, unsigned y, int xrel, int yrel, Uint8 buttons);

    std::string statsString(); // vraci statistiku - pocet vrcholu, facu,...

protected:
	SDL_Window* m_window;

	Scene* scene;
	Gui* gui;
    ModelContainer* container;
    Physics *physics;
	ShadowVolumes* shadowVolumes;

	// handle retezce ukazujici cas
	unsigned int guiTime, guiCheckpoint;

	bool mouseCaptured;

    // indexy polozek v kreslici fronte
	unsigned int carQueueItem;
	unsigned int wheelQueueItem[PhysicsCar::WHEEL_COUNT];

    // pomocna promenna pro moznost kreslit wireframe (TAB)
    bool drawWireframe;

    // pomocna promenna pro moznost zapnuti kamery ktera nasleduje auto (F)
    bool followCamera;

	// pole priznaku rozsvicenych a zhasnutych svetel (moznost prepinani klavesami 1-9)
	std::vector<bool> enabledLights;

	// kreslit stiny? (F6)
	bool drawShadows;

	// zobrazujeme napovedu? (F1)
	bool showHelp;
};

#endif