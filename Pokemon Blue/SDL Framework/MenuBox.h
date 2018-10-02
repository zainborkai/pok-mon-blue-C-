#ifndef MENUBOX_H
#define MENUBOX_H

class MenuBox : public TiledTexture {
public:
	MenuBox(int width, int height) :
		TiledTexture("battle/menustuff.png") {
		Add(0, 0, 0, 0, 8, 8, 1, 1);
		Add(0, 8 * (height + 1), 8, 0, 8, 8, 1, 1);
		Add(8 * (width + 1), 0, 16, 0, 8, 8, 1, 1);
		Add(8 * (width + 1), 8 * (height + 1), 24, 0, 8, 8, 1, 1);
		Add(0, 8, 32, 0, 8, 8, 1, height);
		Add(8 * (width + 1), 8, 32, 0, 8, 8, 1, height);
		Add(8, 0, 40, 0, 8, 8, width, 1);
		Add(8, 8 * (height + 1), 40, 0, 8, 8, width, 1);
		//
		Add(8, 8, 56, 0, 8, 8, width, height);
	}
};


#endif
