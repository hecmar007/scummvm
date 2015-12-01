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

/*
 * This code is based on Labyrinth of Time code with assistance of
 *
 * Copyright (c) 1993 Terra Nova Development
 * Copyright (c) 2004 The Wyrmkeep Entertainment Co.
 *
 */

#ifndef LAB_LABFUN_H
#define LAB_LABFUN_H

#include "common/events.h"
#include "lab/parsetypes.h"

// For the Music class - TODO: Move to another header file
#include "audio/mixer.h"
#include "audio/audiostream.h"
#include "audio/decoders/raw.h"

#include "common/file.h"
#include "common/savefile.h"

#include "engines/savestate.h"

namespace Lab {

class LabEngine;

/* Direction defines */
#define NORTH   0
#define SOUTH   1
#define EAST    2
#define WEST    3

struct Image;
struct TextFont;
struct Gadget;

struct SaveGameHeader {
	byte version;
	SaveStateDescriptor desc;
	uint16 roomNumber;
	uint16 direction;
};

/*----------------------------*/
/*----- From graphics.c ------*/
/*----------------------------*/

/* Reads in pictures */

bool readPict(const char *filename, bool PlayOnce);
bool readMusic(const char *filename, bool waitTillFinished);
byte *readPictToMem(const char *filename, uint16 x, uint16 y);

/* Window text stuff */

uint32 flowText(void *font,  /* the TextAttr pointer */
                int16 spacing,          /* How much vertical spacing between the lines */
                byte pencolor,         /* pen number to use for text */
                byte backpen,          /* the background color */
                bool fillback,                /* Whether to fill the background */
                bool centerh,                 /* Whether to center the text horizontally */
                bool centerv,                 /* Whether to center the text vertically */
                bool output,                  /* Whether to output any text */
                uint16 x1,               /* Cords */
                uint16 y1, uint16 x2, uint16 y2, const char *text); /* The text itself */

uint32 flowTextToMem(Image *DestIm, void *font,     /* the TextAttr pointer */
                     int16 spacing,          /* How much vertical spacing between the lines */
                     byte pencolor,         /* pen number to use for text */
                     byte backpen,          /* the background color */
                     bool fillback,                /* Whether to fill the background */
                     bool centerh,                 /* Whether to center the text horizontally */
                     bool centerv,                 /* Whether to center the text vertically */
                     bool output,                  /* Whether to output any text */
                     uint16 x1,               /* Cords */
                     uint16 y1, uint16 x2, uint16 y2, const char *text); /* The text itself */

void drawMessage(const char *text);
void drawStaticMessage(byte index);
int32 longDrawMessage(const char *text);

/* The Wipes */

void doWipe(uint16 WipeType, CloseDataPtr *CPtr, char *filename);

/* Double Buffer stuff */

void newFlipViews(void *scrPtr, uint16 *newpal, uint16 numcolors);
void flipViews(void *scrPtr);

/*----------------------------*/
/*----- From Interface.c -----*/
/*----------------------------*/

Gadget *addGadButton(uint16 x, uint16 y, void *UpImage, void *DownImage, uint16 id);
void gadgetsOnOff(void *gptr, void *win, int32 num, bool on);

/*----------------------*/
/*----- From Lab.c -----*/
/*----------------------*/

void eatMessages();
bool quitPlaying();

/*---------------------------*/
/*------ From LabFile.c -----*/
/*---------------------------*/

/* Buffer a whole file */
byte **isBuffered(const char *fileName);
byte **openFile(const char *name, uint32 &size);
void readBlock(void *Buffer, uint32 Size, byte **File);
void resetBuffer();
bool initBuffer(uint32 BufSize, bool IsGraphicsMem);
void freeBuffer();

/* Functions that borrow memory from the buffer */
bool allocFile(void **Ptr, uint32 Size, const char *fileName);
void *stealBufMem(int32 Size);
void freeAllStolenMem();


/* Read chunks of a file */
Common::File *openPartial(const char *name);
void closePartial(int32 File);

/*---------------------------*/
/*----- From LabSets.c ------*/
/*---------------------------*/

class LargeSet {
public:
    LargeSet(uint16 last, LabEngine *vm);
    ~LargeSet();
    bool in(uint16 element);
    void inclElement(uint16 element);
    void exclElement(uint16 element);
    bool readInitialConditions(const char *fileName);

private:
	LabEngine *_vm;

public:
    uint16 _lastElement;
    uint16 *_array;
};

/*---------------------------*/
/*----- From Machine.c ------*/
/*---------------------------*/

uint16 scaleX(uint16 x);
uint16 scaleY(uint16 y);
int16 VGAScaleX(int16 x);
int16 VGAScaleY(int16 y);
uint16 SVGACord(uint16 cord);
int VGAUnScaleX(int x);
int VGAUnScaleY(int y);
char *translateFileName(const char *filename);

/*---------------------------*/
/*-------- From Map.c -------*/
/*---------------------------*/

void fade(bool fadein, uint16 res);
void setAmigaPal(uint16 *pal, uint16 numcolors);
void readImage(byte **buffer, Image **im);
void doMap(uint16 CurRoom);
void doJournal();
void doNotes();
void doWestPaper();
void doMonitor(char *background, char *textfile, bool isinteractive, uint16 x1, uint16 y1, uint16 x2, uint16 y2);
bool saveRestoreGame();

/*--------------------------*/
/*----- From saveGame.c ----*/
/*--------------------------*/

bool saveGame(uint16 Direction, uint16 Quarters, int slot, Common::String desc);
bool loadGame(uint16 *Direction, uint16 *Quarters, int slot);
bool readSaveGameHeader(Common::InSaveFile *in, SaveGameHeader &header);

/*--------------------------*/
/*----- From Special.c -----*/
/*--------------------------*/

void showCombination(const char *filename);
void mouseCombination(Common::Point pos);
void showTile(const char *filename, bool showsolution);
void mouseTile(Common::Point pos);

} // End of namespace Lab

#endif /* LAB_LABFUN_H */
