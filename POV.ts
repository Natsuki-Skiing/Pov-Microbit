namespace POV {
    //% block
    //% s.defl="hi"
    export function showString(s: string) {

    }
    //% block
    //%shim=POV::init_Pov
    export function initlizePov(): void { 
        Basic.showString("POV Init");
    }
}
