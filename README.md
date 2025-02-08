# hmoog-native (Native bindings for Hackmud OOG)

Just some native bindings needed to get out-of-game input into Hackmud. Currently Windows-only,
but Linux has xdotools, so this maybe isn't needed. MacOS, not sure yet.

## Too lazy to write your own native stuff for Windows?

First of all: based.

```ts
import native from '@sarahisweird/hmoog-native';

if (!native.init()) {
    // Usually means that Hackmud isn't open.
    console.error('Failed to initialize the native module!');
    process.exit(1);
}

const waitMs = (ms) => new Promise(resolve => setTimeout(resolve, ms));

native.sendKeystrokes('scripts.user\n');
// If you send keystrokes too soon, the CLI will append that to the old command.
// Nothing I can do about that apart from telling you about it :^)
await waitMs(100);
native.sendKeystrokes('flush\n');

// sendMouseClick IS BROKEN RIGHT NOW!
native.sendMouseClick(false); // Left-click
native.sendMouseClick(true); // Right-click
```

## Building from source

Make sure your Node.js installation is reasonably up-to-date, as it will already include the Windows build tools.

```
> pnpm i
> pnpm run build-native
```
