import Qt 4.7
import "mx" as Mx

Rectangle {

    width: 480
    height: 800

    FontLoader { id: droidSans; source: "mx/fonts/Droid-Sans/DroidSans.ttf" }
    FontLoader { id: droidSansBold; source: "mx/fonts/Droid-Sans/DroidSans-Bold.ttf" }
    Column {
        Mx.Label {
            text: 'Label';
        }
        Mx.Button {
            text: 'Button';
        }
        Row{
            spacing: 2
            Mx.Slider{width: 128; id: slider}
            Text{y: 2; text:'Slider'; opacity: slider.value}
        }
    }
}
