namespace POV {
    //% block
    //% s.defl="hi"
    //%shim=extension::showString
    export function showString(s: string):void {
        (extension as any).showString(s);
    }
    //% block
    //%shim=extension::initPov
    export function initPov(): void { 
       (extension as any).initPov();
    }
}
