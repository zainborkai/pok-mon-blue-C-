#ifndef TILEDTEXTURE_H
#define TILEDTEXTURE_H

#include <vector>
#include "Actor.h"


class TiledTexture : public Actor {
public:
	class TileData {
	public:
		TileData(float _x, float _y, int _tx, int _ty, int _tw, int _th, int repx = 1, int repy = 1) {
			x = _x;
			y = _y;
			tx = _tx;
			ty = _ty;
			tw = _tw;
			th = _th;
			repeatX = repx;
			repeatY = repy;
		}
		float x, y;
		int tx, ty, tw, th;
		int repeatX;
		int repeatY;
	};

public:
	TiledTexture(std::string filename) {
		AssignTexture(filename);
		//
		Pos(VEC2_ZERO);
		Scale(VEC2_ONE);
	};

	std::vector<TileData*> tiles;

	void Add(float _x, float _y, int _tx, int _ty, int _tw, int _th, int repx = 1, int repy = 1) {
		TileData* Q = new TileData(_x, _y, _tx, _ty, _tw, _th, repx, repy);
		tiles.push_back(Q);
	}
	void Clear() {
		for (TileData* Q : tiles) {
			delete Q;
		}
		//
		tiles.clear();
	}

	int restrictBegin = -9999;
	int restrictEnd = 9999;

	void Update() {
		Actor::Update();
	}

	void Render() {
		if (visible) {
			for (int n = 0; n < tiles.size(); n++) {
				TileData* Q = tiles[n];
				if (n < restrictBegin) { continue; }
				else if (n > restrictEnd) { continue; }

				for (int yy = 0; yy < Q->repeatY; yy++) {
					for (int xx = 0; xx < Q->repeatX; xx++) {
						Vector2 pos = (Pos(WORLD) + Graphics::GamePos)*Graphics::GameScale;
						Vector2 scale = (Scale(WORLD))*Graphics::GameScale;

						mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x + (Q->x * scale.x) + xx * Q->tw * scale.x);
						mRenderRect.y = (int)(pos.y - mHeight * scale.y * centering.y + (Q->y * scale.y) + yy * Q->th * scale.y);
						mRenderRect.w = (int)(Q->tw * scale.x);
						mRenderRect.h = (int)(Q->th * scale.y);

						mClipRect.x = Q->tx;
						mClipRect.y = Q->ty;
						mClipRect.w = Q->tw;
						mClipRect.h = Q->th;
						mClipped = true;
						//
						mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
					}
				}
			}
		}
	}
};


#endif
