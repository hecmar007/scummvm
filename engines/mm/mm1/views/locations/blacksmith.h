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

#ifndef MM1_VIEWS_LOCATIONS_BLACKSMITH_H
#define MM1_VIEWS_LOCATIONS_BLACKSMITH_H

#include "mm/mm1/views/locations/location.h"
#include "mm/mm1/views/locations/blacksmith_buy_weapons.h"
#include "mm/mm1/views/locations/blacksmith_buy_armor.h"
#include "mm/mm1/views/locations/blacksmith_buy_misc.h"
#include "mm/mm1/views/locations/blacksmith_sell_item.h"

namespace MM {
namespace MM1 {
namespace Views {
namespace Locations {

class Blacksmith : public Location {
private:
	BlacksmithBuyWeapons _buyWeapons;
	BlacksmithBuyArmor _buyArmor;
	BlacksmithBuyMisc _buyMisc;
	BlacksmithSellItem _sellItem;
private:
	/**
	 * Buy weapons
	 */
	void buyWeapons();

	/**
	 * Buy armor
	 */
	void buyArmor();

	/**
	 * Buy misc items
	 */
	void buyMisc();

	/**
	 * Sell an item
	 */
	void sellItem();

public:
	Blacksmith();
	virtual ~Blacksmith() {}

	bool msgFocus(const FocusMessage &msg) override;
	bool msgKeypress(const KeypressMessage &msg) override;
	void draw() override;
};

} // namespace Locations
} // namespace Views
} // namespace MM1
} // namespace MM

#endif
