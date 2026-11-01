# Perf Mode

Performance mod for Geometry Dash 2.2 that cuts frame cost in heavy levels.
Level data, physics and timing are never touched.

## What it does

- **Off-screen culling** — level sprites whose bounds fall outside the view are
  hidden before the draw pass, so the GPU never submits them. Objects stay in
  the level, still collide and still count.
- **Particle skip** — emitters completely outside the view stop doing per-frame
  work.
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
