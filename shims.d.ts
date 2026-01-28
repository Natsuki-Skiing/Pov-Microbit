// Auto-generated. Do not edit.
declare namespace shakeScreen {
    /**
     * Show a POV message
     */
    //% shim=Pov::povShowMessage
    function povShowMessage(message: string): void;

    /**
     * Update the POV message
     */
    //% shim=shakeScreen::povUpdateMessage
    function povUpdateMessage(message: string): void;

    //% shim=shakeScreen::povStopMessage
    function povStopMessage(): void;

    //% shim=shakeScreen::povIsRunning
    function povIsRunning(): boolean;

    //% shim=shakeScreen::povSetNumberOfCharacters
    function povSetNumberOfCharacters(number: number): void;

    //% shim=shakeScreen::povGetNumberOfCharacters
    function povGetNumberOfCharacters(): number;

    //% shim=shakeScreen::povIsLooping
    function povIsLooping(): boolean;
    //% shim=shakeScreen::povSetLooping
    function povSetLooping(value: boolean): void;
}
