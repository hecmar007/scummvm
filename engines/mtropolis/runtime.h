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

#ifndef MTROPOLIS_RUNTIME_H
#define MTROPOLIS_RUNTIME_H

#include "common/array.h"
#include "common/language.h"
#include "common/platform.h"
#include "common/ptr.h"
#include "common/stream.h"
#include "common/hashmap.h"
#include "common/hash-str.h"

#include "graphics/pixelformat.h"

#include "mtropolis/data.h"
#include "mtropolis/debug.h"
#include "mtropolis/vthread.h"

class OSystem;

namespace Graphics {

struct WinCursorGroup;
class MacCursor;
class MacFontManager;
class Cursor;
struct PixelFormat;
struct Surface;

} // End of namespace Graphics

namespace MTropolis {

class Asset;
class CursorGraphic;
class CursorGraphicCollection;
struct DynamicValueReadProxy;
struct DynamicValueWriteProxy;
class Element;
class MessageDispatch;
class MiniscriptThread;
class Modifier;
class ObjectLinkingScope;
class PlugInModifier;
class RuntimeObject;
class PlugIn;
class Project;
class Runtime;
class Structural;
class VisualElement;
class Window;
struct IMessageConsumer;
struct IModifierContainer;
struct IModifierFactory;
struct IPlugInModifierFactory;
struct IPlugInModifierFactoryAndDataFactory;
struct IStructuralReferenceVisitor;
struct MessageProperties;
struct ModifierLoaderContext;
struct PlugInModifierLoaderContext;
template<typename TElement, typename TElementData> class ElementFactory;

char invariantToLower(char c);
Common::String toCaseInsensitive(const Common::String &str);
bool caseInsensitiveEqual(const Common::String &str1, const Common::String &str2);

enum ColorDepthMode {
	kColorDepthMode1Bit,
	kColorDepthMode2Bit,
	kColorDepthMode4Bit,
	kColorDepthMode8Bit,
	kColorDepthMode16Bit,
	kColorDepthMode32Bit,

	kColorDepthModeCount,

	kColorDepthModeInvalid,
};

enum TransitionType {
	kTransitionTypeNone = 0,
	kTransitionTypePatternDissolve = 0x0406,
	kTransitionTypeRandomDissolve = 0x0410, // No steps
	kTransitionTypeFade = 0x041a,
	kTransitionTypeSlide = 0x03e8, // Directional
	kTransitionTypePush = 0x03f2,  // Directional
	kTransitionTypeZoom = 0x03fc,
	kTransitionTypeWipe = 0x0424, // Directional
};

enum TransitionDirection {
	kTransitionDirectionUp = 0x385,
	kTransitionDirectionDown = 0x385,
	kTransitionDirectionLeft = 0x386,
	kTransitionDirectionRight = 0x387,
};

namespace DynamicValueTypes {

enum DynamicValueType {
	kInvalid,

	kNull,
	kInteger,
	kFloat,
	kPoint,
	kIntegerRange,
	kBoolean,
	kVector,
	kLabel,
	kEvent,
	kVariableReference,
	kIncomingData,
	kString,
	kList,
	kObject,
	kReadProxy,
	kWriteProxy,

	kEmpty,
};

} // End of namespace DynamicValuesTypes

namespace AttributeIDs {

enum AttributeID {
	kAttribCache = 55,
	kAttribDirect = 56,
	kAttribVisible = 58,
	kAttribLayer = 24,
	kAttribPosition = 1,
	kAttribWidth = 2,
	kAttribHeight = 3,
};

} // End of namespace AttributeIDs

namespace EventIDs {

enum EventID {
	kNothing = 0,

	kElementEnableEdit = 207,
	kElementDisableEdit = 220,
	kElementSelect = 209,
	kElementDeselect = 210,
	kElementToggleSelect = 213,
	kElementUpdatedCalculated = 219,
	kElementShow = 222,
	kElementHide = 223,

	kElementScrollUp = 1001,
	kElementScrollDown = 1002,
	kElementScrollRight = 1005,
	kElementScrollLeft = 1006,

	kMotionStarted = 501,
	kMotionEnded = 502,

	kTransitionStarted = 503,
	kTransitionEnded = 504,

	kMouseUp = 301,
	kMouseDown = 302,
	kMouseOver = 303,
	kMouseOutside = 304,
	kMouseTrackedInside = 305,
	kMouseTracking = 306,
	kMouseTrackedOutside = 307,
	kMouseUpInside = 309,
	kMouseUpOutside = 310,

	kSceneStarted = 101,
	kSceneEnded = 102,
	kSceneDeactivated = 103,
	kSceneReactivated = 104,
	kSceneTransitionEnded = 506,

	kSharedSceneReturnedToScene = 401,
	kSharedSceneSceneChanged = 402,
	kSharedSceneNoNextScene = 403,
	kSharedSceneNoPrevScene = 404,

	kParentEnabled = 2001,
	kParentDisabled = 2002,
	kParentChanged = 227,

	kPreloadMedia = 1701,
	kFlushMedia = 1703,
	kPrerollMedia = 1704,

	kCloseProject = 1601,

	kUserTimeout = 1801,
	kProjectStarted = 1802,
	kProjectEnded = 1803,
	kFlushAllMedia = 1804,

	kAttribGet = 1300,
	kAttribSet = 1200,

	kClone = 226,
	kKill = 228,

	kPlay = 201,
	kStop = 202,
	kPause = 801,
	kUnpause = 802,
	kTogglePause = 803,
	kAtFirstCel = 804,
	kAtLastCel = 805,


	kAuthorMessage = 900,
};

bool isCommand(EventID eventID);

} // End of namespace EventIDs

struct Point16 {
	int16 x;
	int16 y;

	bool load(const Data::Point &point);

	inline bool operator==(const Point16 &other) const {
		return x == other.x && y == other.y;
	}

	inline bool operator!=(const Point16 &other) const {
		return !((*this) == other);
	}

	inline static Point16 create(int16 x, int16 y) {
		Point16 result;
		result.x = x;
		result.y = y;
		return result;
	}
};

struct Rect16 {
	int16 top;
	int16 left;
	int16 bottom;
	int16 right;

	bool load(const Data::Rect &rect);

	inline bool operator==(const Rect16 &other) const {
		return top == other.top && left == other.left && bottom == other.bottom && right == other.right;
	}

	inline bool operator!=(const Rect16 &other) const {
		return !((*this) == other);
	}

	inline uint16 getWidth() const { return static_cast<uint16>(right - left); }
	inline uint16 getHeight() const { return static_cast<uint16>(bottom - top); }
	inline static Rect16 create(int16 left, int16 top, int16 right, int16 bottom) {
		Rect16 result;
		result.left = left;
		result.top = top;
		result.right = right;
		result.bottom = bottom;
		return result;
	}
};

struct IntRange {
	int32 min;
	int32 max;

	bool load(const Data::IntRange &range);

	inline bool operator==(const IntRange &other) const {
		return min == other.min && max == other.max;
	}

	inline bool operator!=(const IntRange &other) const {
		return !((*this) == other);
	}
};

struct Label {
	uint32 superGroupID;
	uint32 id;

	bool load(const Data::Label &label);

	inline bool operator==(const Label &other) const {
		return superGroupID == other.superGroupID && id == other.id;
	}

	inline bool operator!=(const Label &other) const {
		return !((*this) == other);
	}
};

struct Event {
	EventIDs::EventID eventType;
	uint32 eventInfo;

	static Event create();
	static Event create(EventIDs::EventID eventType, uint32 eventInfo);

	// Returns true if this event, interpreted as a filter, recognizes another event.
	// Handles cases where eventInfo is ignored (hopefully).
	bool respondsTo(const Event &otherEvent) const;

	bool load(const Data::Event &data);

	inline bool operator==(const Event &other) const {
		return eventType == other.eventType && eventInfo == other.eventInfo;
	}

	inline bool operator!=(const Event &other) const {
		return !((*this) == other);
	}
};

struct VarReference {
	uint32 guid;
	Common::String *source;

	inline bool operator==(const VarReference &other) const {
		return guid == other.guid && (*source) == (*other.source);
	}

	inline bool operator!=(const VarReference &other) const {
		return !((*this) == other);
	}
};

struct AngleMagVector {
	double angleRadians;
	double magnitude;

	inline bool operator==(const AngleMagVector &other) const {
		return angleRadians == other.angleRadians && magnitude == other.magnitude;
	}

	inline bool operator!=(const AngleMagVector &other) const {
		return !((*this) == other);
	}
};

struct ColorRGB8 {
	uint8 r;
	uint8 g;
	uint8 b;

	bool load(const Data::ColorRGB16 &color);
};

struct MessageFlags {
	MessageFlags();

	bool relay : 1;
	bool cascade : 1;
	bool immediate : 1;
};

struct DynamicValue;
struct DynamicList;

struct IDynamicValueReadInterface {
	virtual bool read(DynamicValue &dest, const void *objectRef, uintptr_t ptrOrOffset) const = 0;
	virtual bool readAttrib(DynamicValue &dest, const void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib) const = 0;
	virtual bool readAttribIndexed(DynamicValue &dest, const void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib, const DynamicValue &index) const = 0;
};

struct IDynamicValueWriteInterface {
	virtual bool write(const DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset) const = 0;
	virtual bool refAttrib(DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib) const = 0;
	virtual bool refAttribIndexed(DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib, const DynamicValue &index) const = 0;
};

struct DynamicValueReadProxy {
	uintptr_t ptrOrOffset;
	const void *objectRef;
	IDynamicValueReadInterface *ifc;
};

struct DynamicValueWriteProxy {
	uintptr_t ptrOrOffset;
	void *objectRef;
	IDynamicValueWriteInterface *ifc;
};

template<class TClass, bool (TClass::*TWriteMethod)(const DynamicValue &dest)>
struct DynamicValueWriteFuncHelper : public IDynamicValueWriteInterface {
	bool write(const DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset) const override {
		return (static_cast<TClass *>(objectRef)->*TWriteMethod)(dest);
	}
	bool refAttrib(DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib) const override {
		return false;
	}
	bool refAttribIndexed(DynamicValue &dest, void *objectRef, uintptr_t ptrOrOffset, const Common::String &attrib, const DynamicValue &index) const override {
		return false;
	}

	static DynamicValueWriteProxy create(TClass *obj) {
		DynamicValueWriteProxy proxy;
		proxy.ptrOrOffset = 0;
		proxy.objectRef = obj;
		proxy.ifc = &_instance;
		return proxy;
	}

private:
	static DynamicValueWriteFuncHelper _instance;
};

template<class TClass, bool (TClass::*TWriteMethod)(const DynamicValue &dest)>
DynamicValueWriteFuncHelper<TClass, TWriteMethod> DynamicValueWriteFuncHelper<TClass, TWriteMethod>::_instance;

class DynamicListContainerBase {
public:
	virtual ~DynamicListContainerBase();
	virtual bool setAtIndex(size_t index, const DynamicValue &dynValue) = 0;
	virtual bool getAtIndex(size_t index, DynamicValue &dynValue) const = 0;
	virtual void setFrom(const DynamicListContainerBase &other) = 0; // Only supports setting same type!
	virtual const void *getConstArrayPtr() const = 0;
	virtual size_t getSize() const = 0;
	virtual bool compareEqual(const DynamicListContainerBase &other) const = 0;
	virtual DynamicListContainerBase *clone() const = 0;
};

struct DynamicListDefaultSetter {
	static void defaultSet(int32 &value);
	static void defaultSet(double &value);
	static void defaultSet(Point16 &value);
	static void defaultSet(IntRange &value);
	static void defaultSet(bool &value);
	static void defaultSet(AngleMagVector &value);
	static void defaultSet(Label &value);
	static void defaultSet(Event &value);
	static void defaultSet(Common::String &value);
	static void defaultSet(Common::SharedPtr<DynamicList> &value);
	static void defaultSet(Common::WeakPtr<RuntimeObject> &value);
};

struct DynamicListValueImporter {
	static bool importValue(const DynamicValue &dynValue, const int32 *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const double *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Point16 *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const IntRange *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const bool *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const AngleMagVector *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Label *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Event *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Common::String *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Common::SharedPtr<DynamicList> *&outPtr);
	static bool importValue(const DynamicValue &dynValue, const Common::WeakPtr<RuntimeObject> *&outPtr);
};

struct DynamicListValueExporter {
	static void exportValue(DynamicValue &dynValue, const int32 &value);
	static void exportValue(DynamicValue &dynValue, const double &value);
	static void exportValue(DynamicValue &dynValue, const Point16 &value);
	static void exportValue(DynamicValue &dynValue, const IntRange &value);
	static void exportValue(DynamicValue &dynValue, const bool &value);
	static void exportValue(DynamicValue &dynValue, const AngleMagVector &value);
	static void exportValue(DynamicValue &dynValue, const Label &value);
	static void exportValue(DynamicValue &dynValue, const Event &value);
	static void exportValue(DynamicValue &dynValue, const Common::String &value);
	static void exportValue(DynamicValue &dynValue, const Common::SharedPtr<DynamicList> &value);
	static void exportValue(DynamicValue &dynValue, const Common::WeakPtr<RuntimeObject> &value);
};

template<class T>
class DynamicListContainer : public DynamicListContainerBase {
public:
	bool setAtIndex(size_t index, const DynamicValue &dynValue) override;
	bool getAtIndex(size_t index, DynamicValue &dynValue) const override;
	void setFrom(const DynamicListContainerBase &other) override;
	const void *getConstArrayPtr() const override;
	size_t getSize() const override;
	bool compareEqual(const DynamicListContainerBase &other) const override;
	DynamicListContainerBase *clone() const override;

private:
	Common::Array<T> _array;
};

template<>
class DynamicListContainer<void> : public DynamicListContainerBase {
public:
	DynamicListContainer();

	bool setAtIndex(size_t index, const DynamicValue &dynValue) override;
	bool getAtIndex(size_t index, DynamicValue &dynValue) const override;
	void setFrom(const DynamicListContainerBase &other) override;
	const void *getConstArrayPtr() const override;
	size_t getSize() const override;
	bool compareEqual(const DynamicListContainerBase &other) const override;
	DynamicListContainerBase *clone() const override;

public:
	size_t _size;
};

template<>
class DynamicListContainer<VarReference> : public DynamicListContainerBase {
public:
	bool setAtIndex(size_t index, const DynamicValue &dynValue) override;
	bool getAtIndex(size_t index, DynamicValue &dynValue) const override;
	void setFrom(const DynamicListContainerBase &other) override;
	const void *getConstArrayPtr() const override;
	size_t getSize() const override;
	bool compareEqual(const DynamicListContainerBase &other) const override;
	DynamicListContainerBase *clone() const override;

private:
	void rebuildStringPointers();

	Common::Array<VarReference> _array;
	Common::Array<Common::String> _strings;
};

template<class T>
bool DynamicListContainer<T>::setAtIndex(size_t index, const DynamicValue &dynValue) {
	const T *valuePtr = nullptr;
	if (!DynamicListValueImporter::importValue(dynValue, valuePtr))
		return false;

	_array.reserve(index + 1);
	if (_array.size() <= index) {
		if (_array.size() < index) {
			T defaultValue;
			DynamicListDefaultSetter::defaultSet(defaultValue);
			while (_array.size() < index) {
				_array.push_back(defaultValue);
			}
		}
		_array.push_back(*valuePtr);
	} else {
		_array[index] = *valuePtr;
	}

	return true;
}

template<class T>
bool DynamicListContainer<T>::getAtIndex(size_t index, DynamicValue &dynValue) const {
	if (index >= _array.size())
		return false;

	DynamicListValueExporter::exportValue(dynValue, _array[index]);
	return true;
}

template<class T>
void DynamicListContainer<T>::setFrom(const DynamicListContainerBase &other) {
	_array = static_cast<const DynamicListContainer<T> &>(other)._array;
}

template<class T>
const void *DynamicListContainer<T>::getConstArrayPtr() const {
	return &_array;
}

template<class T>
size_t DynamicListContainer<T>::getSize() const {
	return _array.size();
}

template<class T>
bool DynamicListContainer<T>::compareEqual(const DynamicListContainerBase &other) const {
	const DynamicListContainer<T> &otherTyped = static_cast<const DynamicListContainer<T> &>(other);
	return _array == otherTyped._array;
}

template<class T>
DynamicListContainerBase *DynamicListContainer<T>::clone() const {
	return new DynamicListContainer<T>(*this);
}

struct DynamicList {
	DynamicList();
	DynamicList(const DynamicList &other);
	~DynamicList();

	DynamicValueTypes::DynamicValueType getType() const;

	const Common::Array<int32> &getInt() const;
	const Common::Array<double> &getFloat() const;
	const Common::Array<Point16> &getPoint() const;
	const Common::Array<IntRange> &getIntRange() const;
	const Common::Array<AngleMagVector> &getVector() const;
	const Common::Array<Label> &getLabel() const;
	const Common::Array<Event> &getEvent() const;
	const Common::Array<VarReference> &getVarReference() const;
	const Common::Array<Common::String> &getString() const;
	const Common::Array<bool> &getBool() const;

	bool getAtIndex(size_t index, DynamicValue &value) const;
	bool setAtIndex(size_t index, const DynamicValue &value);
	size_t getSize() const;

	static bool dynamicValueToIndex(size_t &outIndex, const DynamicValue &value);

	DynamicList &operator=(const DynamicList &other);

	bool operator==(const DynamicList &other) const;
	inline bool operator!=(const DynamicList &other) const {
		return !((*this) == other);
	}

	void swap(DynamicList &other);

	Common::SharedPtr<DynamicList> clone() const;

private:
	void clear();
	void initFromOther(const DynamicList &other);
	bool changeToType(DynamicValueTypes::DynamicValueType type);

	DynamicValueTypes::DynamicValueType _type;
	DynamicListContainerBase *_container;
};

// Dynamic value container.  Somewhat importantly, lists stored in dynamic values
// are BY REFERENCE and must be cloned as necessary.
struct DynamicValue {
	DynamicValue();
	DynamicValue(const DynamicValue &other);
	~DynamicValue();

	bool load(const Data::InternalTypeTaggedValue &data, const Common::String &varSource, const Common::String &varString);
	bool load(const Data::PlugInTypeTaggedValue &data);

	DynamicValueTypes::DynamicValueType getType() const;

	const int32 &getInt() const;
	const double &getFloat() const;
	const Point16 &getPoint() const;
	const IntRange &getIntRange() const;
	const AngleMagVector &getVector() const;
	const Label &getLabel() const;
	const Event &getEvent() const;
	const VarReference &getVarReference() const;
	const Common::String &getString() const;
	const bool &getBool() const;
	const Common::SharedPtr<DynamicList> &getList() const;
	const Common::WeakPtr<RuntimeObject> &getObject() const;
	const DynamicValueReadProxy &getReadProxy() const;
	const DynamicValueWriteProxy &getWriteProxy() const;
	const Common::SharedPtr<DynamicList> &getReadProxyList() const;
	const Common::SharedPtr<DynamicList> &getWriteProxyList() const;

	void clear();

	void setInt(int32 value);
	void setFloat(double value);
	void setPoint(const Point16 &value);
	void setIntRange(const IntRange &value);
	void setVector(const AngleMagVector &value);
	void setLabel(const Label &value);
	void setEvent(const Event &value);
	void setVarReference(const VarReference &value);
	void setString(const Common::String &value);
	void setBool(bool value);
	void setList(const Common::SharedPtr<DynamicList> &value);
	void setObject(const Common::WeakPtr<RuntimeObject> &value);
	void setReadProxy(const Common::SharedPtr<DynamicList> &list, const DynamicValueReadProxy &readProxy);
	void setWriteProxy(const Common::SharedPtr<DynamicList> &list, const DynamicValueWriteProxy &writeProxy);

	DynamicValue &operator=(const DynamicValue &other);

	bool operator==(const DynamicValue &other) const;
	inline bool operator!=(const DynamicValue &other) const {
		return !((*this) == other);
	}

	void swap(DynamicValue &other);

private:
	union ValueUnion {
		double asFloat;
		int32 asInt;
		IntRange asIntRange;
		AngleMagVector asVector;
		Label asLabel;
		VarReference asVarReference;
		Event asEvent;
		Point16 asPoint;
		bool asBool;
		DynamicValueReadProxy asReadProxy;
		DynamicValueWriteProxy asWriteProxy;
	};

	template<class T>
	void internalSwap(T &a, T &b) {
		T temp = a;
		a = b;
		b = temp;
	}

	void initFromOther(const DynamicValue &other);

	DynamicValueTypes::DynamicValueType _type;
	ValueUnion _value;
	Common::String _str;
	Common::SharedPtr<DynamicList> _list;
	Common::WeakPtr<RuntimeObject> _obj;
};

struct MessengerSendSpec {
	MessengerSendSpec();
	bool load(const Data::Event &dataEvent, uint32 dataMessageFlags, const Data::InternalTypeTaggedValue &dataLocator, const Common::String &dataWithSource, const Common::String &dataWithString, uint32 dataDestination);
	bool load(const Data::PlugInTypeTaggedValue &dataEvent, const MessageFlags &dataMessageFlags, const Data::PlugInTypeTaggedValue &dataWith, uint32 dataDestination);

	void linkInternalReferences(ObjectLinkingScope *outerScope);
	void visitInternalReferences(IStructuralReferenceVisitor *visitor);
	void resolveDestination(Runtime *runtime, Modifier *sender, Common::WeakPtr<Structural> &outStructuralDest, Common::WeakPtr<Modifier> &outModifierDest) const;

	void sendFromMessenger(Runtime *runtime, Modifier *sender) const;

	Event send;
	MessageFlags messageFlags;
	DynamicValue with;
	uint32 destination; // May be a MessageDestination or GUID

	enum LinkType {
		kLinkTypeNotYetLinked,
		kLinkTypeStructural,
		kLinkTypeModifier,
		kLinkTypeCoded,
		kLinkTypeUnresolved,
	};

	LinkType _linkType;
	Common::WeakPtr<Structural> resolvedStructuralDest;
	Common::WeakPtr<Modifier> resolvedModifierDest;

private:
	void resolveHierarchyStructuralDestination(Runtime *runtime, Modifier *sender, Common::WeakPtr<Structural> &outStructuralDest, Common::WeakPtr<Modifier> &outModifierDest, bool (*compareFunc)(Structural *structural)) const;
	static bool isSceneFilter(Structural *section);
	static bool isSectionFilter(Structural *section);
	static bool isSubsectionFilter(Structural *section);
	static bool isElementFilter(Structural *section);
};

struct Message {
	Message();

	Event evt;
	DynamicValue data;
};

enum MessageDestination {
	kMessageDestNone = 0,

	kMessageDestSharedScene = 0x65,
	kMessageDestScene = 0x66,
	kMessageDestSection = 0x67,
	kMessageDestProject = 0x68,
	kMessageDestActiveScene = 0x69,
	kMessageDestElementsParent = 0x6a,
	kMessageDestChildren = 0x6b,	// Saw this somewhere but can't find it any more?
	kMessageDestModifiersParent = 0x6c,
	kMessageDestSubsection = 0x6d,

	kMessageDestElement = 0xc9,
	kMessageDestSourcesParent = 0xcf,

	kMessageDestBehavior = 0xd4,
	kMessageDestNextElement = 0xd1,
	kMessageDestPrevElement = 0xd2,
	kMessageDestBehaviorsParent = 0xd3,
};

struct SegmentDescription {
	int volumeID;
	Common::String filePath;
	Common::SeekableReadStream *stream;
};

struct IPlugInModifierRegistrar {
	virtual void registerPlugInModifier(const char *name, const Data::IPlugInModifierDataFactory *loader, const IPlugInModifierFactory *factory) = 0;
	void registerPlugInModifier(const char *name, const IPlugInModifierFactoryAndDataFactory *loaderFactory);
};

class PlugIn {
public:
	virtual ~PlugIn();

	virtual void registerModifiers(IPlugInModifierRegistrar *registrar) const = 0;
};

struct ProjectResources {
	virtual ~ProjectResources();
};

class CursorGraphicCollection {
public:
	CursorGraphicCollection();
	~CursorGraphicCollection();

	void addWinCursorGroup(uint32 cursorGroupID, const Common::SharedPtr<Graphics::WinCursorGroup> &cursorGroup);
	void addMacCursor(uint32 cursorID, const Common::SharedPtr<Graphics::MacCursor> &cursor);

private:
	Common::HashMap<uint32, Graphics::Cursor *> _cursorGraphics;

	Common::Array<Common::SharedPtr<Graphics::WinCursorGroup> > _winCursorGroups;
	Common::Array<Common::SharedPtr<Graphics::MacCursor> > _macCursors;
};

class ProjectDescription {
public:
	ProjectDescription();
	~ProjectDescription();

	void addSegment(int volumeID, const char *filePath);
	void addSegment(int volumeID, Common::SeekableReadStream *stream);
	const Common::Array<SegmentDescription> &getSegments() const;

	void addPlugIn(const Common::SharedPtr<PlugIn> &plugIn);
	const Common::Array<Common::SharedPtr<PlugIn> > &getPlugIns() const;

	void setResources(const Common::SharedPtr<ProjectResources> &resources);
	const Common::SharedPtr<ProjectResources> &getResources() const;

	void setCursorGraphics(const Common::SharedPtr<CursorGraphicCollection> &cursorGraphics);

	void setLanguage(const Common::Language &language);
	const Common::Language &getLanguage() const;

private:
	Common::Array<SegmentDescription> _segments;
	Common::Array<Common::SharedPtr<PlugIn> > _plugIns;
	Common::SharedPtr<ProjectResources> _resources;
	Common::SharedPtr<CursorGraphicCollection> _cursorGraphics;
	Common::Language _language;
};

struct VolumeState {
	Common::String name;
	int volumeID;
	bool isMounted;
};

class ObjectLinkingScope {
public:
	ObjectLinkingScope();
	~ObjectLinkingScope();

	void setParent(ObjectLinkingScope *parent);
	void addObject(uint32 guid, const Common::String &name, const Common::WeakPtr<RuntimeObject> &object);
	Common::WeakPtr<RuntimeObject> resolve(uint32 staticGUID) const;
	Common::WeakPtr<RuntimeObject> resolve(const Common::String &name, bool isNameAlreadyInsensitive) const;
	Common::WeakPtr<RuntimeObject> resolve(uint32 staticGUID, const Common::String &name, bool isNameAlreadyInsensitive) const;

	void reset();

private:
	Common::HashMap<uint32, Common::WeakPtr<RuntimeObject> > _guidToObject;
	Common::HashMap<Common::String, Common::WeakPtr<RuntimeObject> > _nameToObject;
	ObjectLinkingScope *_parent;
};

struct LowLevelSceneStateTransitionAction {
	enum ActionType {
		kLoad,
		kUnload,
		kSendMessage,
	};

	explicit LowLevelSceneStateTransitionAction(const Common::SharedPtr<MessageDispatch> &msg);
	explicit LowLevelSceneStateTransitionAction(ActionType actionType);
	LowLevelSceneStateTransitionAction(const LowLevelSceneStateTransitionAction &other);
	LowLevelSceneStateTransitionAction(const Common::SharedPtr<Structural> &scene, ActionType actionType);

	ActionType getActionType() const;
	const Common::SharedPtr<Structural> &getScene() const;
	const Common::SharedPtr<MessageDispatch> &getMessage() const;

	LowLevelSceneStateTransitionAction &operator=(const LowLevelSceneStateTransitionAction &other);

private:
	ActionType _actionType;
	Common::SharedPtr<Structural> _scene;
	Common::SharedPtr<MessageDispatch> _msg;
};

struct HighLevelSceneTransition {
	enum Type {
		kTypeReturn,
		kTypeChangeToScene,
	};

	HighLevelSceneTransition(const Common::SharedPtr<Structural> &scene, Type type, bool addToDestinationScene, bool addToReturnList);

	Common::SharedPtr<Structural> scene;
	Type type;
	bool addToDestinationScene;
	bool addToReturnList;
};

struct SceneTransitionEffect {
	uint32 duration; // 6000000 is maximum
	uint16 steps;
	TransitionType transitionType;
	TransitionDirection transitionDirection;
};

class MessageDispatch {
public:
	MessageDispatch(const Common::SharedPtr<MessageProperties> &msgProps, Structural *root, bool cascade, bool relay, bool couldBeCommand);
	MessageDispatch(const Common::SharedPtr<MessageProperties> &msgProps, Modifier *root, bool cascade, bool relay, bool couldBeCommand);

	bool isTerminated() const;
	VThreadState continuePropagating(Runtime *runtime);

private:
	struct PropagationStack {
		union Ptr {
			Structural *structural;
			Modifier *modifier;
			IModifierContainer *modifierContainer;
		};

		enum PropagationStage {
			kStageSendToModifier,
			kStageSendToModifierContainer,

			kStageSendToStructuralSelf,
			kStageSendToStructuralModifiers,
			kStageSendToStructuralChildren,

			kStageSendCommand,
		};

		PropagationStage propagationStage;
		size_t index;
		Ptr ptr;
	};

	Common::Array<PropagationStack> _propagationStack;
	Common::SharedPtr<MessageProperties> _msg;
	bool _cascade; // Traverses structure tree
	bool _relay;   // Fire on multiple modifiers
	bool _terminated;
	bool _isCommand;
};

class Scheduler;

class ScheduledEvent : Common::NonCopyable {
	friend class Scheduler;

public:
	void cancel();
	uint64 getScheduledTime() const;
	void activate(Runtime *runtime) const;

private:
	ScheduledEvent(void *obj, void (*activateFunc)(void *, Runtime *), uint64 scheduledTime, Scheduler *scheduler);

	void *_obj;
	void (*_activateFunc)(void *obj, Runtime *runtime);

	uint64 _scheduledTime;
	Scheduler *_scheduler;
};

class Scheduler {
	friend class ScheduledEvent;

public:
	Scheduler();
	~Scheduler();

	template<class T, void (T::*TMethodPtr)(Runtime *)>
	Common::SharedPtr<ScheduledEvent> scheduleMethod(uint64 scheduledTime, T* obj) {
		Common::SharedPtr<ScheduledEvent> evt(new ScheduledEvent(obj, Scheduler::methodActivateHelper<T, TMethodPtr>, scheduledTime, this));
		insertEvent(evt);
		return evt;
	}

	Common::SharedPtr<ScheduledEvent> getFirstEvent() const;
	void descheduleFirstEvent();

private:
	template<class T, void (T::*TMethodPtr)(Runtime *)>
	static void methodActivateHelper(void *obj, Runtime *runtime) {
		(static_cast<T *>(obj)->*TMethodPtr)(runtime);
	}

	void insertEvent(const Common::SharedPtr<ScheduledEvent> &evt);
	void removeEvent(const ScheduledEvent *evt);

	Common::Array<Common::SharedPtr<ScheduledEvent>> _events;
};

class Runtime {
public:
	explicit Runtime(OSystem *system);

	bool runFrame();
	void drawFrame();
	void queueProject(const Common::SharedPtr<ProjectDescription> &desc);

	void addVolume(int volumeID, const char *name, bool isMounted);
	void addSceneStateTransition(const HighLevelSceneTransition &transition);

	Project *getProject() const;

	void postConsumeMessageTask(IMessageConsumer *msgConsumer, const Common::SharedPtr<MessageProperties> &msg);
	void postConsumeCommandTask(Structural *structural, const Common::SharedPtr<MessageProperties> &msg);

	uint32 allocateRuntimeGUID();

	void addWindow(const Common::SharedPtr<Window> &window);
	void removeWindow(Window *window);

	// Sets up a supported display mode
	void setupDisplayMode(ColorDepthMode displayMode, const Graphics::PixelFormat &pixelFormat);

	// Switches to a specified display mode.  Returns true if the mode was actually changed.  If so, all windows will need
	// to be recreated.
	bool switchDisplayMode(ColorDepthMode realDisplayMode, ColorDepthMode fakeDisplayMode);
	void setDisplayResolution(uint16 width, uint16 height);
	void getDisplayResolution(uint16 &outWidth, uint16 &outHeight) const;

	ColorDepthMode getRealColorDepth() const;
	ColorDepthMode getFakeColorDepth() const;	// Fake color depth that will be reported to scripts

	const Graphics::PixelFormat &getRenderPixelFormat() const;

	const Common::SharedPtr<Graphics::MacFontManager> &getMacFontManager() const;

	const Common::SharedPtr<Structural> &getActiveMainScene() const;
	const Common::SharedPtr<Structural> &getActiveSharedScene() const;

	bool mustDraw() const;

	uint64 getRealTime() const;
	uint64 getPlayTime() const;

	VThread &getVThread() const;

	// Sending a message on the VThread means "immediately"
	void sendMessageOnVThread(const Common::SharedPtr<MessageDispatch> &dispatch);
	void queueMessage(const Common::SharedPtr<MessageDispatch> &dispatch);

	Scheduler &getScheduler();

	void getScenesInRenderOrder(Common::Array<Structural *> &scenes) const;

	void instantiateIfAlias(Common::SharedPtr<Modifier> &modifier, const Common::WeakPtr<RuntimeObject> &relinkParent);

#ifdef MTROPOLIS_DEBUG_ENABLE
	void debugSetEnabled(bool enabled);
	void debugBreak();
	Debugger *debugGetDebugger() const;
#endif

private:
	enum SceneTransitionState {
		kSceneTransitionStateNotTransitioning,
		kSceneTransitionStateWaitingForDraw,
		kSceneTransitionStateDrawingTargetFrame,
		kSceneTransitionStateTransitioning,
	};

	struct SceneStackEntry {
		SceneStackEntry();

		Common::SharedPtr<Structural> scene;
	};

	struct Teardown {
		Common::WeakPtr<Structural> structural;
		bool onlyRemoveChildren;
	};

	struct SceneReturnListEntry {
		Common::SharedPtr<Structural> scene;
		bool isAddToDestinationSceneTransition;
	};

	struct DispatchMethodTaskData {
		Common::SharedPtr<MessageDispatch> dispatch;
	};

	struct ConsumeMessageTaskData {
		IMessageConsumer *consumer;
		Common::SharedPtr<MessageProperties> message;
	};

	struct ConsumeCommandTaskData {
		Structural *structural;
		Common::SharedPtr<MessageProperties> message;
	};

	static Common::SharedPtr<Structural> findDefaultSharedSceneForScene(Structural *scene);
	void executeTeardown(const Teardown &teardown);
	void executeLowLevelSceneStateTransition(const LowLevelSceneStateTransitionAction &transitionAction);
	void executeHighLevelSceneTransition(const HighLevelSceneTransition &transition);
	void executeCompleteTransitionToScene(const Common::SharedPtr<Structural> &scene);
	void executeSharedScenePostSceneChangeActions();

	void recursiveDeactivateStructural(Structural *structural);
	void recursiveActivateStructural(Structural *structural);

	void queueEventAsLowLevelSceneStateTransitionAction(const Event &evt, Structural *root, bool cascade, bool relay);

	void loadScene(const Common::SharedPtr<Structural> &scene);

	void ensureMainWindowExists();

	void unloadProject();
	void refreshPlayTime();	// Updates play time to be in sync with the system clock.  Used so that events occurring after storage access don't skip.

	VThreadState dispatchMessageTask(const DispatchMethodTaskData &data);
	VThreadState consumeMessageTask(const ConsumeMessageTaskData &data);
	VThreadState consumeCommandTask(const ConsumeCommandTaskData &data);

	Common::Array<VolumeState> _volumes;
	Common::SharedPtr<ProjectDescription> _queuedProjectDesc;
	Common::SharedPtr<Project> _project;
	Common::ScopedPtr<VThread> _vthread;
	Common::Array<Common::SharedPtr<MessageDispatch> > _messageQueue;
	ObjectLinkingScope _rootLinkingScope;

	Common::Array<Teardown> _pendingTeardowns;
	Common::Array<LowLevelSceneStateTransitionAction> _pendingLowLevelTransitions;
	Common::Array<HighLevelSceneTransition> _pendingSceneTransitions;
	Common::Array<SceneStackEntry> _sceneStack;
	Common::SharedPtr<Structural> _activeMainScene;
	Common::SharedPtr<Structural> _activeSharedScene;
	Common::Array<SceneReturnListEntry> _sceneReturnList;

	SceneTransitionState _sceneTransitionState;
	SceneTransitionEffect _sceneTransitionEffect;
	uint32 _sceneTransitionEndTime;

	Common::WeakPtr<Window> _mainWindow;
	Common::Array<Common::SharedPtr<Window> > _windows;

	Common::SharedPtr<Graphics::MacFontManager> _macFontMan;

	uint32 _nextRuntimeGUID;

	bool _displayModeSupported[kColorDepthModeCount];
	Graphics::PixelFormat _displayModePixelFormats[kColorDepthModeCount];
	ColorDepthMode _realDisplayMode;
	ColorDepthMode _fakeDisplayMode;
	uint16 _displayWidth;
	uint16 _displayHeight;

	uint64 _realTimeBase;
	uint64 _playTimeBase;

	uint32 _realTime;
	uint32 _playTime;

	Scheduler _scheduler;
	OSystem *_system;

#ifdef MTROPOLIS_DEBUG_ENABLE
	Common::SharedPtr<Debugger> _debugger;
#endif
};

struct IModifierContainer {
	virtual const Common::Array<Common::SharedPtr<Modifier> > &getModifiers() const = 0;
	virtual void appendModifier(const Common::SharedPtr<Modifier> &modifier) = 0;
};

class SimpleModifierContainer : public IModifierContainer {
public:
	const Common::Array<Common::SharedPtr<Modifier> > &getModifiers() const;
	void appendModifier(const Common::SharedPtr<Modifier> &modifier) override;

private:
	Common::Array<Common::SharedPtr<Modifier> > _modifiers;
};

class RuntimeObject {
	template<typename TElement, typename TElementData>
	friend class ElementFactory;

public:
	RuntimeObject();
	virtual ~RuntimeObject();

	uint32 getStaticGUID() const;
	uint32 getRuntimeGUID() const;

	void setRuntimeGUID(uint32 runtimeGUID);

	void setSelfReference(const Common::WeakPtr<RuntimeObject> &selfReference);
	const Common::WeakPtr<RuntimeObject> &getSelfReference() const;

	virtual bool isStructural() const;
	virtual bool isProject() const;
	virtual bool isSection() const;
	virtual bool isSubsection() const;
	virtual bool isModifier() const;
	virtual bool isElement() const;

	virtual bool readAttribute(MiniscriptThread *thread, DynamicValue &result, const Common::String &attrib);
	virtual bool readAttributeIndexed(MiniscriptThread *thread, DynamicValue &result, const Common::String &attrib, const DynamicValue &index);
	virtual bool writeRefAttribute(MiniscriptThread *thread, DynamicValueWriteProxy &writeProxy, const Common::String &attrib);
	virtual bool writeRefAttributeIndexed(MiniscriptThread *thread, DynamicValueWriteProxy &writeProxy, const Common::String &attrib, const DynamicValue &index);

protected:
	// This is the static GUID stored in the data, it is not guaranteed
	// to be globally unique at runtime.  In particular, cloning an object
	// and using aliased modifiers will cause multiple objects with the same
	// static GUID to exist with separate runtime GUIDs.
	uint32 _guid;
	uint32 _runtimeGUID;
	Common::WeakPtr<RuntimeObject> _selfReference;
};

struct MessageProperties {
	MessageProperties(const Event &evt, const DynamicValue &value, const Common::WeakPtr<RuntimeObject> &source);

	const Event &getEvent() const;
	const DynamicValue &getValue() const;
	const Common::WeakPtr<RuntimeObject> &getSource() const;

private:
	Event _evt;
	DynamicValue _value;
	Common::WeakPtr<RuntimeObject> _source;
};

struct IStructuralReferenceVisitor {
	virtual void visitChildStructuralRef(Common::SharedPtr<Structural> &structural) = 0;
	virtual void visitChildModifierRef(Common::SharedPtr<Modifier> &modifier) = 0;
	virtual void visitWeakStructuralRef(Common::WeakPtr<Structural> &structural) = 0;
	virtual void visitWeakModifierRef(Common::WeakPtr<Modifier> &modifier) = 0;
};

struct IMessageConsumer {
	// These should only be implemented as direct responses - child traversal is handled by the message propagation process
	virtual bool respondsToEvent(const Event &evt) const = 0;
	virtual VThreadState consumeMessage(Runtime *runtime, const Common::SharedPtr<MessageProperties> &msg) = 0;
};

class Structural : public RuntimeObject, public IModifierContainer, public IMessageConsumer, public IDebuggable {
public:
	Structural();
	virtual ~Structural();

	bool isStructural() const override;

	const Common::Array<Common::SharedPtr<Structural> > &getChildren() const;
	void addChild(const Common::SharedPtr<Structural> &child);
	void removeAllChildren();
	void removeAllModifiers();
	void removeChild(Structural *child);
	void removeAllAssets();

	void holdAssets(const Common::Array<Common::SharedPtr<Asset> > &assets);

	Structural *getParent() const;
	void setParent(Structural *parent);

	const Common::String &getName() const;

	const Common::Array<Common::SharedPtr<Modifier> > &getModifiers() const override;
	void appendModifier(const Common::SharedPtr<Modifier> &modifier) override;

	bool respondsToEvent(const Event &evt) const override;
	VThreadState consumeMessage(Runtime *runtime, const Common::SharedPtr<MessageProperties> &msg) override;

	void materializeSelfAndDescendents(Runtime *runtime, ObjectLinkingScope *outerScope);
	void materializeDescendents(Runtime *runtime, ObjectLinkingScope *outerScope);

	virtual VThreadState consumeCommand(Runtime *runtime, const Common::SharedPtr<MessageProperties> &msg);

	virtual void activate();
	virtual void deactivate();

#ifdef MTROPOLIS_DEBUG_ENABLE
	SupportStatus debugGetSupportStatus() const override;
	const Common::String &debugGetName() const override;
	Common::SharedPtr<DebugInspector> debugGetInspector() const override;
	Debugger *debugGetDebugger() const override;

	virtual DebugInspector *debugCreateInspector();
#endif

protected:
	virtual ObjectLinkingScope *getPersistentStructuralScope();
	virtual ObjectLinkingScope *getPersistentModifierScope();

	// If you override this, you must override visitInternalReferences too.
	virtual void linkInternalReferences(ObjectLinkingScope *outerScope);

	Structural *_parent;
	Common::Array<Common::SharedPtr<Structural> > _children;
	Common::Array<Common::SharedPtr<Modifier> > _modifiers;
	Common::String _name;

	Common::Array<Common::SharedPtr<Asset> > _assets;

#ifdef MTROPOLIS_DEBUG_ENABLE
	Common::SharedPtr<DebugInspector> _debugInspector;
	Debugger *_debugger;
#endif
};

struct ProjectPresentationSettings {
	ProjectPresentationSettings();

	uint16 width;
	uint16 height;
	uint32 bitsPerPixel;
};

struct AssetDefLoaderContext {
	Common::Array<Common::SharedPtr<Asset> > assets;
};

struct ChildLoaderContext {
	enum Type {
		kTypeUnknown,
		kTypeCountedModifierList,
		kTypeFlagTerminatedModifierList,
		kTypeProject,
		kTypeSection,
		kTypeFilteredElements,
	};

	struct FilteredElements {
		Structural *structural;
		bool (*filterFunc)(Data::DataObjectTypes::DataObjectType dataObjectType);
	};

	union ContainerUnion {
		IModifierContainer *modifierContainer;
		Structural *structural;
		FilteredElements filteredElements;
	};

	ChildLoaderContext();

	uint remainingCount;
	Type type;
	ContainerUnion containerUnion;
};

struct ChildLoaderStack {
	Common::Array<ChildLoaderContext> contexts;
};

class ProjectPlugInRegistry : public IPlugInModifierRegistrar  {
public:
	ProjectPlugInRegistry();

	void registerPlugInModifier(const char *name, const Data::IPlugInModifierDataFactory *dataFactory, const IPlugInModifierFactory *factory) override;

	const Data::PlugInModifierRegistry &getDataLoaderRegistry() const;
	const IPlugInModifierFactory *findPlugInModifierFactory(const char *name) const;

private:
	Data::PlugInModifierRegistry _dataLoaderRegistry;
	Common::HashMap<Common::String, const IPlugInModifierFactory *> _factoryRegistry;
};

struct IPostRenderSignalReceiver {
	virtual void onPostRender(Runtime *runtime, Project *project) = 0;
};

class PostRenderSignaller {
public:
	PostRenderSignaller();
	~PostRenderSignaller();

	void onPostRender(Runtime *runtime, Project *project);
	void addReceiver(IPostRenderSignalReceiver *receiver);
	void removeReceiver(IPostRenderSignalReceiver *receiver);

private:
	Common::Array<IPostRenderSignalReceiver *> _receivers;
};

struct ISegmentUnloadSignalReceiver {
	virtual void onSegmentUnloaded(int segmentIndex) = 0;
};

class SegmentUnloadSignaller {
public:
	explicit SegmentUnloadSignaller(Project *project, int segmentIndex);
	~SegmentUnloadSignaller();

	void onSegmentUnloaded();
	void addReceiver(ISegmentUnloadSignalReceiver *receiver);
	void removeReceiver(ISegmentUnloadSignalReceiver *receiver);

private:
	Project *_project;
	int _segmentIndex;
	Common::Array<ISegmentUnloadSignalReceiver *> _receivers;
};

class Project : public Structural {
public:
	explicit Project(Runtime *runtime);
	~Project();

	void loadFromDescription(const ProjectDescription &desc);
	void loadSceneFromStream(const Common::SharedPtr<Structural> &structural, uint32 streamID);

	Common::SharedPtr<Modifier> resolveAlias(uint32 aliasID) const;
	void materializeGlobalVariables(Runtime *runtime, ObjectLinkingScope *scope);

	const ProjectPresentationSettings &getPresentationSettings() const;

	bool isProject() const override;

	Common::WeakPtr<Asset> getAssetByID(uint32 assetID) const;
	size_t getSegmentForStreamIndex(size_t streamIndex) const;
	void openSegmentStream(int segmentIndex);
	void closeSegmentStream(int segmentIndex);
	Common::SeekableReadStream *getStreamForSegment(int segmentIndex);
	Common::SharedPtr<SegmentUnloadSignaller> notifyOnSegmentUnload(int segmentIndex, ISegmentUnloadSignalReceiver *receiver);

	void onPostRender();
	Common::SharedPtr<PostRenderSignaller> notifyOnPostRender(IPostRenderSignalReceiver *receiver);

#ifdef MTROPOLIS_DEBUG_ENABLE
	const char *debugGetTypeName() const override { return "Project"; }
#endif

private:
	struct LabelSuperGroup {
		size_t firstRootNodeIndex;
		size_t numRootNodes;
		size_t numTotalNodes;

		uint32 superGroupID;
		Common::String name;
	};

	struct LabelTree {
		size_t firstChildIndex;
		size_t numChildren;

		uint32 id;
		Common::String name;
	};

	struct Segment {
		Segment();

		SegmentDescription desc;
		Common::SharedPtr<Common::SeekableReadStream> rcStream;
		Common::SeekableReadStream *weakStream;
		Common::SharedPtr<SegmentUnloadSignaller> unloadSignaller;
	};

	enum StreamType {
		kStreamTypeUnknown,

		kStreamTypeAsset,
		kStreamTypeBoot,
		kStreamTypeScene,
	};

	struct StreamDesc {
		StreamType streamType;
		uint16 segmentIndex;
		uint32 size;
		uint32 pos;
	};

	struct AssetDesc {
		uint32 typeCode;
		size_t id;
		Common::String name;

		// If the asset is live, this will be its asset info
		Common::WeakPtr<Asset> asset;
	};

	void loadBootStream(size_t streamIndex);

	void loadPresentationSettings(const Data::PresentationSettings &presentationSettings);
	void loadAssetCatalog(const Data::AssetCatalog &assetCatalog);
	void loadGlobalObjectInfo(ChildLoaderStack &loaderStack, const Data::GlobalObjectInfo &globalObjectInfo);
	void loadAssetDef(size_t streamIndex, AssetDefLoaderContext &context, const Data::DataObject &dataObject);
	void loadContextualObject(size_t streamIndex, ChildLoaderStack &stack, const Data::DataObject &dataObject);
	Common::SharedPtr<Modifier> loadModifierObject(ModifierLoaderContext &loaderContext, const Data::DataObject &dataObject);
	void loadLabelMap(const Data::ProjectLabelMap &projectLabelMap);
	static size_t recursiveCountLabels(const Data::ProjectLabelMap::LabelTree &tree);

	ObjectLinkingScope *getPersistentStructuralScope() override;
	ObjectLinkingScope *getPersistentModifierScope() override;

	void assignAssets(const Common::Array<Common::SharedPtr<Asset> > &assets);

	Common::Array<Segment> _segments;
	Common::Array<StreamDesc> _streams;
	Common::Array<LabelTree> _labelTree;
	Common::Array<LabelSuperGroup> _labelSuperGroups;
	Data::ProjectFormat _projectFormat;
	bool _isBigEndian;

	Common::Array<AssetDesc *> _assetsByID;
	Common::Array<AssetDesc> _realAssets;

	Common::HashMap<Common::String, size_t> _assetNameToID;

	ProjectPresentationSettings _presentationSettings;

	bool _haveGlobalObjectInfo;
	bool _haveProjectStructuralDef;
	SimpleModifierContainer _globalModifiers;

	ProjectPlugInRegistry _plugInRegistry;

	Common::Array<Common::SharedPtr<PlugIn> > _plugIns;
	Common::SharedPtr<ProjectResources> _resources;
	ObjectLinkingScope _structuralScope;
	ObjectLinkingScope _modifierScope;

	Common::SharedPtr<PostRenderSignaller> _postRenderSignaller;

	Runtime *_runtime;
};

class Section : public Structural {
public:
	bool load(const Data::SectionStructuralDef &data);

	bool isSection() const;

#ifdef MTROPOLIS_DEBUG_ENABLE
	const char *debugGetTypeName() const override { return "Section"; }
#endif

private:
	ObjectLinkingScope *getPersistentStructuralScope() override;
	ObjectLinkingScope *getPersistentModifierScope() override;

	ObjectLinkingScope _structuralScope;
	ObjectLinkingScope _modifierScope;
};

class Subsection : public Structural {
public:
	bool load(const Data::SubsectionStructuralDef &data);

	ObjectLinkingScope *getSceneLoadMaterializeScope();

	bool isSubsection() const override;

#ifdef MTROPOLIS_DEBUG_ENABLE
	const char *debugGetTypeName() const override { return "Subsection"; }
#endif

private:
	ObjectLinkingScope *getPersistentStructuralScope() override;
	ObjectLinkingScope *getPersistentModifierScope() override;

	ObjectLinkingScope _structuralScope;
	ObjectLinkingScope _modifierScope;
};

class Element : public Structural {
public:
	virtual bool isVisual() const = 0;
	bool isElement() const override;

	uint32 getStreamLocator() const;

protected:
	uint32 _streamLocator;
	uint16 _sectionID;
};

class VisualElement : public Element {
public:
	bool isVisual() const override;

	bool isVisible() const;
	bool isDirectToScreen() const;
	uint16 getLayer() const;

	bool readAttribute(MiniscriptThread *thread, DynamicValue &result, const Common::String &attrib);
	bool writeRefAttribute(MiniscriptThread *thread, DynamicValueWriteProxy &writeProxy, const Common::String &attrib);

	bool scriptSetVisibility(const DynamicValue &result);

	virtual void render(Window *window) = 0;

protected:
	bool loadCommon(const Common::String &name, uint32 guid, const Data::Rect &rect, uint32 elementFlags, uint16 layer, uint32 streamLocator, uint16 sectionID);

	bool scriptSetDirect(const DynamicValue &dest);

	struct ChangeFlagTaskData {
		bool desiredFlag;
		Runtime *runtime;
	};

	VThreadState changeVisibilityTask(const ChangeFlagTaskData &taskData);

	bool _directToScreen;
	bool _visible;
	Rect16 _rect;
	uint16 _layer;
};

class NonVisualElement : public Element {
public:
	bool isVisual() const override;

	bool loadCommon(const Common::String &name, uint32 guid, uint32 elementFlags);
};

struct ModifierFlags {
	ModifierFlags();
	bool load(const uint32 dataModifierFlags);

	bool isLastModifier : 1;
	bool flagsWereLoaded : 1;
};

class Modifier : public RuntimeObject, public IMessageConsumer, public IDebuggable {
public:
	Modifier();
	virtual ~Modifier();

	void materialize(Runtime *runtime, ObjectLinkingScope *outerScope);

	virtual bool isAlias() const;
	virtual bool isVariable() const;
	bool isModifier() const override;

	// This should only return a propagation container if messages should actually be propagated (i.e. NOT switched-off behaviors!)
	virtual IModifierContainer *getMessagePropagationContainer();
	virtual IModifierContainer *getChildContainer();

	const Common::WeakPtr<RuntimeObject> &getParent() const;
	void setParent(const Common::WeakPtr<RuntimeObject> &parent);

	bool respondsToEvent(const Event &evt) const override;
	VThreadState consumeMessage(Runtime *runtime, const Common::SharedPtr<MessageProperties> &msg) override;

	void setName(const Common::String &name);
	const Common::String &getName() const;

	const ModifierFlags &getModifierFlags() const;

	// Shallow clones only need to copy the object.  Descendent copies are done using visitInternalReferences.
	virtual Common::SharedPtr<Modifier> shallowClone() const = 0;

	// Visits any internal references in the object.
	// Any references to other elements owned by the object MUST be SharedPtr, any references to non-owned objects
	// MUST be WeakPtr, in order for the cloning and materialization logic to work correctly.
	virtual void visitInternalReferences(IStructuralReferenceVisitor *visitor);

	bool loadPlugInHeader(const PlugInModifierLoaderContext &plugInContext);

#ifdef MTROPOLIS_DEBUG_ENABLE
	SupportStatus debugGetSupportStatus() const override;
	const Common::String &debugGetName() const override;
	Common::SharedPtr<DebugInspector> debugGetInspector() const override;
	Debugger *debugGetDebugger() const override;

	virtual DebugInspector *debugCreateInspector();
#endif

protected:
	bool loadTypicalHeader(const Data::TypicalModifierHeader &typicalHeader);

	// Links any references contained in the object, resolving static GUIDs to runtime object references.
	// If you override this, you must override visitInternalReferences too.
	virtual void linkInternalReferences(ObjectLinkingScope *scope);

	Common::String _name;
	ModifierFlags _modifierFlags;
	Common::WeakPtr<RuntimeObject> _parent;

#ifdef MTROPOLIS_DEBUG_ENABLE
	Common::SharedPtr<DebugInspector> _debugInspector;
	Debugger *_debugger;
#endif
};

class VariableModifier : public Modifier {
public:
	virtual bool isVariable() const;
	virtual bool setValue(const DynamicValue &value) = 0;
	virtual void getValue(DynamicValue &dest) const = 0;
};

enum AssetType {
	kAssetTypeNone,

	kAssetTypeMovie,
	kAssetTypeAudio,
	kAssetTypeColorTable,
	kAssetTypeImage,
	kAssetTypeText,
};

class Asset {
public:
	Asset();
	virtual ~Asset();

	uint32 getAssetID() const;

	virtual AssetType getAssetType() const = 0;

protected:
	uint32 _assetID;
};


} // End of namespace MTropolis

#endif
