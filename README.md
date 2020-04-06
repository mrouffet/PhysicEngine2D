All rights of any files from this repository are reserved.

Physic Engine - Maxime ROUFFET

7 scenes demo:
	- Debug triangle test
	- Random polygon: 200 bodies
	- Random polygon: 500 bodies
	- 33 circles with gravity
	- Circle and cube tower
	- Simple geometry scene
	- Complex geometry scene



Keys:

F1: Switch Debug level:
	- Recap
	- Landmarks
	- AABB

F2: Switch FPS mode:
	- Unlimited
	- 60 FPS
	- 30 FPS


Scene:

F3: Reload scene
F4: Prev scene
F5: Next scene


Physic:

F6: Switch broad phase algorithm:
	- Sweep and Prune
	- Dynamic AABB Tree

F7: Toogle broad phase debug

F8: Switch narrow phase algorithm:
	- SAT
	- GJK

F9: Toogle narrow phase debug.


Extra keys:

P: Spawn trigangle at mouse location.
Mouse wheel: Zoom / Unzoom.

G: Toogle gravity

Up arrow: Set gravity up (ie: Vec2(0.0f, 9.81f))
Down arrow: Set gravity down (ie: Vec2(0.0f, -9.81f))
Left arrow: Set gravity left (ie: Vec2(-9.81f, 0.0f))
Right arrow: Set gravity right (ie: Vec2(9.81f, 0.0f))

## Authors

**Maxime "mrouffet" ROUFFET** - main developer (maximerouffet@gmail.com)