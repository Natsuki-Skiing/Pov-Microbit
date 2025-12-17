namespace POV {
    //% block
    //% s.defl="hi"
    
    export function showString(s: string):void {
        if (typeof extension !== 'undefined') {
            (extension as any).showString(s);
        }
    }
    //% block
    
    export function initPov(): void { 
        if (typeof extension !== 'undefined') {
            (extension as any).initPov();
        }
    }
}
