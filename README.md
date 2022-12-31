# RGSS player
A very basic player for RPG Maker VX Ace games - inspired by [Omni RGSSx Player](https://gist.github.com/gabteles/10000006).

# Build
```
cmake -DCMAKE_GENERATOR_PLATFORM=WIN32 .
msbuild rgss_player.sln /t:build /p:Configuration=Release;Platform=WIN32
```
