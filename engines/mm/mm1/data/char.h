/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MM1_DATA_CHAR_H
#define MM1_DATA_CHAR_H

#include "common/serializer.h"

namespace MM {
namespace MM1 {

#define INVENTORY_COUNT 6

enum CharacterClass {
	KNIGHT = 1, PALADIN = 2, ARCHER = 3, CLERIC = 4,
	SORCERER = 5, ROBBER = 6, NONE = 0
};

enum Race {
	HUMAN = 1, ELF = 2, DWARF = 3, GNOME = 4, HALF_ORC = 5
};

enum Alignment {
	GOOD = 1, NEUTRAL = 2, EVIL = 3
};

enum Sex {
	MALE = 1, FEMALE = 2, YES_PLEASE = 3
};

enum Condition {
	FINE = 0, BAD_CONDITION = 0x80, ERADICATED = 0xff,
	DEAD = 0x40, STONE = 0x20,
	UNCONSCIOUS = 0x40, PARALYZED = 0x20, POISONED = 0x10,
	DISEASED = 8,  SILENCED = 4, BLINDED = 2, ASLEEP = 1
};

enum Town {
	NO_TOWN = 0, SORPIGAL = 1, PORTSMITH = 2, ALGARY = 3,
	DUSK = 4, ERLIQUIN = 5
};

struct Character {
	char _name[16] = { 0 };
	Sex _sex = MALE;
	int _field11 = 0;
	Alignment _alignment = GOOD;
	Race _race = HUMAN;
	CharacterClass _class = NONE;
	uint8 _int = 0, _mgt = 0, _per = 0, _end = 0;
	uint8 _spd = 0, _acy = 0, _luc = 0;
	uint8 _level = 0;
	uint8 _age = 0;
	uint32 _exp = 0;
	uint16 _sp = 0, _spMax = 0;
	uint8 _sp1 = 0, _sp2 = 0;
	uint16 _gems = 0;
	uint16 _hp = 0, _hp2 = 0, _hpMax = 0;
	uint16 _gold = 0;
	byte _ac = 0;
	uint8 _food = 0;
	uint8 _condition = 0;
	uint8 _equipped[INVENTORY_COUNT] = { 0 };
	uint8 _backpack[INVENTORY_COUNT] = { 0 };

	// TODO: Figure out what these are
	int _v58, _v59, _v62, _v63, _v64, _v65;
	int _v66, _v67, _v6c, _v6f;

	void synchronize(Common::Serializer &s);
	void clear();
};

} // namespace MM1
} // namespace MM

#endif
