input.onButtonPressed(Button.A, function () {
    pov.showNumber(0)
})
input.onButtonPressed(Button.B, function () {
    if (pov.POVIsRunning()) {
        pov.stopMessage()
        basic.showIcon(IconNames.Heart)
    } else {
        music.play(music.tonePlayable(262, music.beat(BeatFraction.Whole)), music.PlaybackMode.InBackground)
    }
})
basic.showIcon(IconNames.SmallHeart)
