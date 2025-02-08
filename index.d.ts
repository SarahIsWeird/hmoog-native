declare module 'hmoog-native' {
    export function init(): boolean;
    export function sendKeystrokes(str: string): boolean;
    export function sendMouseClick(isRightClick: boolean): boolean;
}
