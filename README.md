# CSCE 441 - A6

Name: Miles Versaw
UIN: 913007618
email: mkversaw@tamu.edu

Highest task completed: Scene 7 + Blended Reflection and Anti-aliasing

Citations:
None

Note:

Since im in the honors section I skipped scene 8 and instead implemented blended reflection and anti-aliasing for the 10 mandatory bonus points.

Scene 0 -> blended reflection
Scene 9 -> anti-aliasing
Scene 10 -> NOT additional bonus, but combined blended reflection and anti-aliasing

for scene 9 if you edit line 380 in main.cpp to `scene->renderAA16X()` instead of `scene->renderAA4X()`, it will further increase the level of anti-aliasing if you find the base (4x) amount insufficient

The `CMakeLists.txt` file references openGL, glsl, and glew, but none of these are actually used anywhere in the assignment. They are there because its just a slightly modified version of the one from A5.