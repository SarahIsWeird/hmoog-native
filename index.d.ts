declare module 'hmoog-native' {
    /**
     * @property width the width of the primary screen in pixels
     * @property height the height of the primary screen in pixels
     */
    type NativeInfo = {
        width: number;
        height: number;
    };

    /**
     * Initializes the native module. Must be called before any other method.
     * If Hackmud isn't currently opened, the call will fail.
     *
     * @returns whether the initialization was successful
     */
    export function init(): boolean;

    /**
     * Returns information about the system.
     *
     * @see NativeInfo
     */
    export function getInfo(): NativeInfo;

    /**
     * Sends the string to Hackmud as a series of keystrokes (or something of similar effect).
     * Does not automatically focus the shell.
     *
     * @param str The string to type
     * @returns whether the underlying system operations were successful
     */
    export function sendKeystrokes(str: string): boolean;

    /**
     * Sends a mouse click to the Hackmud window.
     *
     * Both `x` and `y` are *absolute* coordinates relative to the top-left of the Hackmud window!
     *
     * **Windows-specific**: Because Windows does not allow mouse events for windows not in the foreground,
     * the Hackmud window is maximized, the click is performed, and then the window is minimized again. However,
     * this requires `Sleep` calls for both Windows and Hackmud to catch up.
     * Hence, this function is slow and takes 150ms *at minimum*.
     *
     * @param x The absolute x coordinate of the mouse click
     * @param y The absolute y coordinate of the mouse click
     * @param isRightClick `false` for a left click, `true` for a right click
     * @returns whether the underlying system operations were successful
     */
    export function sendMouseClick(x: number, y: number, isRightClick: boolean): boolean;
}
