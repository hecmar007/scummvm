/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "cruise/cruise_main.h"
#include "graphics/cursorman.h"

namespace Cruise {

int16 main10;

	static const byte mouseCursorNormal[] = {
		0x00, 0x00, 0x40, 0x00, 0x60, 0x00, 0x70, 0x00,
		0x78, 0x00, 0x7C, 0x00, 0x7E, 0x00, 0x7F, 0x00,
		0x7F, 0x80, 0x7C, 0x00, 0x6C, 0x00, 0x46, 0x00,
		0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00,

		0xC0, 0x00, 0xE0, 0x00, 0xF0, 0x00, 0xF8, 0x00,
		0xFC, 0x00, 0xFE, 0x00, 0xFF, 0x00, 0xFF, 0x80,
		0xFF, 0xC0, 0xFF, 0xC0, 0xFE, 0x00, 0xFF, 0x00,
		0xCF, 0x00, 0x07, 0x80, 0x07, 0x80, 0x03, 0x80
	};

	static const byte mouseCursorDisk[] = {
		0x7F, 0xFC, 0x9F, 0x12, 0x9F, 0x12, 0x9F, 0x12,
		0x9F, 0x12, 0x9F, 0xE2, 0x80, 0x02, 0x9F, 0xF2,
		0xA0, 0x0A, 0xA0, 0x0A, 0xA0, 0x0A, 0xA0, 0x0A,
		0xA0, 0x0A, 0xA0, 0x0A, 0x7F, 0xFC, 0x00, 0x00,

		0x7F, 0xFC, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE,
		0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE,
		0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE,
		0xFF, 0xFE, 0xFF, 0xFE, 0x7F, 0xFC, 0x00, 0x00
	};

	static const byte mouseCursorCross[] = {
		0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
		0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x7C, 0x7C,
		0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
		0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,

		0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80,
		0x03, 0x80, 0x03, 0x80, 0xFF, 0xFE, 0xFE, 0xFE,
		0xFF, 0xFE, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80,
		0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00
	};

	static const byte mouseCursorNoMouse[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	static const byte mouseCursorWalk[] = {
		0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x01, 0xE0,
		0x03, 0xF0, 0x03, 0x38, 0x1B, 0xDC, 0x1B, 0xCC,
		0x03, 0xCC, 0x03, 0x80, 0x07, 0x00, 0x0E, 0xC0,
		0x1C, 0xE0, 0x18, 0x70, 0x18, 0x38, 0x18, 0x18,

		0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x03, 0xF0,
		0x07, 0xF8, 0x07, 0xFC, 0x3F, 0xFE, 0x3F, 0xFE,
		0x07, 0xFE, 0x07, 0xC0, 0x0F, 0x80, 0x1F, 0xE0,
		0x3F, 0xF0, 0x3C, 0xF8, 0x3C, 0x7C, 0x3C, 0x3C
	};

	static const byte mouseCursorExit[] = {
		0x7f, 0xf8, 0x60, 0x18, 0x60, 0x18, 0x60, 0x18,
		0x60, 0x00, 0x60, 0x08, 0x60, 0x0c, 0x60, 0xfe,
		0x60, 0xfe, 0x60, 0x0c, 0x60, 0x08, 0x60, 0x00,
		0x60, 0x18, 0x60, 0x18, 0x60, 0x18, 0x7f, 0xf8,

		0xff, 0xfc, 0xf0, 0x3c, 0xf0, 0x3c, 0xf0, 0x3c,
		0xf0, 0x00, 0xf0, 0x1c, 0xf0, 0x1e, 0xf1, 0xff,
		0xf1, 0xff, 0xf0, 0x1e, 0xf0, 0x1c, 0xf0, 0x00,
		0xf0, 0x3c, 0xf0, 0x3c, 0xf0, 0x3c, 0xff, 0xfc
	};

	static const byte mouseCursorMagnifyingGlass[] = {
		0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x02, 0x02,
		0x02, 0x02, 0x02, 0x02, 0x00, 0x22, 0x00, 0x02,
		0x07, 0x82, 0x03, 0x82, 0x07, 0x9e, 0xfe, 0x80,
		0xfc, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,

		0x00, 0x00, 0x07, 0xff, 0x07, 0xff, 0x06, 0x03,
		0x06, 0x03, 0x06, 0x03, 0x00, 0x23, 0x0f, 0xc3,
		0x0f, 0xc3, 0x07, 0xc3, 0xff, 0xdf, 0xff, 0xdf,
		0xfe, 0xc0, 0xfc, 0x00, 0xf8, 0x00, 0x00, 0x00
	};

	struct MouseCursor {
		int hotspotX;
		int hotspotY;
		const byte *bitmap;
	};

	static const MouseCursor mouseCursors[] = {
		{ 1, 1, mouseCursorNormal },
		{ 0, 0, mouseCursorDisk },
		{ 7, 7, mouseCursorCross },
		{ 0, 0, mouseCursorNoMouse },
		{ 10, 6, mouseCursorWalk },
		{ 10, 6, mouseCursorExit },
		{ 10, 6, mouseCursorMagnifyingGlass }
	};

	CursorType currentCursor = CURSOR_NOMOUSE;

	static const byte cursorPalette[] = {
		0, 0, 0, 0xff,
		0xff, 0xff, 0xff, 0xff
	};

	void changeCursor(CursorType eType) {
		assert(eType >= 0 && eType < CURSOR_MAX);
		if (currentCursor != eType) {
			byte mouseCursor[16 * 16];
			const MouseCursor *mc = &mouseCursors[eType];
			const byte *src = mc->bitmap;
			for (int i = 0; i < 32; ++i) {
				int offs = i * 8;
				for (byte mask = 0x80; mask != 0; mask >>= 1) {
					if (src[0] & mask) {
						mouseCursor[offs] = 1;
					} else if (src[32] & mask) {
						mouseCursor[offs] = 0;
					} else {
						mouseCursor[offs] = 0xFF;
					}
					++offs;
				}
				++src;
			}
			CursorMan.replaceCursor(mouseCursor, 16, 16, mc->hotspotX, mc->hotspotY);
			CursorMan.replaceCursorPalette(cursorPalette, 0, 2);
			currentCursor = eType;
		}
	}

} // End of namespace Cruise
