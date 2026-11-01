# Perf Mode

Performance mod for Geometry Dash 2.2 that reduces frame cost in heavy levels
without changing level data, physics or timing.

## Settings

Everything is in the mod's settings page in Geode:

| Setting | What it does |
| --- | --- |
| Enable Perf Mode | Master switch |
| Skip off-screen objects | Skips draw calls for objects fully outside the view |
| Culling margin | Pixels of extra space kept drawn around the screen |
| Skip particles far off-screen | Stops updating particle systems that are outside the view |
| Skip off-screen labels | Skips text labels outside the view |
| Cap visible particles | Limits particles drawn per emitter |
| Particle cap | The per-emitter limit used by the option above |
| Pre-warm sprite cache | Loads a level's sprite frames before it starts |
| Show stats overlay | Draws a small drawn/skipped counter |
| Key: toggle Perf Mode | Kill switch, F7 by default |

## Building

Requires the Geode SDK and the Geode CLI.

```
set GEODE_SDK=C:/path/to/Geode
geode build
```

The packaged `zZalix.perfmode.geode` is written to `build/`.

Pushing a tag like `v1.0.0` builds a release on GitHub Actions and attaches the
packaged mod to it.

## Credits

Made by zZalix.
