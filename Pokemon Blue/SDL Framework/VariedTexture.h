#ifndef VARIEDTEXTURE_H
#define VARIEDTEXTURE_H

#include <map>
#include "Actor.h"


class VariedTexture : public Actor {
public:
	class TileData {
	public:
		TileData(float _x, float _y, float _scalex, float _scaley, int _tx, int _ty, int _tw, int _th, Vector2 _cen) {
			x = _x;
			y = _y;
			w = _scalex;
			h = _scaley;
			tx = _tx;
			ty = _ty;
			tw = _tw;
			th = _th;
			cen = _cen;
		}
		float x, y;
		float w, h;
		int tx, ty, tw, th;
		Vector2 cen;
	};

public:
	VariedTexture(std::string filename) {
		AssignTexture(filename);
		//
		Pos(VEC2_ZERO);
		Scale(VEC2_ONE);
	};

	std::map<std::string, TileData*> tiles;

	void Add(std::string id, float _x, float _y, float _w, float _h, int _tx, int _ty, int _tw, int _th, Vector2 _cen) {
		TileData* Q = new TileData(_x, _y, _w, _h, _tx, _ty, _tw, _th, _cen);
		tiles[id] = Q;
	};
	TileData* Get(std::string index) { return tiles[index]; };
	void Clear() {
		for (auto Q : tiles) {
			delete Q.second;
		}
		//
		tiles.clear();
	};

	void Update() {
		Actor::Update();
	};

	void Render() {
		if (visible) {
			for (auto pairs : tiles) {
				TileData* Q = pairs.second;
				//
				Vector2 pos = (Pos(WORLD) + Graphics::GamePos)*Graphics::GameScale;
				Vector2 scale = (Scale(WORLD))*Graphics::GameScale;

				mRenderRect.x = (int)(pos.x - mWidth * scale.x *Q->w * Q->cen.x + (Q->x * scale.x));
				mRenderRect.y = (int)(pos.y - mHeight * scale.y *Q->h * Q->cen.y + (Q->y * scale.y));
				mRenderRect.w = (int)(Q->tw * scale.x *Q->w);
				mRenderRect.h = (int)(Q->th * scale.y *Q->h);

				mClipRect.x = Q->tx;
				mClipRect.y = Q->ty;
				mClipRect.w = Q->tw;
				mClipRect.h = Q->th;
				mClipped = true;
				//
				mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
			}
		}
	};
};


#endif
