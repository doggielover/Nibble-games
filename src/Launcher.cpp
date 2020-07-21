#include "Launcher.h"
#include "ByteBoi.hpp"
#include <Input/Input.h>

#include "GameScroller.h"
#include "Elements/Logo.h"
#include "Elements/GameTitle.h"

#include "../GameInfo.hpp"

const GameInfo RedInfo {
		"RED",
		"",
		nullptr,
		[](Display& display) -> Context* { return nullptr; }
};

const GameInfo BlueInfo {
		"BLUE",
		"",
		nullptr,
		[](Display& display) -> Context* { return nullptr; }
};

const GameInfo YellowInfo {
		"YELLOW",
		"",
		nullptr,
		[](Display& display) -> Context* { return nullptr; }
};

const GameInfo GreenInfo {
		"GREEN",
		"",
		nullptr,
		[](Display& display) -> Context* { return nullptr; }
};

const GameInfo games[] = {
	RedInfo, BlueInfo, YellowInfo, GreenInfo
};

Launcher* instance = nullptr;

Launcher::Launcher(Display* display) : display(display), canvas(display->getBaseSprite()),
		scroller(new GameScroller(canvas, this)), logo(new Logo(canvas)), title(new GameTitle(canvas)){

	instance = this;
	canvas->setChroma(TFT_TRANSPARENT);

	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		instance->next();
	});

	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		instance->prev();
	});

	title->change(games[selectedGame].title);
}

void Launcher::prev(){
	uint8_t selecting = instance->scroller->prev();
	if(selecting != selectedGame){
		instance->title->change(games[selecting].title);
	}
	selectedGame = selecting;
}

void Launcher::next(){
	uint8_t selecting = instance->scroller->next();
	if(selecting != selectedGame){
		instance->title->change(games[selecting].title);
	}
	selectedGame = selecting;
}

void Launcher::update(uint micros){
	draw();
	display->commit();
}

void Launcher::draw(){
	canvas->clear(TFT_BLACK);
	logo->draw();
	title->draw();
	scroller->draw();
}
