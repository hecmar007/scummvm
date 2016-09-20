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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "gui/debugger.h"

#include "chewy/chewy.h"
#include "chewy/console.h"
#include "chewy/graphics.h"
#include "chewy/resource.h"
#include "chewy/sound.h"

namespace Chewy {

Console::Console(ChewyEngine *vm) : GUI::Debugger(), _vm(vm) {
	registerCmd("dump",			WRAP_METHOD(Console, Cmd_Dump));
	registerCmd("dump_bg",		WRAP_METHOD(Console, Cmd_DumpBg));
	registerCmd("draw",			WRAP_METHOD(Console, Cmd_Draw));
	registerCmd("play_sound",	WRAP_METHOD(Console, Cmd_PlaySound));
	registerCmd("play_speech",	WRAP_METHOD(Console, Cmd_PlaySpeech));
	registerCmd("play_music",	WRAP_METHOD(Console, Cmd_PlayMusic));
	registerCmd("text",			WRAP_METHOD(Console, Cmd_Text));
}

Console::~Console() {
}

bool Console::Cmd_Dump(int argc, const char **argv) {
	if (argc < 4) {
		debugPrintf("Usage: dump <file> <resource number> <dump file name>\n");
		return true;
	}

	Common::String filename = argv[1];
	int resNum = atoi(argv[2]);
	Common::String dumpFilename = argv[3];

	Resource *res = new Resource(filename);
	Chunk *chunk = res->getChunk(resNum);
	byte *data = res->getChunkData(resNum);
	uint32 size = chunk->size;

	Common::DumpFile outFile;
	outFile.open(dumpFilename);
	outFile.write(data, size);
	outFile.flush();
	outFile.close();

	delete[] data;
	delete res;

	return true;
}

bool Console::Cmd_DumpBg(int argc, const char **argv) {
	if (argc < 4) {
		debugPrintf("Usage: dump_bg <file> <resource number> <dump file name>\n");
		return true;
	}

	Common::String filename = argv[1];
	int resNum = atoi(argv[2]);
	Common::String dumpFilename = argv[3];

	BackgroundResource *res = new BackgroundResource(filename);
	TBFChunk *image = res->getImage(resNum);

	Common::DumpFile outFile;
	outFile.open(dumpFilename);
	outFile.write(image->data, image->size);
	outFile.flush();
	outFile.close();

	delete[] image->data;
	delete image;
	delete res;

	return true;
}


bool Console::Cmd_Draw(int argc, const char **argv) {
	if (argc < 3) {
		debugPrintf("Usage: draw <file> <resource number>\n");
		return true;
	}

	Common::String filename = argv[1];
	int resNum = atoi(argv[2]);
	
	Graphics *g = new Graphics();
	g->drawImage(filename, resNum);
	delete g;

	return false;
}

bool Console::Cmd_PlaySound(int argc, const char **argv) {
	if (argc < 2) {
		debugPrintf("Usage: play_sound <number>\n");
		return true;
	}

	int resNum = atoi(argv[1]);
	_vm->_sound->playSound(resNum);

	return true;
}

bool Console::Cmd_PlaySpeech(int argc, const char **argv) {
	if (argc < 2) {
		debugPrintf("Usage: play_speech <number>\n");
		return true;
	}

	int resNum = atoi(argv[1]);
	_vm->_sound->playSpeech(resNum);

	return true;
}

bool Console::Cmd_PlayMusic(int argc, const char **argv) {
	if (argc < 2) {
		debugPrintf("Usage: play_music <number>\n");
		return true;
	}

	int resNum = atoi(argv[1]);
	_vm->_sound->playMusic(resNum);

	return true;
}

bool Console::Cmd_Text(int argc, const char **argv) {
	if (argc < 2) {
		debugPrintf("Usage: <file> <text number>\n");
		return true;
	}

	Common::String filename = argv[1];
	int resNum = atoi(argv[2]);

	TextResource *res = new TextResource(filename);
	Common::String str = res->getText(resNum);
	this->debugPrintf("Text: %s\n", str.c_str());
	delete res;

	return true;
}

} // End of namespace Chewy
