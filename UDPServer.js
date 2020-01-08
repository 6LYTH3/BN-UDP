const Blynk = require('blynk-library') // Links variable 'Blynk' to the Blynk Library
const AUTH = '9urhJb3HrX_K9WD0YgzaWl60fj4nXa4N' // Your top secret auth code
const blynk = new Blynk.Blynk(
    AUTH,
    (options = {
        connector: new Blynk.TcpClient(
            (options = { addr: '192.168.1.37', port: 8080 })
        ) // This takes all the info and directs the connection to you Local Server.
    })
)

const name = 'xxx'
var myCache = { [name]: [0, 0, 0, 0, 0, 0, 0, 0, 0] }
var v1 = new blynk.VirtualPin(1)
var v2 = new blynk.VirtualPin(2)
var v3 = new blynk.VirtualPin(3)
var v4 = new blynk.VirtualPin(4)
var v5 = new blynk.VirtualPin(5)
var v6 = new blynk.VirtualPin(6)
var v7 = new blynk.VirtualPin(7)
var v8 = new blynk.VirtualPin(8)
var v9 = new blynk.VirtualPin(9)

v1.on('write', function(param) {
    myCache[name][0] = param[0]
    console.log(myCache)
})

v2.on('write', function(param) {
    myCache[name][1] = param[0]
    console.log(myCache)
})

v3.on('write', function(param) {
    myCache[name][2] = param[0]
    console.log(myCache)
})

v4.on('write', function(param) {
    myCache[name][3] = param[0]
    console.log(myCache)
})

v5.on('write', function(param) {
    myCache[name][4] = param[0]
    console.log(myCache)
})

v6.on('write', function(param) {
    myCache[name][5] = param[0]
    console.log(myCache)
})

v7.on('write', function(param) {
    myCache[name][6] = param[0]
    console.log(myCache)
})

v8.on('write', function(param) {
    myCache[name][7] = param[0]
    console.log(myCache)
})

v9.on('write', function(param) {
    myCache[name][8] = param[0]
    console.log(myCache)
})

function writeToBlynk(vPins) {
    vPins.forEach((i, pin) => {
        if (i == 0) {
            v1.write(pin)
        } else if (i == 1) {
            v2.write(pin)
        } else if (i == 2) {
            v3.write(pin)
        } else if (i == 3) {
            v4.write(pin)
        } else if (i == 4) {
            v5.write(pin)
        } else if (i == 5) {
            v6.write(pin)
        } else if (i == 6) {
            v7.write(pin)
        } else if (i == 7) {
            v8.write(pin)
        } else if (i == 8) {
            v9.write(pin)
        }
    })
}

var PORT = 33333
var HOST = '127.0.0.1'

var dgram = require('dgram')
var server = dgram.createSocket('udp4')

server.on('listening', () => {
    let address = server.address()
    console.log(
        'UDP Server listening on ' + address.address + ':' + address.port
    )
})

server.on('message', (message, remote) => {
    strBuff = message.toString()

    if (strBuff.includes('REQ')) {
        content = strBuff.split(':')
        vPins = Array.from(content[1])
        myCache[name] = vPins
        console.log(myCache)
        writeToBlynk(vPins)
    }
    server.send(myCache[name].join(), remote.port, remote.address, err => {
        if (err) {
            server.close()
        } else {
            console.log('Data sent !!')
        }
    })
})

server.on('close', () => {
    console.log('Socket is closed !')
})

server.bind(PORT, HOST)
