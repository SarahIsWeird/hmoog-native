# hmoog-native (Native bindings for Hackmud OOG)

Just some native bindings needed to get out-of-game input into Hackmud. Currently Windows-only,
but Linux has xdotools, so this maybe isn't needed. MacOS, not sure yet.

Good for people who are too lazy to write their own native stuff for Windows (which is understandable tbh)

## Installation

```bash
# Or npm or yarn or whatever
pnpm install @sarahisweird/hmoog-native
```

## TL;DR:

Check the TSDocs or peep this:

```ts
import native from '@sarahisweird/hmoog-native';

if (!native.init()) {
    // Usually means that Hackmud isn't open.
    console.error('Failed to initialize the native module!');
    process.exit(1);
}

const { width, height } = native.getInfo();

const waitMs = (ms) => new Promise(resolve => setTimeout(resolve, ms));

native.sendKeystrokes('scripts.user\n');
// If you send keystrokes too soon, the CLI will append that to the old command.
// Nothing I can do about that apart from telling you about it :^)
await waitMs(100);
native.sendKeystrokes('flush\n');

native.sendMouseClick(100, 100, false); // Left-click at (100px, 100px)
native.sendMouseClick(300, 300, true); // Right-click at (300px, 300px)
```

## Building from source

Make sure your Node.js installation is reasonably up-to-date, as it will already include the Windows build tools.

```bash
pnpm i
pnpm run build-native
```
