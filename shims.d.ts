// Auto-generated. Do not edit.
declare namespace pov {
    /**
     * Show a POV message
     */
    //% shim=pov::povShowMessage
    function povShowMessage(message: string): void;
    
    /**
     * Update the POV message
     */
    //% shim=pov::povUpdateMessage
    function povUpdateMessage(message: string): void;

    //% shim=pov::povStopMessage
    function povStopMessage():void;

    //% shim=pov::povIsRunning
    function povIsRunning(): boolean;
}