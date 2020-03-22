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

#ifndef ULTIMA4_SETTINGS_H
#define ULTIMA4_SETTINGS_H

#include "ultima/ultima4/observable.h"
#include "ultima/ultima4/core/types.h"
#include "common/hash-str.h"

namespace Ultima {
namespace Ultima4 {

#define MIN_SHAKE_INTERVAL              50

#define MAX_BATTLE_SPEED                10
#define MAX_KEY_DELAY                   1000
#define MAX_KEY_INTERVAL                100
#define MAX_CYCLES_PER_SECOND           20
#define MAX_SPELL_EFFECT_SPEED          10
#define MAX_CAMP_TIME                   10
#define MAX_INN_TIME                    10
#define MAX_SHRINE_TIME                 20
#define MAX_SHAKE_INTERVAL              200
#define MAX_VOLUME                      10

#define DEFAULT_SCALE                   2
#define DEFAULT_FULLSCREEN              0
#define DEFAULT_FILTER                  "Scale2x"
#define DEFAULT_VIDEO_TYPE              "new"
#define DEFAULT_GEM_LAYOUT              "Standard"
#define DEFAULT_LINEOFSIGHT             "DOS"
#define DEFAULT_SCREEN_SHAKES           1
#define DEFAULT_GAMMA                   100
#define DEFAULT_MUSIC_VOLUME            10
#define DEFAULT_SOUND_VOLUME            10
#define DEFAULT_VOLUME_FADES            1
#define DEFAULT_SHORTCUT_COMMANDS       0
#define DEFAULT_KEY_DELAY               500
#define DEFAULT_KEY_INTERVAL            30
#define DEFAULT_FILTER_MOVE_MESSAGES    0
#define DEFAULT_BATTLE_SPEED            5
#define DEFAULT_ENHANCEMENTS            1
#define DEFAULT_CYCLES_PER_SECOND       4
#define DEFAULT_ANIMATION_FRAMES_PER_SECOND 24
#define DEFAULT_DEBUG                   0
#define DEFAULT_VALIDATE_XML            1
#define DEFAULT_SPELL_EFFECT_SPEED      10
#define DEFAULT_CAMP_TIME               10
#define DEFAULT_INN_TIME                8
#define DEFAULT_SHRINE_TIME             16
#define DEFAULT_SHAKE_INTERVAL          100
#define DEFAULT_BATTLE_DIFFICULTY       "Normal"
#define DEFAULT_LOGGING                 ""
#define DEFAULT_TITLE_SPEED_RANDOM      150
#define DEFAULT_TITLE_SPEED_OTHER       30

#define DEFAULT_PAUSE_FOR_EACH_TURN     100
#define DEFAULT_PAUSE_FOR_EACH_MOVEMENT 10

//--Tile transparency stuff
#define DEFAULT_SHADOW_PIXEL_OPACITY    64
#define DEFAULT_SHADOW_PIXEL_SIZE       2

struct SettingsEnhancementOptions {
	bool _activePlayer;
	bool _u5spellMixing;
	bool _u5shrines;
	bool _u5combat;
	bool _slimeDivides;
	bool _gazerSpawnsInsects;
	bool _textColorization;
	bool _c64chestTraps;
	bool _smartEnterKey;
	bool _peerShowsObjects;
	bool _u4TileTransparencyHack;
	int  _u4TileTransparencyHackPixelShadowOpacity;
	int  _u4TrileTransparencyHackShadowBreadth;

};

struct MouseOptions {
	bool enabled;
};

/**
 * SettingsData stores all the settings information.
 */
class SettingsData {
public:
	bool operator==(const SettingsData &) const;
	bool operator!=(const SettingsData &) const;

	int                 _battleSpeed;
	bool                _campingAlwaysCombat;
	int                 _campTime;
	bool                _debug;
	bool                _enhancements;
	SettingsEnhancementOptions _enhancementsOptions;
	bool                _filterMoveMessages;
	bool                _fullscreen;
	int                 _gameCyclesPerSecond;
	int                 _screenAnimationFramesPerSecond;
	bool                _innAlwaysCombat;
	int                 _innTime;
	int                 _keydelay;
	int                 _keyinterval;
	MouseOptions        _mouseOptions;
	int                 _musicVol;
	unsigned int        _scale;
	bool                _screenShakes;
	int                 _gamma;
	int                 _shakeInterval;
	bool                _shortcutCommands;
	int                 _shrineTime;
	int                 _soundVol;
	int                 _spellEffectSpeed;
	bool                _validateXml;
	bool                _volumeFades;
	int                 _titleSpeedRandom;
	int                 _titleSpeedOther;

	//Settings that aren't in file yet
	int                 _pauseForEachTurn;
	int                 _pauseForEachMovement;

	/**
	 * Strings, classes, and other objects that cannot
	 * be bitwise-compared must be placed here at the
	 * end of the list so that our == and != operators
	 * function correctly
	 */
	long                _end_of_bitwise_comparators;

	Common::String              _filter;
	Common::String              _gemLayout;
	Common::String              _lineOfSight;
	Common::String              _videoType;
	Common::String              _battleDiff;
	Common::String              _logging;
	Common::String              _game;
};

/**
 * The settings class is a singleton that holds all the settings
 * information.  It is dynamically initialized when first accessed.
 */
class Settings : public SettingsData, public Observable<Settings *> {
	typedef Common::HashMap<Common::String, Common::String> SettingsMap;

public:
	/* Methods */
	void init();
	static Settings &getInstance();
	void setData(const SettingsData &data);
	bool read();
	bool write();

	const Std::vector<Common::String> &getBattleDiffs();

private:
	Settings();

	static Settings *_instance;
	Std::vector<Common::String> _battleDiffs;
};

/* the global settings */
#define settings (Settings::getInstance())

} // End of namespace Ultima4
} // End of namespace Ultima

#endif
