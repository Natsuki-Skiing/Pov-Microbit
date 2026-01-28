/**
 * POV Display blocks
 */
//% weight=100 color=#0fbc11 icon="\uf06e"
//% groups=['Display']
namespace shakeScreen {
    
    /**
     * Show a message using POV display
     * @param message the message to display
     */
    //% block="Show  message $message"
    //% message.defl="HELLO"
    //% weight=100
    //% group="Screen Control"
    export function showMessage(message: string): void {
        povShowMessage(message);
    }

    /**
     * Show a number using POV display
     * @param number the number to display
     */
    //% block="Show number $number"
    //% number.defl=67
    //% weight=90
    //% group="Screen Control"
    export function showNumber(number:number): void {
        povShowMessage(number.toString());
    }
    //% block="Stop"
    //% weight=50
    //% group="Screen Control"
    export function stopMessage(): void {
        povStopMessage();
    }

    //% block="Number of letters"
    //% weight= 10
    //% group="Attributes"
    export function getNumberOfCharacters():number{
        //Place Holder
        return(1);
    }

    //% block="Is shake on"
    //% weight=0
    //% group="Attributes"
    export function POVIsRunning(): boolean {
        return(povIsRunning());
    }



    
    
}