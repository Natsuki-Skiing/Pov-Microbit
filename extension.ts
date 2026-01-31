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
    //% message.defl="Hi"
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

    //% block="looping enabled"
    //% weight=40
    //% group="Attributes"
    export function isLooping(): boolean {
        return povIsLooping();
    }
    //% block="set looping $enabled"
    //% enabled.shadow="toggleOnOff"
    //% enabled.defl=false
    //% weight=50
    //% group="Settings"
    export function setLooping(enabled: boolean): void {
        povSetLooping(enabled);
    }

    //% block="Set number of Characters $numberLetter"
    //% weight=20
    //% group="Settings"
    //% numberLetter.min=2 numberLetter.max=10
    //% numberLetter.defl=3
    export function setNumberOfCharacters(numberLetter:number):void{
        povSetNumberOfCharacters(numberLetter);
    }
    //% block="Number of Characters"
    //% weight= 10
    //% group="Attributes"
    export function getNumberOfCharacters():number{
        //Place Holder
        return(povGetNumberOfCharacters());
    }

    //% block="Screen Shake on"
    //% weight=0
    //% group="Attributes"
    export function getRunning(): boolean {
        return(povIsRunning());
    }
    
    // //% block="Looping on"
    // //% weight=0
    // //% group="Attributes"
    // export function getLooping(): boolean {
    //     return (povIsLooping());
    // }


    
    
}