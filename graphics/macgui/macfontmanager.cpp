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
 */

#include "common/archive.h"
#include "common/stream.h"
#include "common/unzip.h"
#include "common/macresman.h"
#include "graphics/fonts/bdf.h"
#include "graphics/fonts/macfont.h"

#include "graphics/macgui/macfontmanager.h"

namespace Graphics {

// Source: Apple IIGS Technical Note #41, "Font Family Numbers"
// http://apple2.boldt.ca/?page=til/tn.iigs.041
static const char *const fontNames[] = {
	"Chicago",	// system font
	"Geneva",	// application font
	"New York",
	"Geneva",

	"Monaco",
	"Venice",
	"London",
	"Athens",

	"San Francisco",
	"Toronto",
	NULL,
	"Cairo",
	"Los Angeles", // 12

	"Zapf Dingbats",
	"Bookman",
	"Helvetica Narrow",
	"Palatino",
	NULL,
	"Zapf Chancery",
	NULL,

	"Times", // 20
	"Helvetica",
	"Courier",
	"Symbol",
	"Taliesin", // mobile?
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // 30
	NULL,
	NULL,
	"Avant Garde",
	"New Century Schoolbook"
};

MacFontManager::MacFontManager() {
	for (uint i = 0; i < ARRAYSIZE(fontNames); i++)
		if (fontNames[i])
			_fontNames.setVal(fontNames[i], i);

	loadFonts();
}

void MacFontManager::loadFontsBDF() {
	Common::Archive *dat;

	dat = Common::makeZipArchive("classicmacfonts.dat");

	if (!dat) {
		warning("Could not find classicmacfonts.dat. Falling back to built-in fonts");
		_builtInFonts = true;

		return;
	}

	Common::ArchiveMemberList list;
	dat->listMembers(list);

	for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
		Common::SeekableReadStream *stream = dat->createReadStreamForMember((*it)->getName());

		Graphics::BdfFont *font = Graphics::BdfFont::loadFont(*stream);

		delete stream;

		Common::String fontName;
		MacFont *macfont;

		if (font->getFamilyName() && *font->getFamilyName()) {
			fontName = Common::String::format("%s-%s-%d", font->getFamilyName(), font->getFontSlant(), font->getFontSize());

			macfont = new MacFont(_fontNames.getVal(font->getFamilyName(), kMacFontNonStandard), font->getFontSize(), parseFontSlant(font->getFontSlant()));
		} else { // Get it from the file name
			fontName = (*it)->getName();

			// Trim the .bdf extension
			for (int i = fontName.size() - 1; i >= 0; --i) {
				if (fontName[i] == '.') {
					while ((uint)i < fontName.size()) {
						fontName.deleteLastChar();
					}
					break;
				}
			}

			macfont = new MacFont(kMacFontNonStandard);
			macfont->setName(fontName);
		}

		FontMan.assignFontToName(fontName, font);
		//macfont->setFont(font);
		_fontRegistry.setVal(fontName, macfont);

		debug(2, " %s", fontName.c_str());
	}

	_builtInFonts = false;

	delete dat;
}

void MacFontManager::loadFonts() {
	Common::Archive *dat;

	dat = Common::makeZipArchive("classicmacfonts.dat");

	if (!dat) {
		warning("Could not find classicmacfonts.dat. Falling back to built-in fonts");
		_builtInFonts = true;

		return;
	}

	Common::ArchiveMemberList list;
	dat->listMembers(list);

	for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
		Common::SeekableReadStream *stream = dat->createReadStreamForMember((*it)->getName());

		Common::MacResManager *fontFile = new Common::MacResManager();

		if (!fontFile->loadFromMacBinary(*stream))
			continue;

		Common::MacResIDArray fonds = fontFile->getResIDArray(MKTAG('F','O','N','D'));
		if (fonds.size() > 0) {
			for (Common::Array<uint16>::iterator iterator = fonds.begin(); iterator != fonds.end(); ++iterator) {
				Common::SeekableReadStream *fond = fontFile->getResource(MKTAG('F', 'O', 'N', 'D'), *iterator);

				Common::String familyName = fontFile->getResName(MKTAG('F', 'O', 'N', 'D'), *iterator);

				Graphics::MacFontFamily *fontFamily = new MacFontFamily();
				fontFamily->load(*fond);

				Common::Array<Graphics::MacFontFamily::AsscEntry> *assoc = fontFamily->getAssocTable();

				for (uint i = 0; i < assoc->size(); i++) {
					debug("size: %d style: %d id: %d", (*assoc)[i]._fontSize, (*assoc)[i]._fontStyle,
											(*assoc)[i]._fontID);

					Common::SeekableReadStream *fontstream;
					MacFont *macfont;
					Graphics::MacFONTFont *font;

					fontstream = fontFile->getResource(MKTAG('N', 'F', 'N', 'T'), (*assoc)[i]._fontID);

					if (!fontstream)
						fontstream = fontFile->getResource(MKTAG('F', 'O', 'N', 'T'), (*assoc)[i]._fontID);

					if (!fontstream) {
						warning("Unknown FontId: %d", (*assoc)[i]._fontID);

						continue;
					}

					font = new Graphics::MacFONTFont;
					font->loadFont(*fontstream, fontFamily, (*assoc)[i]._fontSize, (*assoc)[i]._fontStyle);

					delete fontstream;

					Common::String fontName = Common::String::format("%s-%d-%d", familyName.c_str(), (*assoc)[i]._fontStyle, (*assoc)[i]._fontSize);

					macfont = new MacFont(_fontNames.getVal(familyName, kMacFontNonStandard), (*assoc)[i]._fontSize, (*assoc)[i]._fontStyle);

					FontMan.assignFontToName(fontName, font);
					macfont->setFont(font);
					_fontRegistry.setVal(fontName, macfont);

					debug(2, " %s", fontName.c_str());
				}

				delete fond;
			}
		}

		delete fontFile;
	}

	_builtInFonts = false;

	delete dat;
}

const Font *MacFontManager::getFont(MacFont macFont) {
	const Font *font = 0;

	if (!_builtInFonts) {
		if (macFont.getName().empty())
			macFont.setName(getFontName(macFont.getId(), macFont.getSize(), macFont.getSlant()));

		if (!_fontRegistry.contains(macFont.getName()))
			generateFontSubstitute(macFont);

		font = FontMan.getFontByName(macFont.getName());

		if (!font) {
			warning("Cannot load font '%s'", macFont.getName().c_str());

			font = FontMan.getFontByName(MacFont(kMacFontChicago, 12).getName());
		}
	}

	if (_builtInFonts || !font)
		font = FontMan.getFontByUsage(macFont.getFallback());

	return font;
}

int MacFontManager::parseFontSlant(Common::String slant) {
	slant.toUppercase();
	int slantVal = 0;

	if (slant == "I")
		slantVal |= kMacFontItalic;
	if (slant == "B")
		slantVal |= kMacFontBold;
	if (slant == "R")
		slantVal |= kMacFontRegular;

	return slantVal;
}

const char *MacFontManager::getFontName(int id, int size, int slant) {
	static char name[128];

	if (id > ARRAYSIZE(fontNames))
		return NULL;

	snprintf(name, 128, "%s-%d-%d", fontNames[id], slant, size);

	return name;
}

const char *MacFontManager::getFontName(MacFont &font) {
	return getFontName(font.getId(), font.getSize(), font.getSlant());
}

int MacFontManager::getFontIdByName(Common::String name) {
	for (int f = 0; f < ARRAYSIZE(fontNames); f++)
		if (fontNames[f] != NULL && strcmp(fontNames[f], name.c_str()) == 0)
			return f;
	return 1;
}

void MacFontManager::generateFontSubstitute(MacFont &macFont) {
	Common::String name;

	// First we try twice size
	name = getFontName(macFont.getId(), macFont.getSize() * 2, macFont.getSlant());
	if (_fontRegistry.contains(name) && !_fontRegistry[name]->isGenerated()) {
		generateFont(macFont, *_fontRegistry[name]);

		return;
	}

	// Now half size
	name = getFontName(macFont.getId(), macFont.getSize() / 2, macFont.getSlant());
	if (_fontRegistry.contains(name) && !_fontRegistry[name]->isGenerated()) {
		generateFont(macFont, *_fontRegistry[name]);

		return;
	}

	// No simple substitute was found. Looking for neighborhood fonts

	// First we gather all font sizes for this font
	Common::Array<int> sizes;
	for (Common::HashMap<Common::String, MacFont *>::iterator i = _fontRegistry.begin(); i != _fontRegistry.end(); ++i) {
		if (i->_value->getId() == macFont.getId() && i->_value->getSlant() == macFont.getSlant() && !i->_value->isGenerated())
			sizes.push_back(i->_value->getSize());
	}

	if (sizes.empty()) {
		warning("No viable substitute found for font %s", getFontName(macFont));
		return;
	}

	// Now looking next larger font, and store the largest one for next check
	int candidate = 1000;
	int maxSize = sizes[0];
	for (uint i = 0; i < sizes.size(); i++) {
		if (sizes[i] > macFont.getSize() && sizes[i] < candidate)
			candidate = sizes[i];

		if (sizes[i] > maxSize)
			maxSize = sizes[i];
	}

	if (candidate != 1000) {
		generateFont(macFont, *_fontRegistry[getFontName(macFont.getId(), candidate, macFont.getSlant())]);
		return;
	}

	// Now next smaller font, which is the biggest we have
	generateFont(macFont, *_fontRegistry[getFontName(macFont.getId(), maxSize, macFont.getSlant())]);
}

void MacFontManager::generateFont(MacFont &toFont, MacFont &fromFont) {
	debugN("Found font substitute for font '%s' ", getFontName(toFont));
	debug("as '%s'", getFontName(fromFont));

	MacFONTFont *font = Graphics::MacFONTFont::scaleFont(fromFont.getFont(), toFont.getSize());

	if (!font) {
		warning("Failed to generate font '%s'", getFontName(toFont));
	}

	toFont.setGenerated(true);
	toFont.setFont(font);

	FontMan.assignFontToName(getFontName(toFont), font);
	_fontRegistry.setVal(getFontName(toFont), new MacFont(toFont));

	debug("Generated font '%s'", getFontName(toFont));
}

} // End of namespace Graphics
