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

#include "twine/script/script_life.h"
#include "twine/twine.h"
#include "twine/scene/scene.h"

namespace TwinE {

ScriptLife::ScriptLife(TwinEEngine *engine, const ScriptLifeFunction *functionMap, size_t entries) : _engine(engine), _functionMap(functionMap), _functionMapSize(entries) {
}

void ScriptLife::doLife(int32 actorIdx) {
	ActorStruct *actor = _engine->_scene->getActor(actorIdx);
	int32 end = -2;

	LifeScriptContext ctx(actorIdx, actor);
	debugC(3, kDebugLevels::kDebugScripts, "LIFE::BEGIN(%i)", actorIdx);
	do {
		const byte scriptOpcode = ctx.stream.readByte();
		if (scriptOpcode < _functionMapSize) {
			debugC(3, kDebugLevels::kDebugScripts, "LIFE::EXEC(%s, %i)", _functionMap[scriptOpcode].name, actorIdx);
			end = _functionMap[scriptOpcode].function(_engine, ctx);
		} else {
			error("Actor %d with wrong offset/opcode - Offset: %d/%d (opcode: %i)", actorIdx, (int)ctx.stream.pos() - 1, (int)ctx.stream.size(), scriptOpcode);
		}

		if (end < 0) {
			warning("Actor %d Life script [%s] not implemented", actorIdx, _functionMap[scriptOpcode].name);
		} else if (end == 1) {
			debugC(3, kDebugLevels::kDebugScripts, "LIFE::BREAK(%i)", actorIdx);
		}
		ctx.updateOpcodePos();
	} while (end != 1);
	debugC(3, kDebugLevels::kDebugScripts, "LIFE::END(%i)", actorIdx);
}

} // namespace TwinE
