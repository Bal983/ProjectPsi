# OUTLINE FOR THE AI PROJECT
## OUR GOAL

	To create a simplistic tile based evolution simulator with AI aspects and and a simple GUI

## GRAND SCHEME
0. A Menu System
	* - [ ] A Main menu to select between:
		* - [ ] Start a new simulation
		* - [ ] Load an existing simulation (this is to come in the future)
		* - [ x ] View the controls
		* - [ x ] View the credits
		* - [ x ] Exit the game
	* - [ ] The new simulaton menu
		* - [ ] Need to be able to change a variety of parameters
		* - [ ] Possibly an export button so that you can pass/save parameters
		* Should have the following functionality:
			* Export parameters as a string so that you can save the current loadout and in the future start faster
			* Import parameters from a string so that you can quickly start a game
			* A list of parameters that can be set
	* - [ ] The load simulation Menu (possibly just load from a file, maybe save it to the system itself
	    * Note: this is going to be a feature implemented in the future.
		* It should have the following functionality:
			* Load from a save file
			* Maybe have some sort of "load from string" functionality in which the menu will generate a simulation starting at some point
	* - [ x ] The Controls Menu
		* - [ x ] Display a list of controls, possibly with images
	* - [ ] The Credits Menu
		* - [ x ] Sam and Brytons name
		* - [ x ] Credits to any inclusions
		* - [ x ] Something else maybe
1. A board representation
	* - [ ] 2D square tiles
2. Some analytics
	* - [ ] CLAD diagrams
	* - [ ] Total populations
	* This will probably have to be done via a SQL database
		* An SQL database would be good because then we have really fast read/writes, we will never need to update the logs so there is no reason to keep them in a database
			* Note: SQL might be a bad idea because i know nothing about databases
3. The actual creatures that will be evolving
	* - [ ] Ai for said creatures
		* - [ ] Different styles of AI
	* - [ ] Attributes that can develop and change
		* - [ ] Some attributes unique to a species, such as underwater breathing
		* - [ ] Herbivore/carnivors/omivores
		* - [ ] Aggressiveness
		* - [ ] Size
		* - [ ] Colour
		* - [ ] Reproduction Speed
		* - [ ] Metabolism
		* - [ ] Sex
		* - [ ] Food Preference
		* - [ ] Energy Content
			* - [ ] How long they can live without food
			* - [ ] The amount of food they are worth to kill
		* - [ ] Basic Senses
		* - [ ] Temperature Preference
		* - [ ] Environmental Preference
		* - [ ] Body parts that can mutate (meaning a generation can have an extra limb)
			* This needs to be much slower then Other attributes changing
		* - [ ] Tirtiary Atributes
			* - [ ] Gills
			* - [ ] Wings
			* - [ ] Digging
	* - [ ] Ways for the creatures to interact with eachother
		* - [ ] Attack eachother
		* - [ ] Breed with eachother
	* - [ ] Ways for the creatures to interact with the environment
	* - [ ] Eating foods
	* - [ ] Hiding?
4. We need an environment that is adaptive and changes over time
	* - [ ] Change temperatures
	* - [ ] Food variance
	* - [ ] Shifting land/water
	* - [ ] Random events
	* - [ ] Random birth of new creatures
	* - [ ] Possibly make plants agents
5. Set custom parameters to change the way creatures react (playing god)
	* - [ ] Scale spawnrate of new creatures
	* - [ ] Scale the rapidness of evolution
	* - [ ] Scale richness of soil (means howmuch food spawns in tiles)
	* - [ ] Scale water/land distribution
	* - [ ] Spawn in new creatures with whatever attributes you want
	* - [ ] Maybe turn it into a game with having a preset goal
6. An in-game options menu
	* - [ ] Control volumn if sound exists
	* - [ ] Allow resizing of the screen
	* - [ ] Control brightness
	* - [ ] An advanced menu
		* - [ ] How long should records be kept for
		* - [ ] How frequent should records be generated
		* - [ ] How detailed are the records
			* Note: this won't be required if we use a sql database because we only would have one schema per AI
	
## Future Plans
1. Think of a way this can be transformed from a information simulator into a game
2. Change it from a 2d simulator to a 3d simulator with better models
