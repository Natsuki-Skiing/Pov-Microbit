namespace POV {
    //% block
    //% s.defl="hi"
    
    export function showString(s: string):void {
        (extension as any).showString(s);
    }
    //% block
    
    export function initPov(): void { 
        (extension as any).initPov();
    }
}
