# Framework-AR-7R
## Introduction

7R Mission Framework for Arma Reforger

## Status
### Current Add-ons

* 7R Core
    - Mission Manager
    - Custom Commands menu for 7R (default keybind: H)
* 7R Full
    - Empty add-on containing all dependencies
    - All in one subscribe
* 7R Loadouts
    - Loadout selection
    - US Vanilla loadouts
    - Supply loadouts
    - Vehicle loadouts
* 7R Missions
    - Add-on for storing missions
* 7R Reinsertion
    - Rally deployment
* 7R Support System
    - Supplies
    - IDF
    - Vehicle spawner with loadout

### Planned Features

* 7R Core
    - Triggers
    - Custom Objectives
    - Use AIGroups
    - Briefing
* 7R Loadouts
    - ActionContextMenu for boxes
* 7R Support System
    - CAS (not in AR yet)
    - UAV (not in AR yet)
* 7R Better Respawn System
* 7R Warcrime Tracker

## Import addons into Arma Reforger Tools

1. Open 'Enfusion Workbench Launcher'
2. Press 'Add Project' > 'Add Existing Project'
3. Find the 'addon.gproj' in the desired addon folder

## Folder Structure for Arma Reforger

### Configs

Contains Config files that can be imported into slots.

### languages

String table for localization

### Prefabs

In-game compositions of entities with pre-filled properties/attributes.

Several prefabs are made for the 7R Mission Gamemode

### Scripts

Scripts folder contains several scripts that define:

- Config files layout
- Components
- Entities
- Modded classes

### UI

All custom UI elements can be found here.

### Worlds

Pre-made missions can be saved in here until the framework can be used inside the game as an add-on for mission making
