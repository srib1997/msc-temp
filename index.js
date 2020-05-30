const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const db = require('./knex/knex.js')
const port = new SerialPort('/dev/tty.usbmodem14401', { baudRate: 9600 })

const parser = new Readline()
port.pipe(parser)

var datas = {
  uv: '',
  temp: '',
  humidity: '',
  wind: ''
}

parser.on('data', async(line) => {
  const result = line.split(",")
  datas = {
    uv: result[0],
    temp: result[1],
    humidity: result[2],
    wind: result[3].replace(' \r','')
  }
})

async function insetDb(){
  try {
    await db('uv_sensor').insert({
      data: datas.uv
    }
    ).returning('*')
  } catch (error) {
    console.log('uv_sensor error:', error)
  }

  try {
    await db('temp_sensor').insert({
      celsius: datas.temp
    }
    ).returning('*')
  } catch (error) {
    console.log('temp_sensor error:', error)
  }

  try {
    await db('humidity_sensor').insert({
      data: datas.humidity
    }
    ).returning('*')
  } catch (error) {
    console.log('humidity_sensor error:', error)
  }

  try {
    await db('wind_sensor').insert({
      meter_second: datas.wind
    }
    ).returning('*')
  } catch (error) {
    console.log('wind_sensor error:', error)
  }
}

setInterval(insetDb, 5000)