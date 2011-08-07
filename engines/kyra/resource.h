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

#ifndef KYRA_RESOURCE_H
#define KYRA_RESOURCE_H


#include "common/scummsys.h"
#include "common/str.h"
#include "common/file.h"
#include "common/list.h"
#include "common/hash-str.h"
#include "common/hashmap.h"
#include "common/stream.h"
#include "common/ptr.h"
#include "common/archive.h"

#include "kyra/kyra_v1.h"
#include "kyra/eob2.h"
#include "kyra/lol.h"
#include "kyra/kyra_hof.h"

namespace Kyra {

class Resource;

class ResArchiveLoader;

class Resource {
public:
	Resource(KyraEngine_v1 *vm);
	~Resource();

	bool reset();

	bool loadPakFile(Common::String filename);
	bool loadPakFile(Common::String name, Common::ArchiveMemberPtr file);

	void unloadPakFile(Common::String filename, bool remFromCache = false);

	bool isInPakList(Common::String filename);

	bool isInCacheList(Common::String name);

	bool loadFileList(const Common::String &filedata);
	bool loadFileList(const char * const *filelist, uint32 numFiles);

	// This unloads *all* pakfiles, even kyra.dat and protected ones.
	// It does not remove files from cache though!
	void unloadAllPakFiles();

	void listFiles(const Common::String &pattern, Common::ArchiveMemberList &list);

	bool exists(const char *file, bool errorOutOnFail=false);
	uint32 getFileSize(const char *file);
	uint8 *fileData(const char *file, uint32 *size);
	Common::SeekableReadStream *createReadStream(const Common::String &file);

	bool loadFileToBuf(const char *file, void *buf, uint32 maxSize);
protected:
	typedef Common::HashMap<Common::String, Common::Archive *, Common::CaseSensitiveString_Hash, Common::CaseSensitiveString_EqualTo> ArchiveMap;
	ArchiveMap _archiveCache;

	Common::SearchSet _files;
	Common::SearchSet _archiveFiles;
	Common::SearchSet _protectedFiles;

	Common::Archive *loadArchive(const Common::String &name, Common::ArchiveMemberPtr member);
	Common::Archive *loadInstallerArchive(const Common::String &file, const Common::String &ext, const uint8 offset);

	bool loadProtectedFiles(const char * const * list);

	void initializeLoaders();

	typedef Common::List<Common::SharedPtr<ResArchiveLoader> > LoaderList;
	LoaderList _loaders;

	KyraEngine_v1 *_vm;
};

enum KyraResources {
	kLoadAll = -1,

	// This list has to match orderwise (and thus value wise) the static data list of "devtools/create_kyradat/create_kyradat.h"!
	k1ForestSeq = 1,
	k1KallakWritingSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,

	k1Demo1Seq,
	k1Demo2Seq,
	k1Demo3Seq,
	k1Demo4Seq,

	k1AmuleteAnimSeq,

	k1OutroReunionSeq,

	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,

	k1OutroHomeString,

	k1RoomFilenames,
	k1RoomList,

	k1CharacterImageFilenames,

	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,

	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1PoisonGoneString,
	k1HealingTipString,
	k1WispJewelStrings,
	k1MagicJewelStrings,

	k1ThePoisonStrings,
	k1FluteStrings,

	k1FlaskFullString,
	k1FullFlaskString,

	k1VeryCleverString,
	k1NewGameString,

	k1DefaultShapes,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,

	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,

	k1GUIStrings,
	k1ConfigStrings,

	k1AudioTracks,
	k1AudioTracks2,
	k1AudioTracksIntro,

	k1CreditsStrings,

	k1TownsMusicFadeTable,
	k1TownsSFXwdTable,
	k1TownsSFXbtTable,
	k1TownsCDATable,

	k1PC98StoryStrings,
	k1PC98IntroSfx,

	k1AmigaIntroSFXTable,
	k1AmigaGameSFXTable,

	k2SeqplayPakFiles,
	k2SeqplayCredits,
	k2SeqplayCreditsSpecial,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplayTlkFiles,
	k2SeqplaySeqData,
	k2SeqplayIntroTracks,
	k2SeqplayFinaleTracks,
	k2SeqplayIntroCDA,
	k2SeqplayFinaleCDA,
	k2SeqplayShapeAnimData,

	k2IngamePakFiles,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTracks,
	k2IngameCDA,
	k2IngameTalkObjIndex,
	k2IngameTimJpStrings,
	k2IngameShapeAnimData,
	k2IngameTlkDemoStrings,

	k3MainMenuStrings,
	k3MusicFiles,
	k3ScoreTable,
	k3SfxFiles,
	k3SfxMap,
	k3ItemAnimData,
	k3ItemMagicTable,
	k3ItemStringMap,

#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	kLolEobCommonMoreStrings,
	kLolEobCommonDscShapeIndex,
	kLolEobCommonDscX,
	kLolEobCommonDscTileIndex,
	kLolEobCommonDscUnk2,
	kLolEobCommonDscDoorShapeIndex,
	kLolEobCommonDscDimData1,
	kLolEobCommonDscDimData2,
	kLolEobCommonDscBlockMap,
	kLolEobCommonDscDimMap,
	kLolEobCommonDscDoorY2,
	kLolEobCommonDscBlockIndex,

	kEobBaseChargenStrings1,
	kEobBaseChargenStrings2,
	kEobBaseChargenStartLevels,
	kEobBaseChargenStatStrings,
	kEobBaseChargenRaceSexStrings,
	kEobBaseChargenClassStrings,
	kEobBaseChargenAlignmentStrings,
	kEobBaseChargenEnterGameStrings,
	kEobBaseChargenClassMinStats,
	kEobBaseChargenRaceMinStats,
	kEobBaseChargenRaceMaxStats,

	kEobBaseConstModTable1,
	kEobBaseConstModTable2,
	kEobBaseConstModTable3,
	kEobBaseConstModTable4,
	kEobBaseConstModLvlIndex,
	kEobBaseConstModDiv,
	kEobBaseConstModExt,

	kEobBasePryDoorStrings,
	kEobBaseWarningStrings,

	kEobBaseItemSuffixStringsRings,
	kEobBaseItemSuffixStringsPotions,
	kEobBaseItemSuffixStringsWands,
	
	kEobBaseRipItemStrings,
	kEobBaseCursedString,
	kEobBaseEnchantedString,
	kEobBaseMagicObjectStrings,
	kEobBaseMagicObjectString5,
	kEobBasePatternSuffix,
	kEobBasePatternGrFix1,
	kEobBasePatternGrFix2,
	kEobBaseValidateArmorString,
	kEobBaseValidateCursedString,
	kEobBaseValidateNoDropString,
	kEobBasePotionStrings,
	kEobBaseWandStrings,
	kEobBaseItemMisuseStrings,

	kEobBaseTakenStrings,
	kEobBasePotionEffectStrings,

	kEobBaseYesNoStrings,
	kEobBaseNpcMaxStrings,
	kEobBaseOkStrings,
	kEobBaseNpcJoinStrings,
	kEobBaseCancelStrings,
	kEobBaseAbortStrings,

	kEobBaseMenuStringsMain,
	kEobBaseMenuStringsSaveLoad,
	kEobBaseMenuStringsOnOff,
	kEobBaseMenuStringsSpells,
	kEobBaseMenuStringsRest,
	kEobBaseMenuStringsDrop,
	kEobBaseMenuStringsExit,
	kEobBaseMenuStringsStarve,
	kEobBaseMenuStringsScribe,
	kEobBaseMenuStringsDrop2,
	kEobBaseMenuStringsHead,
	kEobBaseMenuStringsPoison,
	kEobBaseMenuStringsMgc,
	kEobBaseMenuStringsPrefs,
	kEobBaseMenuStringsRest2,
	kEobBaseMenuStringsRest3,
	kEobBaseMenuStringsRest4,
	kEobBaseMenuStringsDefeat,
	kEobBaseMenuStringsTransfer,
	kEobBaseMenuStringsSpec,
	kEobBaseMenuStringsSpellNo,
	kEobBaseMenuYesNoStrings,

	kEobBaseSpellLevelsMage,
	kEobBaseSpellLevelsCleric,
	kEobBaseNumSpellsCleric,
	kEobBaseNumSpellsWisAdj,
	kEobBaseNumSpellsPal,
	kEobBaseNumSpellsMage,

	kEobBaseCharGuiStringsHp,
	kEobBaseCharGuiStringsWp1,
	kEobBaseCharGuiStringsWp2,
	kEobBaseCharGuiStringsWr,
	kEobBaseCharGuiStringsSt1,
	kEobBaseCharGuiStringsSt2,
	kEobBaseCharGuiStringsIn,

	kEobBaseCharStatusStrings7,
	kEobBaseCharStatusStrings81,
	kEobBaseCharStatusStrings82,
	kEobBaseCharStatusStrings9,
	kEobBaseCharStatusStrings12,
	kEobBaseCharStatusStrings131,
	kEobBaseCharStatusStrings132,

	kEobBaseLevelGainStrings,
	kEobBaseExperienceTable0,
	kEobBaseExperienceTable1,
	kEobBaseExperienceTable2,
	kEobBaseExperienceTable3,
	kEobBaseExperienceTable4,

	kEobBaseClassModifierFlags,

	kEobBaseMonsterStepTable01,
	kEobBaseMonsterStepTable02,
	kEobBaseMonsterStepTable1,
	kEobBaseMonsterStepTable2,
	kEobBaseMonsterStepTable3,
	kEobBaseMonsterCloseAttPosTable1,
	kEobBaseMonsterCloseAttPosTable21,
	kEobBaseMonsterCloseAttPosTable22,
	kEobBaseMonsterCloseAttUnkTable,
	kEobBaseMonsterCloseAttChkTable1,
	kEobBaseMonsterCloseAttChkTable2,
	kEobBaseMonsterCloseAttDstTable1,
	kEobBaseMonsterCloseAttDstTable2,

	kEobBaseMonsterProximityTable,
	kEobBaseFindBlockMonstersTable,
	kEobBaseMonsterDirChangeTable,
	kEobBaseMonsterDistAttStrings,

	kEobBaseEncodeMonsterDefs,
	kEobBaseNpcPresets,

	kEobBaseWllFlagPreset,
	kEobBaseDscShapeCoords,

	kEobBaseDscDoorScaleOffs,
	kEobBaseDscDoorScaleMult1,
	kEobBaseDscDoorScaleMult2,
	kEobBaseDscDoorScaleMult3,
	kEobBaseDscDoorScaleMult4,
	kEobBaseDscDoorScaleMult5,
	kEobBaseDscDoorScaleMult6,
	kEobBaseDscDoorType5Offs,
	kEobBaseDscDoorXE,
	kEobBaseDscDoorY1,
	kEobBaseDscDoorY3,
	kEobBaseDscDoorY4,
	kEobBaseDscDoorY5,
	kEobBaseDscDoorY6,
	kEobBaseDscDoorY7,
	kEobBaseDscDoorCoordsExt,

	kEobBaseDscItemPosIndex,
	kEobBaseDscItemShpX,
	kEobBaseDscItemScaleIndex,
	kEobBaseDscItemTileIndex,
	kEobBaseDscItemShapeMap,

	kEobBaseDscMonsterFrmOffsTbl1,
	kEobBaseDscMonsterFrmOffsTbl2,

	kEobBaseInvSlotX,
	kEobBaseInvSlotY,
	kEobBaseSlotValidationFlags,

	kEobBaseProjectileWeaponTypes,
	kEobBaseWandTypes,

	kEobBaseDrawObjPosIndex,
	kEobBaseFlightObjFlipIndex,
	kEobBaseFlightObjShpMap,
	kEobBaseFlightObjSclIndex,

	kEobBaseDscTelptrShpCoords,

	kEobBasePortalSeqData,
	kEobBaseManDef,
	kEobBaseManWord,
	kEobBaseManPrompt,

	kEobBaseBookNumbers,
	kEobBaseMageSpellsList,
	kEobBaseClericSpellsList,
	kEobBaseSpellNames,
	kEobBaseMagicStrings1,
	kEobBaseMagicStrings2,
	kEobBaseMagicStrings3,
	kEobBaseMagicStrings4,
	kEobBaseMagicStrings6,
	kEobBaseMagicStrings7,
	kEobBaseMagicStrings8,

	kEobBaseExpObjectTlMode,
	kEobBaseExpObjectTblIndex,
	kEobBaseExpObjectShpStart,
	kEobBaseExpObjectTbl1,
	kEobBaseExpObjectTbl2,
	kEobBaseExpObjectTbl3,
	kEobBaseExpObjectY,

	kEobBaseSparkDefSteps,
	kEobBaseSparkDefSubSteps,
	kEobBaseSparkDefShift,
	kEobBaseSparkDefAdd,
	kEobBaseSparkDefX,
	kEobBaseSparkDefY,
	kEobBaseSparkOfFlags1,
	kEobBaseSparkOfFlags2,
	kEobBaseSparkOfShift,
	kEobBaseSparkOfX,
	kEobBaseSparkOfY,

	kEobBaseSpellProperties,
	kEobBaseMagicFlightProps,
	kEobBaseTurnUndeadEffect,
	kEobBaseBurningHandsDest,

	kEob1MainMenuStrings,
	kEob1DoorShapeDefs,
	kEob1DoorSwitchShapeDefs,
	kEob1DoorSwitchCoords,
	kEob1MonsterProperties,

	kEob1EnemyMageSpellList,
	kEob1EnemyMageSfx,
	kEob1BeholderSpellList,
	kEob1BeholderSfx,

	kEob1TurnUndeadString,

	kEob1NpcShpData,
	kEob1NpcSubShpIndex1,
	kEob1NpcSubShpIndex2,
	kEob1NpcSubShpY,
	kEob1Npc0Strings,
	kEob1Npc11Strings,
	kEob1Npc12Strings,
	kEob1Npc21Strings,
	kEob1Npc22Strings,
	kEob1Npc31Strings,
	kEob1Npc32Strings,
	kEob1Npc4Strings,
	kEob1Npc5Strings,
	kEob1Npc6Strings,
	kEob1Npc7Strings,

	kEob2MainMenuStrings,
	kEob2IntroStrings,
	kEob2IntroCPSFiles,
	kEob2IntroSeqData00,
 	kEob2IntroSeqData01,
 	kEob2IntroSeqData02,
 	kEob2IntroSeqData03,
 	kEob2IntroSeqData04,
 	kEob2IntroSeqData05,
 	kEob2IntroSeqData06,
 	kEob2IntroSeqData07,
 	kEob2IntroSeqData08,
 	kEob2IntroSeqData09,
 	kEob2IntroSeqData10,
 	kEob2IntroSeqData11,
 	kEob2IntroSeqData12,
 	kEob2IntroSeqData13,
 	kEob2IntroSeqData14,
 	kEob2IntroSeqData15,
 	kEob2IntroSeqData16,
 	kEob2IntroSeqData17,
 	kEob2IntroSeqData18,
 	kEob2IntroSeqData19,
 	kEob2IntroSeqData20,
 	kEob2IntroSeqData21,
 	kEob2IntroSeqData22,
 	kEob2IntroSeqData23,
 	kEob2IntroSeqData24,
 	kEob2IntroSeqData25,
 	kEob2IntroSeqData26,
 	kEob2IntroSeqData27,
 	kEob2IntroSeqData28,
 	kEob2IntroSeqData29,
 	kEob2IntroSeqData30,
 	kEob2IntroSeqData31,
 	kEob2IntroSeqData32,
 	kEob2IntroSeqData33,
 	kEob2IntroSeqData34,
 	kEob2IntroSeqData35,
 	kEob2IntroSeqData36,
 	kEob2IntroSeqData37,
 	kEob2IntroSeqData38,
 	kEob2IntroSeqData39,
 	kEob2IntroSeqData40,
 	kEob2IntroSeqData41,
 	kEob2IntroSeqData42,
 	kEob2IntroSeqData43,
	kEob2IntroShapes00,
 	kEob2IntroShapes01,
 	kEob2IntroShapes04,
 	kEob2IntroShapes07,

	kEob2FinaleStrings,
	kEob2CreditsData,
	kEob2FinaleCPSFiles,
	kEob2FinaleSeqData00,
 	kEob2FinaleSeqData01,
 	kEob2FinaleSeqData02,
 	kEob2FinaleSeqData03,
 	kEob2FinaleSeqData04,
 	kEob2FinaleSeqData05,
 	kEob2FinaleSeqData06,
 	kEob2FinaleSeqData07,
 	kEob2FinaleSeqData08,
 	kEob2FinaleSeqData09,
 	kEob2FinaleSeqData10,
 	kEob2FinaleSeqData11,
 	kEob2FinaleSeqData12,
 	kEob2FinaleSeqData13,
 	kEob2FinaleSeqData14,
 	kEob2FinaleSeqData15,
 	kEob2FinaleSeqData16,
 	kEob2FinaleSeqData17,
 	kEob2FinaleSeqData18,
 	kEob2FinaleSeqData19,
 	kEob2FinaleSeqData20,
	kEob2FinaleShapes00,
 	kEob2FinaleShapes03,
 	kEob2FinaleShapes07,
 	kEob2FinaleShapes09,
 	kEob2FinaleShapes10,

	kEob2NpcShapeData,
	kEob2Npc1Strings,
	kEob2Npc2Strings,
	kEob2MonsterDustStrings,

	kEob2DranFoolsStrings,
	kEob2HornStrings,
	kEob2HornSounds,

	kLolIngamePakFiles,
	kLolCharacterDefs,
	kLolIngameSfxFiles,
	kLolIngameSfxIndex,
	kLolMusicTrackMap,
	kLolIngameGMSfxIndex,
	kLolIngameMT32SfxIndex,
	kLolIngamePcSpkSfxIndex,
	kLolSpellProperties,
	kLolGameShapeMap,
	kLolSceneItemOffs,
	kLolCharInvIndex,
	kLolCharInvDefs,
	kLolCharDefsMan,
	kLolCharDefsWoman,
	kLolCharDefsKieran,
	kLolCharDefsAkshel,
	kLolExpRequirements,
	kLolMonsterModifiers,
	kLolMonsterShiftOffsets,
	kLolMonsterDirFlags,
	kLolMonsterScaleY,
	kLolMonsterScaleX,
	kLolMonsterScaleWH,
	kLolFlyingObjectShp,
	kLolInventoryDesc,

	kLolLevelShpList,
	kLolLevelDatList,
	kLolCompassDefs,
	kLolItemPrices,
	kLolStashSetup,

	kLolDscWalls,
	kLolDscOvlMap,
	kLolDscScaleWidthData,
	kLolDscScaleHeightData,
	kLolBaseDscY,

	kLolDscDoorScale,
	kLolDscDoor4,
	kLolDscDoorX,
	kLolDscDoorY,
	kLolDscOvlIndex,

	kLolScrollXTop,
	kLolScrollYTop,
	kLolScrollXBottom,
	kLolScrollYBottom,

	kLolButtonDefs,
	kLolButtonList1,
	kLolButtonList2,
	kLolButtonList3,
	kLolButtonList4,
	kLolButtonList5,
	kLolButtonList6,
	kLolButtonList7,
	kLolButtonList8,

	kLolLegendData,
	kLolMapCursorOvl,
	kLolMapStringId,

	kLolSpellbookAnim,
	kLolSpellbookCoords,
	kLolHealShapeFrames,
	kLolLightningDefs,
	kLolFireballCoords,

	kLolCredits,

	kLolHistory,
#endif // ENABLE_EOB || ENABLE_LOL

	kMaxResIDs
};

struct Shape;
struct Room;
struct AmigaSfxTable;

class StaticResource {
public:
	static const Common::String staticDataFilename() { return "KYRA.DAT"; }

	StaticResource(KyraEngine_v1 *vm) : _vm(vm), _resList(), _fileLoader(0), _dataTable() {}
	~StaticResource() { deinit(); }

	bool loadStaticResourceFile();

	bool init();
	void deinit();

	const char * const *loadStrings(int id, int &strings);
	const uint8 *loadRawData(int id, int &size);
	const Shape *loadShapeTable(int id, int &entries);
	const AmigaSfxTable *loadAmigaSfxTable(int id, int &entries);
	const Room *loadRoomTable(int id, int &entries);
	const HofSeqData *loadHofSequenceData(int id, int &entries);
	const ItemAnimData_v1 *loadShapeAnimData_v1(int id, int &entries);
	const ItemAnimData_v2 *loadShapeAnimData_v2(int id, int &entries);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	const uint16 *loadRawDataBe16(int id, int &entries);
	const uint32 *loadRawDataBe32(int id, int &entries);
#endif // (ENABLE_EOB || ENABLE_LOL)
#ifdef ENABLE_LOL
	const LoLCharacter *loadCharData(int id, int &entries);
	const SpellProperty *loadSpellData(int id, int &entries);
	const CompassDef *loadCompassData(int id, int &entries);
	const FlyingObjectShape *loadFlyingObjectData(int id, int &entries);
	const LoLButtonDef *loadButtonDefs(int id, int &entries);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	const EobSequenceStep *loadEob2SeqData(int id, int &entries);
	const EobShapeDef *loadEob2ShapeData(int id, int &entries);
	const EobCharacter *loadEobNpcData(int id, int &entries);
#endif // ENABLE_EOB

	// use '-1' to prefetch/unload all ids
	// prefetchId retruns false if only on of the resources
	// can't be loaded and it breaks then the first res
	// can't be loaded
	bool prefetchId(int id);
	void unloadId(int id);
private:
	bool tryKyraDatLoad();

	KyraEngine_v1 *_vm;

	struct FileType;

	bool checkResList(int id, int &type, const void *&ptr, int &size);
	const FileType *getFiletype(int type);
	const void *getData(int id, int requesttype, int &size);

	bool loadStringTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRawData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadAmigaSfxTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRoomTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadHofSequenceData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeAnimData_v1(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeAnimData_v2(Common::SeekableReadStream &stream, void *&ptr, int &size);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	bool loadRawDataBe16(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRawDataBe32(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // (ENABLE_LOL || ENABLE_EOB)
#ifdef ENABLE_LOL
	bool loadCharData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadSpellData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadCompassData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadFlyingObjectData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadButtonDefs(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	bool loadEob2SeqData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadEob2ShapeData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadEobNpcData(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // ENABLE_EOB

	void freeRawData(void *&ptr, int &size);
	void freeStringTable(void *&ptr, int &size);
	void freeShapeTable(void *&ptr, int &size);
	void freeAmigaSfxTable(void *&ptr, int &size);
	void freeRoomTable(void *&ptr, int &size);
	void freeHofSequenceData(void *&ptr, int &size);
	void freeHofShapeAnimDataV1(void *&ptr, int &size);
	void freeHofShapeAnimDataV2(void *&ptr, int &size);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	void freeRawDataBe16(void *&ptr, int &size);
	void freeRawDataBe32(void *&ptr, int &size);
#endif // (ENABLE_EOB || ENABLE_LOL)
#ifdef ENABLE_LOL
	void freeCharData(void *&ptr, int &size);
	void freeSpellData(void *&ptr, int &size);
	void freeCompassData(void *&ptr, int &size);
	void freeFlyingObjectData(void *&ptr, int &size);
	void freeButtonDefs(void *&ptr, int &size);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	void freeEob2SeqData(void *&ptr, int &size);
	void freeEob2ShapeData(void *&ptr, int &size);
	void freeEobNpcData(void *&ptr, int &size);
#endif // ENABLE_EOB

	enum ResTypes {
		kStringList = 0,
		kRawData = 1,
		kRoomList = 2,
		kShapeList = 3,
		kAmigaSfxTable = 4,

		k2SeqData = 5,
		k2ShpAnimDataV1 = 6,
		k2ShpAnimDataV2 = 7,

		kLolCharData = 8,
		kLolSpellData = 9,
		kLolCompassData = 10,
		kLolFlightShpData = 11,
		kLolButtonData = 12,
		kLolRawDataBe16 = 13,
		kLolRawDataBe32 = 14,

		kEob2SequenceData = 15,
		kEob2ShapeData = 16,
		kEobNpcData = 17
	};

	struct FileType {
		int type;
		typedef bool (StaticResource::*LoadFunc)(Common::SeekableReadStream &stream, void *&ptr, int &size);
		typedef void (StaticResource::*FreeFunc)(void *&ptr, int &size);

		LoadFunc load;
		FreeFunc free;
	};

	struct ResData {
		int id;
		int type;
		int size;
		void *data;
	};

	Common::List<ResData> _resList;

	const FileType *_fileLoader;

	struct DataDescriptor {
		DataDescriptor() : filename(0), type(0) {}
		DataDescriptor(uint32 f, uint8 t) : filename(f), type(t) {}

		uint32 filename;
		uint8 type;
	};
	typedef Common::HashMap<uint16, DataDescriptor> DataMap;
	DataMap _dataTable;
};

} // End of namespace Kyra

#endif
