namespace POV {
    //% block
    //% s.defl="hi"
    export function showString(s: string) {

    }
    //% block
    //%shim=extension::init_display
    export function initlizePov(): void { 
        Basic.showString("POV Init");
    }
}
