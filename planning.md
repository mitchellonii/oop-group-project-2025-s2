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



# UI Features

## Main HUD (Always Visible During Gameplay)
- **Cargo Counter**
  - Visual representation of your 3 "lives" (cargo portions remaining)
  - Could be displayed as 3 cargo boxes/crates at the top of screen
  - When pirates steal cargo, one box visually breaks/disappears
  - Flashes red when cargo is stolen

- **Task Timer Display**
  - Appears when a task becomes active
  - Large, prominent countdown (e.g., "0:45" remaining)
  - Changes color as urgency increases:
    - **Green:** >40 seconds remaining
    - **Yellow:** 20-40 seconds
    - **Red/Flashing:** <20 seconds
  - Shows task name/icon above timer

- **Current Objective Indicator**
  - Small text box showing current priority, e.g., "Navigate to Control Module" or "Repair Tractor Beam"
  - Arrow indicator pointing left/right to guide player to task location
  - Pulsing highlight on the task object itself in the game world

## Dialogue UI (Pirate Encounters)
- **Dialogue Box Overlay**
  - Semi-transparent dark overlay dims the game world
  - Large dialogue box in center/bottom of screen
  - Pirate portrait on one side, showing which type you're facing
  - Pirate's dialogue text displayed with typewriter effect

- **Choice Selection**
  - Three clearly labeled options displayed as buttons
    - Selected option highlights (border glow or color change)
    - Visual indicator showing which key corresponds to which option
    - Brief description of each approach (e.g., "Offer them credits")

- **Outcome Display**
  - After selection, shows result: "The pirate accepts!" or "The pirate is offended!"
  - If successful: pirate leaves, cargo safe
  - If failed: animation of cargo being stolen, cargo counter decreases

## Menu Screens
- **Main Menu**
  - Pixelated space/ship background
  - Game title: "SPACEFAIRER" in retro pixel font
  - Options:
    - "START DELIVERY"
    - "HOW TO PLAY" (tutorial/instructions)
    - "QUIT"
  - Simple navigation with arrow keys or WASD

- **Game Over Screens**
  - Different screens based on failure type:
    - Asteroid Collision: Ship exploding, "NAVIGATION FAILURE"
    - Cargo Lost: Trailer floating away, "CARGO DETACHED"
    - Safety Violation: Official notice, "TERMINATED BY SPACE OSHA"
    - Pirates Won: Three broken cargo boxes, "CARGO STOLEN"
  - Shows statistics: "Tasks Completed: X" "Pirates Defeated: X"
  - Options: "TRY AGAIN" or "MAIN MENU"

- **Victory Screen**
  - "DELIVERY SUCCESSFUL!"
  - Roggert celebrating
  - Final stats displayed
  - Potential score/rating system

## Notification System
- **Task Alerts**
  - Pop-up notification when new task appears: "⚠️ NAVIGATION UPDATE REQUIRED"
  - Appears at top of screen, fades after 2-3 seconds
  - Accompanied by warning sound

- **Pirate Warnings**
  - "⚠️ INCOMING TRANSMISSION" when pirate is about to board
  - 3-second warning before dialogue starts
  - Gives player time to finish current action

- **Status Messages**
  - "Task Complete!" with checkmark
  - "Cargo Secured" when successfully defeating pirate

## User Flow

### Game Start Flow
1. Launch Game → Main Menu appears
2. Select "START DELIVERY" → Brief loading/transition
3. Intro Sequence (optional, can be skipped)
   - Text: "Roggert Spacemin here, pilot of the Bongo Frontier..."
   - "Today's delivery: 3 cargo containers to Sector 7..."
   - Camera pans across the ship interior
4. Game Begins → Player spawns in center of ship, full control

### Typical Gameplay Loop
- **Idle State**
  - Player can move freely left/right exploring ship
  - HUD shows cargo counter (3/3) and current position
  - Ambient ship sounds playing

- **Task Appears**
  - Notification pops up: [task x has appeared]
  - HUD updates: Timer appears (1:00), objective indicator points left
  - Visual cue: Control module panel highlights/flashes
  - Player must move to location

- **Task Interaction**
  - Player reaches task location
  - Prompt appears: "Press E to xxxx"
  - Player holds E
  - Progress bar fills showing completion
  - **Success:** "Task Complete!" notification, timer disappears
  - **Failure:** Timer hits 0:00 → Game Over (associated fail sequence)

- **Pirate Encounter**
  - Game pauses player movement automatically
  - Dialogue UI appears: Screen dims, pirate portrait shows, dialogue begins
  - Example dialogue: "Well well, what do we have here? Hand over your cargo, spacer."

- **Dialogue Choice**
  - Player uses A/D or arrow keys to highlight choice
  - Current selection glows/highlights
  - Player presses E or Space to confirm

- **Outcome**
  - **Success:** "The pirate laughs and leaves" → Resume gameplay
  - **Failure:** "The pirate scowls and grabs a cargo container" → Cargo counter drops (3/3 → 2/3) → Resume gameplay

- **Multi-tasking Scenario**
  - Timer already running for navigation task (0:30 left)
  - Pirate boards during task
  - Player must decide: finish task or deal with pirate first
  - Creates tension and prioritization decisions

### Victory Flow
- **Deliver All Cargo**
  - Player survives all encounters and tasks for set duration (or reaches destination)
  - Screen fades to white

- **Victory Screen**
  - "DELIVERY SUCCESSFUL!"
  - Stats display
  - "TRY AGAIN" (restart) or "MAIN MENU"

### Failure Flow
- Timer reaches 0:00 or player fails third pirate encounter
- Warning sound
- Screen shakes violently
- Associated animation
- Screen goes black
- Game Over screen: “[game over reason]”

### Restart Flow (if time permits)
- From any Game Over screen, select "TRY AGAIN"
- Quick fade to black
- Spawn back at start position
- Fresh attempt with 3 cargo portions
- Randomized task/pirate timing for replayability

# Player Movement Tests
- Verify left/right movement responds to all input keys (A, D, arrows)
- Test boundary collision at ship edges (can't move beyond control module/cargo panel)
- Confirm movement is disabled during pirate dialogue
- Validate smooth acceleration/deceleration physics

# Interaction System Tests
- Test interact button (E/Space) triggers on correct objects
- Verify hold-to-complete mechanic fills progress bar accurately
- Confirm items can be picked up and carried
- Test interaction prompts appear/disappear at correct distances

# Task Logic Tests
- Each task timer counts down correctly (60 seconds → 0)
- Task completion stops timer and removes task
- Task failure triggers correct game over state
- Multiple concurrent tasks display properly

# Pirate Dialogue Tests
- All three pirate types load correctly
- Rock-paper-scissors logic works for each type (2 win conditions, 1 loss per pirate)
- Cargo counter decrements on pirate victory
- Dialogue choices navigate correctly with A/D/arrows

# Game State Tests
- State transitions work (menu → playing → paused → game over)
- Win condition triggers after appropriate duration/tasks
- All four loss conditions trigger correct game over screens
- Restart resets all variables properly

# Input Validation Approach

## Keyboard Input Validation
- Test all control schemes work simultaneously:
  - WASD and arrow keys both functional for movement
  - Both E and Space work for interactions
  - ESC triggers pause reliably
- Verify no input conflicts (e.g., pressing multiple keys at once)
- Test rapid key presses don't break interaction system
- Confirm input is properly disabled/enabled during state changes

## Interaction Range Validation
- Player must be within defined distance to interact with objects
- Prompts only appear when in valid range
- Out-of-range interactions are rejected gracefully

## Timing Validation
- Task spawn intervals are within acceptable ranges
- Pirate encounters don't overlap improperly
- Timer values are accurate (1 minute = 60 seconds in-game)
- No tasks spawn simultaneously if not intended

## Edge Case Testing
- What happens if timer expires during pirate dialogue?
- Can player move during task completion animation?
- What if player pauses during critical moments?
- Test all combinations of concurrent events


