var PORT = 33333
var HOST = '127.0.0.1'

var dgram = require('dgram')
// var message = new Buffer.from('ACK:000000000')
var message = new Buffer.from('REQ:000000001')

var client = dgram.createSocket('udp4')
client.send(message, 0, message.length, PORT, HOST, (err, bytes) => {
    if (err) throw err
    console.log('UDP message sent to ' + HOST + ':' + PORT)

    setTimeout(() => {
        client.close()
    }, 1000)
})

client.on('message', (message, remote) => {
    console.log('Data received from server: ' + message.toString())
})
