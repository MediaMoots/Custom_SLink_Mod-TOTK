# Custom SLink Mod - TOTK
A exefs mod to play custom sounds in Tears Of The Kingdom.

## Usage
Download the latest release and install it as a ExeFS mod.

Any slink calls with the prefix `CSM_` will be rerouted and the asset with that name will be played directly.

So for example, if you have a sound effect/bgm you want to add, name it `CSM_YourSFX` and then mod SLink calls in eventflows/ainb/asb/etc to call `CSM_YourSFX`. 

If a bwav with that name exists in the loaded bars for that event/actor/etc then it will play.

Use https://github.com/MediaMoots/TOTK_BARS_Tool to add bwavs to bars.

## ToDo
- Support more AssetParam configs

## Credit
- exlaunch - @shadowninja108
- mc_decompressor @watertoon
- Atmosphère: A great reference and guide.
- oss-rtld: Included for (pending) interop with rtld in applications (License [here](https://github.com/shadowninja108/exlaunch/blob/main/source/lib/reloc/rtld/LICENSE.txt)).
