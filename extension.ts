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
    //% block="Show POV message $message"
    //% message.defl="HELLO"
    //% weight=100
    //% group="Display"
    export function showMessage(message: string): void {
        povShowMessage(message);
    }


    //% block="Stop POV"
    //% weight=100
    //% group="Display"
    export function stopMessage(): void {
        povStopMessage();
    }
    
    
}