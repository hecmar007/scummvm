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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef MADS_SCENE_H
#define MADS_SCENE_H

#include "common/scummsys.h"
#include "common/array.h"
#include "common/rect.h"
#include "mads/assets.h"
#include "mads/screen.h"
#include "mads/hotspots.h"
#include "mads/messages.h"
#include "mads/msurface.h"
#include "mads/scene_data.h"
#include "mads/animation.h"
#include "mads/sequence.h"
#include "mads/sprites.h"
#include "mads/user_interface.h"

namespace MADS {

class Scene {
private:
	/**
	 * Return the index of a given Vocab in the active vocab list
	 */
	int activeVocabIndexOf(int vocabId);

	/**
	 * Secondary loading vocab list
	 */
	void loadVocabStrings();

	/*
	 * Initialises the data for palette animation within the scene
	 */
	void initPaletteAnimation(Common::Array<RGB4> &animData, bool animFlag);

	/**
	 * Handles a single frame within the game scene
	 */
	void doFrame();

	void doPreactions();

	void doAction();

	void checkStartWalk();

	void doSceneStep();

	void checkKeyboard();

	/**
	 * Checks for a highlighted hotspot, and updates the cursor accordingly
	 */
	void updateCursor();
protected:
	MADSEngine *_vm;
public:
	SceneLogic *_sceneLogic;
	int _priorSceneId;
	int _nextSceneId;
	int _currentSceneId;
	Common::Array<VerbInit> _verbList;
	TextDisplayList _textDisplay;
	SpriteSlots _spriteSlots;
	SpriteSets _sprites;
	int _spritesIndex;
	DynamicHotspots _dynamicHotspots;
	Common::Array<int> _activeVocabs;
	SequenceList _sequences;
	KernelMessages _kernelMessages;
	Common::String _talkFont;
	int _textSpacing;
	Hotspots _hotspots;
	DirtyAreas _dirtyAreas;
	int _v1;
	SceneInfo *_sceneInfo;
	MSurface _backgroundSurface;
	DepthSurface _depthSurface;
	UserInterface _userInterface;
	bool _animFlag;
	int _animVal1;
	int _animCount;
	Common::Array<uint32> _animTicksList;
	Common::Array<RGB4> _animPalData;
	SceneNodeList _nodes;
	Common::StringArray _vocabStrings;
	Animation *_animationData;
	Animation *_activeAnimation;
	bool _freeAnimationFlag;
	int _depthStyle;
	int _bandsRange;
	int _scaleRange;
	int _interfaceY;
	int _spritesCount;
	MADSAction _action;
	bool _roomChanged;
	bool _reloadSceneFlag;
	Common::Point _destPos;
	Facing _targetFacing;
	Common::Point _posAdjust;
	uint32 _frameStartTime;
	Layer _layer;
	bool _lookFlag;
	int _highlightedHotspot;
	Common::Point _customDest;

	/**
	 * Constructor
	 */
	Scene(MADSEngine *vm);

	/**
	 * Destructor
	 */
	~Scene();

	/**
	 * Clear the vocabulary list
	 */
	void clearVocab();

	/**
	 * Add a given vocab entry to the active list
	 */
	void addActiveVocab(int vocabId);

	/**
	 * Clear the sequence list
	 */
	void clearSequenceList();

	/**
	 * Clear the message list
	 */
	void clearMessageList();

	/**
	 * Loads the scene logic for a given scene
	 */
	void loadSceneLogic();

	/**
	 * Loads the resources associated with the given scene
	 * @param sceneId		Scene to load
	 * @param prefix		Prefix to use for retrieving animation data
	 * @param palFlag		Flag for whether to reset the high/lo palette areas
	 */
	void loadScene(int sceneId, const Common::String &prefix, bool palFlag);

	/**
	 * Loads the hotstpots for the scene
	 */
	void loadHotspots();

	/**
	 * Loads the vocab list
	 */
	void loadVocab();

	bool getDepthHighBits(const Common::Point &pt);

	/**
	 * Main scene loop
	 */
	void loop();

	/**
	 * Draw all the elements onto the scene
	 */
	void drawElements(ScreenTransition transitionType, bool surfaceFlag);

	/**
	 * Load an animation
	 */
	void loadAnimation(const Common::String &resName, int abortTimers = 0);

	/**
	 * Returns a vocab entry
	 */
	Common::String getVocab(int vocabId) { return _vocabStrings[vocabId - 1]; }

	/**
	 * Clear the data for the scene
	 */
	void free();

	void changeDepthSurface(int arg1);

	void resetScene();
};

} // End of namespace MADS

#endif /* MADS_SCENE_H */
