/**
 * POV Display blocks
 */
//% weight=100 color=#0fbc11 icon="\uf06e"
//% groups=['Display']
namespace pov {
    
    /**
     * Show a message using POV display
     * @param message the message to display
     */
    //% block="show POV message $message"
    //% message.defl="HELLO"
    //% weight=100
    //% group="Display"
    export function showMessage(message: string): void {
        povShowMessage(message);
    }
    
    /**
     * Update the POV message while running
     * @param message the new message to display
     */
    //% block="update POV message $message"
    //% message.defl="WORLD"
    //% weight=90
    //% group="Display"
    export function updateMessage(message: string): void {
        povUpdateMessage(message);
    }
}