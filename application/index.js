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

const s = new RTPSession(1373);

s.on('message', (msg) => {
  ht = msg.payload.toString();
  t = parseFloat(ht.split("\n")[0]);
  h = parseFloat(ht.split("\n")[1]);
  console.log(t);
  console.log(h);
});
