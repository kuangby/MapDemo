# CoralMap

[简体中文](README_zh.md) | English

A minimap / world map mod for Minecraft Bedrock (Windows client) powered by [LeviLamina](https://github.com/LiteLDev/LeviLamina). It draws through a DirectX 11 hook with an ImGui overlay and is client-side only.

## Showcase

![World map with biome-based terrain coloring and hill shadows](resource/showcase/showcase1.png)

![Desert island with long shadow-map shadows at high zoom](resource/showcase/showcase2.png)

![Zoomed-out overview of explored regions](resource/showcase/showcase3.png)

## Features

- **Minimap**: circular minimap at the top-right corner showing surrounding terrain, chunk grid lines, the current chunk highlighted, a player heading arrow, and coordinates — with configurable size, margins, and colors
- **World map**: toggled with the `M` key (rebindable), scroll-wheel zoom (0.2–40 px/block), drag-to-pan; rendered as per-region (256×256 blocks) textures composited via ImGui, with idle-texture VRAM reclamation
- **Terrain coloring**: biome-based colors loaded from `resource/biome_color.json`, falling back to in-game biome sampling when unavailable; transparent water that turns more opaque with depth
- **Shadow rendering**: three modes — none / simple heightmap gradient / shadow map with edge bevel — plus PCF soft shadows and a configurable fixed light direction (northwest azimuth, 60° zenith by default)
- **Smooth camera**: spring-damper smoothed following, with adjustable stiffness and damping
- **Background terrain scanning**: small per-frame batches to avoid stutters (32 chunks/frame, 128-block radius by default), periodic rescans, region-level baking when too many chunks are dirty, and a LevelDB disk cache

## Configuration

A `config.json` is generated in the mod's config directory on first load. Common options:

| Option | Description |
| --- | --- |
| `worldMap.toggleKey` | Key to toggle the world map (Win32 virtual-key code; `0x4D` = `M` by default) |
| `miniMap.sizeRatio` / `radiusChunks` | Minimap diameter as a fraction of window width / chunk radius shown |
| `terrain.scanRadius` / `scanMaxChunksPerFrame` | Scan radius in blocks / max chunks scanned per frame |
| `terrain.enableDiskCache` | Enable the disk cache |
| `terrain.shadow.*` | Shadow mode, strength, softening radius, light direction |
| `fontSize` | UI font size |

## Building

Dependencies: xmake, Visual Studio (clang-cl toolchain), LeviLamina client and its xmake-repo.

```bash
xmake f -y -p windows -a x64 -m release
xmake
```

After a successful build, the mod is packed into `bin/CoralMap/` (including `CoralMap.dll`, `manifest.json`, and the `resource/` assets).

## Installation

Copy the whole `bin/CoralMap` folder into the `mods/` directory of your LeviLamina client installation and start the game.

## Project Structure

```
src/
├── mod/     Entry point (CoralMap class, mod registration, memory operators)
├── render/  Minimap / world map renderers
├── state/   Core state: terrain scanning, chunk management, coloring, shadow rendering
├── data/    Chunk / region data structures, memory and disk caches
├── helper/  DX11 hook, game event hooks, input blocking
└── config/  Configuration definitions
```

## Contributing

Questions are welcome via issues; PRs accepted.

## License

CC0-1.0 © CoralMap contributors
