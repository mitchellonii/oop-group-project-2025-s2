# Project plan

## Use Case & Project Scope 

Spacefairer is a pixelated 2D side-viewed orthographic game (similar to Terraria) that takes place inside a cargo ship.

In this game you play as the protagonist, Roggert Spacemin - pilot of the Bongo Frontier, as they take loads of cargo across the cosmos.

The player must help Roggert deliver this cargo by maintaining the ship (with various upkeep tasks), fend off space pirates (dialogue-based, minimal 'combat’), and repairing safety mechanisms

[![Fig 1.0, Game design-style inspiration](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/Picture1.jpg?raw=true "Fig 1.0, Game design-style inspiration")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/Picture1.jpg?raw=true "Fig 1.0, Game design-style inspiration")
>Fig 1.0, Game design-style inspiration

[![Fig 1.1, Initial game sketches](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/Picture2.jpg?raw=true "Fig 1.1, Initial game sketches")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/Picture2.jpg?raw=true "Fig 1.1, Initial game sketches")
>Fig 1.1, Initial game sketches

## Use case

The player can only move left and right on the ship, using **A, D, Left arrow, and/or Right arrow.** The leftmost point is the control module, and the rightmost point is the cargo trailer’s control panel *(Fig 1.1)*.

The ‘interact’ button will probably be either **Space or E,** though may change

Upkeep tasks are completed by picking up any necessary materials (with the interact button) then walking up to the highlighted objects and holding the interact button for a predetermined amount of time. 

There are three types of pirates which may board the ship at anytime. Once boarded, you are forced into dialogue and have to pick between three dialogue choices: **bribe, sympathise, and insult**. Depending on the type of pirate and your dialogue choice, they will either leave or take your cargo. Dialogue options can be selected with **A, D, Left arrow, and/or Right arrow.**
The types of pirates and their dialogue responses will be similar to rock-paper-scissors (2 are positive/neutral, 1 is negative)

### Events that can lead to failure / losing 

**Tasks:**
- Correct course task: fail to update the navigation path within a minute path and the ship will hit an asteroid and explodes
- Cargo tractor beam repair: fail to repair the cargo trailer within a minute and the cargo will fly off.
- WHS review: If you don’t fix the handrail within a minute, you fail to comply with space safety regulations and will be terminated.

**Otherwise:**
- If you fail to bargain with any pirate (ie. pick the wrong dialogue choice), they steal a portion of your cargo. If you lose three portions you fail (‘three lives’)

## Initial class concepts (GameController, RenderElement, PhysicsElement, Player, Item)

[![Game controller](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/e.png?raw=true "Game controller")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/e.png?raw=true "Game controller")
[![RenderElement](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/d.png?raw=true "RenderElement")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/d.png?raw=true "RenderElement")
[![PhysicsElement](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/c.png?raw=true "PhysicsElement")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/c.png?raw=true "PhysicsElement")
[![Item](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/b.png?raw=true "Item")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/b.png?raw=true "Item")
[![Character](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/a.png?raw=true "Character")](https://github.com/mitchellonii/oop-group-project-2025-s2/blob/mitchell/images/a.png?raw=true "Character")

## Timeline

### Team Structure & Roles TBD
<mark style="color:red">**Person A - Core Systems & Player Mechanics**</mark>
<mark style="color:orange">**Person B - Tasks & Game Events**</mark>
<mark style="color:green">**Person C - Pirates, UI & Polish**</mark>

------------

### Week 1: Core Systems & Foundation

**Priority 1:**
<mark style="color:red">- Set up project structure and development environment<br>- Implement base class system (GameController, RenderElement, PhysicsElement)</mark>
<mark style="color:orange">- Design and create ship background art (control module to cargo trailer)<br>- Set up rendering pipeline for 2D pixelated graphics</mark>
<mark style="color:green">- Design basic HUD layout (cargo counter, timer display)<br>- Create UI rendering system</mark>

**Priority 2:**
<mark style="color:red">- Implement Player class with left/right movement (A, D, arrow keys)<br>- Add collision detection for ship boundaries<br>- Create player sprite and basic animations (idle, walking)</mark>
<mark style="color:orange">- Develop task highlight system<br>- Build timer framework (1-minute countdown system)<br>- Implement "Correct Course" task mechanic</mark>
<mark style="color:green">- Create main menu/title screen mockups<br>- Design three pirate character sprites<br>- Create dialogue UI overlay mockup</mark>

**Priority 3:**
<mark style="color:red">- Implement interact button functionality (Space/E)<br>- Create Item class for pickable objects</mark>
<mark style="color:orange">- Test and refine player movement feel<br>- Plan pirate dialogue tree structure</mark>
<mark style="color:green">- Draft dialogue text for all three pirate types (bribe, sympathise, insult options)<br>- Create pirate boarding animation concept</mark>

------------

### Week 2: Tasks, Pirates & Game Mechanics

**Priority 1:**
<mark style="color:red">- Refine hold-to-complete interaction mechanic<br>- Create pickup and carry system for repair items</mark>
<mark style="color:orange">- Implement "Cargo Tractor Beam Repair" task:<br>&nbsp;&nbsp;* Repair interaction mechanic<br>&nbsp;&nbsp;* Item pickup and placement</mark>
<mark style="color:green">- Add visual feedback for interactions (highlights, animations)<br>- Implement dialogue UI overlay (fully functional)<br>- Build dialogue choice system (A, D, arrow key navigation)<br>- Create dialogue display animations and transitions</mark>

**Priority 2:**
<mark style="color:red">- Implement game state management (playing, paused, game over)<br>- Create transition system between game states</mark>
<mark style="color:orange">- Optimize collision detection and movement physics<br>- Handle player input during dialogue (disable movement, enable choice selection)</mark>
<mark style="color:green">- Implement "WHS Review" task:<br>&nbsp;&nbsp;* Handrail repair mechanic<br>&nbsp;&nbsp;* Safety termination failure state<br>- Program rock-paper-scissors logic for all three pirate types<br>&nbsp;&nbsp;* Define win/lose conditions for each dialogue choice<br>- Implement cargo loss counter (three strikes system)<br>- Create outcome animations (pirate leaves vs. steals cargo)</mark>

**Priority 3:**
<mark style="color:red">- Create task spawning system with random timing<br>- Balance task frequency and difficulty</mark>
<mark style="color:orange">- Add visual/audio cues for incoming tasks<br>- Create priority/queue system for multiple concurrent tasks</mark>
<mark style="color:green">- Implement pirate spawn mechanics and timing<br>- Integrate pirate boarding with game flow<br>- Test all pirate type and dialogue combinations</mark>

------------

### Week 3: Polish, Testing & Completion

**Priority 1:**
<mark style="color:red">- Create all game over screens:<br>&nbsp;&nbsp;* Asteroid collision<br>&nbsp;&nbsp;* Cargo loss (trailer detaches)<br>&nbsp;&nbsp;* Safety violation<br>&nbsp;&nbsp;* Three cargo theft failures</mark>
<mark style="color:orange">- Implement win condition (successful delivery)<br>- Balance task difficulty and timing based on playtesting<br>- Polish task visual indicators</mark>
<mark style="color:green">- Implement complete HUD:<br>&nbsp;&nbsp;* Cargo counter display (lives remaining)<br>&nbsp;&nbsp;* Active task timers with visual warnings<br>&nbsp;&nbsp;* Current objective indicators<br>- Add background music<br>- Sound effects for pirate boarding and movement</mark>

**Priority 2:**
<mark style="color:red">- Add restart functionality (if time permits)<br>- Implement pause system with pause menu (if time permits)<br>- Create settings/options (if time permits)</mark>
<mark style="color:orange">- Comprehensive playtesting of all tasks<br>- Fix task-related bugs<br>- Balance spawn rates and difficulty curve<br>- Final testing of edge cases</mark>
<mark style="color:green">- Contribute to integration testing<br>- Polish all animations and transitions<br>- Final art pass on sprites and backgrounds<br>- UI/UX refinements from playtesting</mark>

**Priority 3:**
<mark style="color:red">- Bug fixing from playtest feedback<br>- Code cleanup and documentation</mark>
<mark style="color:orange">- Performance optimization<br>- Final integration testing<br>- Create final build</mark>
<mark style="color:green">- Write README and documentation<br>- Prepare presentation
