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

#include "ags/plugins/core/dynamic_sprite.h"
#include "ags/engine/ac/dynamic_sprite.h"

namespace AGS3 {
namespace Plugins {
namespace Core {

void DynamicSprite::AGS_EngineStartup(IAGSEngine *engine) {
	SCRIPT_METHOD_EXT(DynamicSprite::ChangeCanvasSize^4, ChangeCanvasSize);
	SCRIPT_METHOD_EXT(DynamicSprite::CopyTransparencyMask^1, CopyTransparencyMask);
	SCRIPT_METHOD_EXT(DynamicSprite::Crop^4, Crop);
	SCRIPT_METHOD_EXT(DynamicSprite::Delete, Delete);
	SCRIPT_METHOD_EXT(DynamicSprite::Flip^1, Flip);
	SCRIPT_METHOD_EXT(DynamicSprite::GetDrawingSurface^0, GetDrawingSurface);
	SCRIPT_METHOD_EXT(DynamicSprite::Resize^2, Resize);
	SCRIPT_METHOD_EXT(DynamicSprite::Rotate^3, Rotate);
	SCRIPT_METHOD_EXT(DynamicSprite::SaveToFile^1, SaveToFile);
	SCRIPT_METHOD_EXT(DynamicSprite::Tint^5, Tint);
	SCRIPT_METHOD_EXT(DynamicSprite::get_ColorDepth, GetColorDepth);
	SCRIPT_METHOD_EXT(DynamicSprite::get_Graphic, GetGraphic);
	SCRIPT_METHOD_EXT(DynamicSprite::get_Height, GetHeight);
	SCRIPT_METHOD_EXT(DynamicSprite::get_Width, GetWidth);
	SCRIPT_METHOD_EXT(DynamicSprite::Create^3, Create);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromBackground, CreateFromBackground);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromDrawingSurface^5, CreateFromDrawingSurface);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromExistingSprite^1, CreateFromExistingSprite_Old);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromExistingSprite^2, CreateFromExistingSprite);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromFile, CreateFromFile);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromSaveGame, CreateFromSaveGame);
	SCRIPT_METHOD_EXT(DynamicSprite::CreateFromScreenShot, CreateFromScreenShot);
}

void DynamicSprite::ChangeCanvasSize(ScriptMethodParams &params) {
	PARAMS5(ScriptDynamicSprite *, sds, int, width, int, height, int, x, int, y);
	AGS3::DynamicSprite_ChangeCanvasSize(sds, width, height, x, y);
}

void DynamicSprite::CopyTransparencyMask(ScriptMethodParams &params) {
	PARAMS2(ScriptDynamicSprite *, sds, int, sourceSprite);
	AGS3::DynamicSprite_CopyTransparencyMask(sds, sourceSprite);
}

void DynamicSprite::Crop(ScriptMethodParams &params) {
	PARAMS5(ScriptDynamicSprite *, sds, int, x1, int, y1, int, width, int, height);
	AGS3::DynamicSprite_Crop(sds, x1, y1, width, height);
}

void DynamicSprite::Delete(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, sds);
	AGS3::DynamicSprite_Delete(sds);
}

void DynamicSprite::Flip(ScriptMethodParams &params) {
	PARAMS2(ScriptDynamicSprite *, sds, int, direction);
	AGS3::DynamicSprite_Flip(sds, direction);
}

void DynamicSprite::GetDrawingSurface(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, dss);
	params._result = AGS3::DynamicSprite_GetDrawingSurface(dss);
}

void DynamicSprite::Resize(ScriptMethodParams &params) {
	PARAMS3(ScriptDynamicSprite *, sds, int, width, int, height);
	AGS3::DynamicSprite_Resize(sds, width, height);
}

void DynamicSprite::Rotate(ScriptMethodParams &params) {
	PARAMS4(ScriptDynamicSprite *, sds, int, angle, int, width, int, height);
	AGS3::DynamicSprite_Rotate(sds, angle, width, height);
}

void DynamicSprite::SaveToFile(ScriptMethodParams &params) {
	PARAMS2(ScriptDynamicSprite *, sds, const char *, namm);
	params._result = AGS3::DynamicSprite_SaveToFile(sds, namm);
}

void DynamicSprite::Tint(ScriptMethodParams &params) {
	PARAMS6(ScriptDynamicSprite *, sds, int, red, int, green, int, blue, int, saturation, int, luminance);
	AGS3::DynamicSprite_Tint(sds, red, green, blue, saturation, luminance);
}

void DynamicSprite::GetColorDepth(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, sds);
	params._result = AGS3::DynamicSprite_GetColorDepth(sds);
}

void DynamicSprite::GetGraphic(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, sds);
	params._result = AGS3::DynamicSprite_GetGraphic(sds);
}

void DynamicSprite::GetHeight(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, sds);
	params._result = AGS3::DynamicSprite_GetHeight(sds);
}

void DynamicSprite::GetWidth(ScriptMethodParams &params) {
	PARAMS1(ScriptDynamicSprite *, sds);
	params._result = AGS3::DynamicSprite_GetWidth(sds);
}

void DynamicSprite::Create(ScriptMethodParams &params) {
	PARAMS3(int, width, int, height, int, alphaChannel);
	params._result = AGS3::DynamicSprite_Create(width, height, alphaChannel);
}

void DynamicSprite::CreateFromBackground(ScriptMethodParams &params) {
	PARAMS5(int, frame, int, x1, int, y1, int, width, int, height);
	params._result = AGS3::DynamicSprite_CreateFromBackground(frame, x1, y1, width, height);
}

void DynamicSprite::CreateFromDrawingSurface(ScriptMethodParams &params) {
	PARAMS5(ScriptDrawingSurface *, sds, int, x, int, y, int, width, int, height);
	params._result = AGS3::DynamicSprite_CreateFromDrawingSurface(sds, x, y, width, height);
}

void DynamicSprite::CreateFromExistingSprite_Old(ScriptMethodParams &params) {
	PARAMS1(int, slot);
	params._result = AGS3::DynamicSprite_CreateFromExistingSprite_Old(slot);
}

void DynamicSprite::CreateFromExistingSprite(ScriptMethodParams &params) {
	PARAMS2(int, slot, int, preserveAlphaChannel);
	params._result = AGS3::DynamicSprite_CreateFromExistingSprite(slot, preserveAlphaChannel);
}

void DynamicSprite::CreateFromFile(ScriptMethodParams &params) {
	PARAMS1(const char *, filename);
	params._result = AGS3::DynamicSprite_CreateFromFile(filename);
}

void DynamicSprite::CreateFromSaveGame(ScriptMethodParams &params) {
	PARAMS3(int, sgslot, int, width, int, height);
	params._result = AGS3::DynamicSprite_CreateFromSaveGame(sgslot, width, height);
}

void DynamicSprite::CreateFromScreenShot(ScriptMethodParams &params) {
	PARAMS2(int, width, int, height);
	params._result = AGS3::DynamicSprite_CreateFromScreenShot(width, height);
}

} // namespace Core
} // namespace Plugins
} // namespace AGS3
