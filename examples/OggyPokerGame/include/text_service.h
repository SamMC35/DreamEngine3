
#ifndef TEXT_SERVICE_H
#define TEXT_SERVICE_H
#include <dream_variables.h>

typedef struct TextBox {
	Vector2 position;
	int borderSize;
	Color bgColor;
	Color borderColor;
	Timer timer;
}TextBox;

void addTextBox(TextBox* textBox);
void renderQueue();

#endif //TEXT_SERVICE_H
