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

    /**
     * Show a number using POV display
     * @param number the number to display
     */
    //% block="Show POV number $number"
    //% number.defl=67
    //% weight=90
    //% group="Display"
    export function showNumber(number:number): void {
        povShowMessage(number.toString());
    }
    //% block="Stop POV"
    //% weight=50
    //% group="Display"
    export function stopMessage(): void {
        povStopMessage();
    }

    //% block="POV is on"
    //% weight=0
    //% group="Display"
    export function POVIsRunning(): boolean {
        return(povIsRunning());
    }



    
    
}