
#ifndef NUMBER_SELECTOR_H
#define NUMBER_SELECTOR_H
#include <dream_variables.h>
#include <vector>

using namespace std;

class NumberSelector {
	vector<int> integerArray;

	Vector2 pos;
	Color color;
	Font* font;

public:
	NumberSelector(vector<int> integerArray, Vector2 pos, Color color, Font* font);

	void renderNumber();
	void processInput();
	int getNumber();
};


#endif //NUMBER_SELECTOR_H
