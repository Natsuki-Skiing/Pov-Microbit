// Auto-generated. Do not edit.
declare namespace shakeScreen {
    /**
     * Show a POV message
     */
    //% shim=shakeScreen::povShowMessage
    function povShowMessage(message: string): void;
    
    /**
     * Update the POV message
     */
    //% shim=shakeScreen::povUpdateMessage
    function povUpdateMessage(message: string): void;

    //% shim=shakeScreen::povStopMessage
    function povStopMessage():void;

    //% shim=shakeScreen::povIsRunning
    function povIsRunning(): boolean;

    //% shim=shakeScreen::povGetNumberOfCharacters
    function povGetNumberOfCharacters(): number;
}