//% color=#bebb56 icon="\uf0eb" block="POV"
namespace extension {
    /**
     * Initializes the POV hardware.
     */
    //% blockId="extension_init_pov" block="init pov"
    //% shim=extension::initPov
    export function initPov(): void { 
       // Simulator fallback
       console.log("Simulator: POV initialized");
    }

    /**
     * Shows a string on the POV display.
     */
    //% blockId="extension_show_string" block="show string %s"
    //% s.defl="hi"
    //% shim=extension::showString
    export function showString(s: string): void {
        // Simulator fallback
        console.log("POV showing: " + s);
    }
}