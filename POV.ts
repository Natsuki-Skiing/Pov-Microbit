//% color=#bebb56 icon="\uf0eb"
//% block="POV"
namespace extension{
    //% block
    //% s.defl="hi"
    //% shim=extension::showString
    export function showString(s: string):void {
        console.log("POV showing: " + s);
    }
    //% block
    //% shim=extension::initPov
    export function initPov(): void { 
       console.log("Simulator: POV initialized");
    }
}
