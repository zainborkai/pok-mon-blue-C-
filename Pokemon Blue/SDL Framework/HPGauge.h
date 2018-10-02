#ifndef HPGAUGE_H
#define HPGAUGE_H

#include "VariedTexture.h"


class HPGauge : public VariedTexture {
public:
	HPGauge(float val, bool glitchyPlayerBar = false) : VariedTexture("battle/healthbar.png") {
		Add("bar_H", 0, 0, 1, 1, 0, 0, 8, 8, Vector2(0, 0));
		Add("bar_P", 8, 0, 1, 1, 8, 0, 8, 8, Vector2(0, 0));
		Add("bar_health_holder", 16, 0, 6, 1, 24, 0, 8, 8, Vector2(0, 0));
		Add("bar_health_filler", 16, 0, 6, 1, 32, 0, 8, 8, Vector2(0, 0));
		Add("bar_end", 16 + 8 * 6, 0, 1, 1, (glitchyPlayerBar ? 40 : 16), 0, 8, 8, Vector2(0, 0));
		//
		SetValue(val);
	}

	void SetValue(float val) {
		value = val;
		//
		UpdateGauge();
	}

	float value = 1.0f;

	void UpdateGauge() {
		TileData* Q = Get("bar_health_filler");
		//
		Q->w = 6 * value;
	}
};


#endif
