# TF2 Classified Econ Data

A library to get TF2 item data from game memory, intended as a successor to TF2ItemsInfo and
TF2IDB.  No more parsing the schema file and maintaining your own structure for plugin support.

There's [a semi-guide on porting from existing libraries to this one][port-old-itemdata],
as well as [a WIP plugin that implements the natives from those libraries][econcompat].

[port-old-itemdata]: https://github.com/nosoop/SM-TFEconData/wiki/Porting-TF2IDB-and-TF2II-plugins-to-TFEconData

Notes for this fork: this is redux version of plugin ported for tf2 classified. 
TF2 Classified doesn't support paint kits, rarities (not qualities) and particle attribute system so I got rid of them in this version.
Also I removed GetMapDefinitionIndexByName, because it doesn't exist for Windows for some reason.
Other things for items, attributes, bodygroups and qualities work as intended (check .inc file for more info).

## Installation

1. Make sure you have the latest version of Metamod:Source (dev 2.0 build 1387 or later).
2. Make sure you have the version of Sourcemod dev 1.13 build 7294 (update will be a bit later).
3. Download this repository.
4. Copy `tf_econ_data.smx` to `addons/sourcemod/plugins/`.
5. Copy `tf2.econ_data.txt` to `addons/sourcemod/gamedata/`.
6. If you're a developer, copy `tf_econ_data.inc` to `addons/sourcemod/scripting/include/`
(or the appropriate path for your compiler toolchain / project).

## Features

- Retrieve certain properties of an item given its definition index, including entity class
name, level range, and item slot.
- Get lists of definition indices filtered with a user-defined function.
- Translate an entity classname for the appropriate player class (making spawned multiclass
weapons work correctly).  Technically, this is just handled as a call to the game's function,
but it saves you effort from adding / maintaining the `SDKCall` boilerplate yourself.
- Get a loadout slot name by index or translate slot indices (retrieved from item definitions)
to names.
- Read attributes and attribute properties.
- Read quality names / values.
- Access item equip regions and their equip region overlap masks, so you can determine if two
wearable items are overlapping.  Also access equip region names / group indices.
- Directly get the addresses of any supported definition type, as well as the schema, in case you want to do something the library doesn't support out of the box.

Note that the abstractions are intentionally low; this plugin **doesn't** implement higher-level
functions in SourcePawn to do things like:

- Check for equipment conflicts based on multiple definition indices.
- Determine which items can be Australium.

