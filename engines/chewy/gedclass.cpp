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

#include "common/file.h"
#include "chewy/chewy.h"
#include "chewy/gedclass.h"
#include "chewy/fehler.h"
#include "chewy/ngshext.h"

namespace Chewy {

void gedclass::load_ged_pool(const char *fname, GedChunkHeader *Gh, int16 ch_nr, byte *speicher) {
	Common::File f;
	if (f.open(fname)) {
		load_ged_pool(&f, Gh, ch_nr, speicher);
	} else {
		modul = 3;
		fcode = 0;
		err->set_user_msg("GED POOL");
	}
}

void gedclass::load_ged_pool(Common::SeekableReadStream *stream, GedChunkHeader *Gh, int16 ch_nr, byte *speicher) {
	if (stream) {
		stream->seek(0, SEEK_SET);
		if (_gedPoolHeader.load(stream)) {
			load_ged_chunk(Gh, stream, ch_nr, speicher);
		}
	} else {
		modul = 3;
		fcode = 0;
		err->set_user_msg("GED POOL");
	}
}

void gedclass::load_ged_chunk(GedChunkHeader *Gh, Common::SeekableReadStream *stream, int16 nr, byte *speicher) {
	if (stream) {
		// Scan for the correct index entry
		int i = 0;
		do {
			if (!Gh->load(stream)) {
				modul = 3;
				fcode = 1;
			} else if (i != nr) {
				// Skip over the entry's data
				stream->seek(Gh->Len, SEEK_CUR);
			}
		} while (!modul && ++i <= nr);

		if (!modul) {
			if (stream->read(speicher, Gh->Len) != Gh->Len) {
				modul = 3;
				fcode = 1;
			}
		}
	} else {
		modul = 3;
		fcode = 0;
		err->set_user_msg("GED FILE");
	}
}

int16 gedclass::ged_idx(int16 x, int16 y, int16 x_anz, byte *speicher) {
	int16 result = 0;
	if (_gedUserFunc)
		result = _gedUserFunc(speicher[((x / 8) * x_anz) + (y / 8)]);

	return result;
}

int16 gedclass::ged_idx(int16 g_idx, int16 x_anz, byte *speicher) {
	int16 result = 0;
	if (_gedUserFunc)
		result = _gedUserFunc(speicher[g_idx]);

	return result;
}

} // namespace Chewy
