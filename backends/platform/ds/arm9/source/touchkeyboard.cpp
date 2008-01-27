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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include <nds.h>
#include "touchkeyboard.h"
#include "keyboard_raw.h"
#include "keyboard_pal_raw.h"
#include "8x8font_tga_raw.h"
#include "dsmain.h"
#include "osystem_ds.h"

namespace DS {

struct key_data {
	char keyNum;
	signed char x, y;
	int character;
	bool pressed;
};

#define DS_NUM_KEYS 72
#define DS_SHIFT 2
#define DS_BACKSPACE 8
#define DS_RETURN 13
#define DS_CAPSLOCK 1


key_data keys[DS_NUM_KEYS] = {
	// Key number		x		y		character

	// Numbers
	{28,				3,		0,		'1'},
	{29,				5,		0,		'2'},
	{30,				7,		0,		'3'},
	{31,				9,		0,		'4'},
	{32,				11,		0,		'5'},
	{33,				13,		0,		'6'},
	{34,				15,		0,		'7'},
	{35,				17,		0,		'8'},
	{36,				19,		0,		'9'},
	{27,				21,		0,		'0'},
	{45,				23,		0,		Common::KEYCODE_MINUS},
	{50,				25,		0,		Common::KEYCODE_EQUALS},
	{52,				27,		0,		Common::KEYCODE_BACKSPACE},

	// Top row
	{'Q'-'A' + 1,		4,		2,		'Q'},
	{'W'-'A' + 1,		6,		2,		'W'},
	{'E'-'A' + 1,		8,		2,		'E'},
	{'R'-'A' + 1,		10,		2,		'R'},
	{'T'-'A' + 1,		12,		2,		'T'},
	{'Y'-'A' + 1,		14,		2,		'Y'},
	{'U'-'A' + 1,		16,		2,		'U'},
	{'I'-'A' + 1,		18,		2,		'I'},
	{'O'-'A' + 1,		20,		2,		'O'},
	{'P'-'A' + 1,		22,		2,		'P'},
	{43,				24,		2,		Common::KEYCODE_LEFTBRACKET},
	{44,				26,		2,		Common::KEYCODE_RIGHTBRACKET},

	// Middle row
	{55,				3,		4,		DS_CAPSLOCK},
	{'A'-'A' + 1,		5,		4,		'A'},
	{'S'-'A' + 1,		7,		4,		'S'},
	{'D'-'A' + 1,		9,		4,		'D'},
	{'F'-'A' + 1,		11,		4,		'F'},
	{'G'-'A' + 1,		13,		4,		'G'},
	{'H'-'A' + 1,		15,		4,		'H'},
	{'J'-'A' + 1,		17,		4,		'J'},
	{'K'-'A' + 1,		19,		4,		'K'},
	{'L'-'A' + 1,		21,		4,		'L'},
	{42,				23,		4,		Common::KEYCODE_SEMICOLON},
	{41,				25,		4,		Common::KEYCODE_QUOTE},
	{46,				27,		4,		Common::KEYCODE_RETURN},

	// Bottom row
	{51,				4,		6,		DS_SHIFT},
	{'Z'-'A' + 1,		6,		6,		'Z'},
	{'X'-'A' + 1,		8,		6,		'X'},
	{'C'-'A' + 1,		10,		6,		'C'},
	{'V'-'A' + 1,		12,		6,		'V'},
	{'B'-'A' + 1,		14,		6,		'B'},
	{'N'-'A' + 1,		16,		6,		'N'},
	{'M'-'A' + 1,		18,		6,		'M'},
	{38,				20,		6,		Common::KEYCODE_COMMA},
	{39,				22,		6,		Common::KEYCODE_PERIOD},
	{40,				24,		6,		Common::KEYCODE_SLASH},

	// Space bar
	{47,				9,		8,		Common::KEYCODE_SPACE},
	{48,				11,		8,		Common::KEYCODE_SPACE},
	{48,				13,		8,		Common::KEYCODE_SPACE},
	{48,				15,		8,		Common::KEYCODE_SPACE},
	{48,				17,		8,		Common::KEYCODE_SPACE},
	{49,				19,		8,		Common::KEYCODE_SPACE},

	// Cursor arrows
	{52,				27,		8,		Common::KEYCODE_LEFT},
	{54,				29,		8,		Common::KEYCODE_DOWN},
	{53,				31,		8,		Common::KEYCODE_RIGHT},
	{51,				29,		6,		Common::KEYCODE_UP},

	// Close button
	{56,				30,		0,		Common::KEYCODE_INVALID},

	// Function keys (needed for AGI)
	{57,				4,		-2,		Common::KEYCODE_F1},
	{58,				6,		-2,		Common::KEYCODE_F2},
	{59,				8,		-2,		Common::KEYCODE_F3},
	{60,				10,		-2,		Common::KEYCODE_F4},
	{61,				14,		-2,		Common::KEYCODE_F5},
	{62,				16,		-2,		Common::KEYCODE_F6},
	{63,				18,		-2,		Common::KEYCODE_F7},
	{64,				20,		-2,		Common::KEYCODE_F8},
	{65,				24,		-2,		Common::KEYCODE_F9},
	{66,				26,		-2,		Common::KEYCODE_F10},
	{67,				28,		-2,		Common::KEYCODE_F11},
	{68,				30,		-2,		Common::KEYCODE_F12},

};

int keyboardX;
int keyboardY;

int mapBase;
int tileBase;

u16* baseAddress;

bool shiftState;
bool capsLockState;

bool closed;

char autoCompleteWord[NUM_WORDS][32];
int autoCompleteCount;

char autoCompleteBuffer[128];

int selectedCompletion = -1;
int charactersEntered = 0;


void restoreVRAM(int tileBase, int mapBase, u16* saveSpace) {
/*	for (int r = 0; r < 32 * 32; r++) {
		((u16 *) SCREEN_BASE_BLOCK_SUB(mapBase))[r] = *saveSpace++;
	}

	for (int r = 0; r < 4096; r++) {
		((u16 *) CHAR_BASE_BLOCK_SUB(tileBase))[r]	= *saveSpace++;
	}*/
}

void drawKeyboard(int tileBase, int mapBase, u16* saveSpace) {
	int keyboardDataSize = 4736 * 2;

	for (int r = 0; r < 32 * 32; r++) {
//		*saveSpace++ = ((u16 *) SCREEN_BASE_BLOCK_SUB(mapBase))[r];
		((u16 *) SCREEN_BASE_BLOCK_SUB(mapBase))[r] = 0;
	}

	for (int r = 0; r < KEYBOARD_DATA_SIZE / 2; r++) {
//		*saveSpace++ = ((u16 *) CHAR_BASE_BLOCK_SUB(tileBase))[r];
		((u16 *) CHAR_BASE_BLOCK_SUB(tileBase))[r] = ((u16 *) (keyboard_raw))[r];
	}

	for (int r = 0; r < 16; r++) {
		BG_PALETTE_SUB[r] = ((u16 *) (keyboard_pal_raw))[r];
	}

	// this is the font
	for (int tile = 0; tile < 94; tile++) {

		u16* tileAddr = (u16 *) (CHAR_BASE_BLOCK_SUB(tileBase) + ((KEYBOARD_DATA_SIZE) + (tile * 32)));
		u8* src = ((u8 *) (_8x8font_tga_raw)) + 18 + tile * 8;

		for (int y = 0 ; y < 8; y++) {
			for (int x = 0; x < 2; x++) {
				 *(tileAddr + (y * 2) + x) =(*(src + (y * 752) + (x * 4) + 0) & 0x0F)
									 	 | ((*(src + (y * 752) + (x * 4) + 1) & 0x0F) << 4)
										 | ((*(src + (y * 752) + (x * 4) + 2) & 0x0F) << 8)
										 | ((*(src + (y * 752) + (x * 4) + 3) & 0x0F) << 12);

			}
		}
	}




	for (int r = 0; r < 16; r++) {
		int col = ((u16 *) (keyboard_pal_raw))[r];

		int red = col & 0x001F;
		int green = (col & 0x03E0) >> 5;
		int blue = (col & 0x7C00) >> 10;

		red = (red * 8) / 16;
		green = (green * 24) / 16;
		blue = (blue * 8) / 16;

		if (green > 31) green = 31;

		BG_PALETTE_SUB[16 + r] = red | (green << 5) | (blue << 10);
	}

	keyboardX = -2;
	keyboardY = 2;

	DS::mapBase = mapBase;
	DS::tileBase = tileBase;

	shiftState = false;
	capsLockState = false;

	int x = keyboardX;
	int y = keyboardY;

	u16* base = ((u16 *) SCREEN_BASE_BLOCK_SUB(mapBase));
	baseAddress = base;

	for (int r = 0; r < DS_NUM_KEYS; r++) {
		base[(y + keys[r].y) * 32 + x + keys[r].x] = 10 + keys[r].keyNum * 2;
		base[(y + keys[r].y) * 32 + x + keys[r].x + 1] = 10 + keys[r].keyNum * 2 + 1;

		base[(y + keys[r].y + 1) * 32 + x + keys[r].x] = 10 + 148 + keys[r].keyNum * 2;
		base[(y + keys[r].y + 1) * 32 + x + keys[r].x + 1] = 10 + 148 + keys[r].keyNum * 2 + 1;

		keys[r].pressed = false;
	}

	closed = false;
	clearAutoComplete();
}

void drawAutoComplete() {

	for (int y = 12; y < 24; y++) {
		for (int x = 0; x < 32; x++) {
			baseAddress[y * 32 + x] = 0;
		}
	}


	for (int r = 0; r < autoCompleteCount; r++) {
		int y = 12 + (r % 6) * 2;
		int x = 0 + ((r / 6) * 16);

		for (int p = 0; p < strlen(autoCompleteWord[r]); p++) {
			char c = autoCompleteWord[r][p];

			int tile = c - 33 + (KEYBOARD_DATA_SIZE / 32);

			if (selectedCompletion == r) {
				tile |= 0x1000;
			}

			baseAddress[y * 32 + x + p] = tile;


		}
	}
}

bool getKeyboardClosed() {
	return closed;
}

void setKeyHighlight(int key, bool highlight) {
	u16* base = ((u16 *) SCREEN_BASE_BLOCK_SUB(DS::mapBase));

	if (highlight) {
		base[(keyboardY + keys[key].y) * 32 + keyboardX + keys[key].x] |= 0x1000;
		base[(keyboardY + keys[key].y) * 32 + keyboardX + keys[key].x + 1] |= 0x1000;
		base[(keyboardY + keys[key].y + 1) * 32 + keyboardX + keys[key].x] |= 0x1000;
		base[(keyboardY + keys[key].y + 1) * 32 + keyboardX + keys[key].x + 1] |= 0x1000;
	} else {
		base[(keyboardY + keys[key].y) * 32 + keyboardX + keys[key].x] &= ~0x1000;
		base[(keyboardY + keys[key].y) * 32 + keyboardX + keys[key].x + 1] &= ~0x1000;
		base[(keyboardY + keys[key].y + 1) * 32 + keyboardX + keys[key].x] &= ~0x1000;
		base[(keyboardY + keys[key].y + 1) * 32 + keyboardX + keys[key].x + 1] &= ~0x1000;
	}
}

void addAutoComplete(char* word) {
	if (autoCompleteCount == NUM_WORDS) return;
	strcpy(&autoCompleteWord[autoCompleteCount++][0], word);
	drawAutoComplete();
}

void setCharactersEntered(int count) {
	charactersEntered = count;
}

void clearAutoComplete() {
	autoCompleteCount = 0;
	selectedCompletion = -1;
	drawAutoComplete();
}

void typeCompletion(int current) {
	Common::Event event;
   	OSystem_DS* system = OSystem_DS::instance();

	strcat(autoCompleteBuffer, &autoCompleteWord[current][charactersEntered]);
	strcat(autoCompleteBuffer, " ");

/*	consolePrintf("Typing word: %s\n", autoCompleteWord[current]);

	for (int r = charactersEntered; r < strlen(autoCompleteWord[current]); r++) {
		event.kbd.keycode = autoCompleteWord[current][r];
		event.kbd.ascii = autoCompleteWord[current][r];
		event.type = Common::EVENT_KEYDOWN;
		event.kbd.flags = 0;
		system->addEvent(event);

		event.type = Common::EVENT_KEYUP;
		system->addEvent(event);
	}

	event.kbd.keycode = ' ';
	event.kbd.ascii = ' ';

	event.type = Common::EVENT_KEYDOWN;
	system->addEvent(event);

	event.type = Common::EVENT_KEYUP;
	system->addEvent(event);*/
}

void updateTypeEvents()
{
	if (autoCompleteBuffer[0] != '\0')
	{
		Common::Event event;
   		OSystem_DS* system = OSystem_DS::instance();

		event.kbd.keycode = (Common::KeyCode) autoCompleteBuffer[0];
		event.kbd.ascii = autoCompleteBuffer[0];
		event.type = Common::EVENT_KEYDOWN;
		event.kbd.flags = 0;
		system->addEvent(event);

		event.type = Common::EVENT_KEYUP;
		system->addEvent(event);

		for (int r = 0; r < strlen(autoCompleteBuffer); r++)
		{
			autoCompleteBuffer[r] = autoCompleteBuffer[r + 1];
		}
	}
}

void createKeyEvent(int keyNum, Common::Event& event)
{
	event.kbd.flags = 0;

	if ((keys[keyNum].character >= '0') && (keys[keyNum].character <= '9')) {

		if (!DS::shiftState) {
			event.kbd.ascii = keys[keyNum].character;
			event.kbd.keycode = (Common::KeyCode) keys[keyNum].character; //Common::KEYCODE_INVALID;
		} else {
			event.kbd.keycode = (Common::KeyCode) (Common::KEYCODE_F1 - (keys[keyNum].character - '1'));
			event.kbd.ascii = 0;
		}

	} else if ((keys[keyNum].character >= 'A') && (keys[keyNum].character <= 'Z')) {

		if ((!DS::shiftState) && (!DS::capsLockState)) {
			event.kbd.ascii = keys[keyNum].character + 32; // Make key lowercase.
		} else {
			event.kbd.ascii = keys[keyNum].character;
		}

		event.kbd.keycode = (Common::KeyCode) event.kbd.ascii;
	} else {
		event.kbd.ascii = keys[keyNum].character;
		event.kbd.keycode = (Common::KeyCode) keys[keyNum].character;
	}
}

void addKeyboardEvents() {
	updateTypeEvents();

	if (DS::getPenDown()) {
		int x = IPC->touchXpx;
		int y = IPC->touchYpx;

		int tx = (x >> 3);
		int ty = (y >> 3);

		if (ty >= 12) {
			int current = -1;

			if (tx < 12) {
				current = (ty - 12) / 2;
			} else {
				current = 6 + (ty - 12) / 2;
			}

			if (selectedCompletion == current) {
				typeCompletion(current);
			} else {
				selectedCompletion = current;
			}

			drawAutoComplete();
		}

		tx -= keyboardX;
		ty -= keyboardY;

//		consolePrintf("x=%d y=%d\n", tx, ty);

		for (int r = 0; r < DS_NUM_KEYS; r++) {
			if (( (tx >= keys[r].x) && (tx <= keys[r].x + 1)) &&
				   (ty >= keys[r].y) && (ty <= keys[r].y + 1)) {
			   	OSystem_DS* system = OSystem_DS::instance();
				Common::Event event;

//				consolePrintf("Key: %d\n", r);
				if ((keys[r].character == Common::KEYCODE_INVALID)) {
					// Close button
					DS::closed = true;
				} else {
					createKeyEvent(r, event);
				}

				//event.kbd.keycode = keys[r].character;
				//event.kbd.ascii = keys[r].character;
				event.type = Common::EVENT_KEYDOWN;
				system->addEvent(event);

//				event.type = Common::EVENT_KEYUP;
//				system->addEvent(event);

				switch (keys[r].character) {
					case DS_SHIFT: {
						DS::shiftState = !DS::shiftState;
						DS::setKeyHighlight(r, DS::shiftState);
						break;
					}

					case DS_CAPSLOCK: {
						DS::capsLockState = !DS::capsLockState;
						DS::setKeyHighlight(r, DS::capsLockState);
						break;
					}

					default: {
						DS::setKeyHighlight(r, true);
						keys[r].pressed = true;

						if (DS::shiftState) {
							DS::shiftState = false;
							for (int t = 0; t < DS_NUM_KEYS; t++) {
								if (keys[t].character == DS_SHIFT) {
									DS::setKeyHighlight(t, false);
								}
							}
						}
						break;
					}
				}

			}
		}
	}

	if (DS::getPenReleased()) {

		for (int r = 0; r < DS_NUM_KEYS; r++) {
			if (keys[r].pressed) {
				DS::setKeyHighlight(r, false);

			   	OSystem_DS* system = OSystem_DS::instance();

				Common::Event event;
				createKeyEvent(r, event);
				event.type = Common::EVENT_KEYUP;
				system->addEvent(event);

				keys[r].pressed = false;
			}
		}
	}
}

}

