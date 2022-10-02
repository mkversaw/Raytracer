# Raytracer

<p align="center" width="100%">
    <img width="33%" src="pic.png"> 
</p>

## About

My implementation of a Ray Tracer using C++ and the GLM library. Supports Blinn-Phong shading with multiple lights, shadows, and reflections

## Dependencies

* CMake
* GLM

Build with CMake then run with `./Raytracer <SCENE> <IMAGE SIZE> <IMAGE FILENAME>`

## Scene Info

* Scene 0 -> blended reflection
* Scene 1 -> single light no shadows
* Scene 2 -> single light with shadows
* Scene 3 -> multiple lights with shadows
* Scene 4 -> Single reflection
* Scene 5 -> Recursive reflections
* Scene 6 -> Custom mesh w/o model transformation
* Scene 7 -> Custom mesh w/ model transformation
* Scene 9 -> anti-aliasing
* Scene 10 -> combined blended reflection and anti-aliasing
