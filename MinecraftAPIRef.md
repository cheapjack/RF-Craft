# Minecraft API 

This is [Martin O'Hanlon's](https://github.com/martinohanlon) reference for the Minecraft Python API Library, which is supported on Minecraft: Pi edition and the PC/Mac/Linux version using the RaspberryJuice plugin.

If you want to know more about how to use the API, including tutorials, see his projects and download his code, visit my minecraft page.

Structure
 * minecraft.py
  * Class Minecraft - main class for connecting and interacting with the game
   * Class camera - changing camera angle and postion
   * Class player - getting and changing the players position and setting
   * Class entity - getting and changing entities position and setting
   * Class events - retreiving events which have occured in the game
 * block.py
  * Class Block - definition of a block, specifically its type
 * event.py
  *Class BlockEvent - definition of a block event, specifically what event, what block and what player
 * vec3.py
  * Class Vec3 - generic class for managing a 3 dimension vector (i.e. x,y,z)
 * connection.py - internal module used by the api
 * util.py - internal module used by the api

###Compatability
Not all functions and block types are available on all version of the api


![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)Available on Minecraft: Pi edition
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)Available on RaspberryJuice

## Minecraft
"Main class for interacting with the Minecraft world, includes functions for creating a connection, modifying players and blocks and capturing events"

#### .create(address = "localhost", port = 4711)
"Create connection to Minecraft (address, port) => Minecraft object"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#use default address and port
mc = minecraft.Minecraft.create()
#specify ip address and port
mc = minecraft.Minecraft.create("192.168.1.1", 4711)
```

#### .getBlock(x,y,z)
"Get block (x,y,z) => id:int"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#retrieves the block type for the block at 0,0,0
blockType = mc.getBlock(0,0,0)
```

#### .getBlocks(x0,y0,z0,x1,y1,z1)
"Get a cuboid of blocks (x0,y0,z0,x1,y1,z1) => [id:int]"
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#get the block ids in a cuboid
blocks = mc.getBlocks(-1,-1,-1,1,1,1)
for block in blocks:
    print block
```

#### .getBlockWithData(x,y,z)
"Get block with data (x,y,z) => Block"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#retrieves a block object for the block at 0,0,0
blockObj = mc.getBlockWithData(0,0,0)
```

#### .setBlock(x,y,z)
"Set block (x,y,z,id,[data])"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#sets a block at an x, y, z co-ordinate to a particular type
mc.setBlock(0,0,0,block.DIRT.id)
#sets a block to a particular type and 'subtype'
mc.setblock(0,0,0,block.WOOD.id, 1)
```

#### .setBlocks(x0,y0,z0,x1,y1,z1,blockType, blockData)
"Set a cuboid of blocks (x0,y0,z0,x1,y1,z1,id,[data])"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#sets many blocks at a time, filling the gap between 2 sets of x, y, z co-ordinates
mc.setBlocks(-1, -1, -1, 1, 1, 1, block.STONE.id)
```

#### .getHeight(x,z)
"Get the height of the world (x,z) => int"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#find the y (vertical) of an x, z co-ordinate which represents the 'highest' (non-air) block
y = mc.getHeight(0,0)
```

#### .getPlayerEntityIds()
"Get the entity ids of the connected players => [id:int]"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#get the entity ids of the players connected to the game
entityIds = mc.getPlayerEntityIds()
for entityId in entityIds:
    print entityId
```

#### .getPlayerEntityId(playerName)
"Get the entity id for a named player => [id:int]"
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#get the entity id of a name player 'martinohanlon'
entityId = mc.getPlayerEntityId("martinohanlon")
print entityId
```

#### .saveCheckpoint()
"Save a checkpoint that can be used for restoring the world"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)

```
mc.saveCheckpoint()
```

#### .restoreCheckpoint()
"Restore the world state to the checkpoint"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)

```
mc.restoreCheckpoint()
```

#### .postToChat(message)
"Post a message to the game chat"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#write 'Hello Minecraft World' to the chat window
mc.postToChat("Hello Minecraft World")
```

#### .setting(setting, status)
"Set a world setting (setting, status). keys: world_immutable, nametags_visible"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#change world immutable to True
mc.setting("world_immutable", True)
#change nametags_visible setting to False
mc.setting("nametags_visible", False)
```

### Minecraft.player
#### .getPos()
"Gets the player's position in the world as a Vec3 of floats (decimal numbers), if the player is in the middle of a block x.5 is returned"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#get players position as floats
playerPos = mc.player.getPos()
```

#### .setPos(x,y,z)
"Moves the player to a position in the world by passing co-ordinates ([x,y,z])"
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#set the players position as floats
mc.player.setPos(0.0,0.0,0.0)
```

#### .getTilePos()
"Gets the position of the 'tile' the player is currently on."
![PiEdition](http://3.bp.blogspot.com/-jfHVu6wzJ8A/VLZrZRxHviI/AAAAAAAAKnc/QkMuqztRYP8/s1600/Raspi_logo_small.png)
![Bukkit/CanaryMod](http://3.bp.blogspot.com/-kTbsdFgeL4E/VLZrwiMGWZI/AAAAAAAAKnk/AYCZdsaR-Vg/s1600/bukkit_logo_small.png)

```
#get the position of the tile the players is on
playerTile = mc.player.getTilePos()
```

#### .setTilePos(x,y,z)
"Move the player to a tile position in the world by passing co-ordinates ([x,y,z])"

```
#set the position of the tile the player is on
mc.player.setTilePos(0,0,0)
```

#### .setting(setting, status)
"Set a player setting (setting, status). keys: autojump"

```
#change the autojump setting to True
mc.player.setting("autojump", True)
```

#### .getRotation()
"Get the rotational angle (0 to 360) for the player => [angle:float]"

```
#get the rotation of the player
angle = mc.player.getRotation()
print angle
```

#### .getPitch()
"Get the pitch angle (-90 to 90) for the player => [pitch:float]"

```
#get the pitch for the player
pitch = mc.player.getPitch()
print pitch
```

#### .getDirection()
"Get unit vector of x,y,z for the player's direction => [Vec3]"

```
#get the player's direction
direction = mc.player.getDirection()
print direction
```

### Minecraft.entity
The entity functions are used in conjunction with the .getPlayerEntityIds() function to interact with the entity (or players) in a game.  Entity functions are useful for multiplayer games.  

```
#get the entity ids of the players connected to the game
entityIds = mc.getPlayerEntityIds()
1stEntityId = entityIds[0]
2ndEntityId = entityIds[1]
```

#### .getPos(entityId)
"Gets an entities position in the world as a Vec3 of floats (decimal numbers), if the entity is in the middle of a block x.5 is returned"

```
#get first entity position as floats
entityPos = mc.entity.getPos(entityId)
```

#### .setPos(entityId,x,y,z)
"Moves the entity to a position in the world by passing co-ordinates ([x,y,z])"

```
#set the players position as floats
mc.player.setPos(entityId,0.0,0.0,0.0)
```

#### .getTilePos(entityId)
"Gets the position of the 'tile' the entity is currently on."

```
#get the position of the tile the entity is on
entityTile = mc.entity.getTilePos(entityId)
```

#### .setTilePos(entityId, x,y,z)
"Move the entity to a tile position in the world by passing co-ordinates ([x,y,z])"

```
#set the position of the tile the entity is on
mc.player.setTilePos(entityId,0,0,0)
```

#### .getRotation(entityId)
"Get the rotational angle (0 to 360) for an entity => [angle:float]"

```
#get the rotation of an entity
angle = mc.entity.getRotation(entityId)
print angle
```

#### .getPitch(entityId)
"Get the pitch angle (-90 to 90) for an entity => [pitch:float]"

```
#get the pitch for an entity
pitch = mc.entity.getPitch(entityId)
print pitch
```

#### .getDirection(entityId)
"Get unit vector of x,y,z for an entities direction => [Vec3]"

```
#get and entities direction
direction = mc.entity.getDirection(entityId)
print direction
```

### Minecraft.camera

#### .setNormal(entityId)
"Set camera mode to normal Minecraft view ([entityId])"

```
#set camera mode to normal for a specific player
mc.camera.setNormal(entityId)
```

#### .setFixed()
"Set camera mode to fixed view"

```
#set camera mode to fixed 
mc.camera.setFixed()
```

#### .setFollow(entityId)
"Set camera mode to follow an entity ([entityId])"

```
#set camera mode to follow for a specific player
mc.camera.setFollow(entityId)
```

#### .setPos(x,y,z)
"Set camera entity position (x,y,z)"

```
#set camera position to a specific position of x, y, z
mc.camera.setPos(0,0,0)
```

### Minecraft.events

#### .pollBlockHits()
"Block Hits (Only triggered by sword) => [BlockEvent]"

```
#get block event hits that have occured since the last time the function was run
blockEvents = mc.events.pollBlockHits()
for blockEvent in blockEvents:
    print blockEvent
```

#### .clearAll()
"Clear all old events"

```
#clear all events that have happened since the events where last got
mc.events.clearAll()
```

### Block
"The definition of a Block in Minecraft, used to describe a block type and (if applicable) its data; also contains constants for the blocks type id's, e.g. BLOCK.AIR.id"

```
#create block of a specific type
blockObj = block.Block(id)
#create a block of a specific type and apply a data value
blockObj = block.Block(id, data)
```

#### .id

"The id (or type) of block"

```
AIR                 = Block(0)
STONE               = Block(1)
GRASS               = Block(2)
DIRT                = Block(3)
COBBLESTONE         = Block(4)
WOOD_PLANKS         = Block(5)
SAPLING             = Block(6)
BEDROCK             = Block(7)
WATER_FLOWING       = Block(8)
WATER               = WATER_FLOWING
WATER_STATIONARY    = Block(9)
LAVA_FLOWING        = Block(10)
LAVA                = LAVA_FLOWING
LAVA_STATIONARY     = Block(11)
SAND                = Block(12)
GRAVEL              = Block(13)
GOLD_ORE            = Block(14)
IRON_ORE            = Block(15)
COAL_ORE            = Block(16)
WOOD                = Block(17)
LEAVES              = Block(18)
GLASS               = Block(20)
LAPIS_LAZULI_ORE    = Block(21)
LAPIS_LAZULI_BLOCK  = Block(22)
SANDSTONE           = Block(24)
BED                 = Block(26)
COBWEB              = Block(30)
GRASS_TALL          = Block(31)
WOOL                = Block(35)
FLOWER_YELLOW       = Block(37)
FLOWER_CYAN         = Block(38)
MUSHROOM_BROWN      = Block(39)
MUSHROOM_RED        = Block(40)
GOLD_BLOCK          = Block(41)
IRON_BLOCK          = Block(42)
STONE_SLAB_DOUBLE   = Block(43)
STONE_SLAB          = Block(44)
BRICK_BLOCK         = Block(45)
TNT                 = Block(46)
BOOKSHELF           = Block(47)
MOSS_STONE          = Block(48)
OBSIDIAN            = Block(49)
TORCH               = Block(50)
FIRE                = Block(51)
STAIRS_WOOD         = Block(53)
CHEST               = Block(54)
DIAMOND_ORE         = Block(56)
DIAMOND_BLOCK       = Block(57)
CRAFTING_TABLE      = Block(58)
FARMLAND            = Block(60)
FURNACE_INACTIVE    = Block(61)
FURNACE_ACTIVE      = Block(62)
DOOR_WOOD           = Block(64)
LADDER              = Block(65)
STAIRS_COBBLESTONE  = Block(67)
DOOR_IRON           = Block(71)
REDSTONE_ORE        = Block(73)
SNOW                = Block(78)
ICE                 = Block(79)
SNOW_BLOCK          = Block(80)
CACTUS              = Block(81)
CLAY                = Block(82)
SUGAR_CANE          = Block(83)
FENCE               = Block(85)
GLOWSTONE_BLOCK     = Block(89)
BEDROCK_INVISIBLE   = Block(95)
STONE_BRICK         = Block(98)
GLASS_PANE          = Block(102)
MELON               = Block(103)
FENCE_GATE          = Block(107)
GLOWING_OBSIDIAN    = Block(246)
NETHER_REACTOR_CORE = Block(247)
```

#### .data
"The data (or sub-type) of a block"

Data Values of blocks:
```
WOOL:
0: White
1: Orange
2: Magenta
3: Light Blue
4: Yellow
5: Lime
6: Pink
7: Grey
8: Light grey
9: Cyan
10: Purple
11: Blue
12: Brown
13: Green
14: Red
15:Black

WOOD:
0: Oak (up/down)
1: Spruce (up/down)
2: Birch (up/down)
(below not on Pi)
3: Jungle (up/down)
4: Oak (east/west)
5: Spruce (east/west)
6: Birch (east/west)
7: Jungle (east/west)
8: Oak (north/south)
9: Spruce (north/south)
10: Birch (north/south)
11: Jungle (north/south)
12: Oak (only bark)
13: Spruce (only bark)
14: Birch (only bark)
15: Jungle (only bark)

WOOD_PLANKS (Not on Pi):
0: Oak
1: Spruce
2: Birch
3: Jungle

SAPLING:
0: Oak
1: Spruce
2: Birch
3: Jungle (Not on Pi)

GRASS_TALL:
0: Shrub
1: Grass
2: Fern
3: Grass (color affected by biome) (Not on Pi)

TORCH:
1: Pointing east
2: Pointing west
3: Pointing south
4: Pointing north
5: Facing up

STONE_BRICK:
0: Stone brick
1: Mossy stone brick
2: Cracked stone brick
3: Chiseled stone brick

STONE_SLAB / STONE_SLAB_DOUBLE:
0: Stone
1: Sandstone
2: Wooden
3: Cobblestone
4: Brick
5: Stone Brick
Below - not on Pi
6: Nether Brick
7: Quartz

Not on Pi
SNOW_BLOCK:
0-7: Height of snow, 0 being the lowest, 7 being the highest.

TNT:
0: Inactive
1: Ready to explode

LEAVES:
1: Oak leaves
2: Spruce leaves
3: Birch leaves

SANDSTONE:
0: Sandstone
1: Chiseled sandstone
2: Smooth sandstone

STAIRS_[COBBLESTONE, WOOD]:
0: Ascending east
1: Ascending west
2: Ascending south
3: Ascending north
4: Ascending east (upside down)
5: Ascending west (upside down)
6: Ascending south (upside down)
7: Ascending north (upside down)

LADDERS, CHESTS, FURNACES, FENCE_GATE:
2: Facing north
3: Facing south
4: Facing west
5: Facing east

[WATER, LAVA]_STATIONARY:
0-7: Level of the water, 0 being the highest, 7 the lowest

NETHER_REACTOR_CORE:
0: Unused
1: Active
2: Stopped / used up
```

### BlockEvent
"The definition of a BlockEvent in Minecraft, used to describe an event in Minecraft affecting blocks; returned by the Minecraft.events.pollBlockHits() method."
```
blockEvent = mc.events.pollBlockHits()
```
#### .type
"Type of block event; there is only 1 event currently implemented BlockEvent.HIT"

blockEventType = blockEvent.type

BlockEvent types:
0: BlockEvent.HIT

#### .pos
"The position of the block where the event occured, i.e. the block which was hit.  .pos returns a Vec3 object of x,y,z co-ordinates"

blockEventPos = BlockEvent.pos

#### .face
"The face of the block where the event occured"

blockEventFace = BlockEvent.face

#### .entityId
"entityId of the player who caused the block event, i.e. the player who hit the block"

blockEventPlayer - BlockEvent.entityId
Vec3
"The definition of a 3 part vector in Minecraft, i.e. a set of x, y, z co-ordinates; x and z are the horizontal positions, y the vertical"

#### position = vec3.Vec(0,0,0)

.x
"x position"

xPos = position.x
.y
"y position"

yPos = position.y
.z
"z position"

zPos = position.z
