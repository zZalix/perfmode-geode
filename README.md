# Perf Mode

Performance mod for Geometry Dash 2.2 that cuts frame cost in heavy levels.
Level data, physics and timing are never touched.

## What it does

- **Off-screen culling** — level sprites whose bounds fall outside the view are
  hidden before the draw pass, so the GPU never submits them. Objects stay in
  the level, still collide and still count.
- **Particle skip** — emitters completely outside the view stop doing per-frame
  work.
- **Label skip** — text objects outside the view are not drawn.
- **Culling margin** — pixels of slack around the screen so nothing pops in at
  the edges.
- **Kill switch** — F7 toggles everything at runtime, mid-level.

## Settings

| Setting | What it does |
| --- | --- |
| Enable Perf Mode | Master switch |
| Skip off-screen objects | Hides level sprites outside the view |
| Culling margin | Pixels of extra space kept drawn around the screen |
| Skip particles far off-screen | Stops off-view particle emitters |
| Skip off-screen labels | Skips text objects outside the view |
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

The packaged `zzalix.perfmode.geode` is written to `build/`.

## License

MIT
