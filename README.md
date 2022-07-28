# MazeGame

## List of things I changed/added

* Added a level selection screen for accessing Custom Levels.
* Changed out the lives system for a player health system.
* There's now a pause menu in-game where you can access a pause menu.
  * Contains a stats, inventory, and equipment system that affects player stats.
  * Equipping different items that start in the player inventory change the player's stats.
   *Can be seen with the Bronze Sword and Crown of Health.
  * Vitality controls the player's maximum health.
* Health Potion pickup actor that can be placed in the overworld (denoted by H)
..* These can be found in CustomLevel1.txt and CustomLevel2.txt
* "Event log" on the HUD showing the last few events that occured
(player taking damage, picking up items)

## Things that aren't done
* Combat against enemies (They damage you, but you can't deal damage back)
* Other pickupable items outside of the Health Potion
* Shop NPC
  * I originally wanted to make a shop NPC that you could buy items from,
but all of the time was spent on the inventory/equipment/stats system.
* Breaking things down into more classes (PlayerMenuState is pretty ugly)
* Changes to the Level Editor
  * Currently the only way to add Health Potions to the map is modifying the .txt directly