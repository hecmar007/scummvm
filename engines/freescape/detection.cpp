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

#include "base/plugins.h"
#include "engines/advancedDetector.h"
#include "common/translation.h"

#include "freescape/freescape.h"

#define GAMEOPTION_PRERECORDED_SOUNDS   GUIO_GAMEOPTIONS1

namespace Freescape {

static const PlainGameDescriptor freescapeGames[] = {
	{"3dkit", "3D Kit Game"},
	{"driller", "Driller"},
	{"spacestationoblivion", "Space Station Oblivion"},
	{"darkside", "Dark Side"},
	{"totaleclipse", "Total Eclipse"},
	{"castlemaster", "Castle Master"},
	{0, 0}};

static const ADGameDescription gameDescriptions[] = {
	// Original Freescape games
	{"driller",
	 "Driller",
	 {
		{"DRILLER.EXE", 0, "cafc0ea0d3424640a7723af87f8bfc0b", 17427},
		{"DRILLC.EXE", 0, "908dd1f8732ebcbaece7d8f0cffd8830", 43864},
		{"DRILLT.EXE", 0, "afce0e5e0ad8c508e0c31c3e0b18b9a5", 51096},
		{"DRILLE.EXE", 0, "eb7e9e0acb72e30cf6e9ed20a6480e7a", 51944},
		{"DRILLH.EXE", 0, "033d2d45390886d0bff78cf53e83b6ed", 47496},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO3(GUIO_NOMIDI, GUIO_RENDEREGA, GUIO_RENDERCGA)},
	{"driller",
	 "Retail",
	 {
		{"driller", 0, "13dab2e10d8e8b9a364c94a660e0d42a", 282384},
		{"title.seq", 0, "4dd1b3b45110b24e8240a6132241c973", 185296},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformAmiga,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"driller",
	 "Kixx",
	 {
		{"driller", 0, "db1afe151d999f369ae9153d8eeaf254", 175236},
		{"soundfx", 0, "cd91061a1330aef8fcd6b7dc6fa35cf9", 78680},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformAmiga,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"driller",
	 "Rolling Demo",
	 {
		{"driller", 0, "f0d0e9447830e329e110e384371955fd", 162880},
		{"data", 0, "0b056286d2d91f302499c97aca235462", 24220},
		{"demo.cmd", 0, "7b90427c5c3c4bbb42d14076af994d50", 4096},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformAmiga,
	 ADGF_NO_FLAGS | ADGF_DEMO,
	 GUIO1(GUIO_NOMIDI)},
	{"driller",
	 "Rolling Demo",
	 {
		{"x.prg", 0, "cf96e25a11bee1b57258c2fc0b315699", 157143},
		{"data", 0, "0b056286d2d91f302499c97aca235462", 24220},
		{"demo.cmd", 0, "7b90427c5c3c4bbb42d14076af994d50", 4096},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformAtariST,
	 ADGF_NO_FLAGS | ADGF_DEMO,
	 GUIO1(GUIO_NOMIDI)},
	{"darkside",
	 "Dark Side",
	 {
		{"DARKSIDE.EXE", 0, "c6c0d0186ec45e6cecd72bf5550c7f98", 1600},
		{"DSIDEC.EXE", 0, "31e6c169d9270b6de8c1c2e746ac238e", 49504},
		{"DSIDEH.EXE", 0, "5e18e0746647bd04f43b9db24b6a036d", 53232},
		{"DSIDEE.EXE", 0, "524281f7d2dc49e0a41fcb1d38ee2559", 56800},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO3(GUIO_NOMIDI, GUIO_RENDEREGA, GUIO_RENDERCGA)},
	{"totaleclipse",
	 "Total Eclipse",
	 {
		{"TOTAL.EXE", 0, "959703c1cd37b0d9744c492240a8178b", 13327},
		{"TOTEH.EXE", 0, "c68d59874ab2a93cc9cc1b1d3aed8f17", 60628},
		{"TOTEC.EXE", 0, "6c058c48255945a12479c8420321db75", 56900},
		{"TOTET.EXE", 0, "2bc2b0892ca91a77c58e9bedabf45afe", 63732},
		{"TOTEE.EXE", 0, "2ba865d2bdcda0c934baec7b31fb4ab2", 64196},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO3(GUIO_NOMIDI, GUIO_RENDEREGA, GUIO_RENDERCGA)},
	{"spacestationoblivion",
	 "Space Station Oblivion",
	 {
		{"OBLIVION.EXE", 0, "80783622013750d7c88fd1d35dde919a", 6765},
		{"DRILLC.EXE", 0, "56394eae69f535cbddaa463888086ac6", 43864},
		{"DRILLE.EXE", 0, "30edf6be0037b2b0e8c6957df62c2a02", 51944},
		{"DRILLH.EXE", 0, "7f764048050e7a1b1f33aa466230edeb", 47496},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO3(GUIO_NOMIDI, GUIO_RENDEREGA, GUIO_RENDERCGA)},
	{"castlemaster",
	 "Castle Master",
	 {
		{"CASTLE.EXE", 0, "f1a141df0e47860246716db20d2ba061", 2806},
		{"CMC.EXE", 0, "03af2b79b1aad690684cf89025c5f425", 60240},
		{"CMT.EXE", 0, "a603d3f96e981ab0014b7b1a5a2dc28c", 81840},
		{"CME.EXE", 0, "99d8b4dbaad1fd73c9afdde550dc5195", 92320},
		{"CMH.EXE", 0, "1f3b67e649e718e239ebfd7c56e96d47", 63040},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"castlemaster",
	 "Castle Master/VirtualWords",
	 {
		{"CASTLE.EXE", 0, "f1a141df0e47860246716db20d2ba061", 2806},
		{"CMC.EXE", 0, "7b9275df446f82fdd0c377f6ec2db546", 57168},
		{"CMT.EXE", 0, "5814e68a175f74ebce0773a73e7488c7", 78768},
		{"CME.EXE", 0, "d563ae1475752e6a9a81b1350abebef3", 89248},
		{"CMH.EXE", 0, "26337adc7861300e5395e992e42b6329", 59968},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"castlemaster",
	 "Castle Master/DomarkPCCollection",
	 {
		{"X.EXE", 0, "d51d7db1e06814cbf763c43f411df616", 2157},
		{"CMC.EXE", 0, "7b9275df446f82fdd0c377f6ec2db546", 57168},
		{"CMT.EXE", 0, "78002e4b6c14e0a7924317d27e868985", 40685},
		{"CME.EXE", 0, "494268dea6d8580a7f27afb2a8157cc0", 46557},
		{"CMH.EXE", 0, "03b6f4c5b8931259e42e229de06ac5fc", 35645},
		AD_LISTEND
	 },
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"castlemaster",
	 "Castle Master",
	 {
		{"CASTLE.EXE", 0, "42a7d46b418d68e75e31c1cb9d89af14", 2678},
		{"CMC.EXE", 0, "9015c244dc8a97fe55df7b235b31e00c", 57168},
		{"CMT.EXE", 0, "5814e68a175f74ebce0773a73e7488c7", 78768},
		{"CME.EXE", 0, "d563ae1475752e6a9a81b1350abebef3", 89248},
		{"CMH.EXE", 0, "cc68c42d254b3aa0f208cd08731c6805", 59968},
		AD_LISTEND
	 },
	 Common::ES_ESP,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},

	// 3D Construction Kit games
	{"3dkit",
	 "The 3-D Kit Game",
	 AD_ENTRY1s("3DKIT.RUN", "f35147729a2f5b6852a504223aeb6a57", 112158),
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"3dkit",
	 "Menace of Dr. Spoil Sport",
	 AD_ENTRY1s("MODSS.RUN", "409ac1100a15447e742ec1415b2741c3", 91176),
	 Common::EN_ANY,
	 Common::kPlatformDOS,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},
	{"3dkit",
	 "Anarchy Academy",
	 AD_ENTRY2s("ANARCHY.PRG", "78d543be4aad9608093c1e91bc100307", 270,
	            "RUNNER.DAT", "1cf7c049ee59503dd7218b0f45828132", 42802),
	 Common::EN_ANY,
	 Common::kPlatformAtariST,
	 ADGF_NO_FLAGS,
	 GUIO1(GUIO_NOMIDI)},

	AD_TABLE_END_MARKER};
} // End of namespace Freescape

static const DebugChannelDef debugFlagList[] = {
	{Freescape::kFreescapeDebugMove, "move", ""},
	{Freescape::kFreescapeDebugParser, "parser", ""},
	{Freescape::kFreescapeDebugCode, "code", ""},
	{Freescape::kFreescapeDebugMedia, "media", ""},
	DEBUG_CHANNEL_END
};

static const ADExtraGuiOptionsMap optionsList[] = {
	{
		GAMEOPTION_PRERECORDED_SOUNDS,
		{
			_s("Prerecorded sounds"),
			_s("Use high-quality pre-recorded sounds instead of pc speaker emulation"),
			"prerecorded_sounds",
			true,
			0,
			0
		}
	},
	AD_EXTRA_GUI_OPTIONS_TERMINATOR
};

class FreescapeMetaEngineDetection : public AdvancedMetaEngineDetection {
public:
	FreescapeMetaEngineDetection() : AdvancedMetaEngineDetection(Freescape::gameDescriptions, sizeof(ADGameDescription), Freescape::freescapeGames, optionsList) {
		_guiOptions = GUIO2(GUIO_NOMIDI, GAMEOPTION_PRERECORDED_SOUNDS);
	}

	const char *getEngineId() const override {
		return "freescape";
	}

	const char *getName() const override {
		return "Freescape";
	}

	const char *getOriginalCopyright() const override {
		return "Copyright (C) Incentive Software 1987";
	}

	const DebugChannelDef *getDebugChannels() const override {
		return debugFlagList;
	}
};

REGISTER_PLUGIN_STATIC(FREESCAPE_DETECTION, PLUGIN_TYPE_ENGINE_DETECTION, FreescapeMetaEngineDetection);
