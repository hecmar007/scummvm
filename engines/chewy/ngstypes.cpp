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

#include "chewy/ngstypes.h"

namespace Chewy {

bool pcx_header::load(Common::SeekableReadStream *src) {
	id = src->readByte();
	version = src->readByte();
	komp = src->readByte();
	bpp = src->readByte();
	xmin = src->readSint16LE();
	ymin = src->readSint16LE();
	xmax = src->readSint16LE();
	ymax = src->readSint16LE();
	hodpi = src->readSint16LE();
	verdpi = src->readSint16LE();
	src->read(lcmap, 16 * 3);
	reserviert = src->readByte();
	planes = src->readByte();
	bpz = src->readSint16LE();
	palinfo = src->readSint16LE();
	screenx = src->readSint16LE();
	screeny = src->readSint16LE();
	src->read(dummy, 54);

	return true;
}

bool tbf_dateiheader::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	mode = src->readSint16LE();
	komp = src->readSint16LE();
	entpsize = src->readUint32LE();
	width = src->readUint16LE();
	height = src->readUint16LE();
	src->read(palette, 768);

	return true;
}

bool taf_dateiheader::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	mode = src->readSint16LE();
	count = src->readSint16LE();
	allsize = src->readUint32LE();
	src->read(palette, 768);
	next = src->readUint32LE();
	korrekt = src->readSint16LE();

	return true;
}

bool taf_imageheader::load(Common::SeekableReadStream *src) {
	komp = src->readSint16LE();
	width = src->readUint16LE();
	height = src->readUint16LE();
	next = src->readUint32LE();
	image = src->readUint32LE();

	return true;
}

bool NewPhead::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	type = src->readUint16LE();
	PoolAnz = src->readUint16LE();

	return true;
}

bool tff_header::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	size = src->readUint32LE();
	count = src->readSint16LE();
	first = src->readSint16LE();
	last = src->readSint16LE();
	width = src->readSint16LE();
	height = src->readSint16LE();

	return true;
}

bool knopf::load(Common::SeekableReadStream *src) {
	typ = src->readSint16LE();
	enable = src->readSint16LE();
	x1 = src->readSint16LE();
	y1 = src->readSint16LE();
	x2 = src->readSint16LE();
	y2 = src->readSint16LE();
	spritenr1 = src->readSint16LE();
	spritenr2 = src->readSint16LE();
	src->skip(4);
	storlen = src->readSint16LE();
	viewspr3 = src->readSint16LE();
	textptr = src->readSint16LE();

	return true;
}

bool menue::load(Common::SeekableReadStream *src) {
	nr = src->readSint16LE();
	disp = src->readSint16LE();
	typ = src->readSint16LE();
	x = src->readSint16LE();
	y = src->readSint16LE();
	width = src->readSint16LE();
	height = src->readSint16LE();
	anzknoepfe = src->readSint16LE();
	src->skip(4 * MAXKNOPF);
	spritenr = src->readSint16LE();
	src->readUint32LE();
	src->readUint32LE();

	return true;
}

bool dialogue::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	anzmenue = src->readSint16LE();
	src->skip(4 * MAXMENUE);
	src->read(menuetaf, D_GR);
	src->read(knopftaf, D_GR);

	return true;
}

bool dialogue::save(Common::WriteStream *dest) {
	dest->write(id, 4);
	dest->writeSint16LE(anzmenue);
	for (int i = 0; i < MAXMENUE; ++i)
		dest->writeUint32LE(0);
	dest->write(menuetaf, D_GR);
	dest->write(knopftaf, D_GR);

	return true;
}

bool sbi_inst::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	src->read(name, 32);
	modmulti = src->readByte();
	carrmulti = src->readByte();
	modamp = src->readByte();
	carramp = src->readByte();
	modad = src->readByte();
	carrad = src->readByte();
	modsr = src->readByte();
	carrsr = src->readByte();
	modw = src->readByte();
	carrw = src->readByte();
	rv = src->readByte();
	src->read(frei, 5);

	return true;
}

bool voc_header::load(Common::SeekableReadStream *src) {
	src->read(id, 0x14);
	offset = src->readUint16LE();
	ver_low = src->readByte();
	ver_high = src->readByte();
	id_code = src->readUint16LE();

	return true;
}

bool mod_inst::load(Common::SeekableReadStream *src) {
	src->read(name, 22);
	laenge = src->readUint16LE();
	finetune = src->readSByte();
	insvol = src->readSByte();
	repstart = src->readSint16LE();
	replen = src->readSint16LE();

	return true;
}

bool mod_header::load(Common::SeekableReadStream *src) {
	src->read(name, 20);
	for (int i = 0; i < 31; ++i) {
		if (!instrument[i].load(src))
			return false;
	}

	pattern_anz = src->readSByte();
	dummy = src->readSByte();
	src->read(sequenz, 128);
	src->read(id, 4);

	return true;
}

bool mod15_header::load(Common::SeekableReadStream *src) {
	src->read(name, 20);
	for (int i = 0; i < 15; ++i)
		instrument[i].load(src);
	pattern_anz = src->readSByte();
	dummy = src->readSByte();
	src->read(sequenz, 128);
	src->read(id, 4);

	return true;
}

bool tmf_inst::load(Common::SeekableReadStream *src) {
	finetune = src->readByte();
	insvol = src->readByte();
	repstart = src->readUint32LE();
	replen = src->readUint32LE();
	laenge = src->readUint32LE();

	return true;
}

bool tmf_header::load(Common::SeekableReadStream *src) {
	src->read(id, 4);
	for (int i = 0; i < 31; ++i)
		instrument[i].load(src);

	lied_len = src->readByte();
	pattern_anz = src->readByte();
	src->read(sequenz, 128);
	src->skip(4 * 31);

	return true;
}

bool GedPoolHeader::load(Common::SeekableReadStream *src) {
	src->read(Id, 4);
	Anz = src->readUint16LE();

	return true;
}

bool GedChunkHeader::load(Common::SeekableReadStream *src) {
	Len = src->readUint32LE();
	X = src->readSint16LE();
	Y = src->readSint16LE();
	Ebenen = src->readSint16LE();

	return true;
}

bool ChunkHead::load(Common::SeekableReadStream *src) {
	size = src->readUint32LE();
	type = src->readUint16LE();

	return true;
}

} // namespace Chewy
