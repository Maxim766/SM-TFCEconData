/**
 * [TF2] Econ Data
 * Functions to read item information from game memory.
 */

#if defined __tf_econ_data_included
	#endinput
#endif

#include <tf2_stocks>

#define __tf_econ_data_included

/**
 * Item definition index for the special "default" item entry, which is returned by the game's
 * CEconItemSchema::GetItemDefinition() if the given item definition does not exist.
 * 
 * Not a valid item, but points to a valid item definition, so this does return information when
 * `TF2Econ_Get*` functions are called on it.
 */
enum {
	TF_ITEMDEF_DEFAULT = -1,
};

/**
 * Callback for `TF2Econ_GetItemList`.  Return `true` if the specified item definition index
 * should be added to the returned `ArrayList`.
 */
typedef ItemFilterCriteria = function bool(int itemdef, any data);

/**
 * Callback for `TF2Econ_GetAttributeList`.  Return `true` if the specified attribute definition
 * index should be added to the returned `ArrayList`.
 * 
 * This prototype is the same as `TF2Econ_GetItemList`.  Take care to not mix up the callbacks.
 */
typedef AttributeFilterCriteria = function bool(int attrdef, any data);

/**
 * Returns true if there is an item corresponding to the given item definition index.
 * TF_ITEMDEF_DEFAULT returns false here.
 */
native bool TF2Econ_IsValidItemDefinition(int itemdef);

/**
 * Returns true if item is in base set (corresponds to the "baseitem" key).
 */
native bool TF2Econ_IsItemInBaseSet(int itemdef);

/**
 * Returns the item's name (corresponds to the "name" key).
 */
native bool TF2Econ_GetItemName(int itemdef, char[] name, int maxlen);

/**
 * Returns the item's localization token name (corresponds to the "item_name" key).
 */
native bool TF2Econ_GetLocalizedItemName(int itemdef, char[] name, int maxlen);

/**
 * Stores the item class name in the given buffer and returns true if given a valid item
 * definition, otherwise returns false.
 */
native bool TF2Econ_GetItemClassName(int itemdef, char[] buffer, int maxlen);

/**
 * Returns the item's loadout slot for the given class, or -1 if the item definition or
 * item / class combination is not valid.  This is *not* the same value as the weapon slot used
 * in SourceMod's GetPlayerWeaponSlot native; not all values match.
 * 
 * More information about this distinction is available here:
 * https://github.com/nosoop/SM-TFEconData/wiki/Porting-TF2IDB-and-TF2II-plugins-to-TFEconData#notes-about-loadout-slots
 */
native int TF2Econ_GetItemLoadoutSlot(int itemdef, TFClassType playerClass);

/**
 * Returns the item's default loadout slot.
 */
native int TF2Econ_GetItemDefaultLoadoutSlot(int itemdef);

/**
 * Returns the given item's equipment region mask.  This mask can be and-tested with another
 * mask to determine if items conflict.
 */
native int TF2Econ_GetItemEquipRegionMask(int itemdef);

/**
 * Returns the given item's equipment region groups as a bitfield.
 * 
 * Internally, this is called an EquipRegionBitMask, but for the sake of clarity it's been
 * renamed in this library to specify equip region groups.
 */
native int TF2Econ_GetItemEquipRegionGroupBits(int itemdef);

/**
 * Stores the minimum and maximum item level range in the given cell references and
 * returns true for a valid item definition, otherwise returns false.
 */
native bool TF2Econ_GetItemLevelRange(int itemdef, int &iMinLevel, int &iMaxLevel);

/**
 * Returns the given item's statically defined quality.
 */
native int TF2Econ_GetItemQuality(int itemdef);

/**
 * Returns an `ArrayList` containing attribute defindex / value pairs corresponding to the given
 * item definition, or `null` if not a valid item definition.
 * 
 * The `ArrayList` has a blocksize of 2.  Block 0 contains the attribute defindex; block 1
 * contains the attribute value, which is a 32-bit value that may represent an int, float, or
 * pointer to a complex type.
 * 
 * This handle is owned by the calling plugin, so it should be `delete`d when not needed
 * anymore.
 */
native ArrayList TF2Econ_GetItemStaticAttributes(int itemdef);

/**
 * Returns an arbitrary string from an item definition's KeyValues structure.
 * You may use subkey notation ('/') to retrieve nested values.
 * 
 * Returns true if the output buffer is not empty.
 */
native bool TF2Econ_GetItemDefinitionString(int itemdef, const char[] key,
		char[] buffer, int maxlen, const char[] defaultValue = "");

/**
 * Returns an ArrayList containing all valid item definition indices.  If an ItemFilterCriteria
 * callback is passed in, the ArrayList only contains defindexes that the callback returned
 * `true` on.
 * 
 * The resulting ArrayList does not have a defined order.
 * 
 * This handle is owned by the calling plugin, so it should be `delete`d when not needed
 * anymore.
 */
native ArrayList TF2Econ_GetItemList(ItemFilterCriteria func = INVALID_FUNCTION, any data = 0);

/**
 * Returns true if the specified className was translated for the given player class.
 * The buffer is not modified if the className was not translated.
 * 
 * This is used for multiclass weapons -- if given a player class-specific classname,
 * this function returns false.
 */
native bool TF2Econ_TranslateWeaponEntForClass(char[] className, int maxlen,
		TFClassType playerClass);

/**
 * Returns true if the given loadout slot index has a name, false otherwise.
 */
native bool TF2Econ_TranslateLoadoutSlotIndexToName(int index, char[] buffer, int maxlen);

/**
 * Returns the loadout slot index for the given slot name, or -1 if not a valid slot.
 */
native int TF2Econ_TranslateLoadoutSlotNameToIndex(const char[] slotName);

/**
 * Returns the number of valid loadout slots.
 */
native int TF2Econ_GetLoadoutSlotCount();

/**
 * Returns true if there is an attribute corresponding to the given attribute definition index.
 */
native bool TF2Econ_IsValidAttributeDefinition(int attrdef);

/**
 * Returns true if the attribute is considered hidden (corresponds to the "hidden" key).
 */
native bool TF2Econ_IsAttributeHidden(int attrdef);

/** 
 * Returns true if the attribute is stored as an integer (corresponds to the "stored_as_integer"
 * key).
 * 
 * Not sure when this is actually used -- certain attributes such as
 * "mod max primary clip override" are flagged as true, but are float values when retrieved
 * via `TF2Econ_GetItemStaticAttributes()`.
 */
native bool TF2Econ_IsAttributeStoredAsInteger(int attrdef);

/**
 * Stores the attribute name in the given buffer and returns true if given a valid attribute
 * definition, otherwise returns false.
 */
native bool TF2Econ_GetAttributeName(int attrdef, char[] buffer, int maxlen);

/**
 * Stores the attribute class name in the given buffer and returns true if given a valid
 * attribute definition, otherwise returns false.
 */
native bool TF2Econ_GetAttributeClassName(int attrdef, char[] buffer, int maxlen);

/**
 * Returns an arbiitrary string from an item attribute definition's KeyValues structure.
 * You may use subkey notation ('/') to retrieve nested values.
 * 
 * Returns true if the output buffer is not empty.
 */
native bool TF2Econ_GetAttributeDefinitionString(int attrdef, const char[] key,
		char[] buffer, int maxlen, const char[] defaultValue = "");

/**
 * Returns the attribute definition index for a given name, or -1 if the name does not
 * correspond to an attribute.
 */
native int TF2Econ_TranslateAttributeNameToDefinitionIndex(const char[] name);

/**
 * Returns an ArrayList containing all valid attribute definition indices.  If an
 * AttributeFilterCriteria callback is passed in, the ArrayList only contains attribute
 * definition indices that the callback returned `true` on.
 * 
 * The resulting ArrayList does not have a defined order.
 * 
 * This handle is owned by the calling plugin, so it should be `delete`d when not needed
 * anymore.
 */
native ArrayList TF2Econ_GetAttributeList(AttributeFilterCriteria func = INVALID_FUNCTION,
		any data = 0);

/**
 * Stores the quality name in the given buffer and returns true if given a valid quality value,
 * otherwise returns false;
 */
native bool TF2Econ_GetQualityName(int quality, char[] buffer, int maxlen);

/**
 * Returns the quality value for a given name, or -1 if the name does not correspond to an item
 * quality.
 */
native int TF2Econ_TranslateQualityNameToValue(const char[] name, bool caseSensitive = true);

/**
 * Returns an ArrayList containing all valid quality values.
 * 
 * This handle is owned by the calling plugin, so it should be `delete`d when not needed
 * anymore.
 */
native ArrayList TF2Econ_GetQualityList();

/**
 * Returns a StringMap containing all valid equip region names mapped to their equip region
 * group indices.
 */
native StringMap TF2Econ_GetEquipRegionGroups();

/**
 * Returns true if the given equip region name is valid, storing its equip region mask in the
 * given by-ref``mask` argument.
 */
native bool TF2Econ_GetEquipRegionMask(const char[] equipRegion, int &mask);

/**
 * Returns the address of the singleton CTFItemSchema (subclass of CEconItemSchema).
 * 
 * Here be dragons.
 */
native Address TF2Econ_GetItemSchemaAddress();

/**
 * Returns the address of the CEconItemDefinition for the item with the given definition index,
 * or Address_Null if not valid.  The special "default" item definition is returned iff
 * TF_ITEMDEF_DEFAULT is used as the defindex.
 * 
 * Here be dragons.
 */
native Address TF2Econ_GetItemDefinitionAddress(int itemdef);

/**
 * Returns the address of the CEconItemAttributeDefinition for the attribute with the given
 * definition index, or Address_Null if not valid.
 * 
 * Here be dragons.
 */
native Address TF2Econ_GetAttributeDefinitionAddress(int attrdef);

/**
 * @deprecated Renamed native to TF2Econ_IsValidItemDefinition so there is a better distinction
 * between item and attribute definitions.
 * 
 * This native will still be present for backwards compatibility.
 */
#pragma deprecated Use TF2Econ_IsValidItemDefinition instead
native bool TF2Econ_IsValidDefinitionIndex(int itemdef);

/**
 * @deprecated Renamed native to TF2Econ_GetItemLoadoutSlot to remove the confusion on weapon
 * and loadout slots.
 * 
 * This native will still be present for backwards compatibility.
 */
#pragma deprecated Use TF2Econ_GetItemLoadoutSlot instead
native int TF2Econ_GetItemSlot(int itemdef, TFClassType playerClass);

public SharedPlugin __pl_tf_econ_data = {
	name = "tf_econ_data",
	file = "tf_econ_data.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
