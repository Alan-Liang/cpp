const fs = require('fs')

const n = 100
const x = Array.from(Array(n).keys()).map(i => `${i} ${Math.ceil(Math.random() * n)}`)
console.log(n)
console.log(x.join('\n'))
