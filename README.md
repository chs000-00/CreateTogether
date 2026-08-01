# Create Together
This is where he COOKS a mod.

Create Together is a Geometry Dash multiplayer live editing mod. It uses SteamP2P or ENet as its networking backend, depending on your choosing.

<img src="logo.png" width="150" alt="the mod's very epic logo" />

Note: this mod is currently incomplete and may cause issues.
Yes I know this code is gross-looking, but feel free to contribute with a pr.

## Build instructions
For more info, see [the geode docs](https://docs.geode-sdk.org/getting-started/create-mod#build)

This project requires steamworks sdk! ~~Install `steam_api64.dll`~~ and `steam_api64.lib` into the `lib/` folder!
~~EDIT: Not anymore~~

```sh
# Assuming you have the Geode CLI set up already
geode build
```
## Local testing (If you have no friends)
This mod supports ENet for local testing and dedicated servers.

# Resources
* [Geode SDK Documentation](https://docs.geode-sdk.org/)
* [Steamworks SDK Documentation](https://partner.steamgames.com/doc/gettingstarted)
* [Geode SDK Source Code](https://github.com/geode-sdk/geode/)
* [Geode CLI](https://github.com/geode-sdk/cli)
* [Bindings](https://github.com/geode-sdk/bindings/)
* [Dev Tools](https://github.com/geode-sdk/DevTools)

## Preferred header order
Subfolders should always be grouped together. 
1. Geode.hpp
2. <Networking/*>
3. <Types/*>
4. <*.hpp>
5. "*.hpp"
6. Steamworks headers
7. Single header libraries
8. Flatbuffer headers
9. Generated fb serialization headers
10. using namespace geode::prelude;