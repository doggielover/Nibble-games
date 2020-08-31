#ifndef ELEMENTS_SWITCH_H
#define ELEMENTS_SWITCH_H

#include <UI/CustomElement.h>
#include <Loop/LoopListener.h>

class Switch : public CustomElement, public LoopListener {
public:
	Switch(ElementContainer* parent);

	void draw() override;
	void loop(uint micros) override;

	void toggle();
	void set(bool state, bool instant = false);
	bool getState();

private:
	bool state = false;
	bool toggling = false;
	float toggleProgress = 0;
	float toggleAccum = 0;

};


#endif //ELEMENTS_SWITCH_H
