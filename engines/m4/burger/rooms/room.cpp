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

#include "m4/burger/rooms/room.h"
#include "m4/burger/vars.h"

namespace M4 {
namespace Burger {
namespace Rooms {

void Room::shutdown() {
}

void Room::parser_code() {
	warning("TODO: global_parser_code");
}

void Room::npc_say(const char *digiName, int trigger, const char *seriesName,
		int layer, bool shadow, int firstFrame, int lastFrame, int digiSlot, int digiVol) {
	term_message("npc_say: %s     npc_series: %s     npc_trigger: %d",
		digiName, seriesName, trigger);

	_G(npcTrigger) = trigger;

	if (seriesName) {
		_G(npcSpeech1) = series_play(seriesName, layer, 4, -1, 6, -1, 100, 0, 0, firstFrame, lastFrame);

		if (shadow) {
			char temp[20];
			strcpy_s(temp, 20, seriesName);
			strcat_s(temp, 20, "s");
			_G(npcSpeech2) = series_play(temp, layer + 1, 4, -1, 6, -1, 100, 0, 0, firstFrame, lastFrame);
		}
	}

	kernel_trigger_dispatch_now(gNPC_SPEECH_STARTED);
	KernelTriggerType oldMode = _G(kernel).trigger_mode;

	_G(kernel).trigger_mode = KT_DAEMON;
	digi_play(digiName, digiSlot, digiVol, gNPC_SPEECH_FINISHED);

	_G(kernel).trigger_mode = oldMode;
}

void Room::npc_say(int trigger, const char *seriesName, int layer, bool shadow,
		int firstFrame, int lastFrame, int digiSlot, int digiVol) {
	npc_say(conv_sound_to_play(), trigger, seriesName, layer, shadow,
		firstFrame, lastFrame, digiSlot, digiVol);
}

} // namespace Rooms
} // namespace Burger
} // namespace M4
