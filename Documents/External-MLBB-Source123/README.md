# ImGui Unity Template by DivaArvian
> 2022/07/31 14:32: Initial Commit (with imgui v1.85).

> 2022/07/31 19:32: Update support with imgui v1.88.

# What is ImGui?
ImGui is basically a full stack GUI framework made with c++ which supports lots of operating systems

# Why ImGui?
As Its a full stack Framework we/you can easily make lots of things from it easily and it can save lot of time

# How it Works ?
Yes , While Talking about its working method currently we use egl to hook with our EGLSurface or Simply It uses `eglSwapBuffers` with Dobby Hook
  
# How is it's touch Managed?
Currently it uses the touch from game itself, like Unity structure for touch so it gets easy for us to Handle it

# How to inject / implement
1. Extract the lib from your deired Architecture or simply `armeabi-v7a`
2. Place your lib in correct path of the game.
3. Load your Lib from `onCreate` of your Game's Mainactivity or UnityPlayerActivity

The main activity of Unity is: ```com/unity/player/UnityPlayerActivity```

```
const-string v0, "native-lib"

invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
# Recomendations

1. You can open this project using AIDE or Android Studio
2. If you find bugs relating to this project, simply mention on the same repo so that we can improve it

# Credits

* ocornut - ImGui : https://github.com/ocornut/ImGui
* vvb2060 - DobbyHook - https://github.com/vvb2060/dobby-android
