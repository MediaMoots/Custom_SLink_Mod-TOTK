# Custom SLink Mod - TOTK
A exefs mod to play custom sounds in Tears Of The Kingdom.

## Installing
Download the latest release and install it as a ExeFS mod.

## Usage guide for Modders

### Type: Default playback
#### Syntax: 
- Prefix: `CSM_`
- After Prefix: None
- Postfix: None
#### Example
- SLink Call: `CSM_MySFX`
- BWAV Name in BARS: `CSM_MySFX`
#### Notes
Any slink calls with the prefix `CSM_` will be rerouted and the asset with that name will be played directly.

So for example, if you have a sound effect/bgm you want to add, name it `CSM_MySFX` and then mod SLink calls in eventflows/ainb/asb/etc to call `CSM_MySFX`. 

If a bwav with that name exists in the loaded bars for that event/actor/etc then it will play.

### Type: Random playback
#### Syntax: 
- Prefix: `CSM_RND_`
- After Prefix: Number of random sounds
- Postfix: None
#### Example
- SLink Call: `CSM_RND_5_MySFX`
- BWAVs in BARS: `CSM_MySFX_0`, `CSM_MySFX_1`, `CSM_MySFX_2`, `CSM_MySFX_3`, `CSM_MySFX_4`, `CSM_MySFX_5`
#### Notes
Any slink calls with the prefix `CSM_RND_` will be treated as a random sound playback.

A number needs to be provided after `CSM_RND_` that indicates the maximum number of random sounds.

The mod will then call a random sound in range of 0 -> the maximum number specified. 

## Note
Use https://github.com/MediaMoots/TOTK_BARS_Tool to add bwavs to bars.

## ToDo
- Support more AssetParam configs

## Credit
- exlaunch - @shadowninja108
- mc_decompressor @watertoon
- Atmosphère: A great reference and guide.
- oss-rtld: Included for (pending) interop with rtld in applications (License [here](https://github.com/shadowninja108/exlaunch/blob/main/source/lib/reloc/rtld/LICENSE.txt)).
