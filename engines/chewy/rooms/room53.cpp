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

#include "chewy/defines.h"
#include "chewy/events.h"
#include "chewy/global.h"
#include "chewy/ani_dat.h"
#include "chewy/room.h"
#include "chewy/rooms/room53.h"

namespace Chewy {
namespace Rooms {

static const AniBlock ABLOCK35[7] = {
	{ 2, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 7, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 8, 3, ANI_VOR, ANI_WAIT, 0 },
	{ 4, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 5, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 9, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 5, 1, ANI_VOR, ANI_WAIT, 0 },
};


void Room53::entry() {
	hide_cur();
	obj->hide_sib(SIB_VISIT_R53);
	atds->del_steuer_bit(319, ATS_AKTIV_BIT, ATS_DATEI);
	start_detail_wait(0, 1, ANI_VOR);
	det->set_static_ani(1, -1);
	_G(timer_nr)[0] = room->set_timer(1, 7);
	show_cur();
}

void Room53::man_go() {
	room->set_timer_status(1, TIMER_STOP);
	det->del_static_ani(1);
	start_detail_wait(5, 1, ANI_VOR);
	atds->set_steuer_bit(319, ATS_AKTIV_BIT, ATS_DATEI);
	if (!_G(spieler).R53Visit)
		obj->show_sib(SIB_VISIT_R53);
}

void Room53::talk_man() {
	hide_cur();
	auto_move(2, P_CHEWY);
	room->set_timer_status(1, TIMER_STOP);
	det->del_static_ani(1);
	start_detail_wait(2, 1, ANI_VOR);
	det->set_static_ani(3, -1);
	start_aad_wait(269 + (int16)_G(spieler).R53Kostuem, -1);
	det->del_static_ani(3);
	start_detail_wait(4, 1, ANI_VOR);
	man_go();
	show_cur();
}

int16 Room53::use_man() {
	int16 action_ret = false;

	if (is_cur_inventar(BESTELL_INV)) {
		action_ret = true;
		hide_cur();
		_G(spieler).R53Kostuem = true;
		del_inventar(_G(spieler).AkInvent);
		auto_move(2, P_CHEWY);
		start_aad_wait(271, -1);
		room->set_timer_status(1, TIMER_STOP);
		det->del_static_ani(1);
		start_ani_block(7, ABLOCK35);
		obj->add_inventar(JMKOST_INV, &room_blk);
		inventory_2_cur(JMKOST_INV);
		atds->set_steuer_bit(319, ATS_AKTIV_BIT, ATS_DATEI);
		show_cur();
	}

	return action_ret;
}

} // namespace Rooms
} // namespace Chewy
