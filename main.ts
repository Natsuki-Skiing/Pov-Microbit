input.onButtonPressed(Button.A, function () {
    shakeScreen.setLooping(true)
})
input.onButtonPressed(Button.B, function () {
    shakeScreen.setLooping(false)
})
shakeScreen.showMessage("Hello")
