input.onButtonPressed(Button.A, function () {
    pov.showNumber(Number2)
})
input.onButtonPressed(Button.B, function () {
    if (pov.POVIsRunning()) {
        pov.stopMessage()
        basic.showIcon(IconNames.Heart)
    } else {
        music.play(music.tonePlayable(262, music.beat(BeatFraction.Whole)), music.PlaybackMode.InBackground)
    }
})
input.onLogoEvent(TouchButtonEvent.Pressed, function () {
    Number2 += 1
})
let Number2 = 0
music.setVolume(23)
Number2 = 0
basic.showIcon(IconNames.Meh)
