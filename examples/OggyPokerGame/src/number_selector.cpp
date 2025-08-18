#include <number_selector.h>
#include <sstream>

#include <dream_text.h>


NumberSelector::NumberSelector(vector<int> integerArray, Vector2 pos, Color color, Font *font) {
	this->integerArray = integerArray;
	this->pos = pos;
	this->color = color;
	this->font = font;
}


void NumberSelector::renderNumber() {
	writeText((char*)std::to_string(getNumber()).c_str(), pos, color, font);
}

int NumberSelector::getNumber() {
	stringstream numString;
	for (int i : integerArray) {
		numString << i;
	}
	int number;
	numString >> number;

	return number;
}

