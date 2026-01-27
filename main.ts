input.onButtonPressed(Button.A, function () {
    pov.showMessage("HELLO")
})
input.onButtonPressed(Button.B, function () {
    pov.stopMessage()
    basic.showIcon(IconNames.Heart)
})
input.onLogoEvent(TouchButtonEvent.Pressed, function () {
    pov.showMessage("Will")
})
basic.showIcon(IconNames.Fabulous)
