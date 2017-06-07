/*
 * +===============================================
 * | Author:        Parham Alvani (parham.alvani@gmail.com)
 * |
 * | Creation Date: 07-06-2017
 * |
 * | File Name:     index.js
 * +===============================================
 */
const RTPSession = require('krtp').RTPSession;
const express = require('express');

const s = new RTPSession(1373);
const app = express();

let t = 0;
let h = 0;

s.on('message', (msg) => {
  let ht = msg.payload.toString();
  t = parseFloat(ht.split("\n")[0]);
  h = parseFloat(ht.split("\n")[1]);
  console.log(t);
  console.log(h);
  console.log(msg.timestamp);
  console.log(msg.sequenceNumber);
});

app.get('/t', function (req, res) {
  res.json({
    temperature: t
  });
});

app.get('/h', function (req, res) {
  res.json({
    humidity: h
  });
});

app.listen(1373, function () {
    console.log('* http on 0.0.0.0:1373')
});
