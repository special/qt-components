.pragma library

var instances = {};

function get(name) {
    name += ".qml"

    if (instances[name] !== undefined) {
        console.log("style: Using cached instance for style ", name);
        return instances[name];
    }
    
    var component = Qt.createComponent(name);
    instances[name] = component.createObject(null);

    console.log("style: Created ", name, ":", instances[name]);

    return instances[name];
}

